#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

enum value{I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000};
typedef enum value value;

void test();
int romanvalue(char word[]);
int lettervalue(char c);

int main(void){
	test();
}

int romanvalue(char word[]){
	int sum = 0;
	int len = strlen(word);
	int* x = (int* )malloc((len) * sizeof(int));
	for (int i = 0; i < len; i++){
		x[i] = lettervalue(word[i]);
	}
	for (int i = 0; i < len; i++){
		if (i == len - 1){
			sum += x[len-1];
			i++;
		}else if (x[i] < x[i+1]){
			sum += x[i+1] - x[i];
			i++;
		}else{
			sum += x[i];
		}
		
	}
	free(x);
	return sum;
}

int lettervalue(char c){
	if (c == 'I'){
		return I;	
	}else if (c == 'V'){
		return V;
	}else if (c == 'X'){
		return X;
	}else if (c == 'L'){
		return L;
	}else if (c == 'C'){
		return C;
	}else if (c == 'D'){
		return D;
	}else if (c == 'M'){
		return M;
	}else {
		return 0;
	}
}

void test(){
	assert(lettervalue('I') == I);
	assert(lettervalue('X') == X);
	assert(lettervalue('D') == D);
	assert(romanvalue("MCMXCIX") == 1999);
	assert(romanvalue("MCMLXVII") == 1967);
	assert(romanvalue("MCDXCI") == 1491);
}
