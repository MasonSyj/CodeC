#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(char * s){
   int left = 0;
   int len = strlen(s);
   int right = len - 1;
   while (left <= right){
      while (left < len && (!isalpha(s[left]) && !isdigit(s[left]))){
         left++;
      }
      if (left < len){
         s[left] = tolower(s[left]);
      }else{
         return true;
      }
      while (right >= 0 && (!isalpha(s[right]) && !isdigit(s[right]))){
         right--;
      }
      if (right >= 0){
         s[right] = tolower(s[right]);   
      }else{
         return true;
      }
      
      if (left > right){
         return true;
      }
      
      if (s[left] != s[right]){
         return false;
      }
      
      left++;
      right--;
      
   }
   return true;
}

int main(void) {
   char str1[] = "0P";
   int result1 = isPalindrome(str1);
   printf("%d", result1);
}
