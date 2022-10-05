#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL){
		printf("File accessed failed.\n");
		exit(EXIT_FAILURE);
	}
	
	char c;
	while ((c = fgetc(fp)) != EOF){
		putchar(c);
	}
	
	fclose(fp);
	return EXIT_SUCCESS;
}
