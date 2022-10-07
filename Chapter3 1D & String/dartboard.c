#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GREEDYTIMES 5000000
#define N 20

int newarray(int board[], int sum);
int arraysum(int n, int board[]);

int main(void){
	srand((unsigned)time(NULL));
	int board[N] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};
	printf("%d %d\n", board[0], board[1]);
	int sum = arraysum(N, board);
	printf("%d\n",sum);
	// sum 
	int i = 0;
	while (i++ < GREEDYTIMES){
		int thissum = newarray(board, sum);
		if (thissum != sum){
			sum = thissum;		
		}
//		printf("%d\n",sum);
	}
	
}



int newarray(int board[], int sum){
	// pick two random different index
	int x, y;
	do{
		x = rand() % 20;
		y = rand() % 20;
	}while (x !=y);
	// swap 
	int temp = board[x];
	board[x] = board[y];
	board[y] = temp;
	// get sum from the new array
	int thissum = arraysum(N, board);
	// compare and potential unswap
	if (thissum < sum){
		sum = thissum;
		printf("Total = %d  :  ", thissum);
		for (int i = 0; i < 20; i++){
			printf("%d  ", board[i]);
			
		}
		printf("\n");
	}else{ //unswap
		int temp = board[x];
		board[x] = board[y];
		board[y] = temp;
	} 
	return sum;
}

int arraysum(int n, int a[]){
	int sum = 0;		
	for (int i = 0; i < n; i++){
		sum += (a[i] + a[(i+1) % n] + a[(i+2) % n]) * (a[i] + a[(i+1) % n] + a[(i+2) % n]);
	}
	return sum;
}

