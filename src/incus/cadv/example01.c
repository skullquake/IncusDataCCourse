/*@file: ./src/incus/cadv/typedef.c
 *@brief: Example using typedefs as alias to illustrate array types.
 *        There is no such thing as a multidimensional arrays in c in terms of data types
 *        and the standard nomenclature employed with regards to the language.
 *        A main observation with arrays is that the array type encapsulates the identifier
 *        in declarations or definitions of array variables.
 *        Additionally, a pointer type is not an array type. The language rule is that
 *        an array type when referenced in an expression via it's identifier will result
 *        in a pointer to the first element of the array.
 */
#include<stdio.h>
typedef char FOO[10];
typedef FOO BAR[10];
static void test(void){
	{
		char a;
		char b[10];
		char c[10][10];
		printf("%zu\n",sizeof(a));
		printf("%zu\n",sizeof(b));
		printf("%zu\n",sizeof(c));
	}
	{
		FOO a;
		FOO b[10];
		BAR c;
		printf("%zu\n",sizeof(a));
		printf("%zu\n",sizeof(b));
		printf("%zu\n",sizeof(c));
	}
}
