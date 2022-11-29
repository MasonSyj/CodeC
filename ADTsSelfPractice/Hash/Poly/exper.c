#include <stdio.h>
#include <string.h>

unsigned long key(void* newelement, int looptimes);

int main(void){

   char x = 'x';
   int h = 0;
   double j = 5.5;
   unsigned long key1 = key(&x, sizeof(x));
   unsigned long key3 = key(&h, sizeof(h));
   unsigned long key4 = key(&j, sizeof(j));
   printf("%ld %ld %ld\n", sizeof(x), sizeof(h), sizeof(j));
   printf("%ld %ld %ld\n", key1, key3, key4);
}

unsigned long key(void* newelement, int looptimes){
   unsigned long key = 0;

   for (int i = 0; i < looptimes; i++){
      key = key * 2 + (*(char*)newelement + 5);
      newelement = 1 + (char*)newelement; 
   }

   return key;
}
