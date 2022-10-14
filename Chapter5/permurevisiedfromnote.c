#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(A, B) {int temp = *A; *A = *B; *B = temp;}
#define N 5

void permuate(int a[], int s, int e);
void printarray(int a[]);

int main(void){
	int a[] = {1, 2, 3, 4, 5};
	permuate(a, 0, N-1);
	return 0;
}

void permuate(int a[], int s, int e){
	if (s == e){
		printarray(a);
		return;
	}
	
	for (int i = s;i <= e; i++){
		SWAP((a+s), (a+i));
		permuate(a, s+1, e);
		SWAP((a+s), (a+i));
	}
}

void printarray(int a[]){
	for (int i = 0; i < N; i++){
		printf("%-3d", a[i]);
	}
	
	printf("\n");
}
