#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
//0.15
//0.150 - 0.159
//0.001 - 0.009 
//< 0.01
#define D 0.000000001
#define PI 3.141592653

double leibniz(long n);
double eachleibniz(long n);
bool difference(double a, double b, double range);

int main(void){
	long i = 1;
	double x = eachleibniz(i);
	while (!difference(x, PI, D)){
		i++;
		x += eachleibniz(i);
		if (i == 0){
		printf("Out of Range.");		
		break;		
		}
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

double eachleibniz(long n){
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
