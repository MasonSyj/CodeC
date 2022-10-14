#include <stdio.h>
#include <assert.h>

// 1 2 3 5 8 13 21
#define MAXFIB 24

void test();
int fib(int n);


int main(void) {
	test();
	for (int i = 1; i <= MAXFIB; i++){
		printf("%d = %d\n", i, fib(i));
	}
}

int fib(int n){
	
	if (n <= 2){
		return n;
	}else {
		return fib(n - 1) + fib (n - 2);
	}
	
}

void test(){
	assert(fib(1) == 1);
	assert(fib(2) == 2);
	assert(fib(3) == 3);
	assert(fib(4) == 5);
	assert(fib(5) == 8);
	assert(fib(6) == 13);
}
