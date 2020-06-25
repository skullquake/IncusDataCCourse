/*!@file a.c
 * @brief 
 */
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
char*genstr(const char*glyphs,size_t len);
int fitness(char*s0,char*s1);
char*mate(char*s0,char*s1,char*s3);
int genrnd(int lo,int hi);
//bool cmpstr(void*,void*,void*);//not qsort_r under mingw
int cmpstr(const void*,const void*);
char tgt[]="Lorem ipsum sit consecutar dolor amet";//0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
int ga_test(void){
	srand(time(0));
	int genidx=0;
	size_t len=strlen(tgt);
	const char*GLYPHS="01233456789abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.; ";
	unsigned long idx=0;
	int f0=-1;
	int f1=-1;
	int f2=-1;
	size_t populationsz=32;
	char**population=(char**)malloc(sizeof(char*)*populationsz);
	if(population==NULL){
		fprintf(stderr,"Error: Failed to allocate population\n");
		return EXIT_FAILURE;
	}
	for(size_t i=0;i<populationsz;++i){
		population[i]=genstr(GLYPHS,len);
	}
	qsort(population,populationsz,sizeof(&population[0]),cmpstr);
	printf("%8d:%s%8d",genidx,population[0],fitness(population[0],tgt));
	printf("\r");
	bool done=false;
	for(int i=0;i<4096&&!done;i++){
		qsort(population,populationsz,sizeof(&population[0]),cmpstr);
		//from 50% of fittest population individuals mate to produce offspring
		int numoffspring=populationsz*0.5;
		if((population=(char**)realloc(population,sizeof(char*)*(populationsz+numoffspring)))==NULL){
			break;
		}
		for(int j=0;j<numoffspring;j++){
			//mate with 50% weakest
			char*c0=mate(
				population[genrnd(0,numoffspring)],
				population[populationsz-genrnd(0,numoffspring)-1],
				tgt
			);
			population[populationsz+j]=c0;
		}
		populationsz+=numoffspring;
		qsort(population,populationsz,sizeof(&population[0]),cmpstr);
		//50% of weakest die
		for(int j=0;j<numoffspring;j++){
			free(population[populationsz-1-j]);
		}
		if((population=(char**)realloc(population,sizeof(char*)*(populationsz-numoffspring)))==NULL){
			break;
		}
		populationsz-=numoffspring;
		qsort(population,populationsz,sizeof(&population[0]),cmpstr);
		int topfitness=fitness(population[0],tgt);
		done=topfitness==0;
		printf("%8d:%s%8d\n",genidx,population[0],topfitness);
		//printf("\r");
		++genidx;
	}
	printf("\n");
	for(int i=0;i<populationsz;i++)
		free(population[i]);
	free(population);
	return EXIT_SUCCESS;
}
char*genstr(const char*glyphs,size_t len){
	char*ret=NULL;
	if(glyphs!=NULL&&len>0){
		ret=(char*)malloc((len+1)*sizeof(char));
		if(ret!=NULL){
			size_t szglyph=strlen(glyphs);
			for(size_t i=0;i<len;i++){
				ret[i]=glyphs[rand()%szglyph];
			}
			ret[len]='\0';
		}else{
			fprintf(stderr,"Error:genstr: failed to allocate buffer\n");
		}
	}else{
		fprintf(stderr,"Error:genstr: invalid parameters\n");
	}
	return ret;
}
int fitness(char*s0,char*s1){
	int ret=-1;
	if(s0!=NULL&&s1!=NULL){
		size_t szs0=strlen(s0);
		size_t szs1=strlen(s1);
		ret=0;
		for(size_t i=0;i<szs0&&i<szs1;++i){//neq lens???
			ret+=s0[i]==s1[i]?0:1;
		}
	}else{
		fprintf(stderr,"Error:fitness: invalid parameters\n");
	}
	return ret;
}
char*mate(char*s0,char*s1,char*s2){
	char*ret=NULL;
	if(s0!=NULL&&s1!=NULL&&s2!=NULL){
		if(strlen(s0)==strlen(s1)){
			size_t szs0=strlen(s0);
			size_t szs1=strlen(s1);
			size_t szs2=strlen(s2);
			ret=(char*)malloc((szs0+1)*sizeof(char));
			for(size_t i=0;i<szs0;++i){
				int r=genrnd(0,100);
				if(r<45){
					ret[i]=s0[i];
				}else if(r<90){
					ret[i]=s1[i];
				}else if(r<100){
					ret[i]=s2[rand()%szs2];
				}
			}
			ret[szs0]='\0';
		}else{
			fprintf(stderr,"Error:mate: unequal lengths\n");
		}
	}else{
		fprintf(stderr,"Error:mate: invalid parameters\n");
	}
	return ret;
}
int genrnd(int lo,int hi){
	return rand()%(hi-lo)+lo;
}
/* no qsort_r under mingw
bool cmpstr(void*a,void*b,void*arg){
	char*stra=*(char**)a;
	char*strb=*(char**)b;
	char*strarg=*(char**)arg;
	printf("cmpstr:%s:%s\n",stra,strb);
	return fitness(stra,strarg)<fitness(strb,strarg);
	//return true;
}
*/
int cmpstr(const void*a,const void*b){
	char*stra=*(char**)a;
	char*strb=*(char**)b;
	int fita=fitness(stra,tgt);
	int fitb=fitness(strb,tgt);
	bool fit=fita>fitb;
	//printf("cmpstr:%s:%s:[%d,%d]:%s\n",stra,strb,fita,fitb,fit?">":"<");
	//return fit;
	return fita-fitb;
	//return true;
}

