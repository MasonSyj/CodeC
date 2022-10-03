#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
Modify the program you wrote for Exercise 1.8.1 so that all variables are of type int, 
even numbers are ignored and only odd integers are processed. 
Explain all this to the user via appropriate printf() statements.
*/

int findMax(int cnt);

int main(int argc, char *argv[]) {
//	printf("%d mod %d == %d\n", -1, 2, (-1 % 2));
	int cnt;
	printf("Even numbers are ignored and only odd integers are processed. \n");
	printf("How many numbers do you wish to enter ? ");
	scanf("%d", &cnt);
	assert(cnt > 0);
	printf("Max of %d numbers is %d",cnt, findMax(cnt));
}


int findMax(int cnt){
	int max;
	int num;
	bool flag = false;
	printf("Enter %d int numbers: ", cnt);
	int i = 0;
	while(i != cnt+1 && scanf("%d", &num) > 0){
		if (flag == false && abs(num % 2) == 1){
			max = num;
			flag = true;
			i++;
		}
		
		if (flag == true &&  abs(num % 2) == 1){
			if (num > max){
				max = num;				
			}
			i++;
		}
		
	}
	return max;
}
