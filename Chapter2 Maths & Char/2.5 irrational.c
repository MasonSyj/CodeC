#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define min(a, b) ((a)<(b)?(a):(b))
#define PI 3.14159265358979323846
#define DENO 100000

int main(void){
	double bestapprox = 1.0;
	double besta, bestb, a, b = 1;

	while (b++ < DENO){
		/* a within the range of [3.1 * DENO, 3.2 * DENO] */
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
	
	printf("%.0f/%.0f = %.20f", besta, bestb, besta/bestb);
}
