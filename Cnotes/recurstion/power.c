#include <stdio.h>
#include <assert.h>

#define MAX 1000

void test();
unsigned long int power(int x);

int main(void){
   test();

   for (int i = 1; i <= MAX; i++){
      printf("%lu\n", power(i));
   }
}

unsigned long int power(int x){
   if (x == 1){
      return 1;
   }
   
   return x * power(x - 1);
}

void test(){
   assert(power(2) == 2);
   assert(power(3) == 6);
   assert(power(5) == 120);
   assert(power(6) == 720);
   assert(power(1) == 1);
}
