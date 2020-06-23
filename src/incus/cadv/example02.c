/*@file: src/incus/cadv/example01.c
 *@brief: `enum` example. The members of an `enum` are synonyms for `int` values.
 *        it is advisable to use `typedef` for creating synonyms for your `enums`.
 *        You can provide hints as to the value of the `enum` value as illustrated below.
 */
enum A{B,C,D,E};
typedef enum F{G,H,I,J}F;
typedef enum K{L=0,M,N}K;
static void test(void){
	enum A a;
	F f;
}
