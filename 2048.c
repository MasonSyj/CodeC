#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define N 4
#define BASE1 2
#define BASE2 4
#define SCALEFACTOR 2

void lineshow(int line[N]);
void show(int board[][N]);
void init(int board[][N]);
void shuffle(int line[]);
void test();
int* readrowleft2right(int board[][N], int rowindex);
int* readrowright2left(int board[][N], int rowindex);
int* readcolup2down(int board[][N], int colindex);
int* readcoldown2up(int board[][N], int colindex);
void storecolup2down(int board[][N], int i, int* line);
void storecoldown2up(int board[][N], int i, int* line);
void storerowleft2right(int board[][N], int j, int* line);
void storecoldright2left(int board[][N], int j, int* line);
void userinteract(int board[][N]);
void scrollup(int board[][N]);
void scrolldown(int board[][N]);
void scrollleft(int board[][N]);
void scrollright(int board[][N]);

int main(void){
   test();
   int board[N][N] = {0};
   srand((unsigned)time(NULL));
   init(board);
   userinteract(board);
   
}

void userinteract(int board[][N]){
   char c = getchar();
//   getchar();
   do{
      getchar();
      show(board);
      switch(c){
         case 'w': scrollup(board);break;
         case 's': scrolldown(board);break;
         case 'a': scrollleft(board);break;
         case 'd': scrollright(board);break;
      }
     
   }while((c = getchar()) != 'q');
}

void scrollup(int board[][N]){
   for (int i = 0; i < N; i++){
      int* line = readcolup2down(board, i);
      shuffle(line);
      storecolup2down(board, i, line);
      free(line);
   }
}

void scrolldown(int board[][N]){
   for (int i = 0; i < N; i++){
      int* line = readcoldown2up(board, i);
      shuffle(line);
      storecoldown2up(board, i, line);
      free(line);
   }

}

void scrollleft(int board[][N]){
   for (int i = 0; i < N; i++){
      int* line = readrowleft2right(board, i);
      shuffle(line);
      storerowleft2right(board, i, line);
      free(line);
   }
}

void scrollright(int board[][N]){
   for (int i = 0; i < N; i++){
      int* line = readrowright2left(board, i);
      shuffle(line);
      storecoldright2left(board, i, line);
      free(line);
   }
}

void storecolup2down(int board[][N], int i, int* line){
   for (int j = 0; j < N; j++){
      board[j][i] = line[j];
   }
}

void storecoldown2up(int board[][N], int i, int* line){
   for (int j = 0; j < N; j++){
      board[j][i] = line[N - 1 - j];
   }
}

void storerowleft2right(int board[][N], int j, int* line){
   for (int i = 0; i < N; i++){
      board[j][i] = line[i];
   }
}
void storecoldright2left(int board[][N], int j, int* line){
   for (int i = 0; i < N; i++){
      board[j][i] = line[N - 1 - i];
   }
}

void init(int board[][N]){
   int random_row = rand() % N;
   int random_col = rand() % N;
   board[random_row][random_col] = (rand() % 2 + 1) * 2;
}
   
void shuffle(int line[]){
   for (int i = 0; i < N - 1; i++){
      if (line[i] == line[i + 1]){
         line[i] *= SCALEFACTOR;
         for (int j = i + 1; j < N - 1; j++){
            line[j] = line[j+1];
         }
         line[N - 1] = 0;
      }else if (line[i] == 0){
         for (int j = i + 1; j < N - 1; j++){
            line[j] = line[j+1];
         }
      }
   }
}

int* readrowleft2right(int board[][N], int rowindex){
   int* line = (int*)calloc(4, sizeof(int));
   assert(line);
   for (int i = 0; i < N; i++){
      line[i] = board[rowindex][i];
   }
   return line;
}

int* readrowright2left(int board[][N], int rowindex){
   int* line = (int*)calloc(4, sizeof(int));
   assert(line);
   for (int i = 0; i < N; i++){
      line[i] = board[rowindex][N - 1 - i];
   }
   return line;
}

int* readcolup2down(int board[][N], int colindex){
   int* line = (int*)calloc(4, sizeof(int));
   assert(line);
   for (int i = 0; i < N; i++){
      line[i] = board[i][colindex];
   }
   return line;
}

int* readcoldown2up(int board[][N], int colindex){
   int* line = (int*)calloc(4, sizeof(int));
   assert(line);
   for (int i = 0; i < N; i++){
      line[i] = board[N - 1 - i][colindex];
   }
   return line;
}

   
void lineshow(int line[N]){
   for (int i = 0; i < N; i++){
      printf("%-3d", line[i]);
   }
   printf("\n------------------------\n");
}

void show(int board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         printf("%-3d", board[j][i]);
      }
      printf("\n");
   }
   printf("------------------------\n");
}


   
void test(){
/*
   int testa[N] = {2, 2, 0, 0};
   lineshow(testa);
   shuffle(testa);
   lineshow(testa);

   int testb[N] = {2, 4, 4, 0};
   lineshow(testb);
   shuffle(testb);
   lineshow(testb);

   int testc[N] = {2, 2, 4, 4};
   lineshow(testc);
   shuffle(testc);
   lineshow(testc);
*/
/*
2 4 4 8
4 2 2 2
8 2 2 4
4 4 4 2
*/
   int testboard[N][N] = {{2,4,4,8}, {4,2,2,2}, {8,2,2,4}, {4,4,4,2}};
   int* readline1 = readrowleft2right(testboard, 0);
   int* readline2 = readrowright2left(testboard, 2);
   lineshow(readline1);
   lineshow(readline2);
   int* readline3 = readcolup2down(testboard, 1);
   int* readline4 = readcoldown2up(testboard, 3);
   lineshow(readline3);
   lineshow(readline4);
}
