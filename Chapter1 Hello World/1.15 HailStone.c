#include <stdio.h>

void HailStone(int n);

int main(void){
	printf("Input number you want start with in a HailStone. ");
	int n;
	scanf("%d", &n);
	HailStone(n);
}

void HailStone(int n){
	while (n != 1){	
		if (n % 2 == 0){
			n /= 2;
		}else{
			n = 3 * n + 1;	
		}
		printf("%d\n", n);
	}
}
