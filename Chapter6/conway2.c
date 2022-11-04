#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define ROW 8
#define COL 7

typedef struct node{
   bool board[ROW][COL];
   struct node* next;
}node;

void movectrl(node* first);
void newmove(node* this);
node* board_copy(node* mother);
void board_init(node* first);
//add newboard to the list, return the pointer of this new board;
node* board_addlist(node* oldlast, node* newlast);
void board_show(node* this);

int main(void){
   node head;
   head.next = (node*)malloc(sizeof(node));
   board_init(head.next);
   board_show(head.next);
   node* second = board_copy(head.next);
   printf("second: \n");
   board_show(second);
   movectrl(head.next);
   // newmove(head.next);
}

void movectrl(node* first){
   int cnt = 0;
   while(first){
      
      
      newmove(first);
      first = first->next;
      cnt++;
   }
   printf("cnt: %d\n", cnt);
}

void newmove(node* this){
   node* last = this;
   for (int j = 0; j < ROW; j++){
      for (int i = 0; i < COL; i++){
         if (this->board[j][i] == 1 && i + 1 < COL && this->board[j][i+1] == 1){
            if (i - 1 >= 0 && this->board[j][i-1] == 0){
               node* next = board_copy(this);
               next->board[j][i] = 0;
               next->board[j][i+1] = 0;
               next->board[j][i-1] = 1;
               last = board_addlist(last, next);
               
            }else if (i + 2 < COL && this->board[j][i+2] == 0){
              node* next = board_copy(this);
              next->board[j][i] = 0;
              next->board[j][i+1] = 0;
              next->board[j][i+2] = 1;
              last = board_addlist(last, next);
            }
         }
      }
   }

   for (int j = 0; j < ROW; j++){
      for (int i = 0; i < COL; i++){
         if (this->board[j][i] == 1 && j + 1 < ROW && this->board[j+1][i] == 1){
            if (j - 1 >= 0 && this->board[j-1][i] == 0){
               node* next = board_copy(this);
               next->board[j][i] = 0;
               next->board[j+1][i] = 0;
               next->board[j-1][i] = 1;
               last = board_addlist(last, next);
            }
//          }else if (j + 2 < ROW && this->board[j+2][i] == 0){
//            node* next = board_copy(this);
//            next->board[j][i] = 0;
//            next->board[j+1][i] = 0;
//            next->board[j+2][i] = 1;
//            last = board_addlist(last, next);
//          }
         }
      }
   }
}

node* board_copy(node* mother){
   node* new = (node*)malloc(sizeof(node));
   memcpy(new, mother, sizeof(node));
   new->next = NULL;
   return new;
}

void board_init(node* first){
   for (int j = 0; j < ROW; j++){
      for (int i = 0; i < COL; i++){
         if (j < ROW / 2){
            first->board[j][i] = 0;
         }else{
            first->board[j][i] = 1;
         }
      }
   }
   first->next = NULL;
}

node* board_addlist(node* oldlast, node* newlast){
   while(oldlast->next){
      oldlast = oldlast->next;
   }
   oldlast->next = newlast;
   newlast->next = NULL;
   board_show(newlast);
   if (newlast->board[0][3] == 1){
      board_show(newlast);
      printf("----Found-----\n");
      exit(EXIT_SUCCESS);
   }

   return newlast;
}

void board_show(node* this){
   printf("------------------------\n");
   for (int j = 0; j < ROW; j++){
      for (int i = 0; i < COL; i++){
         printf("%d ", this->board[j][i]);
      }
      printf("\n");
   }
}
