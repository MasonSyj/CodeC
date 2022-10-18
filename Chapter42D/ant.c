#include <stdio.h>
#include <stdlib.h>

#define LINE 25
#define LOOPTIMES 30

typedef enum direction {up, left, down, right} dir;

typedef struct tablesim{
   char table[LINE][LINE+1];
   int direction;
} tablesim;

void whilecase(tablesim* t, int* y, int* x);
void blackcase(tablesim* t, int* y, int* x);
void show(tablesim* t);

int main(void){
   tablesim* t = (tablesim*)malloc(sizeof(struct tablesim));
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         t->table[j][i] = '0';
      }
   }
   t->direction = up;
   
   int i = 0;
   int y, x;
   y = x = LINE / 2;
   while (i++ < LOOPTIMES){
       if (t->table[y][x] == '0'){
          whilecase(t, &y, &x);
       }else{
          blackcase(t, &y, &x);
       }
   }
   show(t);
   
}

void whilecase(tablesim* t, int* y, int* x){
   t->table[*y][*x] = '1';
   if (t->direction == up){
      (*x)++;
      t->direction = right;
   }else if (t->direction == right){
      (*y)++;
      t->direction = down;      
   }else if (t->direction == down){
      (*x)--;
      t->direction = left;      
   }else if (t->direction == left){
      (*y)--;
      t->direction = up;
   }
}

void blackcase(tablesim* t, int* y, int* x){
   t->table[*y][*x] = '0';
   if (t->direction == up){
      (*x)--;
      t->direction = left;
   }else if (t->direction == right){
      (*y)--;
      t->direction = up;
   }else if (t->direction == down){
      (*x)++;
      t->direction = right;
   }else if (t->direction == left){
      (*y)++;
      t->direction = down;
   }
}

void show(tablesim* t){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%c", t->table[j][i]);
      }
      printf("\n");
   }
}


