#include <stdio.h>
#include <assert.h>

int majorityElement(int* nums, int numsSize);

int main(void) {
   int x[] = {3, 3, 7, 9, 4, 5, 7, 4, 6, 4, 10, 4, 4, 0, 4, 4};
   int current = x[0];
   int cnt = 1;
   int size = sizeof(x) / sizeof(x[0]);
   printf("%d %d %d\n-----------------------\n", current, cnt, size);

}

int majorityElement(int* nums, int numsSize){
   int current = nums[0];
   int cnt = 1;

   for (int i = 1; i < numsSize; i++){
      if (nums[i] == current){
         cnt++;
      }else{
         cnt--;
      }

      if (cnt == 0){
         current = nums[++i];
         cnt++;
      }
   }
   return current;
}
