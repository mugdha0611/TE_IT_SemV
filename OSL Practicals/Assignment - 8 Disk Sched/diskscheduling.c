#include <stdio.h>
#include <stdlib.h>

int SSTF();
int SCAN();
int CLOOK();

//SSTF algorithm
int SSTF(int n, int Req[], int initialhead){
	int RQ[100], TotalHeadMovement =0, count =0,i;
	for(i =0;i<n;i++){
		RQ[i] = Req[i];
	}
	while(count !=n){
		int min = 1000,d,index;
		for(i =0; i<n;i++){
			d = abs(RQ[i] - initialhead);
			if(min > d){
				min = d;
				index = i;
			}
		}
		
		printf("\nMove head from %d to %d , (seek time = %d)",initialhead,RQ[index],min);
		TotalHeadMovement = TotalHeadMovement + min;
		initialhead = RQ[index];
		RQ[index] = 1000;
		count++;
	}
	printf("\nTotal Head movement : %d", TotalHeadMovement);
	return 0;
}

// SCAN Algorithm
int SCAN(int n, int Req[], int initialhead){
	int RQ[100],i,j,TotalHeadMovement =0,size,move;	
	for(i = 0;i<n;i++){
		RQ[i]=Req[i];
	}
	printf("\nEnter Disk Size :");
	scanf("%d",&size);
	printf("\nEnter direction for head movement - 1 for hight, 0 for low :");
	scanf("%d",&move);
	
	for(i=0;i<n;i++){//sort
		for(j=0;j<n-i-1;j++){
			if(RQ[j]>RQ[j+1]){
				int temp;
				temp = RQ[j];
				RQ[j] = RQ[j+1];
				RQ[j+1] = temp;
			}
		}
	}

	int index;
	for(i=0;i<n;i++){// initial head is less than which index
		if(initialhead<RQ[i]){
			index =i;
			break;
		}
	}
//scan code
	if(move ==1){//right

		for(i =index;i<n;i++){
			int seek = abs(RQ[i] - initialhead);
			printf("\nMove head from %d to %d , (seek time = %d)",initialhead,RQ[i],seek);
			TotalHeadMovement += seek;
			initialhead = RQ[i];
		}
        TotalHeadMovement+=2*(size-initialhead);//183->190->183
       
		for(i =index-1;i>=0;i--){
			int seek = abs(RQ[i]-initialhead);
			printf("Move head from %d to %d (seek time = %d)\n", initialhead, RQ[i], seek);
            		TotalHeadMovement += seek;
            		initialhead = RQ[i];
		}
	}else{//left

		for(i=index-1;i>=0;i--){
			int seek = abs(RQ[i]-initialhead);
			printf("\nMove head from %d to %d (seek time = %d)\n",initialhead,RQ[i],seek);
			TotalHeadMovement +=seek;
			initialhead = RQ[i];
		}
        TotalHeadMovement+=2*initialhead;//23->0->23

		for(i =index;i<n;i++){
			int seek = abs(RQ[i] - initialhead);
			printf("\nMove head from %d to %d , (seek time = %d)",initialhead,RQ[i],seek);
			TotalHeadMovement += seek;
			initialhead = RQ[i];
		}
	}
	
	printf("\nTotal head movement : %d",TotalHeadMovement);
	return 0;
}


// C-LOOK Algorithm
int CLOOK(int n, int Req[],int initial)
{
    int RQ[100], i, j,TotalHeadMovement = 0, size, move;
    for(i = 0;i<n;i++){
		RQ[i]=Req[i];
	}
    printf("Enter total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    int index;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            int seek = abs(RQ[i] - initial);
            printf("Move head from %d to %d (seek time = %d)\n", initial, RQ[i], seek);
            TotalHeadMovement += seek;
            initial = RQ[i];
        }

        for (i = 0; i < index; i++)
        {
            int seek = abs(RQ[i] - initial);
            printf("Move head from %d to %d (seek time = %d)\n", initial, RQ[i], seek);
            TotalHeadMovement += seek;
            initial = RQ[i];
        }
    }
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            int seek = abs(RQ[i] - initial);
            printf("Move head from %d to %d (seek time = %d)\n", initial, RQ[i], seek);
            TotalHeadMovement += seek;
            initial = RQ[i];
        }

        for (i = n - 1; i >= index; i--)
        {
            int seek = abs(RQ[i] - initial);
            printf("Move head from %d to %d (seek time = %d)\n", initial, RQ[i], seek);
            TotalHeadMovement += seek;
            initial = RQ[i];
        }
    }
    printf("Total head movement: %d", TotalHeadMovement);
    return 0;
}


int main(){
	int ch, YN=1, i, l, f;
	char F[10], s[25];
	for(i = 0; i<f; i++){
		F[i]= -1;
	}
	int flag = 1;
	int Req[100],n,initialhead;
	printf("\nEnter the number of Requests: ");
	scanf("%d", &n);
	printf("\nEnter the requests in sequennce :");
	for(i = 0; i<n; i++){
		scanf("%d", &Req[i]);
	}
	printf("\nEnter initial head position :");
	scanf("%d",&initialhead);
	
	do{
		printf("\nMenu");
		printf("\n1. SSTF \n2. SCAN\n3. CLOOK\n4. Exit");
		printf("\nEnter a choice: ");
		scanf("%d", &ch);
		
		switch(ch){
			case 1:
				for(i =0; i<f;i++){
					F[i] = -1;
				}
				SSTF(n,Req,initialhead);
				break;
			case 2:
				for(i =0; i<f;i++){
					F[i] = -1;
				}
				SCAN(n,Req,initialhead);
				break;
			case 3:
				for(i =0; i<f;i++){
					F[i] = -1;
				}
				CLOOK(n,Req,initialhead);
				break;
			case 4:
				flag =0;
				exit(0);
		}
	}while(flag);
	return (0);
}
