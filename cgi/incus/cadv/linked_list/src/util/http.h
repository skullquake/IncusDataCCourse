#ifndef UTIL_HTTP_H
#define UTIL_HTTP_H
#include<stdio.h>
void httpString(char**dest,char*input,const char*find);
int urldecode(const char *s, char *dec);
char* stream2buf(unsigned long len,FILE*fp);
#endif

