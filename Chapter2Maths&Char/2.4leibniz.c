#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define D 0.00000001
#define PI 3.14159265

double leibniz(long n);
double nthleibniz(long n);
bool difference(double a, double b, double range);

int main(void){
	long i = 1;
	double leibnizsum = nthleibniz(i);
	while (!difference(leibnizsum, PI, D)){
		i++;
		leibnizsum += nthleibniz(i);
	}
	printf("%ld", i);
}

double leibniz(long n){
	int opt = 1;
	double sum = 0;
	for (long i = 1; i <= n; i++){
		long fenmu = 2 * i - 1;
		sum += opt * (4.0 / fenmu);
		opt = -opt;
	}
	return sum;
}

double nthleibniz(long n){
	int opt = 1;
	long fenmu = 2 * n - 1;
	if (n % 2 == 0){
		opt = -1;
	}
	return opt * (4.0 / fenmu);
}

bool difference(double a, double b, double range){
	if (fabs(a - b) < range){
		return true;
	}
	return false;
}
