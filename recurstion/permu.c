#include <stdio.h>
#include <string.h>

#define N strlen(s)

void permu(char* s, int i);
void swap(char* a, char* b);

int main(void) {
	char s[] = "XYZ";
	permu(s, 0);
}

void permu(char* s, int i){
	if (i == N){
		puts(s);
	}
	
	for (int x = i; x <= N - 1; x++){
		swap(s+i, s+x);
		permu(s, i+1);
		swap(s+i, s+x);
	}
}

void swap(char* a, char* b){
	char temp = *a;
	*a = *b;
	*b = temp;
}
