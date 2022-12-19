#include <stdio.h>

int searchInsert(int* nums, int numsSize, int target){
	int l = 0, r = numsSize - 1;
	if (target <= nums[0]){
		return 0;
	}
	while (l <= r){
		int middle = (l + r) / 2;
		if (target == nums[middle]){
			return middle;
		}else if (target < nums[middle]){
			r = middle - 1;
		}else if (target > nums[middle]){
			l = middle + 1;
		}
	}
	return l;
}

int main(void) {
	int nums[] = {4, 8};
	int x = searchInsert(nums, 2, 6);
	printf("%d", x);
}