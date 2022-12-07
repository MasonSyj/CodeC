#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int fact(int num);
int stairs(int num);
int list(int num1, int num2);

int main(void){
   assert(fact(3) == 6);
   assert(fact(4) == 24);
   printf("%d\n", stairs(2));
   printf("%d\n", stairs(3));
   assert(stairs(2) == 2);
   assert(stairs(3) == 3);
   assert(stairs(4) == 5);

}

int stairs(int num){
   int sum = 0;
   if (num % 2 == 0){
      sum += 2;
   }else{
      sum += 1;
   }

   int cnt = 1;
   for (int i = num - 1; i >= num / 2 + 1; i--){
      sum += list(i, cnt);
      cnt++;
   }

   return sum;
}

int list(int num1, int num2){
   return fact(num1) / fact(num2) * fact(num1 - num2);
}

int fact(int num){
   if (num == 1){
      return 1;
   }

   return num * fact(num - 1);
}
