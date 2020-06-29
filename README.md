JSExec

Simple utility for executing JavaScript with some native c functionality exposed for calling via
the scripting engine

Options:
 -h      : Help
 -v      : Version
 -r PATH : Run script

Long options:
 --help     : Help
 --version  : Version
 --run PATH : Run script

todo:
	* file/socket/http logging
	* expose assert to javascript
	* make commit target for committing repl to git
	* check repl open ports and/or bookmarklet websocket interception check cors
	* mongoose local server test
	* mongoose serve optional argument: js script to use for root endpoint service handler
	* mongoose serve additional flag[s]:service endpoint/script pairs for various endpoints
	* mongoose cgi enabled and cgi subprojects folder
	* serve up cppreference, like zeal
	  use sqlite and such, prototype in js then make it native c
	* shared object rpath riffraff for seperately compiled endpoint handlers, similar setup to cgi directories
	* sqlite :memory main server cache exposed on scripting language (global lifetime and asu inits)
	* js startup [re]configuration script and shutdown script: handler contexts inherits from main context
          in terms of script engine initialization
	* multiport spinups, exposed in scripting language on threads
	* source tree to support multiple concurrent bin directories, e.g. you have the same folder open on wsl and windows cmd building with wsl gcc and nuwen gcc
          for now supported ./bin/linux and ./bin/windows, which will have all the objects for the specific build and the binary
          the makefile will use the appropriate binary with run/serve, e.g. ./bin/linux/a.out or ./bin/windows/a.exe, depending on the
          host environment
        * WIN32/LINUX cgi interpreter compile time determination, also take a look
          at mongoose config files, and rather set one up for windows and linux, then
          do a compile time file select
	* curl: this is partially implemented (./src/duktape/curl.h/c). The curl source code needs to be incorporated in the source tree
	* duk registration of native functions to be controlled with flags, e.g. there is one now, -DDUK_USE_CURL, which should probably be -DDUK_REGISTER_CURL
	  alternatively, these can be registered in the scripting environment, so you have a function exposed e.g. duk_register("CURL"), or something like that
	  this will also be a good excercise in trying to find out how to "unregister" functions, which will probably be easier if everything
	  is namespaced in the scripting engine, e.g. libc.printf...libc.fwrite   ...   curl.foo...curl.bar  ...  etc.

Extra Topics/Tools to Learn/Try out:
	* CMake (example given)
	* Astyle
	* Vim (vimcast), http://vimcasts.org/
	* https://cdecl.org/
	* #if defined TEST_TOBIN - conditional main file included for test - try this technique when making libraries
	* uuid generation of header guard identifiers
	* #if defined __cplusplus in c files
	* ctemplate check features
	* c mustache, there are a couple of options, find a zeroconf one
		* https://github.com/x86-64/mustache-c/tree/master/src
		* https://gitlab.com/jobol/mustach
	* https://github.com/browsh-org/browsh/releases, https://www.hanselman.com/blog/LynxIsDeadLongLiveBrowshForTextbasedInternetBrowsing.aspx, https://askubuntu.com/questions/29540/browsing-the-internet-from-the-command-line
	* install and try out zeal
	* nohup, try with python chat
	* lots of books, https://download.itadmins.net/Linux/
	* https://github.com/rhysd/vim.wasm
	* add uuid makefile phony target for these header guards
	* add pretty target, to prettify code, only code that has changed, there is a basic example in cgi/incus/cadv/debugging/Makefile
	* create TOUCH makefile function, as windows has no touch, there is a basic one at cgi/incus/cadv/debugging/Makefile

Compilation Notes:
	* std-c99 breaks ctemplate - debug width gdb whats going on here
	* with cgi scripts, for the header, with the \r\n, on windows, an extra
	  \r will be inserted with \n, so it will become \r\r\n\r\r\n,
	  when creating cgi programs in c, just use \n, as this seems portable
	  on both linux and windows
