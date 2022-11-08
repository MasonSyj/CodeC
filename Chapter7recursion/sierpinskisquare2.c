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
         sier[j][i] = '0';
      }
      sier[j][LINE] = '\0';
   }
//   print(sier);   
// int mark = LINE / 3;
   sierpinski(sier, 0, 0, LINE / 2);
/*   for (int j = mark; j < mark + mark; j++){
      for (int i = mark; i < mark + mark; i++){
         sier[j][i] = '0';
      }
   }
*/   
   print(sier);
}

void sierpinski(char sier[][LINE+1], int y, int x, int mark){
   if (mark != LINE / 2){
      draw(sier, y, x, mark);  
      
   }
   
   print(sier);
   
   if (mark == 1 || mark == 0){
      return;
   }
   
   int y1 = y;
   int x1 = x;
   
   int y2 = y;
   int x2 = x + mark * 3 / 4;
   
   int div = mark / 4;
   
// clear(sier);
   
   sierpinski(sier, y1, x1, div);

   sierpinski(sier, y2, x2, div);

   
   
}

void draw(char sier[][LINE+1], int y, int x, int length){
// printf("y = %d, x = %d, length = %d\n", y, x, length);
   for (int j = y; j < y + length * 2; j++){
      for (int i = x; i < x + length; i++){
         sier[j][i] = '.';
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
   printf("------------------------------------------------------------------------\n");
}

void clear(char sier[][LINE+1]){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         sier[j][i] = '.';
      }
   }
}
