#include <stdio.h>
#include <stdlib.h>
int main(void){
	FILE* fp = fopen("helloworld.txt", "w");
	if (fp == NULL){
		fprintf(stderr,"can't open this file.\n");
		exit(EXIT_FAILURE);
	} 
	fprintf(fp, "Hello world!\n");
	fclose(fp);
	return EXIT_SUCCESS;
}
