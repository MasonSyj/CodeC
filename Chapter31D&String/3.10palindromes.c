#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#define SIZE 50

void test();
bool ispalinx(char c[]);

int main(void){
   test();
}

void test(){
   assert(ispalinx("hijkjih"));
   assert(ispalinx("Level, madam, level!"));
   assert(ispalinx("Madam, in Eden I’m Adam,"));
   assert(ispalinx("kayak"));
   assert(ispalinx("A man, a plan, a canal: Panama!"));
}

bool ispalinx(char c[]){
   int i = 0;
   while (c[i]){
      i++;
   }
   int j = i;
   i = 0;
   while (i != j){
      while (!isalpha(c[i])){
         i++;
      }
      
      while (!isalpha(c[j])){
         j--;
      }
      
      if (tolower(c[i]) != tolower(c[j])){
         return false;
      }
      if (i == j){
         return true;
      }else{
         i++;
         j--;
      }
   }
   return true;
}
