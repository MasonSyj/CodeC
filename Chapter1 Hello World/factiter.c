#include <stdio.h>
#include <assert.h>

int iter(int x);
void test();

int main(void){
//	printf("%d",  iter(0));
//	printf("%d",  iter(1) );
	test();
	return 0;
}

int iter(int x){
	int value = 1;
	while(x>0){
		value *= x--;
	}
	return value;
}

void test(){
	assert(iter(0) == 1);
	assert(iter(1) == 1);
	assert(iter(2) == 2);
	assert(iter(3) == 6);
	assert(iter(4) == 24);	
}
