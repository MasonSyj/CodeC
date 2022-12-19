#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int titleToNumber(char * columnTitle);
int digit(int value);
char* toletter(int value);

int main(void){
   int x = 28;
   int y = 500;
   int z = 1000;
   printf("%d\n", 701 / 26);
   printf("%d %d %d %d %d\n", digit(x), digit(y), digit(z), digit(0), digit(701));
   puts(toletter(26));
   puts(toletter(28));
   puts(toletter(500));
   puts(toletter(1000));
   puts(toletter(1));
 
   puts(toletter(701));
   
   printf("%d %d %d", titleToNumber("A"), titleToNumber("AB"), titleToNumber("ZY"));
}

int titleToNumber(char * columnTitle){
   int cnt = 0;
   while (*columnTitle != '\0'){
      cnt = cnt * 26 + (*columnTitle - 'A' + 1);
      columnTitle++;
   }
   return cnt;
}


int digit(int value){
   int digitscnt = 1;
   int threshold = 26;
   while (value > threshold){
      digitscnt++;
      threshold += pow(26, digitscnt); 
   }
   return digitscnt;
}

char* toletter(int value){
   char* str = (char*)calloc(digit(value) + 1, sizeof(char));
   assert(str);

   int i = digit(value) - 1;
   while (value > 0){
      int x = value % 26 - 1;
      if (x == -1){
         x = 25;
         value--;
      }
      str[i--] = x + 'a';
      value /= 26;
   }
   return str;
}
