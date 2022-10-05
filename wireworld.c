#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 40
#define COL 40

int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1], "r");
	if (!fp){
		fprintf(stderr, "Failed to read file: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}	
	
	char map[ROW][COL + 1];
	
	int i = 0;
	while(fgets(map[i], COL, fp)){
		map[i][strlen(map[i]) - 1] = '\0';
		i++;
	}
	
	for (int i = 0; i < ROW; i++){
		puts(map[i]);
	}
	
	fclose(fp);
	return EXIT_SUCCESS;
}
