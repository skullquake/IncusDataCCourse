/* Platform-specific macros. Set from CMake via CMakeLists.txt, which
*  creates `platform.h`. Only edit this file, not `platform.h`.
*/
#if !defined H26F682C8E9864F99987F92676E9685E6
    #define  H26F682C8E9864F99987F92676E9685E6

#if defined __cplusplus
#define CFUNC extern "C"
extern "C" {
#else 
#define CFUNC extern
#endif

/* Literal string for build type.
*/
#if NDEBUG
   #define BUILD_TYPE "Release"
#else
   #define BUILD_TYPE "Debug"
#endif

/* Macro and Literal string for endianness.
*/
#define IS_ENDIAN_LITTLE 1
#define ENDIANNESS "Little"

/* Macro and literal string for the operating system. Macro can be one of
*  `OS_WINDOWS`, `OS_MACOS`, `OS_LINUX`, `OS_FREEBSD`, or `OS_UKNOWN`.
*/
#define OS_LINUX 1
#define OS_NAME "Linux"
#if (OS_MACOS + OS_WINDOWS + OS_LINUX + OS_FREEBSD + OS_UNKNOWN) > 1
   #error Only one of the OS_???? macros is allowed.
#endif

/* Project information
*/
#define PRJ_VERSION_MAJOR 0
#define PRJ_VERSION_MINOR 0
#define PRJ_VERSION_PATCH 1
#define PRJ_VERSION_STR   "0.0.1"
#define PRJ_DESCRIPTION   "C Function Pointer Demo"
#define PRJ_NAME          "tobinrenier"

extern int isum (int, int); /* example function declaration */

#if defined __cplusplus
   }
#endif

#endif
