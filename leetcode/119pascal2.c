#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//assume rowIndex = 4, got 5 elements

int* getRow(int rowIndex, int* returnSize){
   *returnSize = rowIndex + 1;
   int* a = (int*)calloc(*returnSize, sizeof(int));
   a[0] = 1;
   for (int loop = 0; loop < *returnSize; loop++){
      int i = loop / 2;
      while (i > 0){
         a[i] = a[i - 1] + a[i];
         i--;
      }
      a[0] = 1;
      
      i = loop / 2 + 1;
      while (i < loop){
         a[i] = a[loop - i];
         i++;
      }
      
      a[loop] = 1;
      
   }
   return a;
}

int main(void) {
   int x;
   int* a = getRow(4, &x);
   for (int i = 0; i < 5; i++){
      printf("%d ", a[i]);
   }
   printf("\n");
   free(a);
}


/*

Note: The returned array must be malloced, assume caller calls free().
 */

/*
int pascal(int row, int col){ // row >= 0, col >= 0
   if (col == 0 || col == row || row == 0){
      return 1;	
   }
   return pascal(row - 1, col - 1) + pascal(row - 1, col);
}

int* getRow(int rowIndex, int* returnSize){
   *returnSize = rowIndex + 1;
   int* a = (int*)calloc(rowIndex + 1, sizeof(int));
   for (int i = 0; i <= rowIndex / 2; i++){
       a[i] = pascal(rowIndex, i);
   }
   for (int i = rowIndex / 2 + 1; i <= rowIndex; i++){
       a[i] = a[rowIndex - i];
   }
   return a;
}
*/
