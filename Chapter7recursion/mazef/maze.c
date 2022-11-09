#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#define ROW 5
#define COL 5
#define SIZE 20

bool explore(int y, int x, char** maze);

int main(void) {
	
	FILE* fp = fopen("maze.txt", "r");
	int row, col;
	
	assert(fscanf(fp, "%d %d", &row, &col) == 2);
	assert(row == 10);
	assert(col == 10);
	char temp[SIZE];
	
	fgets(temp, col + 2, fp);
//	printf("%s", temp);
	
	char** maze = (char**)calloc(row, sizeof(char*));
	for (int j = 0; j < row; j++){
	   fgets(temp, col+2, fp);
	   maze[j] = (char*)calloc(col + 1, sizeof(char));
	   strncpy(maze[j], temp, col);
      puts(maze[j]);
	}
	
//	assert(memcmp("##########  #      ## # # ## ## # #### ## #    # ## # #### ## #    # ## #### # ##      #  ##########", maze, row * col) == 0);

	int x = explore(0, 1, maze);
	printf("%d", x);
	
	fclose(fp);
}

bool explore(int y, int x, char** maze){
	if (x < 0 || y < 0 || x >= COL || y >= ROW){
		return false;
	}
	
	if (y == ROW - 1 && maze[y][x] == ' ') {
		return true;
	}
	
	if (y + 1 < ROW && maze[y+1][x] == ' '){
		maze[y][x] = '#';
		if (explore(y+1, x, maze)){
			return true;
		}
	}
	
	if (x + 1 < COL && maze[y][x+1] == ' '){
		maze[y][x] = '#';
		if (explore(y, x+1, maze)){
			return true;
		}
	}
	
	
	if (x - 1 > 0 && maze[y][x-1] == ' '){
		maze[y][x] = '#';
		if (explore(y, x-1, maze)){
			return true;
		}
	}
	
	if (y - 1 > 0 && maze[y-1][x] == ' '){
		maze[y][x] = '#';
		if (explore(y-1, x, maze)){
			return true;
		}
	}
	
	return false;
}
