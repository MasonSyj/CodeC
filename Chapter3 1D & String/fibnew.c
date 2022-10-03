#include <stdio.h>
#include <string.h>
#define N 50

void create(int x);

int main(int argc, char *argv[]) {
	create(N);
}

void create(int x){
	char a[2 * N] = "0";
	char b[2 * N] = "01";
	char c[2 * N];
	
	while (strlen(b) < N){
		strcpy(c, b);
		strcat(c, a);
		strcpy(a, b);
		strcpy(b, c);
	}
	printf("%c", b[48]);
}