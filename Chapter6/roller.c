#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define LINE 4
#define SIZE 1000
#define SCALEFACTOR 2

typedef enum movedir{left, right, up, down} movedir;
typedef int indexf;
typedef struct unit{
   int board[LINE][LINE];
}unit;

void show(unit* u, indexf f);

int main(void) {
// int board[LINE][LINE] = {0};
// board[0][0] = board[1][1] = board[2][2] = board[3][3] = 1;
   unit* list = (unit*)calloc(SIZE,sizeof(unit));
   list->board[0][0] = list->board[1][1] = list->board[2][2] = list->board[3][3] = 1;
   
   show(list, 0);
}

void rowleft(unit* u, indexf f, int row, movedir m){
   
}



void move(unit* u, indexf f){
   
}

void show(unit* u, indexf f){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%d ",(u+f)->board[j][i]);
      }
      printf("\n");
   }
}
