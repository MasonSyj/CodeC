#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define HEIGHT 80
#define WIDTH 30
#define G 250
#define L 10 * G
#define TIMES 1000

void lighteningburn(char a[][WIDTH + 1]);
void grow(char a[][WIDTH + 1]);
bool isfire(char a[][WIDTH + 1], int i, int j);
bool istree(char a[][WIDTH + 1], int i, int j);
bool isempty(char a[][WIDTH + 1], int i, int j);
bool isfirearound(char a[][WIDTH + 1], int i, int j);


int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	char a[HEIGHT][WIDTH + 1];
	char b[HEIGHT][WIDTH + 1];
	int l = 0;
	int g = 0;
// randomly fill up the grid with empty cells, tree cells and fire cells
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH; j++){
			int randompick = rand() % 3;
			a[i][j] = randompick + '0';
			b[i][j] = a[i][j];
		}
	}
	
	for (int cnt = 0; cnt < TIMES; cnt++){
		if (l == L){
			lighteningburn(a);
			l = 0;
		}else if (g == G){
			grow(a);
			g = 0;
		}
		
		for (int i = 0; i < HEIGHT; i++){
			for (int j = 0; j < WIDTH; j++){
				if (isfire(a, i, j)){
					b[i][j] = '0';
				}else if (istree(a, i, j)){
					if (isfirearound(a, i, j)){
						b[i][j] = '1';
					}
				}
			}
		}
		
		for (int i = 0; i < HEIGHT; i++){
			for (int j = 0; j < WIDTH; j++){
				a[i][j] = b[i][j];
			}
		}
		
		
		l++;
		g++;
	}
}

void lighteningburn(char a[][WIDTH + 1]){
	
	int x, y;
	
	while (1){
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		if (istree(a, x, y)){
			a[x][y] = '1';
			return;
		}
	}
	
	
}
void grow(char a[][WIDTH + 1]){
	int x, y;
	
	while (1){
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		if (isempty(a, x, y)){
			a[x][y] = '2';
			return;
		}
	}
}
bool isfire(char a[][WIDTH + 1], int i, int j){
	return a[i][j] == '1';
}
bool istree(char a[][WIDTH + 1], int i, int j){
	return a[i][j] == '2';
}

bool isempty(char a[][WIDTH + 1], int i, int j){
	return a[i][j] == '0';
}

bool isfirearound(char a[][WIDTH + 1], int i, int j){
	for (int x = i - 1; x <= i + 1; x++){
		for (int y = j - 1; y <= j + 1; y++){
			if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH){
				continue;
			}
			
			if (isfire(a, x, y)){
				return true;
			}
		}
	}
	return false;
}