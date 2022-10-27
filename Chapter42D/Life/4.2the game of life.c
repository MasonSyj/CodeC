#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "neillsimplescreen.h"

#define M 50
#define N 30
#define LOOPTIMES 1000
#define WORDSIZE 20
#define TOPLEN 10

void print(bool arr[][N]);
int count(bool array[][N], int j, int i);
void lifeonce(bool a[][N], bool b[][N]);

int main(void){
	bool a[M][N];
	bool b[M][N];
	
	memset(a, 0, N * M);
	memset(b, 0, N * M);
	char temp[WORDSIZE];
	FILE* fp = fopen("gosperglidergun_106.lif", "r");
	
	assert(fp);
	assert(fgets(temp, WORDSIZE, fp));
	assert(strncmp(temp, "#Life 1.06", TOPLEN) == 0);
	int xx, yy;
	while (fscanf(fp, "%d %d", &xx, &yy) == 2){
		a[xx + M / 2][yy + N / 2] = true;
	}
//	print(a);
	for (int i = 0; i < LOOPTIMES; i++){
		lifeonce(a, b);
		print(a);
	}
	fclose(fp);
}

int count(bool array[][N], int j, int i){
	int sum = 0;
	for (int y = j - 1; y <= j + 1; y++){
		for (int x = i - 1; x <= i + 1; x++){
			if ((x == i && y == j) || y < 0 || y == M || x < 0 || x == N){
				continue;
			}
			sum += array[y][x];
		}
	}
	return sum;
}

void lifeonce(bool a[][N], bool b[][N]){
		for (int j = 0; j < M; j++){
			for (int i = 0; i < N; i++){
				if (a[j][i]){
					if (count(a, j, i) == 2 || count(a, j, i) == 3 ){
						b[j][i] = true;
					}else{
						b[j][i] = false;
					}
				}
				else{
					if (count(a, j, i) == 3){
						b[j][i] = true;
					}
				}
			}
		}
		
		for (int j = 0; j < M; j++){
			for (int i = 0; i < N; i++){
				a[j][i] = b[j][i];
			}
		}
		
}

void print(bool arr[][N]){
	neillcursorhome();
	neillbgcol(black);
//	neillcol c;
	for (int j = 0; j < M; j++){
		for (int i = 0; i < N; i++){
			if (arr[j][i] == false){
				neillfgcol(red);
			}else{
				neillfgcol(green);
			}
			printf("%-3d", arr[j][i]);
		}
		printf("\n");
	}
	neillclrscrn();
	neillcursorhome();
	neillbusywait(1.0);
}
