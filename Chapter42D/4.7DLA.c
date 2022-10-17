#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define LOOPTIMES 250
#define LINE 50
#define P 0.2

bool isadjacent(char table[][LINE+1], int y, int x);

int main(void){
   srand((unsigned)time(NULL));
   char table[LINE][LINE+1];
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE+1; i++){
         table[j][i] = ' ';
      }
   }
   table[LINE/2][LINE/2] = '1';
   
   int i = 0;
   
   while(i < LOOPTIMES){
      double p = P;
      int randy;
      int randx;
      int y = rand() % 100;
      int x = rand() % 100;
      
      if (y>50){
         randy = LINE - 1;
      }else{
         randy = 0;
      }
      
      if (x>50){
         randx = LINE - 1;
      }else{
         randx = 0;
      }
      while(!isadjacent(table, randy, randx) && fabs((p * 4) - p) > 0.00001 ){
         int direction = rand() % 100;
         if (direction < 25){
            randy++;
            if (randy == LINE){
               randy = 0;
            }
         }else if (direction < 50){
            randy--;
            if (randy == -1){
               randy = LINE - 1;
            }
         }else if (direction < 75){
            randx++;
            if (randx == LINE){
               randx = 0;
            }
         }else if (direction < 100){
            randx--;
            if (randx == -1){
               randx = LINE - 1;
            }
         }
         
         if (isadjacent(table, randy, randx)){
            p += P;
         }
      }
      
      table[randy][randx] = '1';
      i++;
      
   }
   
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE+1; i++){
         printf("%-c", table[j][i]);
      }
      printf("\n");
   }
}

bool isadjacent(char table[][LINE+1], int y, int x){
   if (y + 1 < LINE && table[y+1][x] == '1'){
      return true;
   }
   else if (x + 1 < LINE && table[y][x+1] == '1'){
      return true;
   }
   else if (y - 1 >= 0 && table[y-1][x] == '1'){
      return true;
   }else if (x - 1 >=0 && table[y][x-1] == '1'){
      return true;
   }
   return false;
}

//wrong understanding
//while(i < LOOPTIMES){
// do{
//    randy = rand() % LINE;
//    randx = rand() % LINE;
// }while (table[randy][randx] == '1');
// 
// if (isadjacent(table, randy, randx)){
//    table[randy][randx] = '1';
//    i++;
// }  
//}
