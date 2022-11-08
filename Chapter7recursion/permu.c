#include <stdio.h>
#include <string.h>

#define N (int) strlen(s)

void permu(char* s, int i, char list[][5]);
void swap(char* a, char* b);

int cnt = 0;

int main(void) {
	char s[] = "ABCD";
	char list[24][5];
	permu(s, 0, list);
	for (int i = 0; i < 24; i++){
		puts(list[i]);
	}
}

void permu(char* s, int i, char list[][5]){
	if (i == N){
//		puts(s);
		strcpy(list[cnt++],s);
	}
	
	for (int x = i; x <= N - 1; x++){
		swap(s+i, s+x);
		permu(s, i+1, list);
		swap(s+i, s+x);
	}
}

void swap(char* a, char* b){
	char temp = *a;
	*a = *b;
	*b = temp;
}
