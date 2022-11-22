#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>


#define N 21
#define NUM 10

void board_init(int board[][N]);
void board_show(int board[][N]);
void board_mutate1(int board[][N]);
void board_mutate2(int board[][N]);
int distance(int j, int i, int mid);

int main(void){
   srand((unsigned)time(NULL));
   int board[N][N];
/*
   board_init(board);
   board_show(board);
   board_mutate1(board);
   board_show(board);
*/
   board_init(board);
   board_show(board);
   board_mutate2(board);
   board_show(board);
}

void board_init(int board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         board[j][i] = rand() % NUM;
      }
   }
}

void board_show(int board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         printf("%d", board[j][i]);
      }
      printf("\n");
   }
   printf("---------------------\n");
}

void board_mutate1(int board[][N]){
   int looptimes = N * N * N;
   int col, row, tmp;
   for (int i = 0; i < looptimes; i++){
      col =  rand() % (N - 1);
      row =  rand() % N;
      if (board[row][col] > board[row][col+1]){
         tmp = board[row][col];
         board[row][col] = board[row][col+1];
         board[row][col+1] = tmp;
      }

      col =  rand() % (N);
      row =  rand() % (N - 1);
      if (board[row][col] > board[row+1][col]){
         tmp = board[row][col];
         board[row][col] = board[row+1][col];
         board[row+1][col] = tmp;
      } 
   }
}

int distance(int j, int i, int mid){
   return (j - mid) * (j - mid) + (i - mid) * (i - mid);
}


void board_mutate2(int board[][N]){
   int mid = N / 2;
   int looptimes = N * N * N * N;
   for(int i = 0; i < looptimes; i++){
      int j1 = rand() % N;
      int i1 = rand() % N;
      int j2 = rand() % N;
      int i2 = rand() % N;
      if (distance(j1, i1, mid) < distance(j2, i2, mid) && board[j1][i1] > board[j2][i2]){
         int tmp = board[j1][i1];
         board[j1][i1] = board[j2][i2];
         board[j2][i2] = tmp;
      }

      if (distance(j1, i1, mid) > distance(j2, i2, mid) && board[j1][i1] < board[j2][i2]){
         int tmp = board[j1][i1];
         board[j1][i1] = board[j2][i2];
         board[j2][i2] = tmp;
      }
   }
}

