#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#define N 20
//assume all chars in the word[] are letters

void test();
void upper(char word[]);
void skipletter(int n, char word[]);
void skiplettercontrol(char word[]);
int code(char c);
void soundex(char word[], char soundex[]);


int main(void){
	char word[] = "DeSmet";
	char sound[5];
	upper(word);
	skiplettercontrol(word);
	puts(word);
	soundex(word, sound);	
	puts(sound);
}

void test(){
}

void upper(char word[]){
	int i = 0;
	while (word[i] != '\0'){
		word[i] = toupper(word[i]);
		i++;
	}
}

void skipletter(int n, char word[]){
	while (word[n] != '\0'){
		word[n] = word[n+1];
		n++;
	}
}

void skiplettercontrol(char word[]){
	char temp[N];
	int i = 1;
	while (word[i] != '\0'){
		
		if (word[i] == 'H' || word[i] == 'W'){
			if (code(word[i-1]) == code(word[i+1])){
				skipletter(i+1, word);
			}
		}
		
		if (word[i] == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'O' || word[i] == 'U' || word[i] == 'H' || word[i] == 'W' || word[i] == 'Y'){
			skipletter(i, word);
		}	
		i++;
	}
}


int code(char c){
	int code;
		
	if (c == 'B' || c == 'F' || c == 'P' || c == 'V'){
		code = 1;
	}else if (c == 'C' || c == 'G' || c == 'J' || c == 'K' || c == 'Q' || c == 'S' || c == 'X' || c == 'Z'){
		code = 2;
	}else if (c == 'D' || c == 'T'){
		code = 3;
	}else if (c == 'L'){
		code = 4;
	}else if (c == 'M' || c == 'N'){
		code = 5;
	}else if (c == 'R'){
		code = 6;
	}
	
	return code;
}

void soundex(char word[], char soundex[]){
	soundex[0] = word[0];
	int i = 1;
	int j = 1;
	
	while (word[j] != '\0' && i < 4){
		soundex[i++] = code(word[j++]) + '0';
	}
	
	while (i++ < 4){
		soundex[i] = '0';
	}
	soundex[i] = '\0';
	
}
