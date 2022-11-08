#include <stdio.h>

#define LINE 81

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
   int mark = LINE / 3;
   sierpinski(sier, mark, mark, mark);
/*   for (int j = mark; j < mark + mark; j++){
      for (int i = mark; i < mark + mark; i++){
         sier[j][i] = '0';
      }
   }
*/   
   print(sier);
}

void sierpinski(char sier[][LINE+1], int y, int x, int mark){
   draw(sier, y, x, mark);
   
   if (mark == 1){
      return;
   }
   int div = mark / 3;
   int y1 = y + div * -2;
   int y2 = y + div * 1;
   int y3 = y + div * 4;
   
   int x1 = x + div * -2;
   int x2 = x + div * 1;
   int x3 = x + div * 4;
   
   sierpinski(sier, y1, x1, div);
   sierpinski(sier, y1, x2, div);
   sierpinski(sier, y1, x3, div);
   sierpinski(sier, y2, x1, div);
   sierpinski(sier, y2, x2, div);
   sierpinski(sier, y2, x3, div);
   sierpinski(sier, y3, x1, div);
   sierpinski(sier, y3, x2, div);
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
}
