# include <stdio.h>
# include <pthread.h>
# define BufferSize 10

void *Enqueue();
void *Dequeue();

int BufferIndex=0;
char *BUFFER;

pthread_cond_t Buffer_Not_Full=PTHREAD_COND_INITIALIZER;
pthread_cond_t Buffer_Not_Empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar=PTHREAD_MUTEX_INITIALIZER;

int main()
{    
	pthread_t ptid,ctid;

	BUFFER=(char *) malloc(sizeof(char) * BufferSize);            

	pthread_create(&ptid,NULL,Enqueue,NULL);
	printf("Enqueue thread is created\n");
	pthread_create(&ctid,NULL,Dequeue,NULL);
	printf("Dequeue thread is created\n");

	pthread_join(ptid,NULL);
	pthread_join(ctid,NULL);


	return 0;
}

void *Enqueue()
{    
	int i = 0;
//	for(i = 0 ; i < 10 ; i ++ )
	for(;;)
	{
		pthread_mutex_lock(&mVar);
/*		if(BufferIndex==BufferSize)
		{                        
			pthread_cond_wait(&Buffer_Not_Full,&mVar);
		}       */                 
		BUFFER[BufferIndex++]='@';
		printf("Enqueue : %d \n",BufferIndex);
		pthread_mutex_unlock(&mVar);
		pthread_cond_signal(&Buffer_Not_Empty);        
	}    

}

void *Dequeue()
{
	int i = 0;
//	for(i = 0; i < 10 ; i++)
	for(;;)
	{
		pthread_mutex_lock(&mVar);
/*		if(BufferIndex==-1)
		{            
			pthread_cond_wait(&Buffer_Not_Empty,&mVar);
		}      */          
		printf("Dequeue : %d \n",BufferIndex--);     
//		printf("Dequeued data = %c\n",BUFFER[BufferIndex]);   
		pthread_mutex_unlock(&mVar);        
		pthread_cond_signal(&Buffer_Not_Full);                
	}    
}
