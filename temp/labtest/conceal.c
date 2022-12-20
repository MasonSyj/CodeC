#include <string.h>
#include <ctype.h>

void conceal(const char input[], char output[])
{
   int len = strlen(input);
   output[len] = '\0';
   int digitcnt = 0;
   for(int i = len - 1; i >= 0; i--){
      if (isdigit(input[i])){
         digitcnt++;
      }
      if(digitcnt > 4 && isdigit(input[i])){
         output[i] = '*';
      }else{
         output[i] = input[i];
      }
   }
}
