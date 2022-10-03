#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define min(a, b) ((a)<(b)?(a):(b))
#define PI 3.14159265358979323846
#define deno 100000

int main(void){
	double bestapprox = 1.0;
	double besta, bestb, a, b = 1;
//	for (double a = 1; a < deno; a++){
//		for (double b = 1; b < deno && a > b; b++){
//			
//			if (fabs(thisapprox - PI) < fabs(bestapprox - PI)){
//				besta = a;
//				bestb = b;
//				bestapprox = thisapprox;
//			}
//		}
//	}
//	while (a < deno && b++ < deno && b < deno / PI){
	while (b++ < deno){
		double min = 3.1 * b;
		double max = 3.2 * b;
		for (int i = (int) min; i < max; i++){
			double thisapprox = i / b;
			if (fabs(thisapprox - PI) < fabs(bestapprox - PI)){
				besta = i;
				bestb = b;
				bestapprox = thisapprox;
			}
		}
		
	}
	
	printf("%f/%f = %.10f", besta, bestb, besta/bestb);
}
