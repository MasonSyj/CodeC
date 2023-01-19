#include <stdio.h>
#include <stdbool.h>

#define EXE

#define BOOL

void x(){
   #ifdef BOOL
      printf("I'm Back\n");
   #endif
}

int main(void){
   
   #ifdef BOOL
      #undef BOOL
      printf("CANCELLED.\n");
   #endif

   #if defined EXE && defined BOOL
      printf("Hello World.\n");
   #endif

   #ifndef BOOL
      printf("GoodBye World.\n");
   #endif

   #define BOOL

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
