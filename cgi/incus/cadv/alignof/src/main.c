/*!@file: ./src/main.c
 * @brief: `alignof` demonstration
 *          Every complete object type has a property called alignment requirement,
 *          which is an integer value of type size_t representing the number of bytes between
 *          successive addresses at which objects of this type can be allocated. The valid
 *          alignment values are non-negative integral powers of two. 
 */
#include <stdio.h>
#include <stdalign.h>
 
// objects of struct S can be allocated at any address
// because both S.a and S.b can be allocated at any address
struct S {
    char a; // size: 1, alignment: 1
    char b; // size: 1, alignment: 1
}; // size: 2, alignment: 1
 
// objects of struct X must be allocated at 4-byte boundaries
// because X.n must be allocated at 4-byte boundaries
// because int's alignment requirement is (usually) 4
struct X {
    int n;  // size: 4, alignment: 4
    char c; // size: 1, alignment: 1
    // three bytes padding
}; // size: 8, alignment: 4
 
int main(void)
{
    printf("sizeof(struct S) = %zu\n", sizeof(struct S));
    printf("alignof(struct S) = %zu\n", alignof(struct S));
    printf("sizeof(struct X) = %zu\n", sizeof(struct X));
    printf("alignof(struct X) = %zu\n", alignof(struct X));
}
