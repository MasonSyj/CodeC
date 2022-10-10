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
	for (int i = 5; i <= 100000; i++){
		printf("%-3d", fibword_str(i));
	}
}

bool fibword_str(int n){
	if (n == 1){
		return false;
	}else if (n == 2){
		return true;
	}
	char* a = (char*)malloc((2 * n + 1) * sizeof(char));
	char* b = (char*)malloc((2 * n + 1) * sizeof(char));
	char* c = (char*)malloc((2 * n + 1) * sizeof(char));
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
	
	
	while (sum < n){
		sum += cnta;
		if (sum > n){
			break;
		}
		strcpy(c, a);
		strncat(c, b, cntb);
		
		cnt = cnta + cntb;
		cnta = cntb; 
		cntb = cnt;
		
		
		
		strcpy(a, b);
		strcpy(b, c);
		
		
	}
	
	
	char x = a[cnta - sum + n];
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
