#-------------------------------------------------------------------------------
#DETECT OS
#-------------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
   THEOS := Windows
   SHELL = cmd
    ifeq '$(findstring ;,$(PATH))' ';'
       THEOS := Windows
    else
        THEOS := $(shell uname 2>/dev/null || echo Unknown)
        THEOS := $(patsubst CYGWIN%,Cygwin,$(THEOS))
        THEOS := $(patsubst MSYS%,MSYS,$(THEOS))
        THEOS := $(patsubst MINGW64%,MINGW,$(THEOS))
        THEOS := $(patsubst MINGW%,MINGW64,$(THEOS))
    endif
    EXT := .cgi
else
    UNAME_S := $(shell uname -s)
    THEOS := $(UNAME_S)
    ifeq ($(UNAME_S),Linux)
    endif
    ifeq ($(UNAME_S),Darwin)
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        THEOS=ARM
    endif
    EXT := .cgi
endif
#-------------------------------------------------------------------------------
#PROCESSOR DETECTION
#-------------------------------------------------------------------------------
ifeq ($(THEOS),$(filter $(THEOS),Windows_NT MINGW MINGW64 MSYS))
        ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
            PROC=AMD64
        else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            PROC=AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            PROC=IA32
        endif
    endif
else ifeq ($(THEOS),$(filter $(THEOS),Linux Darwin ARM))
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        PROC=AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        PROC=IA32
    endif
endif
#-------------------------------------------------------------------------------
CC=gcc
STRIP=strip
BINDIR=./bin/
SRCDIR=src
CFLAGS=\
	-Wall\
	-Wextra\
	-Wpedantic\
	-std=c99\
	-I./src\
	-I./src/sqlite
LDFLAGS=
ifeq ($(THEOS),Windows)
	SILENT=> NUL 2>&1
 	LDFLAGS+=-lwsock32
	LDFLAGS+=-lws2_32
	CFLAGS-=-DDUK_USE_CURL
	BINDIR=./bin/windows/
else
	LDFLAGS+=-lpthread
	LDFLAGS+=-lm
	LDFLAGS+=-ldl
	LDFLAGS+=-lcurl
	CFLAGS+=-DDUK_USE_CURL
	BINDIR=./bin/linux/
endif
#-------------------------------------------------------------------------------
#DOCUMENTATION TOOLS
#-------------------------------------------------------------------------------
DOXYGEN=doxygen
DOT=dot
#DOC=./dox/html/index.html
README=./README.md
DOXYFILE=Doxyfile
#-------------------------------------------------------------------------------
#PRETTIFY TOOLS
#-------------------------------------------------------------------------------
INDENT=indent
#-------------------------------------------------------------------------------
#RUN CONFIGURATION
#-------------------------------------------------------------------------------
PORT=5000
INITSCR=./scr/srv/init.js 
ifeq ($(THEOS),Windows)
	PORT=5000
else
	PORT=5001
endif

#-------------------------------------------------------------------------------
#BITBUCKET
#-------------------------------------------------------------------------------
ifeq ($(THEOS),Windows)
	SILENT=> NUL 2>&1
else
	SILENT=> /dev/null 2>&1
endif
#-------------------------------------------------------------------------------
#RM/CP
#-------------------------------------------------------------------------------
ifeq ($(THEOS),Windows)
	MKDIR=mkdir
	RM=erase
	RMDIR=rmdir /s/q
	CP=copy /Y
else
	MKDIR=mkdir -p
	RM=rm -r
	RMDIR=rm -r
	CP=cp -r
endif
#-------------------------------------------------------------------------------
#TOUCH
#-------------------------------------------------------------------------------
ifeq ($(THEOS),Windows)
define FNTOUCH
$(shell (for %%a in ($(1)) do if exist "%%~a" (pushd "%%~dpa" && ( copy /b "%%~nxa"+,, & popd )) else (type nul > "%%~fa")) >nul 2>&1)
endef
else
define FNTOUCH
touch $(1)
endef
endif
#-------------------------------------------------------------------------------
#PATH SEPERATORS
#-------------------------------------------------------------------------------
PATHSEPSTRIPPED=$(patsubst %\,%,$(PATHSEP))
ifeq ($(THEOS),Windows)
	PATHSEP=\\
else
	PATHSEP=/
endif
ifeq ($(THEOS),Windows)
	_SRC=$(subst /,$(PATHSEPSTRIPPED),$(SRC))
else
	_SRC=$(SRC)
endif
ifeq ($(THEOS),Windows)
	_BIN=$(subst /,$(PATHSEPSTRIPPED),$(BIN))
else
	_BIN=$(BIN)
endif
ifeq ($(THEOS),Windows)
	_BINDIR=$(subst /,$(PATHSEPSTRIPPED),$(BINDIR))
else
	_BINDIR=$(BINDIR)
endif
ifeq ($(THEOS),Windows)
	_SRCDIR=$(subst /,$(PATHSEPSTRIPPED),$(SRCDIR))
else
	_SRCDIR=$(SRCDIR)
endif

#-------------------------------------------------------------------------------
ifeq ($(THEOS),Windows)
	_SRC:=$(shell for /f "tokens=1* delims=\" %%A in ('forfiles /p $(_SRCDIR) /s /m *.c /c "cmd /c @echo @relpath"') do @for %%F in (^"%%B) do @echo $(_SRCDIR)$(PATHSEPSTRIPPED)%%~F)
else
	_SRC:=$(shell find $(SRCDIR) -name '*.c')
endif
OBJS:=$(addprefix $(_BINDIR),$(_SRC:%.c=%.o))
ifeq ($(THEOS),Windows)
	_OBJS=$(subst /,$(PATHSEPSTRIPPED),$(OBJS))
else
	_OBJS=$(OBJS)
endif
_BIN=$(_BINDIR)a$(EXT)
#-------------------------------------------------------------------------------
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif
#-------------------------------------------------------------------------------
all:$(_BIN)
#-------------------------------------------------------------------------------
run:$(_BIN)
	@$(_BIN) $(RUN_ARGS) 
serve:$(_BIN)
	@$(_BIN)\
		--serve\
		--port $(PORT)\
		--init $(INITSCR)
#-------------------------------------------------------------------------------
$(_BIN):$(_OBJS)
	@echo "generating $@..."
	@$(CC) \
		$(_OBJS) \
		$(LDFLAGS) \
		-o $(_BIN)
#-------------------------------------------------------------------------------
$(_BINDIR)\%.o: %.c
	@echo "generating $@..."
	@-$(MKDIR) $(@D) $(SILENT)
	@$(CC)\
		$(CFLAGS)\
		-c $<\
		-o $@
# --- kludge ... sort out ---
$(_BINDIR)%.o: %.c
	@echo "generating $@..."
	@-$(MKDIR) $(@D) $(SILENT)
	@$(CC)\
		$(CFLAGS)\
		-c $<\
		-o $@
#-------------------------------------------------------------------------------
define dump
objdump $(1) -t
endef
dumpall:\
	$(_OBJS)
	$(foreach obj,$(_OBJS),$(call dump,$(obj)))
#-------------------------------------------------------------------------------
pretty:$(_SRC)
	$(INDENT) $(_SRC)
	make -t
#$(call FNTOUCH,Makefile)
#-------------------------------------------------------------------------------
doc:\
	$(SRC) \
	$(README) \
	$(DOXYFILE) \
	makefile
	@echo building documentation...
	@$(DOXYGEN)
#-------------------------------------------------------------------------------
.phony:test
#-------------------------------------------------------------------------------
clean:
	$(RMDIR) $(_BINDIR)
#$(SILENT)
#-------------------------------------------------------------------------------
ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_ARGS):;@:)
endif
.phony:test
test:
	-@$(CC)\
		-DDEBUG\
		$(CFLAGS)\
		$(TEST_ARGS)\
		$(LDFLAGS)\
		-o tmp.exe
	-@tmp.exe
	-@$(RM) tmp.exe
#-------------------------------------------------------------------------------
