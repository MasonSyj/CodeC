#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

bool allnine(int* digits, int digitsSize);
int* plusOne(int* digits, int digitsSize, int* returnSize);
void show(int* arr, int size);


int main(void) {
   int a[] = {5};
   int b[] = {9};
   int c[] = {5, 9};
   int d[] = {9, 9};
   int size;
   int* ax = plusOne(a, 1, &size);
   show(ax, size);
   int* bx = plusOne(b, 1, &size);
   show(bx, size);
   int* cx = plusOne(c, 2, &size);
   show(cx, size);
   int* dx = plusOne(d, 2, &size);
   show(dx, size);
}

bool allnine(int* digits, int digitsSize){
    for (int i = 0; i < digitsSize; i++){
        if (digits[i] != 9){
            return false;
        }
    }
    return true;
}

void show(int* arr, int size){
   for (int i = 0; i < size; i++){
      printf("%d, ", arr[i]);
   }
   printf("\n");
}

int* plusOne(int* digits, int digitsSize, int* returnSize){
   if (digits[digitsSize - 1] != 9){
       digits[digitsSize - 1]++;
       *returnSize = digitsSize;
       return digits;
   }else if (!allnine(digits, digitsSize)){
       digits[digitsSize - 1]++;
       for (int i = digitsSize - 1; i >= 0; i--){
          if (digits[i] == 10){
             digits[i] = 0;
             digits[i - 1]++;
          }
       }
       *returnSize = digitsSize;
       return digits;
   }else{
       int* new = (int*)calloc(digitsSize + 1, sizeof(int));
       new[0] = 1;
       *returnSize = digitsSize + 1;
       return new;
   }
}
