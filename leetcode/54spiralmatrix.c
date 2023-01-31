/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum dir{tright, tleft, tup, tdown} dir;
void traverse(int** matrix, int row, int col, int dir, int* res, int j, int i, int cnt);
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize);

int main(void){

   int** matrix = (int**)calloc(3, sizeof(int*));
   for (int j = 0; j < 3; j++){
      matrix[j] = (int*)calloc(4, sizeof(int));
   }
   int cnt = 1;
   for (int j = 0; j < 3; j++){
      for (int i = 0; i < 4; i++){
         matrix[j][i] = cnt++;
      }
   }

   for (int j = 0; j < 3; j++){
      for (int i = 0; i < 4; i++){
         printf("%d ", matrix[j][i]);
      }
   }

   int col = 4;
   int size = 0;
   int* res = spiralOrder(matrix, 3, &col, &size);
   for (int i = 0; i < size; i++){
      printf("%d\n", res[i]);
   }

}

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
   int length = matrixSize * *matrixColSize;
   *returnSize = length;
   printf("%d\n", length);
   int* res = (int*)calloc(length, sizeof(int));

   traverse(matrix, matrixSize, *matrixColSize, tright, res, 0, 0, 0);
   return res;
}

void traverse(int** matrix, int row, int col, int dir, int* res, int j, int i, int cnt){
   if (cnt == row * col - 1){
       res[cnt] = matrix[j][i];
       printf("j: %d i: %d cnt: %d %d\n", j, i, cnt, matrix[j][i]);
       return;
   }

   printf("j: %d i: %d cnt: %d %d\n", j, i, cnt, matrix[j][i]);

   res[cnt] = matrix[j][i];
   printf("%d\n", res[cnt]);
   matrix[j][i] = 101;

   if (dir == tright){
      if (i + 1 == col || matrix[j][i + 1] == 101){
         dir = tdown;
         traverse(matrix, row, col, dir, res, j + 1, i, cnt + 1);
         return;
      }
      traverse(matrix, row, col, dir, res, j, i + 1, cnt + 1);
   }else if (dir == tdown){
       if (j + 1 == row || matrix[j + 1][i] == 101){
          dir = tleft;
          traverse(matrix, row, col, dir, res, j, i - 1, cnt + 1);
          return;
       }
       traverse(matrix, row, col, dir, res, j + 1, i, cnt + 1);
   }else if (dir == tleft){
       if (i == 0 || matrix[j][i - 1] == 101){
          dir = tup;
          traverse(matrix, row, col, dir, res, j - 1, i, cnt + 1);
          return;
       }
       traverse(matrix, row, col, dir, res, j, i - 1, cnt + 1);
   }else if (dir == tup){
       if (j == 0 || matrix[j - 1][i] == 101){
          dir = tright;
          traverse(matrix, row, col, dir, res, j, i + 1, cnt + 1);
          return;
       }
       traverse(matrix, row, col, dir, res, j - 1, i, cnt + 1);
   } 
}
