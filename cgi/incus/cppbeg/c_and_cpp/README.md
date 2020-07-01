Using C and C++

You can use C and C++ together by creating C sources and C++ sources. Conventionally C sources end with
.c, and C++ sources end with .cpp or .cc.

To use them together, you can compiler the C objects from the C sources using gcc, and the C++ sources from
C++ sources using g++. You can also compile the C objects from the C sources using g++ with the -x c flag.

It is recommended to have the main function in a C++ source file.

The final executable consisting of the objects compiled from both C and C++ sources using g++.

When g++ is used to compile C++ sources using external references to functions in C sources, the linker
will complain that it cannot find the symbol. To sort this out, it is advisable to use the following in your
C headers where the function prototypes are declared

#ifdef __cplusplus
extern "C" {
#endif
...
void foo(void);
...
#ifdef __cplusplus
}
#endif

When g++ compiles a C++ source that includes this header, the __cplusplus definition will exist, and the 
conditional statements will be included declaring that these are C functions

The Makefile here has been adjusted to to recursive compilation of C and C++ sources

2020/06/30 
