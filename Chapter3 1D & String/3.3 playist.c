#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

void test();
void init(int a[], int n);
void shuffle(int a[], int n);



int main(void){
	srand((unsigned)time(NULL));
	
	test();
	
	printf("How many songs required ?");
	
	int n;
	scanf("%d", &n);
	int a[n];
	init(a, n);
	shuffle(a, n);
	
	for (int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
}

void test(){
   int sum = 20;
   int x[sum];
   init(x, sum);
   assert(x[0] == 1);
   assert(x[10] == 11);
   assert(x[19] == 20);
 
	int cnt = 0;
   shuffle(x, sum);
   for (int i = 0; i < sum; i++){
   	if (x[i] == i + 1){
   		cnt++;
   	}
   }
   assert(cnt == 0);
   
}

void shuffle(int a[], int n){
   for (int i = 0; i < n - 1; i++){
      int j = rand() % (n - i - 1) + (i + 1);
      int temp = a[j];
      a[j] = a[i];
		a[i] = temp;
	}
}

void init(int a[], int n){
   for (int i = 0; i < n; i++){
      a[i] = i + 1;
	}
}
