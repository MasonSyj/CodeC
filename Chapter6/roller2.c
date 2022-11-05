#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define LINE 4
#define SIZE 10000
#define SCALEFACTOR 2

//typedef enum movedir{left, right, up, down} movedir;
typedef int indexf;

typedef struct board{
   int board[LINE][LINE];
}board;

typedef struct unit{
   board* bd;
   indexf f;
   int capacity;
}unit;


/**
void move(unit* u);

*/
void board_show(board* bd);
void show(unit* u, indexf f);
board* row2left(unit* u, int row, indexf f);
board* row2right(unit* u, int row, indexf f);
board* col2up(unit* u, int col, indexf f);
board* col2down(unit* u, int col, indexf f);
void addnew(unit* u, board* newboard);
void move(unit* list);


int main(void) {
// int board[LINE][LINE] = {0};
// board[0][0] = board[1][1] = board[2][2] = board[3][3] = 1;
   unit* list = (unit*)calloc(1,sizeof(unit));
   list->bd = (board*)calloc(SIZE, sizeof(board));
   list->bd[0].board[0][0] = list->bd[0].board[1][1] = list->bd[0].board[2][2] = list->bd[0].board[3][3] = 1;
   list->f = 1;
   list->capacity = SIZE;

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
//   board* new = (board*)calloc(1, sizeof(board));
//   addnew(list, new);
//   show(list, list->f - 1);
   //add the same one, should fail to add to the end
//   addnew(list, new);
//   printf("list->f:%d\n", list->f);
   
   move(list);
   printf("%d\n", list->f);
   
/*   
   board* newleft = row2left(list, 0, 0);
   addnew(list, newleft);
   show(list, list->f - 1);
   printf("list->f:%d\n", list->f);
   
   board* newright = row2right(list, 1, 0);
   addnew(list, newright);
   show(list, list->f - 1);
   printf("list->f:%d\n", list->f);
   
   board* newup = col2up(list, 2, 0);
   addnew(list, newup);
   show(list, list->f - 1);
   printf("list->f:%d\n", list->f);
   
   board* newdown = col2down(list, 3, 0);
   addnew(list, newdown);
   show(list, list->f - 1);
   printf("list->f:%d\n", list->f);
   
**/
}


void move(unit* list){
   int cnt = 0;
   while(cnt < list->f){
      for (int i = 0; i < LINE; i++){
        board* newleft = row2left(list, i, cnt);
        addnew(list, newleft);
      
        board* newright = row2right(list, i, cnt);
        addnew(list, newright);
      
        board* newup = col2up(list, i, cnt);
        addnew(list, newup);
      
        board* newdown = col2down(list, i, cnt);
        addnew(list, newdown);
     }
     cnt++;
   }
}


void addnew(unit* u, board* newboard){

   if (u->f == u->capacity){
      u->bd = (board*)realloc(u->bd, u->capacity * SCALEFACTOR);
      u->capacity *= SCALEFACTOR;
   }
   
   for (int i = 0; i < u->f; i++){
      if (memcmp(&u->bd[i], newboard, sizeof(board)) == 0){
         free(newboard);
         return;
      }
   }
   u->f++;
   memcpy(&u->bd[u->f-1], newboard, sizeof(board));
   show(u, u->f-1);
   
   if (newboard->board[0][0] == 1 && newboard->board[0][1] == 1 && newboard->board[0][2] == 1 && newboard->board[0][3] == 1){
      printf("------Found------\n");
      exit(EXIT_SUCCESS);
   }
}


board* row2left(unit* u, int row, indexf f){
   board* new = (board*)calloc(1, sizeof(board));
   memcpy(new, &u->bd[f], sizeof(board));
   
   int temp = u->bd[f].board[row][0];
   for (int i = 0; i < LINE - 1; i++){
      new->board[row][i] = u->bd[f].board[row][i+1];
   }
   new->board[row][LINE-1] = temp;
   return new;
}

board* row2right(unit* u, int row, indexf f){
   board* new = (board*)calloc(1, sizeof(board));
   memcpy(new, &u->bd[f], sizeof(board));
   
   int temp = u->bd[f].board[row][LINE-1];
   for (int i = LINE - 2; i >= 0; i--){
      u->bd[f].board[row][i+1] = u->bd[f].board[row][i];
   }
   u->bd[f].board[row][0] = temp;
   
   return new;
}

board* col2up(unit* u, int col, indexf f){
   board* new = (board*)calloc(1, sizeof(board));
   memcpy(new, &u->bd[f], sizeof(board));
   
   int temp = u->bd[f].board[0][col];
   for (int i = 0; i < LINE - 1; i++){
      u->bd[f].board[i][col] = u->bd[f].board[i+1][col];
   }
   u->bd[f].board[LINE-1][col] = temp;
   
   return new;
}

board* col2down(unit* u, int col, indexf f){
   board* new = (board*)calloc(1, sizeof(board));
   memcpy(new, &u->bd[f], sizeof(board));
   
   int temp = u->bd[f].board[LINE-1][col];
   for (int i = LINE - 2; i >= 0; i--){
      u->bd[f].board[i+1][col] = u->bd[f].board[i][col];
   }
   u->bd[f].board[0][col] = temp;
   
   return new;
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

void board_show(board* bd){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%d ", bd->board[j][i]);  
      }
      printf("\n");
   }
   printf("--------------------\n"); 
}

/*    


**/   

