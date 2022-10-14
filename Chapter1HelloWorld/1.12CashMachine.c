#include <stdio.h>
#include <stdlib.h>

/** Some cash dispensers only contain £20 notes. 
When a user types in how much money they’d like to be given, 
you need to check that the amount requested can be dispensed exactly using only £20 notes. 
If not, a choice of the two closest (one lower, one higher) amounts is presented.
*/

/**
	How much money would you like ? 	
	if 175, show 160 and 180
	I can give you 160 or 180 , try again .
	175 % 20 == 8(n)
	n * 20 and (n + 1) *20
	else if 180
	OK , dispensing ...
*/

int main(void){
	
	int value;

	
	while (1){
		printf("How much money would you like ? ");	
		scanf("%d", &value);
		if (value % 20 == 0){
			printf("OK , dispensing ...");
			break;
		}else{
			int divisor = value / 20;
			printf("I can give you %d or %d , try again .\n", divisor * 20, (divisor + 1) * 20); 
		}
	}	
	
	return 0;
}
