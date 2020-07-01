/*!@file: ./src/main.c
 * @brief: The `NDEBUG` macro is used to deactivate debugging
 *         When you have an `assert` statement, the `assert`
 *         macro will emit no code when `NDEBUG` has been defined
 *         You can also write your testing and logging macros
 *         to take `NDEBUG` into account
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
int main(void){
	printf("Content-Type: text/plain\n\n");
	assert(1==1);
	assert(1==2);
	return EXIT_SUCCESS;
}
