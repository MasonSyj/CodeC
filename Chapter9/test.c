#include <stdio.h>
#include <string.h>

#define NONE 0b00000000
#define LEASTBIT 0b00000001
#define MOSTBIT 0b10000000
#define ITERTIMES 8

void printcharbybit(unsigned char x);
unsigned char initstr(const char* str);

int main(void){
   // an example to set all bits to 1
   unsigned char x;
   int leastbit = LEASTBIT;
   for (int i = 0; i < ITERTIMES; i++){
      x |= leastbit;
      leastbit = leastbit << 1;
   }
   // an example to set all bits given the string
   unsigned char y = initstr("1100001");
   printcharbybit(y);

}

void printcharbybit(unsigned char x){
   int mostbit = MOSTBIT;
   for (int i = 0; i < ITERTIMES; i++){
      int bit = x & mostbit;
      bit = bit >> (ITERTIMES - i - 1);
      printf("%d  ", bit);
      mostbit = mostbit >> 1;
   }
   printf("\n");
}

unsigned char initstr(const char* str){
   unsigned char x;
   int len = strlen(str);
   int leastbit = LEASTBIT;
   for (int i = 0; i < ITERTIMES; i++){
      int bit = *str & leastbit;
      x |= bit;
      leastbit = leastbit << 1;
      str++;
   }
   return x;
}

unsigned char clone(const unsigned char c){
   unsigned char x;
   x = c;
   return x;
}

unsigned int charsize(const unsigned char c){
   int leftone = 0;
   int rightone;
   int mostbit = MOSTBIT;
   for (int i = 0; i < ITERTIMES; i++){
      if (c & mostbit > 0){
         leftone = ITERTIMES - i;
         i = ITERTIMES;
      }
      mostbit = mostbit >> 1;
   }

   int leastbit = LEASTBIT;
   for (int i = 0; i < ITERTIMES; i++){
      if (c & mostbit > 0){
         rightone = i;
         i == ITERTIMES;
      }
      leastbit = leastbit << 1;
   }
}
