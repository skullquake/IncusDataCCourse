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

Compilation Notes:
	* std-c99 breaks ctemplate - debug width gdb whats going on here
