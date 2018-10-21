#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int arr[1000];
int chunk=100;
void * sumFunc(void *arg)
{
	int Tsum=0;
	int s=(int)arg;
	for(int i=s;i<s+chunk;i++){
		Tsum+=arr[i];
	}
	return (void*)Tsum;
}

int main ()
{
	for(int i=0;i<1000;i++){arr[i]=i;}
	
	int sum=0,start=0,TotalSum=0;
	pthread_t thread_t1;
	
	for(int i=0;i<10;i++){

	pthread_create(&thread_t1,NULL,sumFunc,(void*)(start));

	pthread_join(thread_t1,(void**) & sum);

	printf("\nSum %d",i);
	printf(" is: %d",sum);
	TotalSum+=sum;
	start+=100;
	sum=0;


	}
	

	printf("\nTotal Sum is: %d\n", TotalSum);

	return 0;
}
