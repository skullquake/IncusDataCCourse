# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build

# Include any dependencies generated for this target.
include CMakeFiles/platform.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/platform.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/platform.dir/flags.make

CMakeFiles/platform.dir/res/platform.c.o: CMakeFiles/platform.dir/flags.make
CMakeFiles/platform.dir/res/platform.c.o: ../res/platform.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/platform.dir/res/platform.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/platform.dir/res/platform.c.o   -c /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/res/platform.c

CMakeFiles/platform.dir/res/platform.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/platform.dir/res/platform.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/res/platform.c > CMakeFiles/platform.dir/res/platform.c.i

CMakeFiles/platform.dir/res/platform.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/platform.dir/res/platform.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/res/platform.c -o CMakeFiles/platform.dir/res/platform.c.s

CMakeFiles/platform.dir/res/platform.c.o.requires:

.PHONY : CMakeFiles/platform.dir/res/platform.c.o.requires

CMakeFiles/platform.dir/res/platform.c.o.provides: CMakeFiles/platform.dir/res/platform.c.o.requires
	$(MAKE) -f CMakeFiles/platform.dir/build.make CMakeFiles/platform.dir/res/platform.c.o.provides.build
.PHONY : CMakeFiles/platform.dir/res/platform.c.o.provides

CMakeFiles/platform.dir/res/platform.c.o.provides.build: CMakeFiles/platform.dir/res/platform.c.o


# Object files for target platform
platform_OBJECTS = \
"CMakeFiles/platform.dir/res/platform.c.o"

# External object files for target platform
platform_EXTERNAL_OBJECTS =

libplatform.a: CMakeFiles/platform.dir/res/platform.c.o
libplatform.a: CMakeFiles/platform.dir/build.make
libplatform.a: CMakeFiles/platform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libplatform.a"
	$(CMAKE_COMMAND) -P CMakeFiles/platform.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/platform.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/platform.dir/build: libplatform.a

.PHONY : CMakeFiles/platform.dir/build

CMakeFiles/platform.dir/requires: CMakeFiles/platform.dir/res/platform.c.o.requires

.PHONY : CMakeFiles/platform.dir/requires

CMakeFiles/platform.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/platform.dir/cmake_clean.cmake
.PHONY : CMakeFiles/platform.dir/clean

CMakeFiles/platform.dir/depend:
	cd /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build /home/runner/NegativeLightcoralLocatorprogram/cgi/incus/cadv/arrtype/build/CMakeFiles/platform.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/platform.dir/depend

