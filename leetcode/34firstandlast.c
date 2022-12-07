#include <stdlib.h>
#include <stdio.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int binary_search(int* nums, int numsSize, int target, int l, int r);
void boundary(int* nums, int target, int piv, int* left, int* right);
int* searchRange(int* nums, int numsSize, int target, int* returnSize);

int main(void){
   int a[] = {5,7,7,8,8,10};
   int size;
   int* x = searchRange(a, 6, 8, &size);
   printf("%d %d", x[0], x[1]);
}

int binary_search(int* nums, int numsSize, int target, int l, int r){
   while (l <= r){
       int mid = (l + r) / 2;
       if (nums[mid] == target){
            return mid; 
       }else if (nums[mid] < target){
           return binary_search(nums, numsSize, target, mid + 1, r);
       }else{
            return binary_search(nums, numsSize, target, l, mid - 1);
       }
   }
   return -1;
}

void boundary(int* nums, int target, int piv, int* left, int* right){
   int temp = piv;
   while (nums[piv] == target){
       piv--;
   }
   *left = piv + 1;

    piv = temp;
    while (nums[piv] == target){
       piv++;
   }

   *right = piv - 1;
}



int* searchRange(int* nums, int numsSize, int target, int* returnSize){
   *returnSize = 2;
   if (target < nums[0] || target > nums[numsSize - 1]){
      int* a = (int*)calloc(2, sizeof(int));
      a[0] = a[1] = -1;
      return a;
   }

   int piv = binary_search(nums, numsSize, target, 0, numsSize - 1);
   int left;
   int right;

   boundary(nums, target, piv, &left, &right);

   int* a = (int*)calloc(2, sizeof(int));
   a[0] = left;
   a[1] = right;
   return a; 
}
