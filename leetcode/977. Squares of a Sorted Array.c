#include <stdio.h>
#include <assert.h>

int main(void) {
	
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize){
   int* ans_arr = (int*)calloc(numsSize, sizeof(int));
   *returnSize = numsSize;
   if (nums[0] >= 0){
       for (int i = 0; i < numsSize; i++){
          ans_arr[i] = nums[i] * nums[i];
       }
       return ans_arr;
   }
   int cnt = numsSize;

   int left = 0;
   int right = numsSize - 1;
   while (left <= right){
       if (nums[left] * nums[left] > nums[right] * nums[right]){
           ans_arr[--numsSize] = nums[left] * nums[left];
           left++;
       }else{
           ans_arr[--numsSize] = nums[right] * nums[right];
           right--;
       }
   }
   return ans_arr;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int* sortedSquares(int* nums, int numsSize, int* returnSize){
   int* ans_arr = (int*)calloc(numsSize, sizeof(int));
   *returnSize = numsSize;
   if (nums[0] >= 0){
       for (int i = 0; i < numsSize; i++){
          ans_arr[i] = nums[i] * nums[i];
       }
       return ans_arr;
   }

   for (int i = 0; i < numsSize; i++){
       ans_arr[i] = nums[i] * nums[i];
   }

   qsort(ans_arr, numsSize, sizeof(int), cmpfunc);

   return ans_arr;
}