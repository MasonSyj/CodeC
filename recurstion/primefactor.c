#include <stdio.h>

void primef(int n);

int main(void){
   int x = 210;
   printf("%d: ", x);
   primef(x);
   printf("\n%d: ", 117);
   primef(117);
   printf("\n%d: ", 768);
   primef(768);
}

void primef(int n){
   if (n == 1){
      return;
   }
   
   for (int i = 2; i <= n; i++){
      if (n % i == 0){
         primef(n/i);
         printf("%d   ", i);
         return;
      }
   }
}
