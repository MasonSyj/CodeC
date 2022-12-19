#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


int palinlength(char* c, int i, int j);
char* longestPalindrome(char * s);

int main(void) {
//	char *s = "a";
	puts(longestPalindrome("a"));
}

int palinlength(char* c, int i, int j){
	int palinlength = 0;
	while (j > i){
		if (*(c + i) == *(c + j)){
			palinlength += 2;
			i++;
			j--;
		}else{
			return 0;
		}
	}
	
	if (j == i){
		return palinlength + 1;
	}else{
		return palinlength;
	}
}
char* longestPalindrome(char * s){
	int this = 0;
	int thisi = 0, thisj = 0;
	int z = strlen(s) - 1;
	for (int i = 0; i < z; i++){
		for (int j = z; j >= i; j--){
			int x = palinlength(s, i, j);
			if (x > this){
				this = x;
				thisi = i;
				thisj = j;
			}
			
		}
	}
	int length = thisj - thisi;
	char* a = (char*)malloc((length + 2) * sizeof(char));
	for (int i = 0; i <= length; i++){
		*(a+i) = *(s + thisi + i);
	}
	a[length+1] = '\0';
	return a;
}

//bool ispalinx(char c[]){
//	int i = 0;
//	while (c[i]){
//		i++;
//	}
//	int j = i;
//	i = 0;
//	while (i != j){
//		while (!isalpha(c[i])){
//			i++;
//		}
//		
//		while (!isalpha(c[j])){
//			j--;
//		}
//		
//		if (tolower(c[i]) != tolower(c[j])){
//			return false;
//		}
//		if (i == j){
//			return true;
//		}else{
//			i++;
//			j--;
//		}
//	}
//	return true;
//}
//
//
//int lengthcnteven(char *s, int i){
//	int length = 0;
//	int cnt = 0;
//	while (s[i - cnt] == s[i + 1 + cnt] && i >= cnt && i + 1 + cnt < N ){
//		length += 2;
//		cnt++;
//	}
//	return length;
//}
//
//int lengthcntodd(char *s, int i){
//	int length = 0;
//	int cnt = 0;
//	while (i >= cnt && i + 2 + cnt < N && s[i - cnt] == s[i + 2 + cnt]){
//		length += 2;
//		cnt++;
//	}
//	return length + 1;
//}
//
//int ispalin(char *s){
//	int i = 1;
//	int this;
//	int max;
//	while (s[i]){
//		if (s[i+1]){
//			if (s[i] == s[i + 1]){
//				this = lengthcnteven(s, i);
//				max = max>this?max:this;
//			}
//		}
//		
//		if (s[i+2]){
//			if (s[i] == s[i + 2]){
//				this = lengthcntodd(s, i);
//				max = max>this?max:this;
//			}
//		}
//		
//		i++;
//		
//	}
//	return max;
//}