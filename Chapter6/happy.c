#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define SIZE 9

typedef struct node{
   char board[SIZE][SIZE];
   int row;
   int col;
   int newrow;
   int oldrow;
   struct node* next;
}node;

void movectrl(node* n);
int dot(char line[]);
bool move(node* n);
void test();
bool linecheck(char line[]);
bool ishappy(node* n);
void show(node* n);
void addtoend(node* n, node* new);

int main(void) {
   
   test();
   node* head = (node*)malloc(sizeof(struct node));
   head->row = 4;
   head->col = 3;
   head->oldrow = -1;
   head->newrow = -1;
   head->next = NULL;
   head->board[0][1] = head->board[1][0] = 'g';
   head->board[0][0] = head->board[1][1] = 'r';
   head->board[2][0] = head->board[3][1] = 'c';
   head->board[2][1] = head->board[3][0] = 'y';
   head->board[0][2] = head->board[1][2] = head->board[2][2] = head->board[3][2] = '.';
   head->board[0][3] = head->board[1][3] = head->board[2][3] = head->board[3][3] = '\0';
// show(head);
// move(head);
   movectrl(head);
}

void movectrl(node* n){
   while(n){
      show(n);
      bool judge = move(n);
      if (judge == 1){
         printf("-----FOUND----\n");
         return;
      }
      n = n->next;
   }
}

bool move(node* n){
   for (int j = 0; j < n->row; j++){
      if (dot(n->board[j]) >= 1 || dot(n->board[j]) == -1){ 
         //ensure there's a letter to move to
         int lastletter = dot(n->board[j]) >= 1 ? (dot(n->board[j]) - 1):(n->col - 1);
         for (int newrow = 0; newrow < n->row; newrow++){
            if ((n->oldrow != newrow && n->newrow != j) && j != newrow && dot(n->board[newrow]) >= 0){
               node* new = (node*)malloc(sizeof(struct node));
               memcpy(new, n, sizeof(node));
               new->board[newrow][dot(n->board[newrow])] = n->board[j][lastletter];
               new->board[j][lastletter] = '.';
               new->oldrow = j;
               new->newrow = newrow;
               if (ishappy(new)){
                  return true;
               }
               addtoend(n, new);
            }
         }
      }
   }
   return false;
}

bool ishappy(node* n){
   for (int j = 0; j < n->row; j++){
      if (!linecheck(n->board[j])){
         return false;
      }
   }
   return true;
}

bool linecheck(char line[]){
   int len = strlen(line);
   for (int i = 0; i < len - 1; i++){
      if (line[i] != line[i+1]){
         return false;
      }
   }
   return true;
}

void test(){
   char line1[] = "rrrrrrrr";
   char line2[] = "rrrrxrrrr";
   assert(linecheck(line1));
   assert(!linecheck(line2));
   
   node* head = (node*)malloc(sizeof(struct node));
   head->row = 4;
   head->col = 3;
   
   for (int j = 0; j < head->row; j++){
      for (int i = 0; i < head->row; i++){
         head->board[j][i] = j + 'a';
      }
   }
   for (int j = 0; j < head->row; j++){
      head->board[j][head->col] = '\0';
   }   
   
   assert(ishappy(head));
   
   char dot1[] = "abc...";
   char dot2[] = "abc";
   char dot3[] = "a....";
   printf("dot1: %d, dot2: %d, dot3: %d\n", dot(dot1), dot(dot2), dot(dot3));
}

void show(node* n){
   for (int j = 0; j < n->row; j++){
      for (int i = 0; i < n->row; i++){
         printf("%c", n->board[j][i]);
      }
      printf("\n");
   }
   printf("----------------------\n");
}

int dot(char line[]){
   int i = 0;
   while(*(line + i) && *(line + i) != '.'){
      i++;
   }
   
   if (i == (int)strlen(line)){
      return -1;
   }else{
      return i;
   }
}
      
//question: does this temp needed
void addtoend(node* n, node* new){
   node* temp = n;
   while (temp->next){
      temp = temp->next;
   }
   temp->next = new;
   new->next = NULL;
}
         