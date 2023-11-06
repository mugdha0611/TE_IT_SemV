#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define Max_Buff 1024

int main(){
	int fd1, fd2, c =0;
	char *myfifo1 = "myfifo1";
	char *myfifo2 = "myfifo2";
	
	char buff[Max_Buff];
	char str;
	int res;
	
	res = mkfifo(myfifo1, 0777);
	if(res == -1){
		printf("\nPipe 1 not created.");
		return 0;
	}
	
	//second fifo
	res = mkfifo(myfifo2,0777);
	if(res == -1){
		printf("\nPipe 2 not created.");
		return 0;
	}
	
	printf("\nEnter the string (terminate with #): \n");
	
	//read char one by one 
	while((str = getchar()) != '#'){
		buff[c++] = str;
		if(c>=Max_Buff -1){}
		printf("\nMax buffer size reached.");
		break;
	}
	
	buff[c] = '\0';
	fd1 = open(myfifo1, O_WRONLY);
	write(fd1, buff, sizeof(buff));
	close(fd1);
	
	fd2 = open(myfifo2, O_RDONLY);
	read(fd2,&buff,Max_Buff);
	close(fd2);
	
	unlink(myfifo2);
	return 0;
	
}