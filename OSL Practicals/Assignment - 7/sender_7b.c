#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

int main(){
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)1122, 1024, 0666 | IPC_CREAT);
    printf("\nkey of shared memory is : %d", shmid);

    shared_memory = shmat(shmid, NULL, 0);
    printf("\nShared memory address is : %p\n", shared_memory);

    printf("\nEnter data to write in shared memory\n ");
    read(0,buff,100);
    strcpy(shared_memory, buff);
    printf("\nThe data you entered = %s", (char *)shared_memory);
}