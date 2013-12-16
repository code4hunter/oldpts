from distutils.core import setup
import py2exe

setup(console=['TestGW.py'],
    options={"py2exe":{"dll_excludes":[ "mswsock.dll", "powrprof.dll" ]}})
