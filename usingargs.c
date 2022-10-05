#include <stdio.h>

int main(int argc, char* argv[]){
   printf("You typed %d arguments\n", argc);
   printf("The name of your excutable is %s\n", argv[0]);
   for (int i = 1; i < argc; i++){
      printf("argc: %d, argv[%d]:%s\n", i, i, argv[i]);
   }
   return 0;
}
