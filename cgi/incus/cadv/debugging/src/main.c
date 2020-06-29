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
  foo();
  return EXIT_SUCCESS;
}
