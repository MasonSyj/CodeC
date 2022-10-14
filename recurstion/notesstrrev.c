#include <stdio.h>
#include <string.h>

#define SWAP(A,B) {char temp; temp = A; A = B; B = temp;}

void swap(char a, char b);
void strrev(char* s, int n);

int main(void) {
	char str[] = "Hello World!";
	swap(str[0], str[1]);
	puts(str);
	SWAP(str[0], str[1]);
	puts(str);
//	strrev(str, strlen(str));
//	puts(str);
	return 0;
}

void strrev(char* s, int n){
	for (int i = 0, j = n - 1; i < j; i++, j--){
		SWAP(s[i], s[j]);
	}
}

void swap(char a, char b){
	char temp = a;
	a = b;
	b = temp;
}
