#include <stdio.h>

void swap(char word[]);
int value(char c);
int sum(char word[]);

int main(void){
	char word[] = "MCDXCI";
	swap(word);
	int x = sum(word);
	printf("%d", x);
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
	int value;
	if (c == 'A')
		value = 1;
	else if (c == 'B')
		value = 5;	
	else if (c == 'C')
		value = 10;
	else if (c == 'D')
		value = 50;
	else if (c == 'E')
		value = 100;
	else if (c == 'F')
		value = 500;
	else if (c == 'G')
		value = 1000;
	return value;
}

int sum(char word[]){
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
