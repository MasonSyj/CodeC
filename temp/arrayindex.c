#include <stdio.h>

void printeach(char* a);
//swap
//summing an array

int main(void){
	char a[] = "Hello World!";
	printeach(a);
	putchar(*a);
	putchar(*(a++));
}

void printeach(char* a){
	while (*a){
		putchar(*a);
		a++;
	}
}


