#include <stdio.h>

int hash(unsigned int sz, char* s);

int main(void){
   char str[] = "Hello World!";
   printf("%d\n", hash(7919, str));
   char str2[] = "Bristol";
   char str3[] = "Nakajima Miyuki";
   char str4[] = "Shanghai";
   printf("%d\n", hash(7919, str2));
   printf("%d\n", hash(7919, str3));
   printf("%d\n", hash(7919, str4));
   return 0;
}

int hash(unsigned int sz, char* s){
   unsigned long hash = 5381;
   int c;
   while (c == (*s++)){
      hash = 33 * hash ^ c;
   }
   return (int)(hash % sz);
}
