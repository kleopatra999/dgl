#!/usr/bin/env python3
import os, re

re_gl_call = re.compile("GL_APICALL (.+?) GL_APIENTRY (gl[^ ]+?) \(([^)]+?)\)")
var_tmpl    = "auto         {name:16} = {value};\n"
val_tmpl    = "auto         {name:16} = read_val<{type}>(buf);\n"
ptr_tmpl    = "auto         {name:16} = read_ptr<{type}>(buf);\n"
buf_tmpl    = "auto         {name:16} = new {type}[{size}];\n"
ret_tmpl    = "write(reply, {name});\n"
retptr_tmpl = "write(reply, {ptr}, {size});\n"
call0_tmpl  = "{call_name}({call_args});\n"
call1_tmpl  = "write(reply, {call_name}({call_args}) );\n"
stack_tmpl  = "{type:12} {name};\n"
def_tmpl    = """
void exec_{call_name}(const char *buf, ostream& reply) {{
    {body}
}}"""

class Duct(dict):
    def __getattr__(self, name):
        return self[name]
    def __setattr__(self, name, value):
        self[name] = value

def main():
    calls = []
    with open("/usr/include/GLES2/gl2.h") as f:
        for line in f.readlines():
            m = re_gl_call.match(line)
            if m:
                calls.append(m.groups())
    definitions = [handle_call(*call) for call in calls]
    definitions = "\n".join(definitions)
    print(definitions)

def handle_call(ret, call_name, args):
    args    = args.split(", ")
    args    = [split_type_name(a) for a in args if a != 'void']
    ctx     = Duct(
        ret         = ret,
        call_name   = call_name,
        args        = args,
        print       = False,
        before_call = [],
        after_call  = [],
        discard     = False)
    if ctx.args:
        ctx.call_args = [n for _, n in ctx.args]
        try:
            handle_call_with_args(ctx)
        except Exception as e:
            print(ctx)
            raise e
    else:
        ctx.call_args = []
    handle_call_special_cases(ctx)
    if ctx.discard:
        return ""
    ctx.call_args   = ", ".join(ctx.call_args)
    call_tmpl       = ctx.ret == 'void' and call0_tmpl or call1_tmpl
    call            = call_tmpl.format(**ctx)
    lines           = ctx.before_call + [call] + ctx.after_call
    body            = "    ".join(lines).rstrip()
    definition      = def_tmpl.format(body=body, **ctx)
    if ctx.print:
        print(definition)
    return definition

def handle_call_special_cases(ctx):
    if ctx.call_name in ("glGetUniformfv", "glGetUniformiv"):
        ctx.before_call += [
            "// size of params can be 1, 2 or 3\n",
            "// depending on kind (scalar, vec2, vec3).\n",
            "// to guess the size we use magic numbers\n",
            "// which get possibly overwritten.\n",
            "int    i;\n",
            "auto   p = params[0];\n",
            "typedef numeric_limits<decltype(p)> num;\n",
            "for (i = 0; i < 3; i++) {\n",
            "    params[i] = num::max();\n",
            "}\n"]
        ret_tmpl = ctx.after_call.pop();
        ctx.after_call += [
            "for (i = 0; i < 3; i++) {\n",
            "    if (params[i] == num::max()) {\n",
            "        break;\n",
            "    }\n",
            "}\n",
            ret_tmpl.replace("3", "i")]
    elif ctx.call_name in ["glGetVertexAttribPointerv"]:
        ctx.before_call += [
            "// TODO pointer is in wrong address space\n"]
    elif ctx.call_name in ["glShaderSource", "glBufferData",
            "glVertexAttribPointer", "glReadPixels", "glDrawElements"]:
        ctx.discard = True

def handle_call_with_args(ctx):
    classify_args(ctx)
    for type, name in ctx.normal_args:
        ctx.before_call    += [val_tmpl.format(type=type, name=name)]
    for type, name in ctx.buffer_args:
        ctx.before_call    += [ptr_tmpl.format(type=type, name=name)]
    for type, name in ctx.return_args:
        size                = parameter_size(ctx.call_name, name)
        if size == 1:
            type                = type[:-1].strip()
            ctx.before_call    += [
                stack_tmpl.format(type=type, name=name)]
            i                   = ctx.call_args.index(name)
            ctx.call_args[i]    = '&'+ctx.call_args[i]
            ctx.after_call     += [
                ret_tmpl.format(name=name)]
        else:
            type                = type[:-1].strip()
            if type == 'void':
                type            = 'char'
            ctx.before_call    += [
                buf_tmpl.format(type=type, name=name, size=size)]
            ctx.after_call     += [
                retptr_tmpl.format(ptr=name, size=size)]
    
def parameter_size(call_name, param_name):
    return parameter_sizes[call_name].get(param_name, 1)

_ = parameter_sizes = {}
_['glGenBuffers'            ] = { 'buffers':        'n' }
_['glGenFramebuffers'       ] = { 'framebuffers':   'n' }
_['glGenRenderbuffers'      ] = { 'renderbuffers':  'n' }
_['glGenTextures'           ] = { 'textures':       'n' }
_['glGetActiveAttrib'       ] = { 'name': 'bufSize' }
_['glGetActiveUniform'      ] = { 'name': 'bufSize' }
_['glGetAttachedShaders'    ] = { 'name': 'bufSize' }
_['glGetBooleanv'           ] = { 'params': 'pname_size(pname)' }
_['glGetFloatv'             ] = { 'params': 'pname_size(pname)' }
_['glGetIntegerv'           ] = { 'params': 'pname_size(pname)' }
_['glGetBufferParameteriv'  ] = { }
_['glGetFramebufferAttachmentParameteriv'] = { }
_['glGetProgramiv'          ] = { }
_['glGetProgramInfoLog'     ] = { 'infoLog': 'bufSize' }
_['glGetRenderbufferParameteriv'] = { }
_['glGetShaderiv'           ] = { }
_['glGetShaderInfoLog'      ] = { 'infoLog': 'bufSize' }
_['glGetShaderPrecisionFormat'] = { 'range': '2' }
_['glGetShaderSource'       ] = { 'source': 'bufSize' }
_['glGetTexParameterfv'     ] = { }
_['glGetTexParameteriv'     ] = { }
_['glGetUniformfv'          ] = { 'params': '3' }
_['glGetUniformiv'          ] = { 'params': '3' }
_['glGetUniformfv'          ] = { 'params': '3' }
_['glGetVertexAttribfv'     ] = { 'params': 'pname_size(pname)' }
_['glGetVertexAttribiv'     ] = { 'params': 'pname_size(pname)' }
_['glGetVertexAttribPointerv'] = { } # TODO client-side state
_['glReadPixels'            ] = {
    'pixels': 'read_pixels_size(width, height, format)' }


def classify_args(ctx):
    ctx.normal_args = []
    ctx.buffer_args = []
    ctx.return_args = []
    for arg in ctx.args:
        type, name = arg
        if '*' in type and 'const' not in type:
            ctx.return_args.append(arg)
        elif '*' in type and 'const' in type:
            ctx.buffer_args.append(arg)
        else:
            ctx.normal_args.append(arg)
        
def split_type_name(arg):
    split = max(arg.rfind(" "), arg.rfind("*"))+1
    return (arg[:split].strip(), arg[split:])

if __name__ == '__main__':
    main()
