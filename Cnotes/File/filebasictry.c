#include <stdio.h>

int main(void){
	FILE *fp = fopen("filebasictry.txt", "w+r");
	if (fp == NULL){
		printf("File open failed.\n");
		return 0;
	}
	
	char c = fgetc(fp);
	while (c != EOF){
		putchar(c);
		c = fgetc(fp);
	}
	
	char x = getchar();
	while (x != '\n'){
		fputc(x, fp);
		x = getchar();
	}
	
	fclose(fp);
}
