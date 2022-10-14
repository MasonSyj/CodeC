#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX 36
#define CAPITAL 1000

int odd_even_bet(int money, int number, int result);
int particular_bet(int money, int number, int result);

int main(void){
	srand((unsigned)time(NULL));

	printf("This is a roulette gamble game!! \n");

	int capital = CAPITAL;
	printf("You have $%d as your capital money! \n", capital);	
	int c;
	
	do{	
		int pick, number, money_bet;	

		
		do{		
			printf("Input 1 if you choose to have an odd/even bet, or 2 for particular bet.\n");
		} while(scanf("%d", &pick) == 1 && pick != 1 && pick != 2);

		do{
			printf("What number would you choose. (0-35)");
		} while(scanf("%d", &number) == 1 && number < 0 && number > 35);

		do{		
			printf("How much would you bet.");
		}while(scanf("%d", &money_bet) == 1 && money_bet > capital);
		
		int result = rand () % MAX;
		printf("The roulette machine show number: %d\n", result);
		int money_after;
		switch(pick){
			case 1:money_after = odd_even_bet(money_bet, number, result);break;
			case 2:money_after = particular_bet(money_bet, number, result);break;
			default: printf("Wrong Input!"); 
		}

		capital += money_after;
		printf("Now you have $%d\n", capital);
		printf("Input y/Y to have next round, n to end game.  \n");		
		
		getchar();
		c = getchar();
	} while (capital > 0 && (c == 'y' || c == 'Y'));
}

int odd_even_bet(int money, int number, int result){

	if (result == 0){
		return 0;
	}else if (number % 2 == result % 2){
		return money * 2;
	}else{
		return -1 * money;
	}
}

int particular_bet(int money, int number, int result){

	if (number == result){
		return money * 35;
	}else{
		return -1 * money;
	}
}
