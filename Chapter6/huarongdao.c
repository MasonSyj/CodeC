#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define LINE 3

void init(char board[][LINE+1]);
void board_show(char board[LINE][LINE+1]);
void board_recur(char board[LINE][LINE+1], int mark);
char* board_tostring(char board[LINE][LINE+1]);

int main(void){
   char board[LINE][LINE+1];
   init(board);
   assert(strcmp("12345678 ", board_tostring(board)) == 0);
   board_recur(board, 0);
}


void init(char board[][LINE+1]){
   int cnt = 1;
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         board[j][i] = '0' + cnt++;
      }
   }
   board[LINE-1][LINE-1] = ' ';
}
   

char* board_tostring(char board[LINE][LINE+1]){
   char* str = (char*)malloc((LINE * LINE + 1) * sizeof(char));
   char* head = str;
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         *str++ = board[j][i];
      }
   }
   *str = '\0';
   return head;
}

/* right: 1, down: 2, up: 3, left: 4**/
/* if mark = 1, then no right **/
void board_recur(char board[LINE][LINE+1], int mark){
   char* strthistime = board_tostring(board);
   if (strcmp("513276 48", strthistime) == 0){
      puts(board_tostring(board));
      exit(EXIT_SUCCESS);
   }
   board_show(board);
   free(strthistime);
   
   int blankj, blanki;
   
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         if (board[j][i] == ' '){
            blankj = j;
            blanki = i;
         }
      }
   }
   //blank cell go up
   if (mark != 3 && blanki - 1 >= 0){
      board[blankj][blanki] = board[blankj][blanki - 1];
      board[blankj][blanki - 1] = ' ';
      board_recur(board, 2);
      board[blankj][blanki - 1] = board[blankj][blanki];
      board[blankj][blanki] = ' ';
   }
   
   //go down
   if (mark != 2 && blanki + 1 < LINE){
      board[blankj][blanki] = board[blankj][blanki + 1];
      board[blankj][blanki + 1] = ' ';
      board_recur(board, 3);
      board[blankj][blanki + 1] = board[blankj][blanki];
      board[blankj][blanki] = ' ';
   }
   
   //go left
   if (mark != 4 && blankj - 1 >= 0){
      board[blankj][blanki] = board[blankj-1][blanki];
      board[blankj-1][blanki] = ' ';
      board_recur(board, 1);
      board[blankj-1][blanki] = board[blankj][blanki];
      board[blankj][blanki] = ' ';
   }
   
   //go right
   if (mark != 1 && blankj + 1 < LINE){
      board[blankj][blanki] = board[blankj+1][blanki];
      board[blankj+1][blanki] = ' ';
      board_recur(board, 4);
      board[blankj+1][blanki] = board[blankj][blanki];
      board[blankj][blanki] = ' ';
   }
}

void board_show(char board[LINE][LINE+1]){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%c ", board[j][i]);
      }
      printf("\n");
   }   
   printf("----------------\n");
}
