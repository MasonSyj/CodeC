#include <stdio.h>
#include <stdbool.h>

#define N 5
#define M 7
#define TIMES 10

int num(bool array[][M], int i, int j){
	int sum = 0;
	
	for (int x = i - 1; x <= i + 1; x++){
		for (int y = j - 1; y <= j + 1; y++){
			if (x == i && y == j){
				continue;
			}
			sum += array[x][y];
		}
	}
	
	return sum;
}

int main(void){
	bool a[M][M];
	bool b[M][M];
	
	for (int i = 0; i < M; i++){
		for (int j = 0; j < M; j++){
			a[i][j] = false;
			b[i][j] = false;
		}
	}
	
	a[2][3] = true;
	a[3][3] = true;
	a[4][3] = true;
	
	for (int cnt = 0; cnt < TIMES; cnt++){
		for (int i = 1; i <= N; i++){
			for (int j = 1; j <= N; j++){
				if (a[i][j]){
					if (num(a, i, j) == 2 || num(a, i, j) == 3 ){
						b[i][j] = true;
					}else{
						b[i][j] = false;
					}
				}
				else{
					if (num(a, i, j) == 3){
						b[i][j] = true;
					}
				}
			}
		}
		
		for (int i = 0; i < M; i++){
			for (int j = 0; j < M; j++){
				a[i][j] = b[i][j];
			}
		}
		
		for (int i = 0; i < M; i++){
			for (int j = 0; j < M; j++){
				printf("%-5d", a[i][j]);
			}
			printf("\n");
		}
		printf("-------------------------\n");
	}
}


