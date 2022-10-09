#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void test();
bool fibword_str(int n);

int main(){
	test();

	bool x = fibword_str(20);
	printf("%d", x);
}

bool fibword_str(int n){
	char* a = (char*)malloc((2 * n) * sizeof(char));
	char* b = (char*)malloc((2 * n) * sizeof(char));
	char* c = (char*)malloc((2 * n) * sizeof(char));
	int t = 2 * n - 1;
	a[t] = b[t] = c[t] = '\0';
	strcpy(a, "");
	strcpy(b, "");
	strcpy(c, "");
	a[0] = b[1] = c[0] = '0';
	b[0] = '1';
	int cnt, cnta, cntb;
	cnt = cnta = 1;
	cntb = 2;
	while (cnt < n){
		strcpy(c, a);
		strncat(c, b, cntb);
		cnt = cnta + cntb;
		cnta = cntb; 
		cntb = cnt;
		strcpy(a, b);
		strcpy(b, c);
	}
	char x = c[cnt-n];
	free(a);
	free(b);
	free(c);
	return (bool)(x - '0');
}

void test(){
	assert(fibword_str(7) == true);
	assert(fibword_str(8) == false);
	assert(fibword_str(9) == false);
	assert(fibword_str(10) == true);
	assert(fibword_str(1) == false);
	assert(fibword_str(20) == true);
}
