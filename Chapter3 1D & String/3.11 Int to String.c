#include <stdio.h>
#include <string.h>
void int2string(int i, char s[]);

int main(int argc, char *argv[]) {
	int x = 123456;
	char s[256];
//	char a1[4] = "abc";
//	char a2[4] = "123";
//	a1[0] = a2[0];
//	puts(a1);
	int2string(x, s);
	puts(s);
}

void int2string(int i, char s[]){
	int cnt = 0;
	while (i > 0){
		s[cnt++] = i % 10 + '0';
		i /= 10;
	}
	s[cnt--] = '\0';
	for (int i = 0; i <= cnt / 2; i++){
		char temp = s[i];
		s[i] = s[cnt - i];
		s[cnt - i] = temp;
	}
}