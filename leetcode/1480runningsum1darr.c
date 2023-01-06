/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize){
   int* arr = (int*)calloc(numsSize, sizeof(int));
   *returnSize = numsSize;
   arr[0] = nums[0];
   for (int i = 1; i < numsSize; i++){
       arr[i] += arr[i - 1] + nums[i];
   }
   return arr;
}
