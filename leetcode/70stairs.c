#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

long fact(long num);
int climbStairs(int n);
int list(int num1, int num2);

int main(void){
   assert(fact(3) == 6);
   assert(fact(4) == 24);
   printf("%d\n", climbStairs(2));
   printf("%d\n", climbStairs(3));
   printf("%d\n", climbStairs(4));
   printf("%d\n", climbStairs(5));
   assert(climbStairs(2) == 2);
   assert(climbStairs(3) == 3);
   assert(climbStairs(4) == 5);

}

int climbStairs(int n){
   int sum = 0;
   if (n % 2 == 0){
      sum += 2;
   }else{
      sum += 1;
   }

   int cnt = 1;
   for (int i = n - 1; i >= n / 2 + 1; i--){
      sum += list(i, cnt);
      cnt++;
   }

   return sum;
}

int list(int num1, int num2){
   long fenzi = 1;
   for (int i = num1; i >= num1 - num2 + 1; i--){
      fenzi *= i;
   }
   long fenmu = num2;
   return fenzi / fact(fenmu);
}

long fact(long num){
   if (num == 1){
      return 1;
   }

   return num * fact(num - 1);
}
