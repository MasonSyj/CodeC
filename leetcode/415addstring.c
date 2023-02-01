#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define TEN 

char * addStrings(char * num1, char * num2);


int main(void){

   char* x = addStrings("222", "456");
   puts(x);

//   assert(strcmp("678", addStrings("222", "456")) == 0);
   x = addStrings("999", "999");
   puts(x);
   x = addStrings("0", "123");
   puts(x);

   x = addStrings("456", "77");
   puts(x);

   x = addStrings("9", "99");
   puts(x);

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
      printf("len1: %d len2: %d, len: %d, char: %c\n", len1, len2, len, res[len]);
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

