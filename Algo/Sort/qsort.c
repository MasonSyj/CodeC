#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define MAX 1000

int intcompare(const void* a, const void* b){
   return *(const int*)a - *(const int*)b;
}

int doublecompare(const void* a, const void* b){
   return *(const double*)a - *(const double*)b;
}
void array_print(int* a, int size);

int main(void){
   srand((unsigned)time(NULL));

   int a[SIZE];
   
   for (int i = 0; i < SIZE; i++){
      a[i] = rand() % MAX; 
   }

   qsort(a, SIZE, sizeof(int), intcompare);

   array_print(a, SIZE);

   double b[SIZE];
   for (int i = 0; i < SIZE; i++){
      b[i] = rand() % MAX; 
   }

   qsort(b, SIZE, sizeof(double), doublecompare);

   for (int i = 0; i < SIZE; i++){
      printf("%.2f ", b[i]); 
   }
   printf("\n");

}

void array_print(int* a, int size){
   for (int i = 0; i < size; i++){
      printf("%d  ", a[i]);
   }
   printf("\n");
}


