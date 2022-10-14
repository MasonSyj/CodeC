#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void test();
bool isTriangle(int a, int b, int c);
void makeCBiggest(int* a, int* b, int* c);

int main(void){


	test();
	}

void test(){
	assert(isTriangle(1, 1, 1) == true);
	assert(isTriangle(3, 4, 5) == true);
	assert(isTriangle(5, 4, 3) == true);
	assert(isTriangle(3, 4, 6) == true);
	assert(isTriangle(-1, 2, 3 == false));
	assert(isTriangle(2, 4, 6) == false);
	
}

bool isTriangle(int a, int b, int c){
	makeCBiggest(&b, &a, &c);
	if (a > 0 && b > 0 && c > 0 && a + b > c){
		return true;	
	}
	return false;
}

void makeCBiggest(int* a, int* b, int* c){
	int temp;
	//make b bigger than a
	if (a > b){
		temp = *b;
		*b = *a;
		*a = temp;
	}

	if (c < b){
		temp = *c;
		*c = *b;
		*b = temp;
	}
}


