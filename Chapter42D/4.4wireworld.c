#include <stdio.h>
#include <stdbool.h>
#define WIDTH 10
#define HEIGHT 10

bool around(char a[][HEIGHT + 1], int i, int j);
void wire(char a[][HEIGHT + 1], char b[][HEIGHT + 1]);
void print(char a[][HEIGHT + 1]);

int main(void){
	char a[WIDTH][HEIGHT + 1];
	char b[WIDTH][HEIGHT + 1];
	
	for (int i = 0; i < WIDTH; i++){
		for (int j = 0; j < HEIGHT; j++){
			a[i][j] = '-';
			b[i][j] = '-';
		}
	}
	
	
	for (int j = 0 ; j < HEIGHT; j++){
		a[5][j] = '0';
		b[5][j] = '0';
	}
	
	a[5][5] = '-';
	b[5][5] = '-';
	
	a[4][4] = '0';
	a[4][5] = '0';
	a[6][4] = '0';
	a[6][5] = '0';
	
	b[4][4] = '0';
	b[4][5] = '0';
	b[6][4] = '0';
	b[6][5] = '0';
	
	a[5][1] = '2';
	a[5][0] = '1';
	
	for (int i = 0; i < 10; i++){
		wire(a, b);
		print(a);
		printf("---------------\n");
	}
}

bool around(char a[][HEIGHT + 1], int i, int j){
	int cnt = 0;
	for (int x = i - 1; x <= i +1; x++){
		for (int y = j - 1; y <= j + 1; y++){
			if (x == -1 || x == WIDTH || y == -1 || y == HEIGHT ){
				continue;
			}
			if (a[x][y] >= '2'){
				cnt++;
			}
		}
	}
	if (cnt == 1 || cnt == 2){
		return true;
	}
		return false;
}

void wire(char a[][HEIGHT + 1], char b[][HEIGHT + 1]){
	for (int i = 0; i < WIDTH; i++){
		for (int j = 0; j < HEIGHT; j++){
				if (a[i][j] == '0'){
					if (around(a, i, j) == true)
						b[i][j] = '2';
				}else if (a[i][j] == '2'){
					b[i][j] = '1';
				}else if (a[i][j] == '1'){
					b[i][j] = '0';	
				}
		}
	}
	
	for (int i = 0; i < WIDTH; i++){
		for (int j = 0; j < HEIGHT; j++){
			a[i][j] = b[i][j];		
		}
	}
}

void print(char a[][HEIGHT + 1]){
	for (int i = 0; i < WIDTH; i++){
		for (int j = 0; j < HEIGHT; j++){
			printf("%-3c", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

