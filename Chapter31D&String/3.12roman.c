#include <stdio.h>
#include <assert.h>

void test();
void swap(char word[]);
int value(char c);
int sum(char word[]);

enum roman{A = 1, B = 5, C = 10, D = 50, E = 100, F = 500, G = 1000};
typedef enum roman roman;

int main(void){
	char word[] = "MDCCXXXII";
	int x = sum(word);
	printf("%d\n", x);
	char word2[] = "MCMXCIX";
	int y = sum(word2);
	printf("%d\n", y);
	printf("%d", sum("ABCDFG"));
//	test();
}


void swap(char word[]){
	int i = 0;
	while (word[i] != '\0'){
		if (word[i] == 'I')
			word[i] = 'A';
		else if (word[i] == 'V')
			word[i] = 'B';
		else if (word[i] == 'X')
			word[i] = 'C';
		else if (word[i] == 'L')
			word[i] = 'D';
		else if (word[i] == 'C')
			word[i] = 'E';
		else if (word[i] == 'D')
			word[i] = 'F';
		else if (word[i] == 'M')
			word[i] = 'G';
		i++;
	}
}

int value(char c){
	int value = 0;
	if (c == 'A')
		value = A;
	else if (c == 'B')
		value = B;	
	else if (c == 'C')
		value = C;
	else if (c == 'D')
		value = D;
	else if (c == 'E')
		value = E;
	else if (c == 'F')
		value = F;
	else if (c == 'G')
		value = G;
	return value;
}

int sum(char word[]){
//	swap(word);
	int i = 0;
	int sum = 0;
	while (word[i] != '\0'){
		if (word[i] < word[i+1]){
			sum += value(word[i+1]) - value(word[i]);
			i++;
		}else {
			sum += value(word[i]);
		}
		i++;
	}
	
	return sum;
}

void test(){
	assert(sum("MCMXCIX") == 1999);
	assert(sum("MCMLXVII") == 1967);
	assert(sum("MCDXCI") == 1491);
}
