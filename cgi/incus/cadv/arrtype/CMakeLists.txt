# Minimal `CMakeLists.txt` for Function Pointer Demo
#
cmake_minimum_required(VERSION 3.10...3.17)

# Set `PROJECT_NAME` from the current directory name.
#
get_filename_component(PRJ_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "-" PRJ_DIR_NAME ${PRJ_DIR_NAME})
project(${PRJ_DIR_NAME} VERSION 0.0.1
	DESCRIPTION "C Array Pointers Exercise"
   LANGUAGES C)

# C standard selection & configuration.
#
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Debug build type config")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)
if(MSVC)
   message(">> COMPILER TYPE: MSVC")
   add_compile_options(/W4 /experimental:preprocessor)
   add_compile_definitions(_CRT_SECURE_NO_WARNINGS=1)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
   message(">> COMPILER TYPE: GCC/Clang")
   add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Create CMake variables used to replace `@···@` placeholders in the
# `platform.h.in` template from which `platform.h` is generated.
#
if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
   set(OS_MACRO OS_MACOS)
   set(OS_NAME MacOS)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
   set(OS_MACRO OS_WINDOWS)
   set(OS_NAME Windows)
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
   set(OS_MACRO OS_LINUX)
   set(OS_NAME Linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
   set(OS_MACRO OS_FREEBSD)
   set(OS_NAME FreeBSD)
else()
   set(OS_RUNIME OS_UNKNOWN)
endif()

# Set one of two possible endianness preprocessor macros. More macros
# for `platform.h.in` replacement.
#
include(TestBigEndian)
TEST_BIG_ENDIAN(BIG_ENDIAN)
if(BIG_ENDIAN)
   message(">> ENDIANNESS   : Big Endian")
   set(ENDIAN IS_ENDIAN_BIG)
   set(ENDIANNESS "Big")
else()
   message(">> ENDIANNESS   : Little Endian")
   set(ENDIAN IS_ENDIAN_LITTLE)
   set(ENDIANNESS "Little")
endif()

# Create `platform.h` from `platform.h.in` in `./res/` directory. It does
# support `platform.c`, which may contain platform-specific functions.
#
configure_file(res/platform.h.in platform.h @ONLY)
add_library(platform STATIC res/platform.c)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Depedencies and directories.
#
include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB SRCS CONFIGURE_DEPENDS
   ${PROJECT_SOURCE_DIR}/src/*.c
   ${PROJECT_SOURCE_DIR}/src/*.h)
set(SRCS ${SRCS} ${CMAKE_CURRENT_BINARY_DIR}/platform.h)

# Executable. Clean build and install example:
#
# `rm bin -rf`
# `cmake --build build/ --config Release`
# `cmake --install build/ --strip [--prefix ‹path›]`
#
set(EXE ${PROJECT_NAME})
add_executable(${EXE} ${SRCS})
#https://stackoverflow.com/questions/30904273/how-to-change-the-name-of-the-output-binary-to-not-be-a-out-with-cmake
set_target_properties(
    ${EXE}
    PROPERTIES 
        OUTPUT_NAME "a"
        SUFFIX ".cgi"
)

target_link_libraries(${EXE} PRIVATE platform)
set_target_properties(${EXE}
   PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
if(NOT GENERATOR_IS_MULTI_CONFIG)
   set_target_properties(${PROJECT_NAME}
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY
         "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")
endif()

install(
   TARGETS ${EXE}
   CONFIGURATIONS Debug Release
   RUNTIME DESTINATION bin/)
