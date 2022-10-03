#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOOP 8
#define A 9
#define C 5
#define M 11
int main(int argc, char *argv[]) {
	int seed = 0;
	srand((unsigned)time(NULL));
	for (int i = 0; i < LOOP; i++){
//		seed = (seed * A + C) % M;
		printf("%d\n", rand() % 100);
//		printf("%d\n", seed);
	}
}