#include <stdio.h>

#define LINE 81

void clear(char sier[][LINE+1]);
void draw(char sier[][LINE+1], int y, int x, int length);
void sierpinski(char sier[][LINE+1], int y, int x, int mark);
void print(char sier[][LINE+1]);

int main(void){
   char sier[LINE][LINE+1];
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         sier[j][i] = '.';
      }
      sier[j][LINE] = '\0';
   }
//   print(sier);   
// int mark = LINE / 3;
   sierpinski(sier, 0, 0, LINE);
/*   for (int j = mark; j < mark + mark; j++){
      for (int i = mark; i < mark + mark; i++){
         sier[j][i] = '0';
      }
   }
*/   
   print(sier);
}

void sierpinski(char sier[][LINE+1], int y, int x, int mark){
   if (mark != LINE){
      draw(sier, y, x, mark);  
   }
   
   if (mark == 1){
      return;
   }
   
   int y1 = y;
   int y2 = y + mark / 2;
   int y3 = y2;
   
   int x1 = x + mark / 4;
   int x2 = x;
   int x3 = x + mark / 2;
   
   int div = mark / 2;
   
// clear(sier);
   
   sierpinski(sier, y1, x1, div);

   sierpinski(sier, y2, x2, div);

   sierpinski(sier, y3, x3, div);
   
   
}

void draw(char sier[][LINE+1], int y, int x, int length){
   for (int j = y; j < y + length; j++){
      for (int i = x; i < x + length; i++){
         sier[j][i] = '0';
      }
   }
}

void print(char sier[][LINE+1]){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%c", sier[j][i]);
      }
      printf("\n");
   }
// printf("------------------------------------------------------------------------\n");
}

void clear(char sier[][LINE+1]){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         sier[j][i] = '.';
      }
   }
}
