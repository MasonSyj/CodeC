#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ROW 3

char ** letterCombinations(char * digits, int* returnSize);
void test();

int main(void) {
   test();
/*
   char* str1 = "2";
   int size;
   char** table = letterCombinations(str1, &size);
   for (int i = 0; i < size; i++){
      puts(table[i]);
   }
*/
}

char ** letterCombinations(char * digits, int* returnSize){
   const char* table[] = {"abc", "def", "pqrs"};
   int arrsize[ROW];
   int arrcnt[ROW] = {0};
   int total = 1;
   for (int i = 0; i < ROW; i++){
      arrsize[i] = strlen(table[i]);
      total *= arrsize[i];
      printf("arrsize[%d], %d\n", i, arrsize[i]);
   }
   printf("total: %d\n", total);
   int i = 0;
   while (i < total){
      for (int index = ROW - 1; index >= 0; index--){
         if (arrcnt[index] == arrsize[index]){
            arrcnt[index] = 0;
            arrcnt[index - 1]++;
         }else{
            break;
         }
      }
      printf("%d: %d %d %d. %c%c%c\n", i, arrcnt[0], arrcnt[1], arrcnt[2], table[0][arrcnt[0]], table[1][arrcnt[1]], table[2][arrcnt[2]]);

      arrcnt[ROW - 1]++;
      
      i++;
   }
}

/*
char ** letterCombinations(char * digits, int* returnSize){
    const char* letter[] = {"", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    char** table;
    int choices;
    int size = 1;
    int cnt = 0;
    while (*digits){
       switch(*digits){
           case '7': choices = 4; break;
           case '9': choices = 4; break;
           default: choices = 3; break;
       }
       size *= choices;
       cnt++;
       if (!table){
          table = (char**)calloc(choices, sizeof(char*));
       }else{
          table = (char**)realloc(table, choices * size);
       }

       for (int i = 0; i < choices; i++){
           if (table[i]){
              table[i] = (char*)realloc(table[i], (cnt + 1) * sizeof(char));
           }else{
              table[i] = (char*)calloc(cnt + 1, sizeof(char));
           }
           table[i] = (char*)calloc(cnt + 1, sizeof(char));
           table[i][0] = letter[*digits - '0' - 1][i];
       }
    }
    *returnSize = 3;
    return table;
}
*/