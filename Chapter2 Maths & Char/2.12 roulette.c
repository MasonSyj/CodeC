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
#include <assert.h>

#define result rand() % 36
#define CAPITAL 1000

int odd_even_bet(int money, int number);
int particular_bet(int money, int number);

int main(void){
	srand((unsigned)time(NULL));

	printf("This is a roulette gamble game!! \n");

	int capital = CAPITAL;
	printf("You have $%d as your capital money! \n", capital);	
	int c;
	
	do{	
		int money_final;
		printf("Input 1 if you choose to have an odd/even bet, or 2 for particular bet.\n");
		int pick;
		scanf("%d", &pick);

		printf("What number would you choose. (0-35)");
		int number;
		scanf("%d", &number);

		printf("How much would you bet.");
		int money_bet;
		scanf("%d", &money_bet);

		capital -= money_bet;
		assert(capital >= 0);

		switch(pick){
			case 1:money_final = odd_even_bet(money_bet, number);break;
			case 2:money_final = particular_bet(money_bet, number);break;
			default: printf("Wrong Input!"); 
		}

		capital += money_final;
		printf("Now you have $%d\n", capital);
		printf("Input 0 to have next round, n to end game.  \n");		
		
		scanf("%d", &c);	
	} while (capital > 0 && c == 0);				
			


//		scanf("%c", &c);		
//		char c = getchar();
		
//		getchar();
//		c = getchar();
//	} while (capital > 0 && (c == 'y' || c == 'Y'));
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
