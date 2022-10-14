#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000000000
#define R 2

double dart(long limit);
	

int main(void){
	srand((unsigned)time(NULL));
	double pi = dart(N);
	printf("Dart times : %ld, Approximation for PI: %f", N, pi);
}

double dart(long limit){
	double p1, p2;
	p1 = p2 = 0;
	while (limit-- > 0){
		double x = ((double) rand () /(double) (RAND_MAX)) * R; 
		double y = ((double) rand () /(double) (RAND_MAX)) * R; 
		if (x * x + y * y <= R * R){
			p1++;
			p2++;
		}else{
			p2++;
		}
	}
	return 4.0 * p1 / p2;
}