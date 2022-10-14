#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#define N 20
//assume all chars in the word[] are letters

void test();
void upper(char word[]);
void skipletter(int n, char word[]);
void skiplettercontrol(char word[]);
int code(char c);
void soundex(char word[], char soundex[]);


int main(void){
	test();
}

void test(){
	char temp1[N] = "ajdsfAJKDL_toupper";
	upper(temp1);
	assert(strcmp(temp1, "AJDSFAJKDL_TOUPPER") == 0);
	char temp2[N]= "ABCDFGH";
	skipletter(5, temp2);
	assert(strcmp(temp2, "ABCDFH") == 0);
	
	char word[] = "Washington";
	char Soundex[5];
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "W252") == 0);
	strcpy(word, "Wu");
	strcpy(Soundex, "");
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "W000") == 0);
	strcpy(word, "DeSmet");
	strcpy(Soundex, "");
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "D253") == 0);	
	strcpy(word, "Gutierrez");
	strcpy(Soundex, "");	
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "G362") == 0);
	strcpy(word, "Pfister");
	strcpy(Soundex, "");
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "P236") == 0);
	strcpy(word, "Jackson");
	strcpy(Soundex, "");
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "J250") == 0);
	strcpy(word, "Tymczak");
	strcpy(Soundex, "");
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "T522") == 0);
	strcpy(word, "Ashcraft");
	strcpy(Soundex, "");
	soundex(word, Soundex);	
//	puts(Soundex);
	assert(strcmp(Soundex, "A261") == 0);

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
	if (code(word[0]) == code(word[1])){
		skipletter(1, word);
	}
	
	int i = 1;
	while (word[i] != '\0'){
		
		if (code(word[i]) == code(word[i+1])){
			skipletter(i+1, word);
			i--;
		}
		
		if (word[i] == 'H' || word[i] == 'W'){
			if (code(word[i-1]) == code(word[i+1])){
				skipletter(i+1, word);
			}
		}
		
		if (word[i] == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'O' || word[i] == 'U' || word[i] == 'H' || word[i] == 'W' || word[i] == 'Y'){
			skipletter(i, word);
			i--;
		}	
		i++;
	}
}


int code(char c){
	int code = 0;
		
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
	upper(word);
	skiplettercontrol(word);
//	puts(word);
	soundex[0] = word[0];
	int i = 1;
	int j = 1;
	
	while (word[j] != '\0' && i < 4){
		soundex[i++] = code(word[j++]) + '0';
	}
	
	while (i < 4){
		soundex[i] = '0';
		i++;
	}
	soundex[i] = '\0';
	
}
