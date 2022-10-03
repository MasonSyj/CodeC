#include <stdio.h>
#define HEIGHT 10

void printLetterC(int height);

int main(int argc, char *argv[]) {
	printLetterC(HEIGHT);
	printLetterC(HEIGHT * 2);
}

void printLetterC(int height){
	int i = 0;
	printf("\n\nIIIIIIIII"); 
	printf("IIIIIIIII\n"); 
	while(i < HEIGHT){ 
		printf(" III\n");
		i = i + 1;
	} 
	printf("IIIIIIIII"); 
	printf("IIIIIIIII\n"); 
}
