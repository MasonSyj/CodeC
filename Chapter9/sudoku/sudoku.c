#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9
#define TRYTIMES 100

typedef struct cell{
   bool num[N];
   int this;
}cell;

void rowfillctrl(cell board[][N]);
void rowfill(cell board[][N], int row);
void colfillctrl(cell board[][N]);
void colfill(cell board[][N], int col);
void unitselect(int rowmark, int colmark, int* left, int* right, int* up, int* down);
void unitfillctrl(cell board[][N]);
void unitfill(cell board[][N], int row, int col);
void areafill(cell board[][N]);
int sumofbool(cell board[][N], int j, int i);
void setallzero(cell board[][N]);
void rowscan(cell board[][N], int j, int i);
void colscan(cell board[][N], int j, int i);
void unitscan(cell board[][N], int j, int i);
void boardprint(cell board[][N]);
void areascan(cell board[][N]);
void unitboundaryset(int j, int i, int* left, int* right, int* up, int* down);

int main(void){
   FILE* fp = fopen("grid2.sud", "r");
   if (!fp){
      fprintf(stderr, "cannot open file.\n");
      exit(EXIT_FAILURE);
   }
   
   cell board[N][N];
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         int number = fgetc(fp);
         board[j][i].this = number - '0';
      }
      // every 9 numbers followed by a newline which needs to be addressed.
      int newline = fgetc(fp);
   }
   setallzero(board);
   
   for (int numcnt = 0; numcnt < N; numcnt++){
      printf("%d ", board[0][0].num[numcnt]);
   }
   printf("\n--------------------\n");
   
   
   // pick a cell to test;
   int testj, testi;
   testj = 0;
   testi = 7;
   //rowscan test
   rowscan(board, testj, testi);
   for (int numcnt = 0; numcnt < N; numcnt++){
      printf("%d ", board[testj][testi].num[numcnt]);
   }
   printf("\n--------------------\n");
   
   //colscan test
   colscan(board, testj, testi);
   for (int numcnt = 0; numcnt < N; numcnt++){
      printf("%d ", board[testj][testi].num[numcnt]);
   }
   printf("\n--------------------\n");
   
   //unitscan test
   unitscan(board, testj, testi);
   for (int numcnt = 0; numcnt < N; numcnt++){
      printf("%d ", board[testj][testi].num[numcnt]);
   }
   printf("\n--------------------\n");
   
   //sumofbool test
   printf("sumofbool for cell row:%d, col: %d: %d\n",
   testj, testi, sumofbool(board, testj, testi));
   
 //  boardprint(board);
   printf("--------------------\n");
   /*areafill
   for (int i = 0; i < TRYTIMES; i++){
      areafill(board);
   }
   **/
   
   boardprint(board);
   printf("--------------------\n");
   for (int i = 0; i < 100000; i++){
      areafill(board);
      unitfillctrl(board);
      rowfillctrl(board);
      colfillctrl(board);
   }
   
   //boardprint
   boardprint(board);
}


void rowfillctrl(cell board[][N]){
   for (int row = 0; row < N; row++){
      rowfill(board, row);
   }
}

void rowfill(cell board[][N], int row){
   int unitnum[N] = {0};
   bool unitexist[N] = {0};
   int blanknums = 0;
   for (int col = 0; col < N; col++){
      if (board[row][col].this == 0){
         blanknums++;
         for (int cnt = 0; cnt < N; cnt++){
            unitnum[cnt] += board[row][col].num[cnt];
         }
      }else{
         unitexist[board[row][col].this - 1] = true;
      }
   }
   
   for (int cnt = 0; cnt < N; cnt++){
      if (unitnum[cnt] == blanknums - 1 && unitexist[cnt] == false){
         for (int col = 0; col < N; col++){
            if (board[row][col].this == 0 && board[row][col].num[cnt] == false){
               board[row][col].this = cnt + 1;
               board[row][col].num[cnt] = true;
            }
         }
      }
   }
}

void colfillctrl(cell board[][N]){
   for (int col = 0; col < N; col++){
      colfill(board, col);
   }
}

void colfill(cell board[][N], int col){
   int unitnum[N] = {0};
   bool unitexist[N] = {0};
   int blanknums = 0;
   for (int row = 0; row < N; row++){
      if (board[row][col].this == 0){
         blanknums++;
         for (int cnt = 0; cnt < N; cnt++){
            unitnum[cnt] += board[row][col].num[cnt];
         }
      }else{
         unitexist[board[row][col].this - 1] = true;
      }
   }
   
   for (int cnt = 0; cnt < N; cnt++){
      if (unitnum[cnt] == blanknums - 1 && unitexist[cnt] == false){
         for (int row = 0; row < N; row++){
            if (board[row][col].this == 0 && board[row][col].num[cnt] == false){
               board[row][col].this = cnt + 1;
               board[row][col].num[cnt] = true;
            }
         }
      }
   }
}

void unitselect(int rowmark, int colmark, int* left, int* right, int* up, int* down){
   if (rowmark == 0){
      *up = 2;
      *down = 0;
   }else if (rowmark == 1){
      *up = 5;
      *down = 3;
   }else{
      *up = 8;
      *down = 6;
   }
   
   if (colmark == 0){
      *left = 0;
      *right = 2;
   }else if (colmark == 1){
      *left = 3;
      *right = 5;
   }else{
      *left = 6;
      *right = 8;
   }
}

void unitfillctrl(cell board[][N]){
   for (int j = 0; j < 2; j++){
      for (int i = 0; i < 2; i++){
         unitfill(board, j, i);
      }
   }
}

void unitfill(cell board[][N], int row, int col){
   int left, right, up, down;
   unitselect(row, col, &left, &right, &up, &down);
   int unitnum[N] = {0};
   bool unitexist[N] = {0};
   int blanknums = 0;
   for (int j = left; j <= right; j++){
      for (int i = down; i <= up; i++){
         if (board[j][i].this == 0){
            blanknums++;
            for (int cnt = 0; cnt < N; cnt++){
               unitnum[cnt] += board[j][i].num[cnt];
            }
         }else{
            unitexist[board[j][i].this - 1] = true;
         }
      }
   }
   for (int cnt = 0; cnt < N; cnt++){
      if (unitnum[cnt] == blanknums - 1 && unitexist[cnt] == false){
         for (int j = left; j <= right; j++){
            for (int i = down; i <= up; i++){
               if (board[j][i].this == 0 && board[j][i].num[cnt] == false){
                  board[j][i].this = cnt + 1;
                  board[j][i].num[cnt] = true;
               }
            }
         }   
      }
   }
   
}

int sumofbool(cell board[][N], int j, int i){
   int sum = 0;
   for (int boolcnt = 0; boolcnt < N; boolcnt++){
      sum += board[j][i].num[boolcnt];
   }
   return sum;
}

void areafill(cell board[][N]){
   areascan(board);
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         if (sumofbool(board, j, i) == 8){
//            printf("cell [%d] [%d] got 8 of sumofbool\n", j , i);
            int fillnumber;
            for (int boolcnt = 0; boolcnt < N; boolcnt++){
               if (board[j][i].num[boolcnt] == false && board[j][i].this == 0){
                  fillnumber = boolcnt + 1;
                  board[j][i].this = fillnumber;
                  board[j][i].num[boolcnt] = true;
               }
            }  
         }
      }
   }
}


//board[j][i] will scan [j][0] [j][1] --- [j][8]
void rowscan(cell board[][N], int j, int i){
   for (int row = 0; row < N; row++){
      if (board[j][row].this != 0){
         board[j][i].num[board[j][row].this - 1] = true;
      }
   }
}
void colscan(cell board[][N], int j, int i){
   for (int col = 0; col < N; col++){
      if (board[col][i].this != 0){
         board[j][i].num[board[col][i].this - 1] = true;
      }
   }
}



void unitscan(cell board[][N], int j, int i){
   int left, right, up, down;
   unitboundaryset(j, i ,&left, &right, &up, &down);
   
   for (int row = left; row <= right; row++){
      for (int col = down; col <= up; col++){
         if (board[row][col].this != 0){
            board[j][i].num[board[row][col].this - 1] = true;
         }
      }
   }
}

void areascan(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         if (board[j][i].this != 0){
            continue;
         }else{
            rowscan(board, j, i);
            colscan(board, j, i);
            unitscan(board, j, i);
         }
      }
   }
}


void setallzero(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         for (int cnt = 0; cnt < N; cnt++){
            board[j][i].num[cnt] = false;
         }
      }
   }
}

void boardprint(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         printf("%d ", board[j][i].this);
      }
      printf("\n");
   }
}

void unitboundaryset(int j, int i, int* left, int* right, int* up, int* down){
   if (j <= 2){
      *left = 0;
      *right = 2;
   }else if (j <= 5){
      *left = 3;
      *right = 5;
   }else{
      *left = 6;
      *right = 8;
   }
   
   if (i <= 2){
      *down = 0;
      *up = 2;
   }else if (i <= 5){
      *down = 3;
      *up = 5;
   }else{
      *down = 6;
      *up = 8;
   }
}