#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char* longestCommonPrefix(char ** strs, int strsSize);
int prefixcnt(char** strs, int strsSize);

int main(void){
   char* test[] = {"flower", "flour", "flow", "abc"};
   char* x = longestCommonPrefix(test, 3);
   puts(x);

   char* test2[] = {""};
   char* x2 = longestCommonPrefix(test2, 1);
   puts(x2);
}

char* longestCommonPrefix(char ** strs, int strsSize){
   if (strsSize == 1){
      return strs[0];	
   }
   int cnt = prefixcnt(strs, strsSize);
   if (cnt == -1){
      char* x = (char*)calloc(1, sizeof(char));
      x[0] = '\0';
      return x;
   }
   char* prefix = (char*)calloc(cnt + 1, sizeof(char));
   strncpy(prefix, strs[0], cnt);
   return prefix;
}

int prefixcnt(char** strs, int strsSize){
   int cnt = 0;
   while (1){
      for (int i = 0; i < strsSize - 1; i++){
         if (cnt > (int)strlen(strs[i + 1]) || strs[i][cnt] != strs[i + 1][cnt]){
//         if (cnt > (int)strlen(strs[i + 1]) || strncmp(strs[i], strs[i + 1], cnt) != 0){
            return cnt;
         }
      }
      cnt++;
   }
}



/*

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int length(char ** strs, int strsSize){
    int length = 1;
    while (1){
        int i = 0;
        for (i = 0; i < strsSize - 1; i++){
            if (strncmp(strs[i], strs[i + 1], length) == 0){
                continue;
            }else{
                break;
            }
        }
        if (i == strsSize - 1){
            length++;
        }else {
            break;
        }
    }
    
    return length - 1;
}

char* longestCommonPrefix(char ** strs, int strsSize){
    int x = length(strs, strsSize);
    char* result = (char*)malloc((x+1) * sizeof(char));
    strncpy(result, strs[0], x);
    return result;
}
*/
