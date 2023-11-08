#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main(){
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)1122,1024,0666);
    printf("\nKey of shared memory is: %d", shmid);
    
    shared_memory = shmat(shmid, NULL, 0);
    printf("\nprocess attatched at %p\n", shared_memory);
    printf("\ndata in shared memory is : %s",(char*)shared_memory);
}