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
    EXT := .dll
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
    EXT := .so
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
ifeq ($(THEOS),Windows)
	CWDNAM=$(shell for %%I in (.) do echo %%~nxI)
else
	CWDNAM=$(shell basename `pwd`)
endif
#-------------------------------------------------------------------------------
CC=gcc
STRIP=strip
BINDIR=./bin/
BINNAM=$(CWDNAM)
INSTALLDIR=../../app
INSTALLDIR_LIB=$(INSTALLDIR)/lib/support
INSTALLDIR_INC=$(INSTALLDIR)/include/support/$(BINNAM)
INCLUDEDIR=./include/
SRCDIR=src
CFLAGS=\
	-Wall\
	-Wextra\
	-Wpedantic\
	-std=c99\
	-I./src\
	-I./include
CXXFLAGS=\
	-Wall\
	-Wextra\
	-Wpedantic\
	-I./src\
	-I./include
LDFLAGS=
ifeq ($(THEOS),Windows)
	BINDIR=./bin/windows/
	LDFLAGS+=-Wl,--allow-shlib-undefined
#LDFLAGS+=-Wl,--export-all-symbols
#LDFLAGS+=-fvisibility=hidden
else
	CFLAGS+=-fPIC
#	CFLAGS+-fvisibility=hidden
	CXXFLAGS+=-fPIC
#	CXXFLAGS+-fvisibility=hidden
	BINDIR=./bin/linux/
endif
LDFLAGS+=-Wl,--allow-shlib-undefined
#-------------------------------------------------------------------------------
#DOCUMENTATION TOOLS
#-------------------------------------------------------------------------------
DOXYGEN=doxygen
DOT=dot
#DOC=./dox/html/index.html
README=./README.md
DOXYFILE=DoxyFile
#-------------------------------------------------------------------------------
#PRETTIFY TOOLS
#-------------------------------------------------------------------------------
INDENT=indent
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
#	CP=xcopy /e/i/c/y
#	CP=xcopy /e/i/y 
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
#PWD
#-------------------------------------------------------------------------------
ifeq ($(THEOS),Windows)
define FNPWD
$(shell echo %cd%)
endef
else
define FNPWD
pwd
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
ifeq ($(THEOS),Windows)
	_INSTALLDIR_LIB=$(subst /,$(PATHSEPSTRIPPED),$(INSTALLDIR_LIB))
	_INSTALLDIR_INC=$(subst /,$(PATHSEPSTRIPPED),$(INSTALLDIR_INC))
	_INCLUDEDIR=$(subst /,$(PATHSEPSTRIPPED),$(INCLUDEDIR))
else
	_INSTALLDIR_LIB=$(INSTALLDIR_LIB)
	_INSTALLDIR_INC=$(INSTALLDIR_INC)
	_INCLUDEDIR=$(INCLUDEDIR)
endif
_BIN=$(_BINDIR)lib$(BINNAM)$(EXT)
#-------------------------------------------------------------------------------
ifeq ($(THEOS),Windows)
        _SRC:=$(shell for %%G in (.c, .cpp) do for /f "tokens=1* delims=\" %%A in ('forfiles /p $(_SRCDIR) /s /m *%%G /c "cmd /c @echo @relpath"') do @for %%F in (^"%%B) do @echo $(_SRCDIR)$(PATHSEPSTRIPPED)%%~F)
else
        _SRC:=$(shell find $(SRCDIR) -type f \( -iname \*.c -o -iname \*.cpp \))
endif                                                                            


OBJS=$(addprefix $(_BINDIR),$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(_SRC))))
ifeq ($(THEOS),Windows)
	_OBJS=$(subst /,$(PATHSEPSTRIPPED),$(OBJS))
else
	_OBJS=$(OBJS)
endif
#-------------------------------------------------------------------------------
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif
#-------------------------------------------------------------------------------
all:$(_BIN)
#-------------------------------------------------------------------------------
$(_BIN):$(_OBJS)
	@echo "generating $@..."
	$(CXX) \
		-shared\
		$(_OBJS) \
		$(LDFLAGS) \
		-o $(_BIN)
	$(STRIP) \
		$(_BIN)
#-------------------------------------------------------------------------------
$(_BINDIR)\%.o: %.c
	@echo "generating $@..."
	@-$(MKDIR) $(@D) $(SILENT)
	$(CC)\
		$(CFLAGS)\
		-c $<\
		-o $@
$(_BINDIR)\%.o: %.cpp
	@echo "generating $@..."
	@-$(MKDIR) $(@D) $(SILENT)
	$(CXX)\
		$(CXXFLAGS)\
		-c $<\
		-o $@
# --- kludge ... sort out ---
$(_BINDIR)%.o: %.c
	@echo "generating $@..."
	@-$(MKDIR) $(@D) $(SILENT)
	$(CC)\
		$(CFLAGS)\
		-c $<\
		-o $@

$(_BINDIR)%.o: %.cpp
	@echo "generating $@..."
	@-$(MKDIR) $(@D) $(SILENT)
	$(CXX)\
		$(CXXFLAGS)\
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
#-------------------------------------------------------------------------------
doc:\
	$(SRC) \
	$(README) \
	$(DOXYFILE) \
	Makefile
	@echo building documentation...
	@$(DOXYGEN) $(DOXYFILE)
#-------------------------------------------------------------------------------
.phony:test
#-------------------------------------------------------------------------------
clean:
	@-$(RMDIR) $(_BINDIR)
	@-$(RMDIR) doc
#-------------------------------------------------------------------------------
ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_ARGS):;@:)
endif
.phony:\
	install
install:
	@echo "installing..."
	@-$(MKDIR) $(_INSTALLDIR_LIB) $(SILENT)
	@-$(MKDIR) $(_INSTALLDIR_INC) $(SILENT)
	@-$(CP) $(_BIN) $(_INSTALLDIR_LIB) $(SILENT)
	@-$(CP) $(_INCLUDEDIR)* $(_INSTALLDIR_INC) $(SILENT)
test:
	@echo _SRC:
	@echo $(_SRC)

#-------------------------------------------------------------------------------
