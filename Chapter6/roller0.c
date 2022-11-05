#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define LINE 4
#define SIZE 1000
#define SCALEFACTOR 2

//typedef enum movedir{left, right, up, down} movedir;
typedef int indexf;
typedef struct unit{
   int board[LINE][LINE];
   indexf f;
}unit;

void show(unit* u, indexf f);
void move(unit* u);
void row2left(unit* u, int row);
void row2right(unit* u, int row);
void col2up(unit* u, int col);
void col2down(unit* u, int col);

int main(void) {
// int board[LINE][LINE] = {0};
// board[0][0] = board[1][1] = board[2][2] = board[3][3] = 1;
   unit* list = (unit*)calloc(SIZE,sizeof(unit));
   list->board[0][0] = list->board[1][1] = list->board[2][2] = list->board[3][3] = 1;
   list[0].f = 0;
   
   show(list, 0);
   row2left(list, 0);
   show(list, 0);
   row2right(list, 1);
   show(list, 0);
   col2up(list, 2);
   show(list, 0);
   col2down(list, 3);
   show(list, 0);
}

void row2left(unit* u, int row){
   int temp = (u+u->f)->board[row][0];
   for (int i = 0; i < LINE - 1; i++){
      (u+u->f)->board[row][i] = (u+u->f)->board[row][i+1];
   }
   (u+u->f)->board[row][LINE-1] = temp;
}

void row2right(unit* u, int row){
   int temp = (u+u->f)->board[row][LINE-1];
   for (int i = LINE - 2; i >= 0; i--){
      (u+u->f)->board[row][i+1] = (u+u->f)->board[row][i];
   }
   (u+u->f)->board[row][0] = temp;
}

void col2up(unit* u, int col){
   int temp = (u+u->f)->board[0][col];
   for (int i = 0; i < LINE - 1; i++){
      (u+u->f)->board[i][col] = (u+u->f)->board[i+1][col];
   }
   (u+u->f)->board[LINE-1][col] = temp;
}

void col2down(unit* u, int col){
   int temp = (u+u->f)->board[LINE-1][col];
   for (int i = LINE - 2; i >= 0; i--){
      (u+u->f)->board[i+1][col] = (u+u->f)->board[i][col];
   }
   (u+u->f)->board[0][col] = temp;
}


void move(unit* u){
   
}

void show(unit* u, indexf f){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%d ",(u+f)->board[j][i]);
      }
      printf("\n");
   }
   printf("--------------------\n");
}
