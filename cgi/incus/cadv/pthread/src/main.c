#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t pth_mutex=PTHREAD_MUTEX_INITIALIZER;
int SharedInt=0;
extern void*pth_func1(void*arg);
extern void*pth_func2(void*arg);
int main(){
	int x=0,y=0,z=0;
	printf("x: %d, y: %d\n",x,y);
	pthread_t pth_obj1,pth_obj2;
	if(pthread_create(&pth_obj1,0,pth_func1,&x)) {
		fprintf(stderr,"\nCould not create thread #1a.\n");
		return EXIT_FAILURE;
	}
	if(pthread_create(&pth_obj2,0,pth_func2,&x)) {
		fprintf(stderr,"\nCould not create thread #1b.\n");
		return EXIT_FAILURE;
	}
	while(++z<100){
		pthread_mutex_lock(&pth_mutex);
		SharedInt+=2;
		pthread_mutex_unlock(&pth_mutex);
		putchar('-');
		usleep(80);
	}
	printf("\nMain job complete.\n");
	if(pthread_join(pth_obj1,0)) {
		fprintf(stderr,"\nError joining thread\n");
		return EXIT_FAILURE+1;
	}
	if(pthread_join(pth_obj2,0)){
		fprintf(stderr,"\nError joining thread\n");
		return EXIT_FAILURE+1;
	}
	printf("SharedInt = %d, x: %d, y: %d, z: %d\n",SharedInt,x,y,z);
	return EXIT_SUCCESS;
}
void* pth_func1 (void* arg) {
	 int* p = (int*)arg;
	 while (++*p < 200) {
			pthread_mutex_lock(&pth_mutex);
			SharedInt += 2;
			pthread_mutex_unlock(&pth_mutex);
			putchar('X');
			usleep(50);
			}
	 printf("\nThread 1 complete...\n");
	 return arg;
}
void* pth_func2 (void* arg) {
	 int* p = (int*)arg;
	 while (++*p < 220) {
			pthread_mutex_lock(&pth_mutex);
			SharedInt += 2;
			pthread_mutex_unlock(&pth_mutex);
			putchar('O');
			usleep(50);
			}
	 printf("\nThread 2 complete...\n");
	 return arg;
}
