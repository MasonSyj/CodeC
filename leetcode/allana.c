#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int* findAnagrams(char * s, char * p, int* returnSize);
bool isana(char* str1, char* str2, int len);
bool issamefre(int* a, int* b);

int main(void){
   char s[] = "cbaebabacd";
   char p[] = "abc";
   int len = 0;
   int* ans = findAnagrams(s, p, &len);
   for (int i = 0; i < len; i++){
      printf("%d  ", ans[i]);
   }

}

int* findAnagrams(char * s, char * p, int* returnSize){
   int weight = 0;
   int cur = 0;
   int cnt = 0;
   int lenp = (int)strlen(p);
   int lens = (int)strlen(s);
   int* ans = (int*)calloc(lens, sizeof(int));
   if (lens < lenp){
      return ans;
   }

   int b1[26] = {0};
   int b2[26] = {0};

   for (int i = 0; i < lenp; i++){
      b1[s[i] - 'a']++;
      b2[p[i] - 'a']++; 
   }

   for (int i = 0; i <= lens - lenp; i++){
      if (issamefre(b1, b2)){
         ans[cnt++] = i;
      }

      b1[s[i] - 'a']--;
      b1[s[i + lenp] - 'a']++;

   }
   *returnSize = cnt;
   return ans;
}

bool issamefre(int* a, int* b){

   for (int i = 0; i < 26; i++){
      if (a[i] != b[i]){
         return false;
      }
   }
   return true;
}

/*

int* findAnagrams(char * s, char * p, int* returnSize){
   int weight = 0;
   int cur = 0;
   int cnt = 0;
   int lenp = (int)strlen(p);
   int lens = (int)strlen(s);
   int* ans = (int*)calloc(lens, sizeof(int));
   if (lens < lenp){
      return ans;
   }

   for (int i = 0; i < lenp; i++){
       weight += p[i];
       cur += s[i];
   }

   for (int i = 0; i <= lens - lenp; i++){
      if (cur == weight && isana(s + i, p, lenp)){
         ans[cnt++] = i;
         printf("here same: %d\n", i);
      }

      cur -= s[i];
      cur += s[i + lenp];
   }
   *returnSize = cnt;
   return ans;
}

bool isana(char* str1, char* str2, int len){
   int b1[26] = {0};
   int b2[26] = {0};

   for (int i = 0; i < len; i++){
      b1[str1[i] - 'a']++;
      b2[str2[i] - 'a']++; 
   }

   for (int i = 0; i < 26; i++){
      if (b1[i] != b2[i]){
         return false;
      }
   }
   return true;
}

*/












