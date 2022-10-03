#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDMAX 50

/**
/	The function rand() returns values in the interval [0, RAND_MAX]. 
/	If we declare the variable median and initialise it to have the value RAND_MAX/2, 
/	then rand() will return a value that is sometimes larger than median and sometimes smaller.
*/

int mediancompare(int max);

int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	
	int i, minus_cnt, plus_cnt;
	i = minus_cnt = plus_cnt = 0;
	int s = 0;
	while (i < 500){
		int cnt = mediancompare(RANDMAX);
		if (cnt == 0){
			minus_cnt++;
		}else{
			plus_cnt++;
		}
		i++;
		printf("%d :the difference: %d\n", s++, minus_cnt - plus_cnt);
		
	}
//	printf("minus_cnt: %d, plus_cnt: %d\n", minus_cnt, plus_cnt);
	
	
}

// return 0 if smaller, and return 1 if bigger
int mediancompare(int max){
	int median = max / 2;
	int result = 0;
	int value;
	do {
		 value = rand() % max + 1;
	}while (value == median);
	if (value > median){
		result = 1;
	}

	return result;
}
