#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define STRSIZE 20

int main(void) {
   bool exit = false;
   char str[STRSIZE];
   while (exit == false){
      fgets(str, STRSIZE, stdin);
      int i = 0;
      while(str[i] != '\n'){
         i++;
      }
      str[i] = '\0';
      puts(str);
      if (strcmp(str, "apple") == 0){
        exit = true;
      }
   }
}
