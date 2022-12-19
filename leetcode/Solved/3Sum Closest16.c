#include <stdlib.h>
#include <stdio.h>
int cmp(const void* a, const void* b);
int threeSumClosest(int* nums, int numsSize, int target);


int main(void){
    int num[] = {1, 2, 4, 10, 0};
    int size = sizeof(num) / sizeof(num[0]);
    int y = threeSumClosest(num, size, 100);
    printf("%d", y);
}

int cmp(const void* a, const void* b){
    return *(int* )a - *(int* )b;
}

int threeSumClosest(int* nums, int numsSize, int target){
    qsort(nums, numsSize, sizeof(int), cmp);
    int result = nums[0] + nums[1] + nums[2];
    int i = 0, j = i + 1, k = numsSize - 1;
    int this;
    while(i < numsSize - 2){
        this = nums[i] + nums[j] + nums[k];
        if (this == target){
            return this;
        }
        else if (abs(this - target) < abs(result - target)){
            result = this;
        }
        
        if (this < target){
            j++;
        }else{
            k--;
        }
        
        if (j == k){
            i++;
            j = i + 1;
            k = numsSize - 1;
        }
        
    }
    
    return result;
}


//int threeSumClosest(int* nums, int numsSize, int target){
//  int result = nums[0] + nums[1] + nums[2];
//  for (int i = 0; i < numsSize - 2; i++){
//      for (int j = i + 1; j < numsSize; j++){
//          for (int k = j + 1; k < numsSize; k++){
//              int this = nums[i] + nums[j] + nums[k];
//              if (abs(target - this) < abs(target - result)){
//                  result = this;
//              }
//          }
//      }
//  }
//  return result;
//}