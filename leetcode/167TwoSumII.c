#include <stdio.h>
#include <assert.h>

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize);

int main(void) {
	
}

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize){
   *returnSize = 2;
   int* arr = (int*)calloc(2, sizeof(int));
   int first = 0;
   int second = numbersSize - 1;
   while (first < second){
    if (numbers[first] + numbers[second] == target){
        arr[0] = first + 1;
        arr[1] = second + 1;
        return arr;
    }else if (numbers[first] + numbers[second] < target){
        first++;
    }else{
        second--;
    }
   }
   return arr;
}
