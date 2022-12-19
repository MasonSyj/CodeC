#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char * s, char * p){
	bool result = true;
	while (1){
		int i = 0;

		if (*p == '.'){
			s++;
			p++;
			continue;
		}else if (*p == '*'){
			if (*(p-1) == '.'){
				return isMatch(s + 1, p + 1);
			}
			while (*s == *(s-1)){
				s++;
			}
			p++;
		}
		
		if (*p != *s){
			result = false;
			break;
		}
		if (*p == '\0' && *s == '\0'){
			break;
		}
		s++;
		p++;
	}
	
	return result;
}

int main(int argc, char *argv[]) {
	char a[] = "ac";
	char b[] = "a*c";
//	int x = strlen(a);
//	int y = strlen(b);
//	printf("%d, %d", x, y);
	printf("%d", isMatch(a, b));
	
}