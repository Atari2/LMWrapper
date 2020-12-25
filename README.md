## LMWrapper
For basic usage info run the program by double clicking on it
OR
You can run "lmwrapper.exe -h" or "lmwrapper.exe --help" on your command line.

Advanced usage:
If you want to use a custom name for the list file or modify the max number of characters a line in the list file can have, check out lmwrapper.ini instead. 
By using that file you can customize those 2 settings, in the future there'll be more to customize.
For now, a standard ini file is provided in "optional/lmwrapper.ini", there's no need to use it unless you want to modify it.
In that case, you need to move it in the same folder as the executable. 
Be aware that any unknown setting (e.g. one that is not already defined in the file) will cause an error.
The .ini file format is:
`<setting name>: <value>`

Be aware that between the colon and the value there needs to be only a single space.

This program can be built with gcc:
- On unix
`gcc -O2 wrapper.c settings.c -o lmwrapper`
- On Windows
`gcc -O2 wrapper.c settings.c -o lmwrapper.exe`
