#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
//int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes){
void reset(int** intervals);
void print(int** intervals);
void caseset(int* new);
void insert(int** intervals, int intervalsSize, int* newInterval);

int main(void){
   int** intervals = (int**)calloc(3, sizeof(int*));
   intervals[0] = (int*)calloc(2, sizeof(int));
   intervals[1] = (int*)calloc(2, sizeof(int));
   intervals[2] = (int*)calloc(2, sizeof(int));
   int i = 0;
   int new[] = {0, 0};

   while (i < 15){
      printf("%dth case\n", i);
      reset(intervals);
      print(intervals);
      caseset(new);
      insert(intervals, 3, new);
      printf("new: [%d, %d]\n", new[0], new[1]);
      print(intervals);
      printf("---------------------------\n---------Separate Line--------\n----------------------\n");
      i++;
   }


}

	
void insert(int** intervals, int intervalsSize, int* newInterval){
   int left, right;
   left = right = 0;
   for (int j = 0; j < intervalsSize; j++){
      if (intervals[j][1] >= newInterval[0]){
         right = j;
         break;
      }
   }

   for (int j = intervalsSize - 1; j >= 0 ; j--){
      if (intervals[j][0] <= newInterval[1]){
         left = j;
         break;
      }
   }
   printf("left: %d, right: %d\n", left, right);

   if (left == 0){
      intervals[0][0] = newInterval[0];
   }else if (newInterval[0] <= intervals[left - 1][1]){
      intervals[left - 1][0] = newInterval[0];
   }else{
      intervals[left][0] = newInterval[0];
   }
	
   if (right == intervalsSize - 1){
      intervals[intervalsSize - 1][1] = newInterval[1];
   }else if (newInterval[1] >= intervals[right + 1][0]){
      intervals[right + 1][1] = newInterval[1];
   }else{
      intervals[right][1] = newInterval[1];
   }

}

void reset(int** intervals){
   intervals[0][0] = 1;
   intervals[0][1] = 4;
   intervals[1][0] = 7;
   intervals[1][1] = 10;
   intervals[2][0] = 13;
   intervals[2][1] = 16;
}

void print(int** intervals){
   printf("[");
   for (int j = 0; j < 3; j++){
      printf("[%d %d],", intervals[j][0], intervals[j][1]);
   }
   printf("]\n");
}

void caseset(int* new){
   static int newleft = 0;
   static int newright = 0;
   int left[] = {2, 5, 8, 11, 14};
   int right[] = {3, 6, 9, 12, 15};
   new[1] = right[newright++];
   new[0] = left[newleft];
   if (newright == 5){
      newright = ++newleft;
   }

}
