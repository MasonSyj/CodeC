#include <stdio.h>
#include <ctype.h>
int main(void){
	char c;
	while ((c = getchar()) != EOF){
		if (islower(c)){
			c = toupper(c);
		}
		
		putchar(c);
	}
}
