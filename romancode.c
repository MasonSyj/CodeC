#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void romanencry(char* s);
void romandecry(char* s);

int main(void){
   char s[] = "i love you";
   romanencry(s);
   puts(s);
   romandecry(s);
   puts(s);
}

void romanencry(char* s){
   while(*s){
      if (isalpha(*s)){
         *s = (*s - 'a' + 3) % 26 + 'a';
      }
      s++;
   }
/*	
   int len = strlen(s);
   for (int i = 0; i < len; i++){
      if (isalpha(s[i])){
         s[i] = (s[i] - 'a' + 3) % 26 + 'a';
      }
   }
*/
}

void romandecry(char* s){
   while(*s){
      if (isalpha(*s)){
         int index = *s - 'a' - 3;
         if (index < 0){
            index += 26;
         }
         *s = index % 26 + 'a';
      }
      s++;
   }	
}
