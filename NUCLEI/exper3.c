#include <stdio.h>
#include <stdbool.h>


#define BOOL EXE

void x(){
   #ifdef BOOL
      printf("I'm Back\n");
   #endif
}

int main(void){
   bool EXE = true;
   #ifdef BOOL
      #undef BOOL
   #endif

   #ifdef BOOL
      printf("Hello World.\n");
   #endif

   #ifndef BOOL
      printf("GoodBye World.\n");
   #endif

   #define BOOL EXE


   x();
}


/*
   bool EXE = true;
   #ifdef BOOL
      EXE = false;
   #endif

   #ifdef BOOL
      printf("Hello World.\n");
   #endif

   #ifndef BOOL
      printf("GoodBye World.\n");
   #endif

   EXE = true;

   #ifdef BOOL
      printf("I'm Back\n");
   #endif
*/
