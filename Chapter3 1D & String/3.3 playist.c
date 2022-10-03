#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){
	srand((unsigned)time(NULL));
	printf(" How many songs required ?");
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; i++){
		a[i] = i + 1;
	}
	for (int i = 0; i < n - 1; i++){
		int j = rand() % (n - i - 1) + (i + 1);
		int temp = a[j];
		a[j] = a[i];
		a[i] = temp;
	}
	for (int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}	
}
