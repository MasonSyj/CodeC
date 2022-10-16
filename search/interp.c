#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM 100
#define TESTTIMES 100000

int inter(int a*, int l, int r, int k);

int main(void){
   int a[NUM];
   for (int i = 0; i < NUM; i++){
      a[i] = i * 2;
   }
   
   int i = 0;
   while (i++ < TESTTIMES){
      int x = rand() % (NUM * 2 - 1);
      if (x % 2 == 0){
          assert(inter(a, 0, NUM - 1, x) == x / 2);
      }else{
          assert(inter(a, 0, NUM - 1, x) == -1);
      }
   }
}

int inter(int a*, int l, int r, int k){
   double md;
   int m;
   
   while (l <= r){
      md = ((double)(k - a[l])/
              (double)(a[r] - a[l])*
              (double)(r));
      m = md + 0.5;
      if (a[m] == k){
         return m;
      }else if (a[m] < k){
         l = m + 1;
      }else{
         r = m - 1;
      }
   }
   
   return -1;
}
