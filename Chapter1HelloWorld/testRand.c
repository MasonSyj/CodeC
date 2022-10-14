#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int randomInt(int maxvalue){
	return rand() % (maxvalue + 1);
}
int main(int argc, char *argv[]) {
	srand((unsigned)time(NULL));
	int i = 0;
	while (i++ < 100){
		int x = rand() % MAX;
		printf("%d\n", x);

	}
	
	
}