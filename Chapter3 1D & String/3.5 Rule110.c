#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define N 20
#define TESTTIMES 40

void init(int a[], int n);
void newline(int a[], int n);
void printline(int a[], int n);
void test();

int main(void){
	srand((unsigned)time(NULL));
	
	int a[N];
	init(a, N);
	
	for (int i = 0; i < TESTTIMES; i++){
		newline(a, N);
		printline(a, N);
	}
}

	/* init origin stage which random one is 1 */
void init(int a[], int n){
	for (int i = 0; i < N; i++){
		a[i] = 0;
	}
	a[rand() % N] = 1;
}
	/* create newline according to rule */
void newline(int a[], int n){
	int b[N];
	for (int i = 0; i < N; i++){
		b[i] = 1;
	}
	b[0] = b[N-1] = 0;
	
	for (int i = 1; i < N - 1; i++){
		if (a[i - 1] + a[i] + a[i + 1] == 0 || a[i - 1] + a[i] + a[i + 1] == 3 || (a[i-1] == 1 && a[i] == 0 && a[i+1] == 0)){
			b[i] = 0;
		}
	}
	
	for (int i = 0; i < N; i++){
		a[i] = b[i];
	}
}

void printline(int a[], int n){
	for (int i = 0; i < N; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");
}


void test(){
	
}

//for (int i = 0; i < N; i++){
//	printf("%d  ", b[i]);
//}