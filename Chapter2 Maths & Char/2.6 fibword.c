#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define RATIO 1.61803398875

bool fibword_phi(int n);
void test();


int main(void){
	test();
}

bool fibword_phi(int n){
	return 2 + floor(n * RATIO) - floor((n + 1) * RATIO);
}

void test(){
	assert(fibword_phi(1) == 0);
	assert(fibword_phi(2) == 1);
	assert(fibword_phi(3) == 0);
	assert(fibword_phi(4) == 0);
	assert(fibword_phi(5) == 1);
}
