/*!@file  tobin.c
*  @brief Conversion to Binary Implementation
*/
#include <stdlib.h>
#include <stdio.h>
#include "tobin.h"

const char* tobin (char* dest, uint64_t num, int len) {
   uint64_t mask = 1;
   dest[len] = '\0';
   for (char* p = dest + len - 1; len; --len, --p, mask <<= 1)
      *p = num & mask ? '1' : '0';
   return dest;
   }

#if defined TEST_TOBIN

int main (int argc, char* argv[]) {
   char buf[sizeof(uint64_t) * 8 + 1] = {0};
   if (argc > 1) {
      int val = 0;
      if (!sscanf(argv[1], "%d", &val)) {
         fprintf(stderr, "Integer argument expected!\n");
         return EXIT_FAILURE;
         }
      printf("%d->%s\n", val, tobin(buf, val, sizeof(uint64_t) * 8));
      }

   printf("123 in binary: %s\n", tobin(buf, 123ULL, 16));
   printf("-1 in binary: %s\n", tobin(buf, -1, sizeof(uint64_t) * 8));
   }

#endif/*TEST_TOBIN*/
