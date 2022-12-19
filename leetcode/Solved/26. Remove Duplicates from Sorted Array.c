#include <stdio.h>

int removeDuplicates(int* nums, int numsSize){
   int cnt = 1;
   for (int j = 1; j < numsSize; j++){
      if (nums[j] > nums[j-1]){
         nums[cnt++] = nums[j];
      }
   }
   return cnt;
}

int main(int argc, char *argv[]) {
   
}