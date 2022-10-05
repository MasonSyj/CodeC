#include <stdio.h>
#include <assert.h>
#define N (int) sizeof(a) / (int)sizeof(a[0])

void swap(int a[], int i, int j);
void swaponearound(int a[], int n);
void printarray(int n, int a[]);


int main(void){
	int a[] = {1, 2, 3, 4};
//	printf("%d", (int)sizeof(a));
//	printf("%d", (int)sizeof(a[0]));
	printf("%d\n", N);
//	swap(a, 0, 1);
//	assert(a[0] == 2);
//	assert(a[1] == 1);
//	swap(a, 0, 1);
	swaponearound(a, N - 1);
}

void swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
    a[j] = temp;
}

void swaponearound(int a[], int n){
	if (n == 0){
		printarray(4, a);
		return;
	}
	
	for (int i = n;i >= 0; i--){
		swap(a, i, n);
		swaponearound(a, n - 1);
		swap(a, i, n);
   }
	
}

void printarray(int n, int a[]){
	for (int i = 0; i < n; i++){
        printf("%-3d", a[i]);
    }
    printf("\n");
}
