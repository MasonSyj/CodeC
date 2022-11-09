#include <stdio.h>

#define LINE 64

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
   
   //draw(sier, 0, 0, LINE);
   sierpinski(sier, 0, 0, LINE);
 
   //print(sier);
}

void sierpinski(char sier[][LINE+1], int y, int x, int len){
   
   if (len == 1){
 //     sier[y][x+1] = '.';
      sier[y+1][x+1] = '.';
      return;
   }
   
   draw(sier, y, x, len);
   
   print(sier);
   
   int y1 = y;
   int y2 = len / 2 + y;
   int y3 = len / 2 + y;
   
   int x1 = x + len / 4;
   int x2 = x;
   int x3 = x + len / 2;
   
   int nextlen = len / 2;
   
   
   sierpinski(sier, y1, x1, nextlen);
   sierpinski(sier, y2, x2, nextlen);
   sierpinski(sier, y3, x3, nextlen);

   
   
}

void draw(char sier[][LINE+1], int y, int x, int length){
   for (int j = y; j <= y + length / 2 + 1; j++){
      for (int i = x; i < x + length / 4; i++){
         sier[j][i] = '.';
      }
   }
   
   for (int j = y; j <= y + length / 2 + 1; j++){
      for (int i = x + length / 4; i <= x + length * 3 / 4; i++){
         sier[j][i] = '0';
      }
   }
   
   for (int j = y; j <= y + length / 2 + 1; j++){
      for (int i = x + length * 3 / 4; i < x + length; i++){
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

