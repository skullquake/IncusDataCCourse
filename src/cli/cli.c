/*!@file cli/cli.c
 * @brief parse command line for this program
 */
#include"cli/cli.h"
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include"duktape/exec.h"
#include"srv/srv.h"
#define OPTPARSE_IMPLEMENTATION
//#define OPTPARSE_API static
#include"optparse/optparse.h"
extern void printhelp(void);
int cli_parse(int argc,char**argv){
	if(argc==1){
		printhelp();
	        exit(EXIT_FAILURE);
	}
	struct optparse_long longopts[]={
	    {"run",'r',OPTPARSE_REQUIRED},
	    {"version",'v',OPTPARSE_NONE},
	    {"help",'h',OPTPARSE_NONE},
	    {"serve",'s',OPTPARSE_NONE},
	    {"port",'p',OPTPARSE_REQUIRED},
	    {"init",'i',OPTPARSE_REQUIRED},
	    {0}
	};
	char *arg;
	int option;
	struct optparse options;
	optparse_init(&options,argv);
	bool bool_srv=false;
	char*srvport=NULL;
	bool bool_srvinitscr=false;
	char*srvinitscr=NULL;
	while((option=optparse_long(&options,longopts,NULL))!=-1){
	    switch(option){
	    case 'h':
	        printhelp();
	        break;
	    case 'v':
	        printf("Version 0.01\n");
	        break;
	    case 'r':
	        duk_exec(options.optarg);
	        break;
	    case 'p':
		srvport=options.optarg;
	        break;
	    case 'i':
		bool_srvinitscr=true;
		srvinitscr=options.optarg;
	        break;
	    case 's':
	        bool_srv=true;
	        break;
	    case '?':
	        fprintf(stderr,"%s: %s\n",argv[0],options.errmsg);
	        exit(EXIT_FAILURE);
	    }
	}
	if(bool_srv){
		if(bool_srvinitscr){
			srv_init(srvinitscr);
		}
		srv_start(srvport);
	}
	return EXIT_SUCCESS;
}
void printhelp(void){
	//replace with standard hex sequences
	printf("\e\e[30;48;5;82mDukExec\e[0m\n");
	printf("\e[40;38;5;82mDescription:\e[0m\n");
	printf("Simple utility for executing JavaScript with\n");
	printf("some native c functionality exposed for calling via\n");
	printf("the scripting engine\n");
	printf("\e[40;38;5;82mOptions\e[0m\n");
	printf("\t -h         : Help\n");
	printf("\t -v         : Version\n");
	printf("\t -r PATH    : Run script\n");
	printf("\t -s         : Start server\n");
	printf("\t -p PORT    : Set server port\n");
	printf("\t -i PATH    : Specify server initialization script\n");
	printf("\e[40;38;5;82mLong options\e[0m\n");
	printf("\t --help     : Help\n");
	printf("\t --version  : Version\n");
	printf("\t --run PATH : Run script\n");
	printf("\t --serve    : Start server\n");
	printf("\t -port PORT : Set server port\n");
	printf("\t -init PATH : Specify server initialization script\n");
}
