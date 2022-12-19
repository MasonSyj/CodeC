#include <stdio.h>
#include <math.h>
#include <assert.h>

int reverse(long x);

int main(void) {
	assert(reverse(321) == 123);
	assert(reverse(-123) == -321);
	assert(reverse(120) == 21);
}

int reverse(long x){
	int flag = 1;
	if (x < 0){
		flag = -1;
		x = -1 * x;
	}
	
	long sum = 0;
	while (x > 0){
		sum = sum * 10 + x % 10;
		x /= 10;
	}
	sum *= flag;   
	if (sum < -1 * pow(2, 31) || sum >= pow(2, 31)){
		return 0;
	}
	
	return sum;
}
