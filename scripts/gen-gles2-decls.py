#!/usr/bin/env python3
import os, re

re_gl_call = re.compile("GL_APICALL (.+?) GL_APIENTRY (gl[^ ]+?) \(([^)]+?)\)")

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

call_id = -1
def handle_call(ret, call_name, args):
    global call_id
    call_id += 1
    return "_DECL({:4}, {:8}, {:32}, ({}))".format(
        call_id, ret, call_name, args)

if __name__ == '__main__':
    main()
