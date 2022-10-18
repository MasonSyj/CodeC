#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX 1000000
#define NUM 3

void boolinit(bool* set);
bool monteh(bool* set, int pick);

int main(void){
		srand((unsigned)time(NULL));
		int cnt = 0;
		bool set[] = {0, 0, 0};
		for (int i = 0; i < MAX; i++){
			boolinit(set);
			cnt += monteh(set, rand() % 3);
		}
		printf("%d", cnt);
}
// set[i], i == 0, 1, 2. two is 0, one is 1 meaning price
bool monteh(bool* set, int pick){
	int i = 0;
	while (i < NUM){
		if (i == pick){
			i++;
			continue;
		}
		if (*(set + i) == 0){
			printf("%d is not price. ", i);
			break;
		}
		i++;
	}
	
	int switched = NUM - i - pick;
	if (*(set + switched)){
		printf("You switched and you won.!\n");
		return 1;
	}else{
		printf("You switched and you lose.!\n");
		return 0;
	}	
}

void boolinit(bool* set){
	for (int i = 0; i < NUM; i++){
		set[i] = 0;
	}
	*(set + rand() % NUM) = 1;
}

