#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
// 1 	2 	3 	5 	8 	13 21
// 1 	3 	6 	11	19	32 53
// 0 10 010 10010 01010010 
void test();
bool fibword_str(int n);

int main(){


	test();
	int x = 1;
	while (x++ < 10000){
		printf("%-3d", fibword_str(x));
	}
//	int i = 1200000000;
//	printf("%-3d", fibword_str(i));

}

bool fibword_str(int n){
	if (n == 1){
		return false;
	}else if (n == 2){
		return true;
	}
	int size = n;
	char* a = (char*)malloc((size) * sizeof(char));
	char* b = (char*)malloc((size) * sizeof(char));
	char* c = (char*)malloc((size) * sizeof(char));
	strcpy(a, "");
	strcpy(b, "");
	strcpy(c, "");
	a[0] = b[1] = c[0] = '0';
	b[0] = '1';
	int t = n;
	a[t] = b[t] = c[t] = '\0';
	int cnt, cnta, cntb;
	cnt = cnta = 1;
	cntb = 2;
	int sum = 1;
	
	
	while (sum + cnta + cntb < n){
		sum += cnta;
		
		strcpy(c, a);
		strncat(c, b, cntb);
		
		cnt = cnta + cntb;
		cnta = cntb; 
		cntb = cnt;
		
		strcpy(a, b);
		strcpy(b, c);
	}
	
	char x;
	if (n < sum + cnta){
		x = a[cnta - sum + n];
	}else{
		x = b[n- sum -cnta];
	}
	
	
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
	assert(fibword_str(21) == false);
	assert(fibword_str(19) == false);
}
