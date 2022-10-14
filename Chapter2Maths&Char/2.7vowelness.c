#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

void test();
bool isvowel(char c);

int main(void){
	test();

}

bool isvowel(char c){
	c = tolower(c);
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
		return true;
	}
	return false;
}

void test(){
	assert(isvowel('a') == 1);
	assert(isvowel('i') == 1);
	assert(isvowel('o') == 1);
	assert(isvowel('a') == 1);
	assert(isvowel('x') == 0);
}
