#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define MAX 100000

bool isPrime(int n);

/**
When you first start thinking about prime numbers, 
it becomes pretty obvious that most of them end with the digit 1,3,7 or 9 
(they can’t end with two, because they can’t be even etc.)

Exercise 1.20.1 Write a program that computes what fraction of all primes end with a 3. 
You can do this by generating a large number of primes, 
in sequence, and keeping a running count of the number that end with 3, as compared to the total of primes generated.
*/

int main(int argc, char *argv[]) {
	
	int allprime, threeprime;
	allprime = threeprime = 0;
	
	for (int n = 2; n < MAX; n++){
		if (isPrime(n)){
			allprime++;
			if (n % 10 == 3){
				threeprime++;
			}
		}	
	}
	
	printf("%d, %d", allprime, threeprime);
//	for (int n = 3; n < MAX; n+=10){
//		if (isPrime(n)){
//			threeprime = 0;
//			printf("%-5d", n);
//		}
//	}
}

bool isPrime(int n){
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0){
			return false;
		}
	}
	return true;
}
