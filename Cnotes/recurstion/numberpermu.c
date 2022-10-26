#include <stdio.h>
#include <assert.h>
// #define N (int)(sizeof(a)/sizeof(a[0])

void swap(int a[], int i, int j);
void swaponearound(int a[], int n);
void printarray(int a[], int n);


int main(void){
	int a[] = {1, 2, 3, 4, 5, 6};
	int n = (int)(sizeof(a)/sizeof(a[0]));
	printf("%d\n", n);
	swaponearound(a, n - 1);
}

void swap(int a[], int i, int j){
	int temp = a[i];
	a[i] = a[j];
    a[j] = temp;
}

void swaponearound(int a[], int n){
	if (n == 0){
		printarray(a, n);
		return;
	}

	for (int i = n;i >= 0; i--){
		swap(a, i, n);
		swaponearound(a, n - 1);
		swap(a, i, n);
   }

}

void printarray(int a[], int n){
   static int cnt = 0;
   printf("%-2d:  ", cnt++);
	for (int i = 0; i < 6; i++){
        printf("%-3d", a[i]);
    }
    printf("\n");
}
