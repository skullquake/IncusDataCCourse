/*!@file: ./src/main.c
 * @brief: description
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"foo/foo.h"
int
main (int argc, char **argv, char **envp)
{
  argc = argc;
  argv = argv;
  envp = envp;
  printf ("Content-Type: text/plain\n\n");
  printf("%d\n",myadd(1,1));
  printf("%d\n",myadd(1,2));
  return EXIT_SUCCESS;
}
