#include <stdio.h>

void cap(char* str);

int main(void){
   char str[] = "The first part of the program has to deal with the first character of the string";
   puts(str);
   cap(str);
   puts(str);
}

void cap(char* str){
   while (*str != '\0'){
      if (*str == ' '){
         if (*(str + 1) >= 'a'){
            if (*(str + 1) <= 'z'){
               *(str + 1) += 'A' - 'a';
            }
         }
      }
      str++;
   }
}
