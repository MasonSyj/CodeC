#include <stdio.h>
#include <string.h>
#define N strlen(s)

int lengthcnteven(char *s, int i){
	int length = 0;
	int cnt = 0;
	while (s[i - cnt] == s[i + 1 + cnt] && i >= cnt && i + 1 + cnt < N ){
		length += 2;
		cnt++;
	}
	return length;
}

int lengthcntodd(char *s, int i){
	int length = 0;
	int cnt = 0;
	while (i >= cnt && i + 2 + cnt < N && s[i - cnt] == s[i + 2 + cnt]){
		length += 2;
		cnt++;
	}
	return length + 1;
}

int ispalin(char *s){
	int i = 1;
	int this;
	int max;
	while (s[i]){
		if (s[i+1]){
			if (s[i] == s[i + 1]){
				this = lengthcnteven(s, i);
				max = max>this?max:this;
			}
		}
		
		if (s[i+2]){
			if (s[i] == s[i + 2]){
				this = lengthcntodd(s, i);
				max = max>this?max:this;
			}
		}
		
		i++;
		
	}
	return max;
}

int main(int argc, char *argv[]) {
	char *s = "babad";
	int x = ispalin(s);
	printf("%d", x);
}