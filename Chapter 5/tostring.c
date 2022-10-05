#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL){
		fprintf(stderr, "Cannot read %s", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	char a[MAX + 1];
	int i = 0;
	char c;
	int row = 0;
	int cnt = 0;
	while ((c = fgetc(fp)) != EOF){
		a[i++] = c;
		if (c == '\n'){
			row++;
		}
		cnt++;
	}
	a[i] = '\0';

	int col = cnt / row;
	char b[row][col + 1];
	
	int x = 0;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			b[i][j] = a[x++];
		}
		b[i][col] = '\0';
	}
	
	for (int i = 0; i < row; i++){
		printf("%s", b[i]);
	}
	
	fclose(fp);
	return EXIT_SUCCESS;
}
