#include <stdio.h>
#include <assert.h>

void test();
int recursion(int x);

int main(void){
	test();
	return 0;
}

int recursion(int x){
	if (x == 0){
		return 1;
	}else {
		return x * recursion(x - 1);
	}
}

void test(){
	assert(recursion(0) == 1);
	assert(recursion(1) == 1);
	assert(recursion(2) == 2);
	assert(recursion(3) == 6);
	assert(recursion(4) == 24);	
}
