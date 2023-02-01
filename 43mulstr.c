#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char * addStrings(char * num1, char * num2);
char* lessten(char* num1, char* num2);
char* lsl(char* value, int bit);


char * multiply(char * num1, char * num2){
   if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0){
      return "0";
   }

   char* res = "0";

   int index = strlen(num2) - 1;
   int i = 0;
   while (index >= 0){
      res = addStrings(res, lsl(lessten(num1, num2 + index), i++));
      index--;
   }


   return res;

}

int main(void){


   puts(lessten("435", "3"));

   char* x = multiply("0", "2333");
   puts(x);

   x = multiply("2", "3");
   puts(x);

   x= multiply("123", "456");
   puts(x);
/*
   puts(lsl("999", 0));

   puts(lsl("999", 1));

   puts(lsl("999", 2));

   puts(lsl("999", 3));



   puts(lessten("456", "2"));

   puts(lessten("415", "2"));

   puts(lessten("456", "3"));

   puts(lessten("456", "9"));

   puts(lessten("999", "9"));

   puts(lessten("456", "0"));

*/
}


char* lessten(char* num1, char* num2){
   
   if (*num2 == '0'){
      return "0";
   }
   
   int len1 = strlen(num1) - 1;
   int len = len1 + 1;
   char* res = (char*)calloc(len + 2, sizeof(char));

   while (len1 >= 0){
      int digit = (int)(num1[len1--] - '0') * (int)(*num2 - '0');
      if (digit < 10){
         res[len--] += digit + '0';
         if (res[len + 1] > '9'){
            res[len + 1] -= 10;
            res[len] += 1;
         }
      }else{
         int temp = res[len] + digit;
         res[len] = temp % 10 + '0';
         res[--len] += temp / 10;
      }
   }

   if (res[0] == '\0'){
      return res + 1;
   }
   res[0] += '0';
   return res;
}

char* lsl(char* value, int bit){
   if (bit == 0){
      return value;
   }

   int len = strlen(value);

   len += bit;
   char* res = (char*)calloc(len + 1, sizeof(char));

   strncpy(res, value, strlen(value));

   for (int i = strlen(value); i < len; i++){
      res[i] = '0';
   }

   return res;
}


char * addStrings(char * num1, char * num2){
   int len1 = strlen(num1);
   int len2 = strlen(num2);
   int len = len1 > len2 ? len1: len2;
   len1--;
   len2--;
   char* res = (char*)calloc(len + 2, sizeof(char));

   while (len1 >= 0 && len2 >= 0){

      res[len] = res[len] + num1[len1] + num2[len2] - '0';

      if (res[len] > '9'){
         res[len] -= 10;
         res[len - 1] += 1;
      }
      len--;
      len1--;
      len2--;

   }
   
   while (len2 >= 0){
      res[len] = res[len] + num2[len2--];
      if (res[len] > '9'){
         res[len] -= 10;
         res[len - 1] += 1;
      }
      len--;
   }

   while (len1 >= 0){
      res[len] = res[len] + num1[len1--];
      if (res[len] > '9'){
         res[len] -= 10;
         res[len - 1] += 1;
      }
      len--;
   }

   if (*res == '\0'){
      return res + 1;
   }else{
      *res = '1';
      return res;
   }

   
}
