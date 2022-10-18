#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE* fp = fopen("filetobewritten", "w");
	if (fp == NULL){
		printf("Failed to open file.\n");
		exit(EXIT_FAILURE);
	}
	
	char c;
	while ((c = getchar()) != EOF){
		fputc(c, fp);	
	}
	
	fclose(fp);
	exit(EXIT_SUCCESS);
}
