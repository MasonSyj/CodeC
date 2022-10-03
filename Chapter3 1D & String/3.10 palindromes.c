#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define SIZE 50

int main(void){
	char a[SIZE];
	char c;
	int i = 0;
	while ((c = getchar()) != '\n'){
		if (isalpha(c)){
			a[i] = tolower(c);
			i++;
		}
	}
	a[i--] = '\0';
	puts(a);
	
	bool t = true;
	for (int x = 0; x < i / 2; x++){
		if (a[x] != a[i-x]){
			t = false;
		}
	}
	printf("%d", t);
}
