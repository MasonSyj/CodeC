#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

int longestPalindrome(char * s);

int main(void) {
   printf("%d\n", longestPalindrome("abcdefg"));
   printf("%d\n", longestPalindrome("hello"));
   printf("%d\n", longestPalindrome("shanghai"));
   printf("%d\n", longestPalindrome("xyzyz"));
   printf("%d\n", longestPalindrome("Aabccb"));
   printf("%d\n", longestPalindrome(""));
   printf("%d\n", longestPalindrome("ccc"));
   printf("%d\n", longestPalindrome("bananas"));
}

//Official ANSWER·
/*
int longestPalindrome(char * s){
   int count[128] = {0};
   while (*s != '\0'){
       count[*s]++;
       s++;
   }
   int ans = 0;
   for (int i = 0; i < 128; i++){
      ans += count[i] / 2 * 2;
      if (ans % 2 == 0 && count[i] % 2 == 1){
          ans++;
      }
   }
   return ans;
}
*/   
   
/*
int longestPalindrome(char * s){
   int lower[26] = {0};
   int upper[26] = {0};
   while (*s != '\0'){
      if (islower(*s)){
         lower[*s - 'a']++;
      }else{
         upper[*s - 'A']++;		
      }
      s++;
   }
   int singlecnt = 0;
   int cnt = 0;
   int one = 0;
   for (int i = 0; i < 26; i++){
      if (lower[i] % 2 == 0){
         cnt += lower[i];
      }else if (lower[i] == 1){
         one++;
      }else if (lower[i] % 2 != 0){
         singlecnt += lower[i];
      }
      
      if (upper[i] % 2 == 0){
         cnt += upper[i];
      }else if (upper[i] == 1){
         one++;
      }else if (lower[i] % 2 != 0){
         singlecnt += lower[i];
      }
   }
//   printf("cnt: %d, singlecnt: %d, one: %d\n", cnt, singlecnt, one);
   cnt += singlecnt;
   if (one >= 1 && cnt % 2 == 0){
      cnt += 1;
   }

   return cnt;
}
*/