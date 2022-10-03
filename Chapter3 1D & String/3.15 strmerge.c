#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>
typedef enum bool {false, true} bool;

void strmerge(const char* s1, const char* s2, char*s3);

#define LARGESTRING 1000

int main(void) {
	char s[LARGESTRING];
//	strmerge("Hello World!", "World! & Everyone.", s); 
//	assert(strcmp(s, "Hello World! & Everyone.")==0);
	
	strmerge("The cat sat", "sat on the mat.", s); 
	assert(strcmp(s, "The cat sat on the mat.")==0);
	
	strmerge("The cat sat on the mat", "The cat sat on the mat.", s); 
	assert(strcmp(s, "The cat sat on the mat.")==0);
	
	strmerge("One ", "Two", s); 
	assert(strcmp(s, "One Two")==0);
	
	strmerge("", "The cat sat on the mat.", s);
	assert(strcmp(s, "The cat sat on the mat.")==0);
	
	strmerge("The cat sat on the mat.", "", s); 
	assert(strcmp(s, "The cat sat on the mat.")==0);
	
	assert(strcmp(s, "123412341234")==0);
}

void strmerge(const char* s1, const char* s2, char*s3){
	int i = 1;
	int lengths1 = strlen(s1);
	int lengths2 = strlen(s2);
	while (i < lengths1 && i < lengths2){
		if (strncmp(s1 + lengths1 - i, s2, i) == 0){
			strcpy(s3, s1);
			strcat(s3, s2 + i);
			exit(0);
		}
		i++;
	}
	
	strcpy(s3, s1);
	strcat(s3, s2);

}
