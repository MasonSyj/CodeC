#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);

int main(void){
    int a[] = {2, 7, 9, 11, 12};
    int b[2];
    int* array = (int *)malloc(2 * sizeof(int));
    array = twoSum(a, 5, 9, array);
    printf("%d %d", array[0], array[1]);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    returnSize = (int *)malloc(2 * sizeof(int));
    for (int i = 0; i < numsSize; i++){
        for (int j = 1; j < numsSize; j++){
            if (nums[i] + nums[j] == target){
                returnSize[0] = i;
                returnSize[1] = j;
                break;
            }
        }
    }
    return returnSize;
}