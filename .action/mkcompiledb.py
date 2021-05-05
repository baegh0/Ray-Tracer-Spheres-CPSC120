#!/usr/bin/env python3

from glob import glob
import json
from os.path import exists
import platform

def create_clang_compile_commands_db():
    """Create a Clang compile commands DB named compile_commands.json in the current working directory."""
    out='compile_commands.json'
    linux_includes = ' -I/usr/include/c++/9/'
    darwin_includes = ' -D OSX -nostdinc++ -I/opt/local/include/libcxx/v1'
    compile_cmd = 'clang++ -g -O3 -Wall -pipe -std=c++14'
    p = platform.system( )
    if p == 'Linux':
        compile_cmd = compile_cmd + linux_includes
    elif p == 'Darwin':
        compile_cmd = compile_cmd + darwin_includes
    
    l = [{'directory':'/tmp', 'command':'{} {}'.format(compile_cmd, f), 'file':f} for f in glob('*.cc')]
    if exists(out):
        print('Error: the file "{}" already exists. Skipping.'.format(out))
    else:
        with open(out, 'w') as fh:
            json.dump(l, fh)


if __name__ == '__main__':
    create_clang_compile_commands_db()
