#include <stdio.h>
#include <assert.h>
#define N 4

void swap(int a[], int i, int j);
void swaponearound(int a[], int n);
void printarray(int a[]);


int main(void){
	int a[] = {1, 2, 3, 4};
	swap(a, 0, 1);
	assert(a[0] == 2);
	assert(a[1] == 1);
	swap(a, 0, 1);
	swaponearound(a, 3);
}

void swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
    a[j] = temp;
}

void swaponearound(int a[], int n){
	int i = n - 1;
	while (i >= 0){ 
		printarray(a);    
		swap(a, i, n);
		swaponearound(a, n-1);
		printarray(a);
		swap(a, i, n);
		i--;
    }
}

void printarray(int a[]){
	for (int i = 0; i < N; i++){
        printf("%-3d", a[i]);
    }
    printf("\n");
}
