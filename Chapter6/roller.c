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

typedef struct board{
   int board[LINE][LINE];
}board;

typedef struct unit{
   board* bd;
   indexf f;
}unit;


/**
void move(unit* u);

*/
void show(unit* u, indexf f);
void row2left(unit* u, int row, indexf f);
void row2right(unit* u, int row, indexf f);
void col2up(unit* u, int col, indexf f);
void col2down(unit* u, int col, indexf f);
void addnew(unit* u, board* newboard);


int main(void) {
// int board[LINE][LINE] = {0};
// board[0][0] = board[1][1] = board[2][2] = board[3][3] = 1;
   unit* list = (unit*)calloc(1,sizeof(unit));
   list->bd = (board*)calloc(SIZE, sizeof(board));
   list->bd[0].board[0][0] = list->bd[0].board[1][1] = list->bd[0].board[2][2] = list->bd[0].board[3][3] = 1;
   list->f = 1;

/**   
   show(list, 0);
   row2left(list, 0, 0);
   show(list, 0);
   row2right(list, 1, 0);
   show(list, 0);
   col2up(list, 2, 0);
   show(list, 0);
   col2down(list, 3, 0);
   show(list, 0);
*/   
   
   //add new test
   board* new = (board*)calloc(1, sizeof(board));
   addnew(list, new);
   show(list, list->f - 1);
   //add the same one, should fail to add to the end
   addnew(list, new);
   printf("list->f:%d", list->f);
   
/*    
**/   
}

void move(unit* u){
   for (int i = 0; i < LINE; i++){
      
   }   
}

void addnew(unit* u, board* newboard){
   for (int i = 0; i < u->f; i++){
      if (memcmp(&u->bd[i], newboard, sizeof(board)) == 0){
         return;
      }
   }
   u->f++;
   memcpy(&u->bd[u->f], newboard, sizeof(board));
}


void row2left(unit* u, int row, indexf f){
   int temp = u->bd[f].board[row][0];
   for (int i = 0; i < LINE - 1; i++){
      u->bd[f].board[row][i] = u->bd[f].board[row][i+1];
   }
   u->bd[f].board[row][LINE-1] = temp;
}

void row2right(unit* u, int row, indexf f){
   int temp = u->bd[f].board[row][LINE-1];
   for (int i = LINE - 2; i >= 0; i--){
      u->bd[f].board[row][i+1] = u->bd[f].board[row][i];
   }
   u->bd[f].board[row][0] = temp;
}

void col2up(unit* u, int col, indexf f){
   int temp = u->bd[f].board[0][col];
   for (int i = 0; i < LINE - 1; i++){
      u->bd[f].board[i][col] = u->bd[f].board[i+1][col];
   }
   u->bd[f].board[LINE-1][col] = temp;
}

void col2down(unit* u, int col, indexf f){
   int temp = u->bd[f].board[LINE-1][col];
   for (int i = LINE - 2; i >= 0; i--){
      u->bd[f].board[i+1][col] = u->bd[f].board[i][col];
   }
   u->bd[f].board[0][col] = temp;
}

void show(unit* u, indexf f){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%d ", u->bd[f].board[j][i]);  
      }
      printf("\n");
   }
   printf("--------------------\n");
}



