#include <stdio.h>


void leftsum(int* left int* nums, int piv);
void sum(int* left, int* right, int* nums, int numsSize, int piv);
int pivotIndex(int* nums, int numsSize);

int main(void){
    int a[] = {1, 2, 3};
    int x= pivotIndex(a, 3);
    printf("x: %d\n", x);
}

void leftsum(int* left int* nums, int piv){
   *left = 0;
   for (int i = 0; i < piv; i++){
       *left += nums[i];
   }
}

int pivotIndex(int* nums, int numsSize){
   int sum = 0;
   for (int i = 0; i < numsSize; i++){
      sum += nums[i];
   }
   int left, right;
   left = right = 0;
   for (int i = 1; i < numsSize; i++){
      left += nums[i - 1];
      right = sum - left - nums[i];
      if (left == right){
         return i;
      }
   }
   return -1;
}

void sum(int* left, int* right, int* nums, int numsSize, int piv){
   *left = 0;
   *right = 0;
   for (int i = 0; i < piv; i++){
       *left += nums[i];
   }
   for (int i = piv + 1; i < numsSize; i++){
       *right += nums[i];
   }   
}

/*
int pivotIndex(int* nums, int numsSize){
   int piv = numsSize / 2;
   int leftsum, rightsum;

   while (piv > 0 && piv < numsSize - 1){
       sum(&leftsum, &rightsum, nums, numsSize, piv);
       if (leftsum == rightsum){
           return piv;
       }else if (leftsum < rightsum){
           piv++;
       }else{
           piv--;
       }
   }
   sum(&leftsum, &rightsum, nums, numsSize, piv);
   if ((piv == 0 && rightsum == 0) || (piv == numsSize - 1 && leftsum == 0)){
      return piv;
   }else{
      return -1;
   }
}
*/
