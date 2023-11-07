#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define Buffer_size 5
#define Num_Producers 3
#define Num_Consumers 2

//defining buffer as size 5
//defining semaphores empty full and mutex with data type sem_t
int buffer[Buffer_size];
sem_t empty, full, mutex;

//in and out are places where the producer produces and consumer consumes
int in = 0;
int out = 0;

//producer function
void *producer(void *arg){
	int item; 
	while(1){
		item = rand()%100; //produces a random number as an item 
		//producer funtion
		//wait decrements value
		sem_wait(&empty);  //this decrements empty and waits till empty>0
		sem_wait(&mutex); //locks the mutex (1 becomes 0 as wait decrements)
		
		//enter the items in the buffer
		buffer[in] = item;
		printf("\nProducer %d produced item : %d\n",*((int *)arg), item);
		in = (in+1) % Buffer_size; //updates the value of "in" in a circular buffer)
		
		//signal or post increments value
		sem_post(&mutex); //unlocks the mutex (0 becomes 1 again to work)
		sem_post(&full); //increments full 
		
		sleep(1); //simulate slower producer
	}
	pthread_exit(NULL);
}

//consumer funtion
void *consumer(void *arg){
	int item;
	while(1){
		sem_wait(&full); //decrements full and waits till full>0
		sem_wait(&mutex); //locks the buffer (1 becomes 0)
		
		//consumes the items 
		item = buffer[out];
		printf("\nConsumer %d cunsumes item : %d\n", *((int *)arg) , item);
		out = (out+1)%Buffer_size;
		
		sem_post(&mutex); //unlocks the mutex
		sem_post(&empty); //increments empty
		
		sleep(2);
	}
	pthread_exit(NULL);
}


int main(){
	//initialization of number of producers and consumers
	pthread_t producers[Num_Producers];
	pthread_t consumers[Num_Consumers];
	int producer_ids[Num_Producers];
	int consumer_ids[Num_Consumers];
	
	//initialising semaphores
	sem_init(&empty , 0 , Buffer_size);
	sem_init(&full , 0 , 0);
	sem_init(&mutex , 0 , 1);
	
	//producing producers (more than one)
	for(int i = 0; i<Num_Producers ; i++){
		producer_ids[i] = i+1;
		pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
	}
	
	//consumer 
	for(int i = 0; i<Num_Consumers; i++){
		consumer_ids[i] = i+1;
		pthread_create(&consumers[i], NULL, consumer, &producer_ids[i]);
	}
	
	while(1){
		// The main thread can perform other tasks or have additional
		//control logic here.
		// For simplicity, we just let the producer and consumer
		//threads run indefinitely.
	}
	
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
	
	return 0;
}