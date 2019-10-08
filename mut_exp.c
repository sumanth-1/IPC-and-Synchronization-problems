#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<fcntl.h>
int a = 10;
pthread_mutex_t lock;
void * fun()
{
//	pthread_mutex_lock(&lock);
	printf("%d\n",a);
	printf("Hiii\n");
	pthread_mutex_unlock(&lock);
	return NULL;
}


void * fun1()
{
	int i = 0;
	pthread_mutex_lock(&lock);
	while( 1024)
	{
		a++;
		i++;
	}
	pthread_mutex_unlock(&lock);
	printf("In fun1\n");
	return NULL;
}

int main(void)
{
	int i = 0;
	pthread_t thread_id[3];
	
	pthread_mutex_init(&lock , NULL);
	for(i = 0 ; i < 3 ; i++ )
	{
		pthread_create(&thread_id[i] ,NULL ,&fun1 ,NULL);
	}
	pthread_create(&thread_id[2] , NULL ,&fun ,NULL);
	
//	pthread_join(
	for(i = 0 ; i < 3  ; i++ )
	{
		pthread_join(thread_id[i] ,NULL);
	}
	
//	pthread_create(&thread_id[10] , NULL ,&fun ,NULL);
	pthread_join(thread_id[2],NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}


	
