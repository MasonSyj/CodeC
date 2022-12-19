#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


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
   while (value != 0){
      str[i--] = (value % 26 - 1) + 'a';
      value /= 26;
   }
   return str;
}

int main(void){
   int x = 28;
   int y = 500;
   int z = 1000;

   printf("%d %d %d %d %d\n", digit(x), digit(y), digit(z), digit(0), digit(701));
   puts(toletter(28));
   puts(toletter(500));
   puts(toletter(1000));
   puts(toletter(1));
   puts(toletter(701));
}
