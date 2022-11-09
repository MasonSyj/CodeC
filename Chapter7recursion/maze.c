#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#define ROW 5
#define COL 5

bool explore(int y, int x, int maze[][COL]);

int main(void) {
	
	int maze[ROW][COL] = { {0, 1, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 1, 0}, {0, 1, 1, 1, 0}, {0, 1, 0, 0, 0}};
	int x = explore(0, 1, maze);
	printf("%d", x);
}

bool explore(int y, int x, int maze[][COL]){
	if (x < 0 || y < 0 || x >= COL || y >= ROW){
		return false;
	}
	
	if (y == ROW - 1 && maze[y][x] == 1) {
		return true;
	}
	
	if (y + 1 < ROW && maze[y+1][x]){
		maze[y][x] = 0;
		if (explore(y+1, x, maze)){
			return true;
		}
	}
	
	if (x + 1 < COL && maze[y][x+1]){
		maze[y][x] = 0;
		if (explore(y, x+1, maze)){
			return true;
		}
	}
	
	
	if (x - 1 > 0 && maze[y][x-1]){
		maze[y][x] = 0;
		if (explore(y, x-1, maze)){
			return true;
		}
	}
	
	if (y - 1 > 0 && maze[y-1][x]){
		maze[y][x] = 0;
		if (explore(y-1, x, maze)){
			return true;
		}
	}
	
	return false;
}
