#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/** 
Exercise 1.11.1 Write a program that selects a random number between 1 and 1000. 
The user is asked to guess this number. If this guess is correct, 
the user is told that they have chosen the correct number and the game ends. 
Otherwise, they are told if their guess was too
high or too low. 
The user has 10 goes to guess correctly before the game ends and they lose. 
*/

int main(void){
	srand((unsigned)time(NULL));
	
	int num = rand() % 1001;	
	int cnt = 0;
	int guessNum;
	printf("Random number generated, try to guess!");
	do {
		scanf("%d", &guessNum);
		if (guessNum < num){
			printf("too low\n");		
		}
		else if (guessNum > num){
			printf("too high\n");
		}
		else{
			printf("You are correct, and you tried %d times", ++cnt);
			break;
		}
		cnt++;
	}while (1);
	
	
	return 0;
}
