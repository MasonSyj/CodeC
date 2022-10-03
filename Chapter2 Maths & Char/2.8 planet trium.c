#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

bool isvowel(char c);


int main(void){

	char x, y, z;
	int cnt = 1;
	for (x = 'a'; x <= 'z'; x++){
		for (y = 'a'; y <= 'z'; y++){
			for (z = 'a'; z <= 'z'; z++){
				if (!isvowel(x) && isvowel(y) && !isvowel(z)){
					printf("%d ", cnt++);
					putchar(x);
					putchar(y);
					putchar(z);
					printf("\n");
				}
			}
		}
	}
}


bool isvowel(char c){
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
		return true;
	}
	return false;
}


