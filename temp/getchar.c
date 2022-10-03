#include <stdio.h>

int main(void){
	printf("please input a string which each letter will output twice: \n");
	printf("Input '!' to terminate.\n");
	char c;
	do{
		c = getchar();
		putchar(c);
		putchar(c);
	}while (c != '!');
	putchar('\n');
	
}
