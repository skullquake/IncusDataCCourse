/*!@file ./src/main.c
 * @brief main driver
 * https://ppanyukov.github.io/2011/06/29/retabbing-in-vim.html
 */
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"b.h"
#include"ea/ga.h"
#include"db/dbtest.h"
#include"incus/cadv/prg000.h"
#include"duktape/exec.h"
#include"macros/logging.h"
#include"cli/cli.h"
int main(int argc,char**argv){
	DBGVAR(main,p);
	cli_parse(argc,argv);
	return EXIT_SUCCESS;
}
