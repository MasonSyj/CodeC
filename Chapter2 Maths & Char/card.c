#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SUIT 4
#define PERSUIT 13
#define DECK (SUIT * PERSUIT)

typedef enum suit {diamond, spade, hearts, clubs} suit;

struct card{
	suit color;
	int value;
};

typedef struct card card;

void test();
void init_card(card c[]);
void shuffle(card c[]);
void print_card(card c[], int n);
void print_All(card c[]);

int main(void){
	srand((unsigned)time(NULL));
	card c[DECK];
	init_card(c);
//	print_All(c);
	shuffle(c);
	print_card(c, 10);
	return 0;
}

void init_card(card c[]){
	for (int i = 0; i < DECK; i++){
		c[i].value = (i % PERSUIT) + 1;
		c[i].color = (i / PERSUIT); 
	}
}

void shuffle(card c[]){
	for (int i = 0; i < DECK; i++){
		card temp = c[i];
		c[i] = c[rand() % (DECK - i) + i];
		c[rand() % (DECK - i) + i] = temp;
	}
}

// printt first n cards
void print_card(card c[], int n){
	for (int i = 0; i < n; i++){
		printf("%d of ", c[i].value);
		switch(c[i].color){
			case 0:printf("diamond\n");break;
			case 1:printf("spade\n");break;
			case 2:printf("hearts\n");break;
			case 3:printf("clubs\n");break;
		}
	}
} 

void print_All(card c[]){
	for (int i = 0; i < DECK; i++){
		printf("%d of %d\n", c[i].value, c[i].color);
	}
}


