#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t wrt;
sem_t mutex;
int readcount = 0, nwt , nrd;

//reader function 
void *reader_thr(void *temp){
	int *id_ptr = (int *)temp;
	int id = *id_ptr;
	free(id_ptr);
	
	printf("\nReader %d is trying to enter database for reading.",id);
	sem_wait(&mutex);
	readcount++;
	if(readcount ==1)
		sem_wait(&wrt);
	sem_post(&mutex);
	
	printf("\nReader %d is now reading in the database.",id);
	sem_wait(&mutex);
	readcount--;
	if(readcount ==0)
		sem_post(&wrt);
	sem_post(&mutex);
	
	printf("\nReader %d has left database.",id);
	sleep(3);
	pthread_exit(NULL);	
}

//writer funtion 
void *writer_thr(void *temp){
	int *id_ptr = (int *)temp;
	int id = *id_ptr;
	free(id_ptr);
	
	printf("\nWriter %d is trying to ente the database for making changes.",id);
	sem_wait(&wrt);
	printf("\nWriter %d is writing in the daatabase.",id);
	sleep(3);
	printf("\nWriter %d is leaving the database.\n",id);
	sem_post(&wrt);
	pthread_exit(NULL);
	
}

int main(){
	long int i;
	sem_init(&mutex , 0, 1);
	sem_init(&wrt, 0, 1);
	pthread_t reader[100], writer[100];
	printf("\nEnter number of readers :");
	scanf("%d",&nrd);
	printf("\nEnter number of writers :");
	scanf("%d", &nwt);
	
	
    for (i = 1; i <= nwt; i++)
    {
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writer[i], NULL, writer_thr, (void *)writer_id);
    }

    for (i = 1; i <= nrd; i++)
    {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&reader[i], NULL, reader_thr, (void *)reader_id);
    }

    for (i = 1; i <= nwt; i++)
    {
        pthread_join(writer[i], NULL);
    }

    for (i = 1; i <= nrd; i++)
    {
        pthread_join(reader[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    pthread_exit(NULL); // Exit the main thread gracefully
  return 0;
}
