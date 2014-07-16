#!/usr/bin/env python3
import os, re, pprint

re_gl_call = re.compile("GL_APICALL (.+?) GL_APIENTRY (gl[^ ]+?) \(([^)]+?)\)")
write1_tmpl     = "write    ({name:16});\n"
writen_tmpl     = "write    ({name:16}, {size});\n"
read1_tmpl      = "read     ({name:16});\n"
readn_tmpl      = "read     ({name:16}, {size});\n"
read_rest_tmpl  = "read_rest({name:16});\n"
stack_tmpl      = "{type:9} {name};\n"
def_tmpl        = """
{ret} {call_name}({params}) {{
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
        return_stmt = '',
        discard     = False)
    ctx.before_call += ['new_call (ID_{});\n'.format(call_name)]
    if ctx.args:
        ctx.params  = [t+" "+n for t, n in args]
        try:
            handle_call_with_args(ctx)
        except Exception as e:
            pprint.pprint(ctx)
            raise e
    else:
        ctx.params  = []
    ctx.before_call += ["send     ();\n"]
    handle_call_special_cases(ctx)
    if ctx.discard:
        return ""
    ctx.params      = ", ".join(ctx.params)
    if ctx.ret != 'void':
        assert(not ctx.after_call)
        ctx.after_call += [
            stack_tmpl.format(type=ret, name='ret'),
            read1_tmpl.format(name='ret')]
        ctx.return_stmt = "return    {};".format('ret')
    if ctx.after_call:
        ctx.after_call += ["receive  ();\n"]
    lines           = (ctx.before_call + ctx.after_call +
                      [ctx.return_stmt])
    body            = "    ".join(lines).rstrip()
    definition      = def_tmpl.format(body=body, **ctx)
    if ctx.print:
        print(definition)
    return definition

def handle_call_special_cases(ctx):
    if ctx.call_name in [
            "glVertexAttribPointer", "glDrawElements", "glBindBuffer",
            "glDrawArrays", "glShaderSource", "glGetError", "glReadPixels",
            "glDeleteBuffers"]:
        ctx.discard = True
    elif ctx.call_name in ["glGetVertexAttribPointerv"]:
        ctx.before_call += [
            "// TODO pointer is in wrong address space\n"]

def handle_call_with_args(ctx):
    classify_args(ctx)
    for type, name in ctx.normal_args:
        ctx.before_call    += [write1_tmpl.format(name=name)]
    for type, name in ctx.buffer_args:
        size                = parameter_size(ctx.call_name, name)
        ctx.before_call    += [writen_tmpl.format(name=name, size=size)]
    one_read_rest = 1
    for type, name in ctx.return_args:
        assert(one_read_rest)
        size                = parameter_size(ctx.call_name, name)
        if size == 1:
            ctx.after_call += [
                read1_tmpl.format(name=name)]
        elif isinstance(size, int) or \
             isinstance(size, str) and size.isnumeric():
            ctx.after_call += [
                readn_tmpl.format(name=name, size=size)]
        else:
            one_read_rest  -= 1
            ctx.after_call += [
                read_rest_tmpl.format(name=name)]
            
    
def parameter_size(call_name, param_name):
    return parameter_sizes[call_name].get(param_name, 1)

_ = parameter_sizes = {}
_['glBindAttribLocation'    ] = { }
_['glBufferData'            ] = { 'data': 'size' }
_['glBufferSubData'         ] = { 'data': 'size' }
_['glCompressedTexImage2D'  ] = { 'data': 'imageSize'}
_['glCompressedTexSubImage2D'] = { 'data': 'imageSize' }
_['glDeleteBuffers'         ] = { 'buffers': 'n' }
_['glDeleteFramebuffers'    ] = { 'framebuffers': 'n' }
_['glDeleteRenderbuffers'   ] = { 'renderbuffers': 'n' }
_['glDeleteTextures'        ] = { 'textures': 'n' }
_['glDrawElements'          ] = { 'indices': 'count' }
_['glGetAttribLocation'     ] = { }
_['glGetUniformLocation'    ] = { }
_['glShaderBinary'          ] = {
    'shaders':  'count',
    'binary':   'length' }
_['glShaderSource'          ] = {
    'string':   'count',
    'length':   'count' }
_['glTexImage2D'            ] = {
    'pixels': 'width * height * bytes_per_pixel(format)'
}
_['glTexSubImage2D'         ] = {
    'pixels': 'width * height * bytes_per_pixel(format)'
}
_['glTexParameterfv'        ] = { 'params': 'pname_size(pname)' }
_['glTexParameteriv'        ] = { 'params': 'pname_size(pname)' }
_['glUniform1fv'            ] = { 'value': 'count * 1' }
_['glUniform1iv'            ] = { 'value': 'count * 1' }
_['glUniform2fv'            ] = { 'value': 'count * 2' }
_['glUniform2iv'            ] = { 'value': 'count * 2' }
_['glUniform3fv'            ] = { 'value': 'count * 3' }
_['glUniform3iv'            ] = { 'value': 'count * 3' }
_['glUniform4fv'            ] = { 'value': 'count * 4' }
_['glUniform4iv'            ] = { 'value': 'count * 4' }
_['glUniformMatrix2fv'      ] = { 'value': 'count * 4' }
_['glUniformMatrix3fv'      ] = { 'value': 'count * 9' }
_['glUniformMatrix4fv'      ] = { 'value': 'count * 16' }
_['glVertexAttrib1fv'       ] = { 'v': '1' }
_['glVertexAttrib2fv'       ] = { 'v': '2' }
_['glVertexAttrib3fv'       ] = { 'v': '3' }
_['glVertexAttrib4fv'       ] = { 'v': '4' }
_['glVertexAttribPointer'   ] = { } # TODO special


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
    'pixels': 'read_pixels_size(width, height, format, type)' }


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
