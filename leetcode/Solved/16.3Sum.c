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
