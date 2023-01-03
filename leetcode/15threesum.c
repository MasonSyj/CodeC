#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//first step, use quick sort to sort
void quicksort(int* a, int left, int right);
int* threeSumonearr(int* nums, int numsSize, int* returnSize);
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);
	
int main(void) {

   int a[] = {-3, 3, 4, -3, 1, 2};

   int size;
   int* x = threeSumonearr(a, 6, &size);
	
   for (int i = 0; i < 6; i++){
      printf("%d ", a[i]);
   }
	printf("\n");
	
	for (int i = 0; i < size; i++){
		printf("%d ", x[i]);
	}
   printf("\n----------Separate Line--------------\n");
	int b[] = {-1,0,1,2,-1,-4};
	int sizeb;
	int col;
	int* colsize = &col;
	int** table = threeSum(b, 6, &sizeb, &colsize);
	for (int j = 0; j < *colsize; j++){
		for (int i = 0; i < sizeb; i++){
			printf("%d ", table[j][i]);
		}
		printf("\n");
	}
}

void quicksort(int* a, int left, int right){
   int i,j,t,temp;
   if(left > right)
      return;
   
   temp = a[left] ; //temp中存的就是基准数
   i = left;
   j = right;
   while(i != j){
      //顺序很重要，要先从右往左找 
      while(a[j] >= temp && i < j)
         j--;
      //再从右往左找
      while(a[i] <= temp && i < j)
         i++;
      
      //交换两个数在数组中的位置
      if(i < j){   //当哨兵i和哨兵j没有相遇时 
         t = a[i];
         a[i] = a[j];
         a[j] = t;	  
      }			
   }
   // 最终将基准数归位
   a[left] = a[i];
   a[i] = temp;
   
   quicksort(a, left,i-1); //继续处理左边的 
   quicksort(a, i+1,right); //继续处理右边的 
   return;
}

int* threeSumonearr(int* nums, int numsSize, int* returnSize){
   quicksort(nums, 0, numsSize - 1);
   int* arr = (int*)calloc(3, sizeof(int));
   *returnSize = 3;
   for (int i = 0; i < numsSize && nums[i] <= 0; i++){
      int first = i + 1;
      int second = numsSize - 1;
      while (first < second){
         if (nums[first] + nums[second] + nums[i] == 0){
           arr[0] = nums[i];
           arr[1] = nums[first];
           arr[2] = nums[second];
           return arr;
         }else if (nums[first] + nums[second] + nums[i] < 0){
            first++;
         }else{
            second--;
         }
      }
   }
   return arr;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
   int** table;
   quicksort(nums, 0, numsSize - 1);
	int cnt = 0;
	
//	int temp[3] = {0};
   for (int i = 0; i < numsSize - 2 && nums[i] <= 0; i++){
		if (i - 1 >= 0 && nums[i] == nums[i-1]){
			continue;
		}
      int first = i + 1;
      int second = numsSize - 1;
      while (first < second){
         if (nums[first] + nums[second] + nums[i] == 0){
/*				
           temp[0] = nums[i];
           temp[1] = nums[first];
           temp[2] = nums[second];
*/		
           if (cnt == 0){
              table = (int**)calloc(++cnt, sizeof(int*));		
           }else{
              table = (int**)realloc(table, ++cnt * sizeof(int*));
           }
           table[cnt - 1] = (int*)calloc(3, sizeof(int));
           table[cnt - 1][0] = nums[i];
           table[cnt - 1][1] = nums[first];
           table[cnt - 1][2] = nums[second];
           first++;
           second--;
         }else if (nums[first] + nums[second] + nums[i] < 0){
            first++;
         }else{
            second--;
         }
      }
   }
   *returnSize = 3;
   **returnColumnSizes = cnt;
   return table;
}
