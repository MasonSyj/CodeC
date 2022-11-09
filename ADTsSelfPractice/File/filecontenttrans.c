#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 3){
		fprintf(stderr, "Usage: %s. <filein> <fileout>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	FILE* fpin = fopen(argv[1], "r");
	if (argv[1] == NULL){
		fprintf(stderr, "Cannot read from %s\n", argv[1]);
		return(EXIT_FAILURE);
	}
	
	FILE* fpout = fopen(argv[2], "w");
	if(argv[2] == NULL){
	    fprintf(stderr, "Cannot write into %s\n", argv[2]);
	}
	
	char c;
	while ((c = fgetc(fpin)) != EOF ){
		fputc(c, fpout);
	}
	
	fclose(fpin);
	fclose(fpout);
	return EXIT_SUCCESS;
}
