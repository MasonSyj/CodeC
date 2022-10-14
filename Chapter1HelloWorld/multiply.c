#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int multiply(int a, int b){
	int value = 0;
	
	if (a == 0 || b == 0){
		value = 0;
	}
	
	for (int i = 0; i < abs(b); i++){
			value += a;
	}
	
	if ((a > 0 && b > 0) || (a < 0 && b < 0)){
		value = abs(value);
	}else{
		value = -abs(value);
	}
	
	return value;
}

int main(int argc, char *argv[]) {
	assert(multiply(4, 5) == 20);
	assert(multiply(-4, 5) == -20);
	assert(multiply(4, -5) == -20);
	assert(multiply(-4, -5) == 20);
	assert(multiply(4, 0) == 0);
	assert(multiply(0, 0) == 0);
	assert(multiply(5, 0) == 0);
}

