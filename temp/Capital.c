#include <stdio.h>

int main(void){
	printf("This program is to translate lower letters to upper.\n");
	printf("Please input your string for transformation. '!' will immediately terminate the program!\n");
	char c;
	while ((c = getchar()) != '!'){
		if (c >= 'a' && c <= 'z'){
			c = c + 'A' - 'a';
		}
		putchar(c);
	}
	putchar('\n');
	return 0;
}
