#include <stdio.h>
int removeDuplicates(int* nums, int numsSize);
int removeDuplicates1(int* nums, int numsSize);

int main(void) {
	int nums[] = {0,0,1,1,1,2,2,3,3,4};
	removeDuplicates(nums, 10);
	for (int i = 0; i < 10; i++){
		printf("%d ", nums[i]);
	}
}

int removeDuplicates(int* nums, int numsSize){
   int this = nums[0];
   for (int j = 0; j < numsSize; j++){
		if (nums[j] != this){
			nu
		}
	}
}
int removeDuplicates1(int* nums, int numsSize){
	int cnt = 1;
	int this = nums[0];
	int i = 1;
	while (i < numsSize){
		if (nums[i] == this){
			if (nums[i] == nums[numsSize-1]){
				break;
			}
			for (int j = i; j < numsSize - 1; j++){
				nums[j] = nums[j+1];
			}
			
		}else{
			this = nums[i];
			cnt++;
			i++;
		}
	}
	return cnt;
}
