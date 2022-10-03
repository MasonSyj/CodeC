#include <stdio.h>
#include <math.h>
#include <assert.h>

#define PI 3.14159265

#define CONSTANTSINCOS(x) (sin(x * PI / 180) * sin(x * PI / 180) + cos(x * PI / 180) * cos(x * PI / 180)) 

void test();

int main(void){
	test();
	return 0;
}

void test(){
	assert(CONSTANTSINCOS(50) == 1);
	assert(CONSTANTSINCOS(60) == 1);
	assert(CONSTANTSINCOS(70) == 1);
	assert(CONSTANTSINCOS(80) == 1);
	assert(CONSTANTSINCOS(0) == 1);
}
