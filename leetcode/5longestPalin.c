#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(char* s);
bool existPalindrome(char* s);
char * longestPalindrome(char * s);
void test();

int main(void) {
   test();
/*
   char* str0 = longestPalindrome("hello"); // ll
   char* str1 = longestPalindrome("cbabd"); // bab
   char* str2 = longestPalindrome("abccba");// abccba
   char* str3 = longestPalindrome("xyaz123321zcyx"); //z123321z
   char* str4 = longestPalindrome("mason"); // ""
*/
}
//method1
char * longestPalindrome(char * s){
   puts(s);
   return "hello";
/*
   int start = 0, end = 0;
   int len = (int)strlen(s);
   for (int i = 0; i < len; i++){
      
   }

   return ;
*/
}

void test(){
   printf("%d %d %d %d %d\n", isPalindrome("hello"), isPalindrome("cbabd"),isPalindrome("abccba"),isPalindrome("xyaz123321zcyx"),isPalindrome("mason"));
   printf("%d %d %d %d %d\n", isPalindrome("abcba"), isPalindrome("XYYX"),isPalindrome("Z232Z"),isPalindrome("HHHHH"),isPalindrome(""));
   printf("exist: %d\n", existPalindrome("hello"));
   printf("exist: %d\n", existPalindrome("mason"));
   printf("exist: %d\n", existPalindrome("apple"));
   printf("exist: %d\n", existPalindrome("xyzyx"));
   printf("exist: %d\n", existPalindrome("xyzyx"));
   printf("exist: %d\n", existPalindrome(""));
}

bool existPalindrome(char* s){
   int len = (int)strlen(s);
   for (int i = 0; i < len; i++){
      int evencnt = 1;
      while (i + evencnt < len && s[i] == s[i + evencnt]){
         evencnt++;
      }
      if (evencnt >= 2){
         return true;
      }
      
      int oddcnt = 1;
      while (i - oddcnt >= 0 && i + oddcnt < len && s[i - oddcnt] == s[i + oddcnt]){
         oddcnt++;
      }
      if (oddcnt >= 2){
         return true;
      }
   }
   return false;
}

bool isPalindrome(char* s){
   int len = (int)strlen(s);
   for (int i = 0; i < len / 2; i++){
      if (s[i] != s[len - 1 - i]){
         return false;
      }
   }
   return true;
}
