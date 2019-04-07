#include<stdio.h>
#include<conio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
pthread_mutex_t mutex,wrt;
     
int rcount=0;

void *reader(void *arg);

void *writer(void *arg);

int d=1;

int c=1;

int main()
{
	int nr,nw,i,a;
	
	pthread_t rid[20],wid[10];
	
	pthread_mutex_init(&mutex,NULL);
	    
	pthread_mutex_init(&wrt,NULL);
    
    printf("Numbers of Writers and readers you want to create : ");
    scanf("%d",&a);
    nr =a;
    nw=a;
	for(i=0;i<nr;i++)
	{
		if(i<nw)
		
		pthread_create(&wid[i],NULL,writer,(void*) i);
		
		pthread_create(&rid[i],NULL,reader,(void*) i);
	}
	for(i=0;i<nr;i++)
	{
		if(i<nw)
		
		pthread_join(wid[i],NULL);
		
		pthread_join(rid[i],NULL);
	}
	return 0;
}
void *writer(void *arg)
{
	pthread_mutex_lock(&wrt);
	                
	int no=((int)arg);
	
	d++;
	
	printf("\t------->writer %d writes %d<----------\n\n",no,d);
	
	printf("\t------->writer %d leaving the class<----------\n\n\t",no);
	sleep(1);
	
	pthread_mutex_unlock(&wrt);               
}
void *reader(void *arg)
{
	int no=((int)arg);
	
	c++;
	
	 pthread_mutex_lock(&mutex);
	           
	rcount++;
	
	
	if(rcount==0)
	
	pthread_mutex_lock(&wrt);
	               
	pthread_mutex_unlock(&mutex);
	
	
	           
	printf("------->Reader %d reads data = %d<-------- \n\n\t",no,d);
	//if(no==5)
	//{
		//for(no=0;no<5;no++)
	printf("------->Reader %d leaving the class<-----------\n\n\t",no);
		
	


	//else

		
	sleep(1);
	
	pthread_mutex_lock(&mutex);   
	
	rcount--;
	
	if(rcount==0)
	
	pthread_mutex_unlock(&wrt); 
	
	pthread_mutex_unlock(&mutex);                   

}
