#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SZ 4096

int main(){
	int shm_id;
	int *shm_ptr;
	int data,ret_val;
	int read_data;
	int pid;
	
	shm_id = shmget(IPC_PRIVATE, SZ, IPC_CREAT | 0666);
	if(shm_id<0){
		printf("\nError at addressing memory.");
	}else {
		printf("\nShared memory is created.");
		printf("\nShared memory ID %d :", shm_id);
		
		shm_ptr = (int*)shmat(shm_id, NULL, 0);
		if((int)shm_ptr != -1){
			printf("\nShared memory is attatched to %d :", shm_ptr);
		}
		printf("\nEnter the data :");
		scanf("%d", &data);
		*shm_ptr = data;
		
		pid = fork();
		if(pid == 0){
			if((int)shm_ptr != -1){
				printf("\nShared memory is attatched to %d :", shm_ptr);
				read_data = *shm_ptr;
				printf("\nDAta from shared memory : %d", *shm_ptr);
			}
		}
		ret_val = shmdt((void *)shm_ptr);
		if(ret_val == 0){
			printf("\nShared memory is successfully detatched.");
		}else{
			printf("\nshmdt error");
		}
	}
	return 0;
}