#include <stdio.h>

int main(void){
	int n;
	int i = 1;
	printf("How many levels of Triangle Numbers you want to reach ? ");
	do {
		
	}while (scanf("%d", &n) != 1);

	for (int num = 1; num <= n * (n + 1) / 2; num++ ){
		printf("%5d", num);

		if (num == i * (i + 1) / 2){
			printf("\n");
			i++;
		}

	}
}
