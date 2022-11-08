#include <stdio.h>

#define LINE 40

void draw(char sier[][LINE+1], int y, int x, int length);
void sierpinski(char sier[][LINE+1], int y, int x, int len);
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
   sierpinski(sier, 0, 0, LINE);
/*   for (int j = mark; j < mark + mark; j++){
      for (int i = mark; i < mark + mark; i++){
         sier[j][i] = '0';
      }
   }
*/   
   print(sier);
}

void sierpinski(char sier[][LINE+1], int y, int x, int len){
   draw(sier, y, x, len / 4);
   draw(sier, y, x + len * 3 / 4, len / 4);
   
   print(sier);
   
   if (len == 3 || len == 4){
      return;
   }
   
   int y1 = y;
   int y2 = len / 2 + y;
   int y3 = len / 2 + y;
   
   int x1 = x + len / 4;
   int x2 = x;
   int x3 = x + len / 2;
   
   int nextlen = len / 2;
   
// clear(sier);
   
   sierpinski(sier, y1, x1, nextlen);
   sierpinski(sier, y2, x2, nextlen);
   sierpinski(sier, y3, x3, nextlen);

   
   
}

void draw(char sier[][LINE+1], int y, int x, int length){
// printf("y = %d, x = %d, length = %d\n", y, x, length);
   for (int j = y; j < y + length * 2 + 1; j++){
      for (int i = x; i < x + length + 1; i++){
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

