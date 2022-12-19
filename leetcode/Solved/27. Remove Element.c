#include <stdio.h>

int removeElement(int* nums, int numsSize, int val){
   int cnt = 0;
   for (int j = 0; j < numsSize; j++){
      if (nums[j] != val){
         nums[cnt++] = nums[j];
      }
   }
   return cnt;
}

int main(int argc, char *argv[]) {
   
}