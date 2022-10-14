#include <stdio.h>
#include <stdlib.h>

void swap(char* a, char* b);
void strrev(char* c);

int main(void) {
	char p[] = "Hello World!";
//	swap(p, p+1);
	puts(p);
	strrev(p);
//	char *c = p;

	puts(p);
}

void swap(char* a, char* b){
	char temp = *a;
	*a = *b;
	*b = temp;

}

void strrev(char* c){
	while (*(c+1)){
		swap(c, c+1);
		c++;
	}
}
