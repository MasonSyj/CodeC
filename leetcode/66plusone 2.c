#include <stdio.h>
#include <stdlib.h>

int* plusOne(int* digits, int digitsSize, int* returnSize){
   
   digitsSize--;
   digits[digitsSize]++;
   while (digitsSize > 0){
      if (digits[digitsSize] >= 10){
         digits[digitsSize] = 0;
         digits[digitsSize - 1]++;
         digitsSize--;
      }else{
         break;
      }
   }
   digitsSize++;
   
   // if (digits[0] == 10){
   //     digitsSize++;
   // }
   
   int *res = (int*)malloc(100 * sizeof(int));
   if (digits[0] == 10){
      res[0] = 1;
      res[1] = 0;
      for (int i = 1; i < digitsSize; i++){
         res[i+1] = digits[i];
      }
      *returnSize = ++digitsSize;
   }else{
      for (int i = 0; i < digitsSize; i++){
         res[i] = digits[i];
      }
   }
   
   
   return res;
}


int main(void) {
   int a[] = {1, 2, 3};
   int b[100];
   int* p = plusOne(a, 3, b);
   for (int i = 0; i < 3; i++){
      printf("%d  ", p[i]);
   }
}
