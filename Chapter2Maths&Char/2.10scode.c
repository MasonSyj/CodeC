#include <stdio.h>
#include <assert.h>

int scode(int a);

int main(void){
	assert(scode('a') == 'z');
	assert(scode('A') == 'Z');
	assert(scode('b') == 'y');
	assert(scode('c') == 'x');
	char a[] = "The Quick Brown Fox Jumps Over the Lazy Dog !";
	int i = 0;
	while (a[i] != '\0'){
		printf("%c", scode(a[i++]));
	}

}

int scode(int a){
	if (a >= 'a' && a <= 'z'){
		a = 'z' - a + 'a';
	}else if (a >= 'A' && a <= 'Z'){
		a = 'Z' - a + 'A';
	}
	return a;
}


