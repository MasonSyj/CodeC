#include <stdio.h>
#include <assert.h>

void test();
int multirecursion(int a, int b);

int main(void){
	test();
	return 0;
}

int multirecursion(int a, int b){
	int value;
	if (a == 0){
		return 0;
	}else if (a > 0){
		value = b + multirecursion(a - 1, b); 
	}else{
		value = - multirecursion(-a, b);
	}
	return value;
}

void test(){
	assert(multirecursion(5, 4) == 20);
	assert(multirecursion(5, -4) == -20);
	assert(multirecursion(-5, 4) == -20);
	assert(multirecursion(-5, -4) == 20);
	assert(multirecursion(-5, 0) == 0);
	assert(multirecursion(0, -5) == 0);
}
