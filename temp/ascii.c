#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	char s[] = "i love computer architecture";
	int i = 0;
	while (s[i] != '\0'){
		if (isalpha(s[i])){
			s[i] += 0xE0;
		}
		i++;
	}
	puts(s);
	
	char x[] = "i love computer architecture";
	int j = 0;
	while (x[j] != '\0'){
		if (isalpha(x[j])){
			x[j] -= 0x20;
		}
		j++;
	}
	puts(x);
	printf("%d", 0xE0 + 0x20);
}