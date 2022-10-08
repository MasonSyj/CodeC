#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GREEDYTIMES 5000000
#define N 20

int createsmallerarray(int sum, int board[]);
int arraysum(int n, int board[]);
void arrayprint(int n, int board[]);

int main(void){
	srand((unsigned)time(NULL));
	
	int board[N] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};
	int sum = arraysum(N, board);


	int i = 0;
	while (i++ < GREEDYTIMES){
		int thissum = createsmallerarray(sum, board);
		if (thissum < sum){
			sum = thissum;
			printf("Total : %d   :   ", sum);
			arrayprint(N, board);
			printf("\n");
		}

	}
	
//	printf("%d\n",sum);
	
}



int createsmallerarray(int sum, int board[]){
	/* pick two random different index */
	int x, y;
	do{
		x = rand() % N;
		y = rand() % N;
	}while (x ==y);
	/* swap */
	int temp = board[x];
	board[x] = board[y];
	board[y] = temp;
	/* get sum from the new array */
	int thissum = arraysum(N, board);
	// compare
	if (thissum < sum){
		sum = thissum;
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

void arrayprint(int n, int board[]){
	for (int i = 0; i < n; i++){
		printf("%3d", board[i]);
	}
}

