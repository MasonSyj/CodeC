#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define STRSIZE 200

typedef union exper{
   int x;
   double y;
}exper;

int firstnum(char* str);
int digits(int num);
char* inttostring(int value);

int main(void){
/*
   exper test1; 
   test1.x = 3;
   printf("%d %f\n",  test1.x, test1.y);
   test1.y = 4.4;
   printf("%d %f\n",  test1.x, test1.y);
*/   
   int x = 436874;
   int y = 13;
   char s1[STRSIZE];
   char s2[STRSIZE];
   
   snprintf(s1, STRSIZE, "%d", x);
   snprintf(s2, STRSIZE, "%d", y);
   puts(s1);
   puts(s2);
// int z = 4;
// char value = z + '0';
// char s3[STRSIZE];
// strcpy(s3, value);
// puts(s3);
   
   char s4[STRSIZE] = "135 123 957 3574";
   printf("%d", firstnum(s4));
   
   int x1 = 45;
   int x2 = 680;
   int x3 = 9999;
   int x4 = -333;
   assert(digits(x1) == 2);
   assert(digits(x2) == 3);
   assert(digits(x3) == 4);
   char* xs1 = inttostring(x1);
   char* xs2 = inttostring(x2);
   char* xs3 = inttostring(x3);
   char* xs4 = inttostring(x4);
   puts(xs1);
   puts(xs2);
   puts(xs3);
   puts(xs4);
   puts(inttostring(1));
   
}

char* inttostring(int value){
   int digit = digits(value);
   char* str = (char*)calloc(digit + 1, sizeof(char));
   int absvalue = abs(value);
   while (digit > 0){
      str[--digit] = absvalue % 10 + '0';
      absvalue /= 10;
   }
   if (value < 0){
      str[0] = '-';
   }
   puts(str);
   return str;
}

//return first num in a very string
int firstnum(char* str){
   int value = 0;
   int flag = 1;
   int index = 0;
   while (str[index] != '\0'){
      if (str[index] == '-'){
         flag = -1;
      }
      if (isdigit(str[index])){
         while (isdigit(str[index])){
            value = value * 10 + (str[index] - '0');
            index++;
         }
         return flag * value;
      }
      index++;
   }
   return flag * value;
}

int digits(int num){
   if (num < 0){
      return digits(-num) + 1; 
   }
   int i = 0;
   do{
      i++;
   }while ((int)pow((double)10, (double)i) < num);
   return i;
}
