#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define BASE 26
#define MODVALUE 97
#define STRSIZE 100

int key(char* s);
int key2(char* s);
int key3(char* s, unsigned long* medium);
void test();


int main(void){
   test();
}

void test(){
   printf("%d\n", key("neill"));
   printf("%d\n", key("mason"));
   printf("%d\n", key("bristol"));
   printf("%d\n", key("computer"));
   printf("--------------------Seperate Line-------------\n");
   printf("%d\n", key2("neill"));
   printf("%d\n", key2("mason"));
   printf("%d\n", key2("bristol"));
   printf("%d\n", key2("computer"));
   printf("--------------------Seperate Line-------------\n");
   unsigned long medium = 0;
   printf("%d\n", key3("Jiang", &medium));
   printf("%d\n", key3("neill", &medium));
   printf("%d\n", key3("mason", &medium));
   printf("%ld\n", medium);
}
int key(char* s){
   unsigned long key = 0;
   while (*s != '\0'){
      key = key * BASE + (*s - 'a');
      s++;
   }
   return (int)(key % MODVALUE);
}

int key2(char* s){
   unsigned long key = 0;
   while (*s != '\0'){
      key = (key * BASE + (*s - 'a'))% MODVALUE;
      s++;
   }
   return (int)(key);
}

int key3(char* s, unsigned long* medium){
   int len = strlen(s);
   unsigned long key = 0;
   for (int i = len - 1; i >= 0; i --){
      key += (s[i] - 'a') * pow(BASE, len - 1 - i);
      if (i == 1){
         *medium = key;
      }
   }
   return (int)(key % MODVALUE);
}


