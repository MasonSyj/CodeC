#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

void test();
bool isPrime(int n);
void firstNPrimes(int n);

int main(void){
//	printf("Input n to output first n primes. ");
//	int n;
//	scanf("%d", &n);

	test();
}

void test(){
	assert(isPrime(2) == 1);
	assert(isPrime(3) == 1);
	assert(isPrime(4) == 0);
	assert(isPrime(5) == 1);
	assert(isPrime(19) == 1);
	assert(isPrime(100) == 0);
}

bool isPrime(int n){
	assert(n>1);
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0){
			printf("Not Prime\n");
			return false;		
		}
	}
	return true;
}

void firstNPrimes(int n){
	int num = 2;	
	int i = 0;
	while (i < n){
		if (isPrime(num)){
			printf("%d", num);
			i++;
		}
		num++;
	}
}
