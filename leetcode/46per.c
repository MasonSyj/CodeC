#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SWAP(A, B) {char temp = A; A = B; B = temp;}

void permu(int* nums, int numsSize, int index, int** table){
    static int cnt = 0;
    if (index == numsSize){
       memcpy(table[cnt], nums, numsSize * sizeof(int));
       cnt++;
       return;
    }

    for (int i = index; i < numsSize; i++){
       SWAP(nums[i], nums[index]);
       permu(nums, numsSize, index + 1, table);
       SWAP(nums[i], nums[index]);
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    int size = 1;
    for (int i = 0; i < numsSize; i++){
        size *= numsSize - i;
    }
    *returnSize = size;
    int** table = (int**)calloc(size, sizeof(int*));
    *returnColumnSizes = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++){
        (*returnColumnSizes)[i] = numsSize;
        table[i] = (int*)calloc(numsSize, sizeof(int));
    }
    
    permu(nums, numsSize, 0, table);
    
    return table;
}

int main(void){
   int size;
   int a[] = {0, 1};
   int* colsize;
   int** table = permute(a, 2, &size, &colsize);
   for (int j = 0; j < size; j++){
      for (int i = 0; i < colsize[j]; i++){
         printf("%d   ", table[j][i]);
      }
      printf("\n");
   }

}


