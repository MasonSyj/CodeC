#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void quicksort(int* a, int l, int r);
int partition(int* a, int l, int r);
void array_print(int* a, int size);

int main(void){
   int a[] = {64, 27, 29, 54, 56, 85, 60, 32, 43, 77};
   array_print(a, 10);
   partition(a, 0, 9);
   array_print(a, 10);
}

int partition(int* a, int l, int r){
   int piv = a[l];
   while (l < r){
      while (l < r && piv < a[r]){
         r--;
      }
      if (l != r){
         a[l] = a[r];
         array_print(a, 10);
      }

      while (l < r && a[l] < piv){
         l++;
      }
      if (l != r){
         a[r] = a[l];
         array_print(a, 10);
      }

   }
   
   a[(l + r) / 2] = piv;
   return l;
}

void array_print(int* a, int size){
   for (int i = 0; i < size; i++){
      printf("%d  ", a[i]);
   }
   printf("\n");
}
