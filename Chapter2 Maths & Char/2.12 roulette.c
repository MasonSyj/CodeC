// rand 0 - 35
// bet choice three:
// one: odd
// two: even
// three: particular

//result
// first: pick particular one correctly win 35 times to 1
// second: pick 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define result  rand() % 36

int odd_even_bet(int money, int number);
int particular_bet(int money, int number);

int main(void){
	srand((unsigned)time(NULL));
	printf("This is a roulette gamble game!! \n");
	printf("Input 1 if you choose to have an odd/even bet, or 2 for particular bet.\n");
	int pick;
	scanf("%d", &pick);
	printf("What number would you choose. (0-35)");
	int number;
	scanf("%d", &number);
	printf("How much would you bet.");
	int money_bet;
	scanf("%d", &money_bet);
	int money_final;
	switch(pick){
		case 1:money_final = odd_even_bet(money_bet, number);break;
		case 2:money_final = particular_bet(money_bet, number);break;
		default: printf("Wrong Input!"); 
	}
	printf("now you have $%d", money_final);
}

int odd_even_bet(int money, int number){
	if (result == 0){
		return 0;
	}else if (number % 2 == result % 2){
		return money * 2;
	}else{
		return 0;
	}
}

int particular_bet(int money, int number){
	if (number == result){
		return money * 35;
	}else{
		return 0;
	}
}
