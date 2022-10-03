#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void createcontro(int n);
//void createorigin();
char* createnew(int x, int y, char* a, char* b);

int main(void){
	createcontro(20);
}

void createcontro(int n){
	int x = 1;
	int y = 2;
	char* a = (char *)malloc(x * sizeof(char));
	char* b = (char *)malloc(y * sizeof(char));
	*a = '0';
	*b = '0';
	*(b+1) = '1';
	
	int length;
	do {
//		length = createnew(x, y, a, b);
//		char* c = (char *)malloc(length * sizeof(char));
		char* c = createnew(x, y, a, b);
		int length = x + y;
		x = y;
		y = length;
		char* a = (char *)malloc(x * sizeof(char));
		strcpy(a, b);
		free(b);
		char* b = (char *)malloc(y * sizeof(char));
		strcpy(b, c);
		free(c);
	}while (length < n);
	puts(b);
}

//void createorigin(){
//	int x = 1;
//	int y = 2;
//	char* a = (char *)malloc(x * sizeof(char));
//	char* b = (char *)malloc(y * sizeof(char));
//	*a = '0';
//	*b = '1';
//	*(b+1) = '0';
//	puts(a);
//	puts(b);
//}

char* createnew(int x, int y, char* a, char* b){
	int z = x + y;
	char* c = (char *)malloc(z * sizeof(char));
	strcpy(c, b);
	strcat(c, a);
	return c;
}
