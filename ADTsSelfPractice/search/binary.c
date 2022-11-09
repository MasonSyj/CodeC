#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 100
#define TESTTIMES 100

int bin_it(int* a, int l, int r, int k);
int bin_recur(int* a, int l, int r, int k);

int main(void){
   int num[SIZE];
   for (int i = 0; i < SIZE; i++){
      num[i] = i * 2;
      // num[3] == 6;
   }
   
   int i = 0;
   while (i++ < TESTTIMES){
      int x = rand() % 100;
      if (x % 2 == 0){
         assert(bin_it(num, 0, SIZE - 1, x) == x / 2);
         assert(bin_recur(num, 0, SIZE - 1, x) == x / 2);
      }else{
         assert(bin_it(num, 0, SIZE - 1, x) == -1);
         assert(bin_recur(num, 0, SIZE - 1, x) == -1);         
      }  
   }
}

int bin_recur(int* a, int l, int r, int k){
   int middle = (l + r) / 2;
   
   if (l > r){
      return -1;
   }
   
   if (a[middle] == k){
      return middle;
   }else{
      if (a[middle] < k){
         return bin_recur(a, middle + 1, r, k);
      }else{
         return bin_recur(a, l, middle - 1, k);
      }
   }
}

int bin_it(int* a, int l, int r, int k){
   while (l <= r){
      int middle = (l + r) / 2;
      if (a[middle] == k){
         return middle;
      }else{
         if (a[middle] < k){
            l = middle + 1;
         }else{
            r = middle - 1;
         }
      }
   }
   return -1;
}
