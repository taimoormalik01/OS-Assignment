#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
	int cpid;
	int sum[10];
	int a=0,k=0,limit=0,s=0,l=0;
	int arr[1000];

	for(int i=0;i<1000;i++){
		arr[i]= i;
	}
	
	int fd1[2],fd2[2];
	//fd1[2] for sum
	//fd2[2] for limit
	
	if(pipe(fd1)==-1){printf("Pipe 1 failed");return 1;}
	if(pipe(fd2)==-1){printf("Pipe 2 failed");return 1;}
	write(fd2[1],&limit,sizeof(int));
	write(fd1[1],&s,sizeof(int));
	
	
	for(int i=0;i<10;i++){
		cpid=fork();
		if(cpid<0){printf("Fork Failed");return 1;}
		
		if(cpid==0){
			s=0,l=0;
			read(fd1[0],&s,sizeof(int));

			read(fd2[0],&l,sizeof(int));
			
			for(int j=l;j<l+100;j++){
				s=s+arr[j];
			} 
			
			write(fd2[1],&l,sizeof(int));
			
			write(fd1[1],&s,sizeof(int));
			
			exit(0);
		}
		else{
			
			wait(NULL);
			
			int b=0,tempsum = 0;
			read(fd1[0],&b,sizeof(int));
			sum[k]=b;
			k++;
			
			read(fd2[0],&limit,sizeof(int));
			
			limit=limit+100;
			write(fd2[1],&limit,sizeof(int));
			
			write(fd1[1],&tempsum,sizeof(int));

		
		}
	}
		int temp =0; 
		for(int i=0;i<10;i++)
		{
			temp += sum[i];
		}
		printf("Total Sum is:%d",temp);
	
	return 0;
}
