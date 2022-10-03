#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000000


int main(void){
	srand((unsigned)time(NULL));
		double four = 0;
		double fullhouse = 0;
	
	int i = 0;
	do{

		int a[6] = {0, 0, 0, 0, 0, 0};
		for (int i = 0; i < 5; i++){
			a[rand() % 6]++;
		}
		
		for (int i = 0; i < 5; i++){
//			if (a[i] == 5){
//				printf("A Five of a kind");
			if (a[i] == 4){
//				printf("A Four of a kind");
				four++;
				break;
			}else if (a[i] == 3 || a[i] == 2){
				for (int j = i + 1; j < 6; j++){
					if (a[j] == 3 || a[j] == 2 && a[i] + a[j] == 5){
//						printf("Full house.");
						fullhouse++;
						break;
					}
				}
			}
		}
	}while (i++ < MAX);
	printf("%f %f\n", four, fullhouse);
	printf("%f %f\n", four/MAX, fullhouse/MAX);
}
