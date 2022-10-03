#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

bool isvowel(char c);
bool iscvc(char a, char b, char c);
bool isvcv(char a, char b, char c);
bool fequaltot(char a, char c);
bool isprime(char a, char b, char c);

int main(void){
	assert(iscvc('z', 'i', 'c'));
	assert(isvcv('i', 'x', 'e'));
	assert(fequaltot('a', 'a'));
	assert(fequaltot('z', 'z'));
	assert(!fequaltot('a', 'x'));

	int cnt = 1;
	for (char a = 'a'; a <= 'z'; a++){
		for (char b = 'a'; b <= 'z'; b++){
			for (char c = 'a'; c <= 'z'; c++){
				if ((iscvc(a, b, c) || isvcv(a, b, c)) && fequaltot(a, c) && isprime (a, b, c)){
					printf("%2d %c%c%c\n", cnt++, a, b, c);
				}
			}
		}
	}
}

bool isvowel(char c){
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ){
		return true;
	}
	return false;
}

/* consonant-vowel-consonant. */
bool iscvc(char a, char b, char c){
	if (!isvowel(a) && isvowel(b) && !isvowel(c)){
		return true;		
	}
	return false;
}
/* vowel-consonant-vowel. */
bool isvcv(char a, char b, char c){
	if (isvowel(a) && !isvowel(b) && isvowel(c)){
		return true;		
	}
	return false;
}
/* first letter equal to third letter */
bool fequaltot(char a, char c){
	return a == c;
}

bool isprime(char a, char b, char c){
	/* a = 1, b = 2 */
	int value = a + b + c - 'a' - 'a' - 'a' + 3;
	for (int i = 2; i <= sqrt(value); i++){
		if (value % i == 0){
			return false;		
		}
	}
	return true;
}
