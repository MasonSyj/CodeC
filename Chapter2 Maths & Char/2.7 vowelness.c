#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

void test();
bool isvowel(char c);
char writeletter(char c);

int main(void){
	test();
	char c;
	while ((c = getchar()) != '!'){
		putchar(writeletter(c));
	}
}


bool isvowel(char c){
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
		return true;
	}
	return false;
}

char writeletter(char c){
	if (isvowel(c)){
		c = toupper(c);
	}
	return c;
}

void test(){
	assert(isvowel('a') == 1);
	assert(isvowel('i') == 1);
	assert(isvowel('o') == 1);
	assert(isvowel('a') == 1);
	assert(isvowel('x') == 0);
}
