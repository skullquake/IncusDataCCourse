/*!@file ./src/tpl/tpl.c
 * @brief ctemplate functions
 */
#include"tpl/tpl.h"
#include<stdio.h>
#include"ctemplate/ctemplate.h"
/* @brief simple template arguments test
 */
static void tpl_test_args(void);
/* @brief template loop test
 */
static void tpl_test_loop(void);
/* @brief main template test
 */
void tpl_test(void){
	printf("tpl_test()\n");
	//tpl_test_args();
	tpl_test_loop();
}
static void tpl_test_args(void){
	printf("tpl_test_args()\n");
	TMPL_varlist*vlst;
	vlst=TMPL_add_var(0,"firstname","John",0);
	TMPL_add_var(vlst,"lastname","Doe",0);
	TMPL_add_var(vlst,"ssoc","1234567890",0);
	TMPL_write("./tpl/test_args.html",0,0,vlst,stdout,stderr);
	TMPL_free_varlist(vlst);
}
static void tpl_test_loop(void){
	printf("tpl_test_loop()\n");
	int n,f;
	char txt1[32],txt2[32];
	TMPL_varlist*mainlist,*vl;
	TMPL_loop*loop;
	loop=0;
	f=1;
	for(n=1;n<11;n++){
		sprintf(txt1,"%d",n);
		sprintf(txt2,"%d",f*=n);
		vl=TMPL_add_var(0,"n",txt1,"nfact",txt2,0);
		loop=TMPL_add_varlist(loop,vl);
	}
	mainlist=TMPL_add_var(0,"title","10 factorials",0);
	mainlist=TMPL_add_loop(mainlist,"fact",loop);
	TMPL_write("./tpl/test_loop.html",0,0,mainlist,stdout,stderr);
	TMPL_free_varlist(mainlist);
}
