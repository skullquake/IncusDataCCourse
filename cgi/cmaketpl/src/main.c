/*!@file  main.c
*  @brief C99 Function Pointer Demo
*/
#include "main.h"
static int (*getfunc(int id))(void);

static void buildinfo (void) ;
int main (int argc, char* argv[]) {
	printf("Content-Type: text/plain\r\n\r\n");
   buildinfo();

   printf("Function? (A,B,C): ");
   int id = 'A';//toupper(getchar());
   int (*fp)(void) = getfunc(id);

   if (fp)
      printf("fp() -> %d\n", fp());
   else {
      fprintf(stderr, "Invalid function ID\n");
      return EXIT_FAILURE;
      }

   for (const char* ip = "ABC"; *ip; ++ip)
      printf("Calling `func%c`: %d\n", *ip, getfunc(*ip)());

   return EXIT_SUCCESS;
   }

static int funcA (void) { /*do some work*/ return 111; }
static int funcB (void) { /*do some work*/ return 222; }
static int funcC (void) { /*do some work*/ return 333; }

static int (*getfunc(int id))(void) {
   static int (*aof[])(void) = { funcA, funcB, funcC };
   if ('C' >= id && id >= 'A')
      return aof[id - 'A'];
   else
      return 0;
   }

static void buildinfo (void) {
   printf("%s: %s (v%s)\n", PRJ_NAME, PRJ_DESCRIPTION, PRJ_VERSION_STR);
   printf(BUILD_TYPE " build on " OS_NAME " (" ENDIANNESS " endian)\n");
   }
