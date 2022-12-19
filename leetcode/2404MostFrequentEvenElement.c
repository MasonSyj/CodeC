#include <stdio.h>
#include <assert.h>

int mostFrequentEven(int* nums, int numsSize);
int firsteven(int* nums, int numsSize);

int main(void) { 
   int nums1[] = {0,1,2,2,4,4,1}; // 7
   int nums2[] = {4,4,4,9,2,4}; // 6
   int nums3[] = {29,47,21,41,13,37,25,7}; // 8
   printf("%d\n", mostFrequentEven(nums1, 7));
   printf("%d\n", mostFrequentEven(nums2, 6));
   printf("%d\n", mostFrequentEven(nums3, 8));
}

int firsteven(int* nums, int numsSize){
   for (int i = 0; i < numsSize; i++){
      if (nums[i] % 2 == 0){
         return i;
      }
   }
   return -1;
}

int mostFrequentEven(int* nums, int numsSize){
   int old;
   int oldcnt = 0;
   int starti = firsteven(nums, numsSize);
   if (starti == -1){
      return -1;
   }
   
   int current = nums[starti];
   int cnt = 1;

   for (int i = starti + 1; i < numsSize; i++){
      if (nums[i] % 2 == 0){
         if (nums[i] == current){
            cnt++;
            
         }else{
            cnt--;
         }
      }
   
      if (cnt == 0){
         old = current;
         current = nums[++i];
         cnt++;
      }
      if (cnt == oldcnt){
         current
      }
      
      oldcnt = oldcnt > cnt ? oldcnt: cnt;
   }
   return current;
}
