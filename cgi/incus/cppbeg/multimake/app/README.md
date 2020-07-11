Multiplatoform Dynamic Lib Loading Demonstration

Tested under Linux,WSL,Termux,Windows

--------------------------------------------------------------------------------
./app
--------------------------------------------------------------------------------

main client program

 * prelimnirary dlopen work
 * this can later be modified to be
 * included in duktape
 * or as a request handler
 * pointing to dll/so files, with a fixed
 * function called from that dll/so, though
 * the dll/so is dynamically loaded in
 * the dll/so can then act much as a cgi
 * endpoint, but running inside the 
 * main server process
 *
 *  https://www.linuxjournal.com/article/3687
 *  take a look at this for overcoming some of the limitations
 *  around the mangling in c++, some of it implemented here
 *  
 *  dealing with windows:
 *  https://www.codeproject.com/Articles/13501/Platform-Independent-Coding-DLLs-and-SOs

Linking agains ./lib/helper/bin/[windows|linux]/liba.[so|dll] is performed at compile time

--------------------------------------------------------------------------------
./lib/helper
--------------------------------------------------------------------------------
Helper shared library. This is necessary because on windows PE executable format
(executables and dll's) cannot be compiled with symbols missing. Under linux
with ELF you can compiler .so files with symbols missing, these symbols will
then be resolved in the client program if the client was compiled with -rdynamic.
The -rdynamic flag is not available under windows under mingw.

Make install will install ./lib/helper/bin/linux/libhelper.so to ./app/lib/support
Make install will install ./lib/helper/bin/windows/libhelper.dll to ./app.
The disparity is due to the fact that rpaths are not well supported under windows

--------------------------------------------------------------------------------
./lib/a
--------------------------------------------------------------------------------
This is source tree contains a sample shared library to be loaded in by the
main program at runtime. Make install will install ./lib/a/bin/windows/liba.dll
or ./lib/a/bin/linux/liba.so to ./app/lib

Linking agains ./lib/helper/bin/[windows|linux]/liba.[so|dll] is performed at compile time

When compiling under Linux(WSL), ./lib/helper/bin/linux/liba.so will automatically
find ./lib/helper/bin/linux/libhelper.so. Under Termux this is not the case, and
there will be issues at runtime tht libhelper.so cannot be located. To remedy this,
Set ./lib/a/bin/linux/liba.so's -rpath at compile time to point to ./lib/support using
LDFLAGS+=-Wl,-rpath=./lib/support


#so many notes, consolidate....
#note the rpath, under termux it cant find support
#which is relative to where this is deployed in the client
#so we specify it here

# helper shared object will provide bridge between client and plugins
# for communication registration etc


--------------------------------------------------------------------------------
notes
--------------------------------------------------------------------------------
references:

https://www.ibm.com/developerworks/aix/library/au-aix-symbol-visibility-part2/index.html
http://blog.fesnel.com/blog/2009/08/19/hiding-whats-exposed-in-a-shared-library/
https://blogs.kde.org/2018/01/19/fun-symbol-visibility
https://labjack.com/news/simple-cpp-symbol-visibility-demo
https://stackoverflow.com/questions/3570355/c-fvisibility-hidden-fvisibility-inlines-hidden
https://stackoverflow.com/questions/15560892/symbol-visibility-and-namespace
API Design for C++ by Martin Reddy.
http://mingw.5.n7.nabble.com/ignoring-unresolved-symbols-in-shared-libraries-td14076.html
https://stackoverflow.com/questions/39477163/can-you-compile-a-shared-object-to-prefer-local-symbols-even-if-its-being-loaded
https://stackoverflow.com/questions/36692315/what-exactly-does-rdynamic-do-and-when-exactly-is-it-needed
https://www.tldp.org/HOWTO/html_single/C++-dlopen/
https://github.com/alainfrisch/flexdll
https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html
https://cygwin.com/cygwin-ug-net/dll.html
mingw issue loading symbols from client
https://stackoverflow.com/questions/39759060/compile-to-dll-with-some-undefined-references-with-mingw
https://atomheartother.github.io/c++/2018/07/12/CPPDynLib.html
https://developer.ibm.com/technologies/systems/articles/au-aix-symbol-visibility/
get module path from this module:
 windows
  GetModuleFilename
  https://www.codeproject.com/Articles/16598/Get-Your-DLL-s-Path-Name
  https://stackoverflow.com/questions/6924195/get-dll-path-at-runtime
 linux
  https://stackoverflow.com/questions/1681060/library-path-when-dynamically-loaded
 sharing globals (used here for registration)
  https://stackoverflow.com/questions/3004318/dynamic-loaded-libraries-and-shared-global-symbols 
How to Write Shared Libraries. http://people.redhat.com/
drepper/dsohowto.pd
Inside ELF Symbol Tables. http://blogs.sun.com/ali/entry/
inside_elf_symbol_tables

