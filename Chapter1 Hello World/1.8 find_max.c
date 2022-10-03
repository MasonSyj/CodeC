#include <stdio.h>

/**
Exercise 1.8.1 Write a program that finds the largest number entered by the user. 
Executing the program will produce something like:
How many numbers do you wish to enter ? 5 
Enter 5 real numbers: 1.01 −3 2.2 7.0700 5 
Maximum value: 7.07
*/

double findMax(int cnt);

int main(void) {
	int cnt;
	printf("How many numbers do you wish to enter ? ");
	scanf("%d", &cnt);
	double max = findMax(cnt);
	printf("Maximum value: %f", max);
}

double findMax(int cnt){
	double max;
	double num;
	printf("Enter %d real numbers: ", cnt);
	int i = 0;
	while(i != cnt && scanf("%lf", &num) > 0){
		if (i == 0){
			max = num;
		}
		
		if (num > max){
			max = num;
		}
		i++;
	}
	return max;
}
