/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int fall(int** grid, int startPlace, int row, int col){
    int j = 0;
    int i = startPlace;

    do{
       if (grid[j][i] == 1 && (i + 1 == col || grid[j][i + 1] == -1)){
          return -1;
       }

       if (grid[j][i] == -1 && (i == 0 || grid[j][i - 1] == 1)){
          return -1;
       }

       if (grid[j][i] == 1){
           i++;
       }else{
           i--;
       }

       j++;
    }while (j != row);

    return i;
}

int* findBall(int** grid, int gridSize, int* gridColSize, int* returnSize){
   int* res = (int*)calloc(*gridColSize, sizeof(int));
   for (int i = 0; i < *gridColSize; i++){
       res[i] = fall(grid, i, gridSize, *gridColSize);
   }
   *returnSize = *gridColSize;
   return res;
}
