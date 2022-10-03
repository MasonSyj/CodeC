#include <stdio.h>
#include <assert.h>

int twiceTheSumPlusC(int a, int b, int c);
void test();

int main(int argc, char *argv[]) {
//	printf("Input three integers: ");
//	int a, b, c;
//	scanf("%d %d %d", &a, &b, &c);
//	printf("Twice the sum of integers plus %d is %d !\n", c, twiceTheSumPlusC(a, b, c));
	test();
}

int twiceTheSumPlusC(int a, int b, int c){
	return 2 * (a + b + c) + c;
}

void test(){
	assert(twiceTheSumPlusC(2, 3, 5) == 25);
	assert(twiceTheSumPlusC(2, 3, 0) == 10);
	assert(twiceTheSumPlusC(2, 3, -5) == -5);
	assert(twiceTheSumPlusC(2, 3, -6) == -8);
}
