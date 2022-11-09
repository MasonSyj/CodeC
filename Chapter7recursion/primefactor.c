#include <stdio.h>
#include <stdlib.h>

void primef(int* t, int n);

int main(void){
   int x = 31;
   int* t = (int*)calloc(x, sizeof(t));
   printf("%d = 1", x);
   primef(t, x);
   
   for (int i = 0; i < x; i++){
      if (t[i] > 1){
         printf(" x %d^%d", i+1, t[i]);
      }else if (t[i] == 1){
         printf(" x %d", i+1);
      }
   }
   
}

void primef(int* t, int n){
   if (n == 1){
      return;
   }
   
   for (int i = 2; i <= n; i++){
      if (n % i == 0){
         primef(t, n / i);
         t[i - 1]++;
         return;
      }
   }
}
