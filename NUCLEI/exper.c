#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PRIME 997
#define SZ 1009

typedef struct hash{
   char** list;
   int size;
   int usage;
}hash;

int doublehash(char* sstr, int sz, int i);
int str2val(char* str);
int hash1(char* str, int sz);
int hash2(char* str, int sz);
hash* hash_init();
void hash_insert(hash* h, char* str);
int  hash_search(hash* h, char* str);
bool isprime(int n);
int firstprimebeforen(int n);
int firstprimeaftern(int n);

int main(void) {
   hash* test = hash_init();
   hash_insert(test, "PRINT");
   hash_insert(test, "GREATER");
   hash_insert(test, "SET");
   hash_insert(test, "EQUAL");
   hash_insert(test, "CAR");
   hash_insert(test, "CDR");
   hash_insert(test, "CONS");
   hash_insert(test, "PLUS");
   hash_insert(test, "LENGTH");
   hash_insert(test, "IF");
   hash_insert(test, "WHILE");

   char* str = "HELLO";
   assert(hash_search(test, str) ==hash_search(test, "PRINT"));

   printf("%d\n", hash_search(test, "PRINT"));
   printf("%d\n", hash_search(test, "GREATER"));
   printf("%d\n", hash_search(test, "SET"));
   printf("%d\n", hash_search(test, "EQUAL"));
   printf("%d\n", hash_search(test, "CAR"));
   printf("%d\n", hash_search(test, "CDR"));
   printf("%d\n", hash_search(test, "CONS"));
   printf("%d\n", hash_search(test, "PLUS"));
   printf("%d\n", hash_search(test, "LENGTH"));
   printf("%d\n", hash_search(test, "IF"));
   printf("%d\n", hash_search(test, "WHILE"));
}

int doublehash(char* str, int sz, int i){
   return (hash1(str, sz) + i * hash2(str, sz)) % sz;
}

int str2val(char* str){
   int val = 0;
   while (*str != '\0'){
      val = val * 10 + (*str - 'A');
      str++;
   }
   return val;
}

int hash1(char* str, int sz){
   return str2val(str) % sz;
}
int hash2(char* str, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (str2val(str) % prime);
}

hash* hash_init(){
   hash* this = (hash*)calloc(1, sizeof(hash));
   this->list = (char**)calloc(SZ, sizeof(char*));
   this->size = SZ; 
   return this;
}

void hash_insert(hash* h, char* str){
   int i = 0;
   int index = 0;
   do{
      index = doublehash(str, h->size, i);
      i++;
   }while(h->list[index]);
   printf("Str: %s, index: %d, i: %d\n", str, index, i);
   h->usage++;
   h->list[index] = str;
}

int hash_search(hash* h, char* str){
   int i = 0;
   int index;
   do {
      index = doublehash(str, h->size, i);
      if (h->list[index] && strcmp(h->list[index], str) == 0){
         return index;
      }
      i++;
   } while (h->list[index]);
   return 0;
}

bool isprime(int n){
   for (int i = 2; i <= (int)sqrt(n); i++){
      if (n % i == 0){
         return false;
      }
   }
   return true;
}

int firstprimebeforen(int n){
   if (n <= 3){
      return 3;
   }

   int i = n - 1;
   while (!isprime(i)){
      i--;
   }
   return i;   
}

int firstprimeaftern(int n){
   int i = n + 1;
   while (!isprime(i)){
      i++;
   }
   return i;
}

/*
   printf("%d\n", hash_search(hashtable, "PRINT"));
   printf("%d\n", hash_search(hashtable, "GREATER"));
   printf("%d\n", hash_search(hashtable, "SET"));
   printf("%d\n", hash_search(hashtable, "EQUAL"));
   printf("%d\n", hash_search(hashtable, "CAR"));
   printf("%d\n", hash_search(hashtable, "CDR"));
   printf("%d\n", hash_search(hashtable, "CONS"));
   printf("%d\n", hash_search(hashtable, "PLUS"));
   printf("%d\n", hash_search(hashtable, "LENGTH"));
   printf("%d\n", hash_search(hashtable, "IF"));
   printf("%d\n", hash_search(hashtable, "WHILE"));
*/
