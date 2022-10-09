#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define PHI 1.61803398

void test();
char fibword_subs(int n);
bool fibword_phi(int n);

int main(void){
	test();
	unsigned long i = 1;
	while (fibword_phi(i) == fibword_subs(i) - '0'){
		i++;
	}
	printf("%ld", i);
	
}

void test(){
	assert(fibword_subs(7) == '1');
	assert(fibword_subs(8) == '0');
	assert(fibword_subs(9) == '0');
	assert(fibword_subs(10) == '1');
	assert(fibword_subs(1) == '0');
	assert(fibword_subs(20) == '1');
}

bool fibword_phi(int n){
	return 2 + floor(n * PHI) - floor((n + 1) * PHI);
}

char fibword_subs(int n){
	char* fib = (char*)malloc((n+1) * sizeof(char));
	strcpy(fib, "0");
	int cnt = 1;
	
	for (int i = 0; i <= n; i++){
		if (cnt >= n){
			return fib[n - 1];
		}
		
		if (fib[i] == '0'){
			strcat(fib, "1");
			cnt++;
			if (cnt != n){
				strcat(fib, "0");
				cnt++;
			}
			
		}else if (fib[i] == '1'){
			strcat(fib, "0");
			cnt++;
		}
	}
	char x = fib[n - 1];
	free(fib);
	return fib[n - 1];
}
