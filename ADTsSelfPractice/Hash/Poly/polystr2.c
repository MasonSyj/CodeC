#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define FIRSTSIZE 97
#define SCALEFACTOR 3
#define STRSIZE 20

typedef struct cell{
   void* value;
}cell;

typedef struct hash{
   void** table;
   int size;
   int elementsize;
   bool* isfilled;
}hash;

bool isprime(int n);
unsigned long key(void* newelement, int looptimes);
int hash1(void* newelement, int sz, int looptimes);
int hash2(void* newelement, int sz, int looptimes);
int doublehash(void* newelement, int sz, int i, int looptimes);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
hash* hash_init(int elementsize);
void hash_insert(hash* this, void* newelement);
bool hash_exist(hash* this, void* element);

hash* hash_init(int elementsize){
   hash* this = (hash*)calloc(1, sizeof(hash));
   assert(this);
   this->table = (void**)calloc(FIRSTSIZE, elementsize);
   assert(this->table);
   this->isfilled = (bool*)calloc(FIRSTSIZE, sizeof(bool));
   assert(this->isfilled);
   this->size = FIRSTSIZE;
   this->elementsize = elementsize;
   return this;
}

void hash_insert(hash* this, void* newelement){
   int index;
   int i = 0;
   int looptimes = strlen((char*)newelement);
   do{
     index = doublehash(newelement, this->size, i, looptimes);
     i++;
   }while (this->isfilled[index] == 1);
   this->isfilled[index] = 1;
   char* str = (char*)newelement;
   puts(str);
   puts((char*)newelement);
   void* temp = (char*)this->table + index;
   temp = (char*)newelement;
   puts((char*)temp);
}

bool hash_exist(hash* this, void* element){
   int index;
   int i = 0;
   puts((char*)element);
   int len = strlen((char*)element);
//   printf()
   do{
     index = doublehash(element, this->size, i, len);
     void* temp = (char*)this->table + index;
     puts((char*)temp);
     if (strncmp((char*)temp, (char*)element, len) == 0){
        return true;
     }
     i++;
   }while (this->isfilled[index] == 1);
   return false;
}


int main(void){
   hash* tableofstr = hash_init(sizeof(char*));
   const char* a[] = {"applejfsal", "hello", "bristol", "china", "different", "computer", "xjx", "miyuki", "england", "mason"};
   for (int i = 0; i < 10; i++){
      puts(*(a + i));
      hash_insert(tableofstr, (void*)(*(a + i)));
   }
/*
   for (int i = 0; i < tableofstr->size; i++){
      void* temp = (char**)tableofstr->table + i * sizeof(char*); 
      puts((char*)temp);
   }
*/
   printf("\n----------------\n");
   for (int i = 0; i < 10; i++){
      printf("%d\n", hash_exist(tableofstr, (void*)(*(a + i))));
   }

}
   
int doublehash(void* newelement, int sz, int i, int looptimes){
   return (hash1(newelement, sz, looptimes) + i * hash2(newelement, sz, looptimes)) % sz;
}

int hash1(void* newelement, int sz, int looptimes){
   return key(newelement, looptimes) % sz;
}

int hash2(void* newelement, int sz, int looptimes){
   int prime = firstprimebeforen(sz);
   return prime - (key(newelement, looptimes) % prime);
}
   
unsigned long key(void* newelement, int looptimes){
   unsigned long key = 0;

   for (int i = 0; i < looptimes; i++){
      key = key * 2 + (*(char*)newelement + 5);
      newelement = 1 + (char*)newelement; 
   }

   return key;
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

bool isprime(int n){
   for (int i = 2; i <= (int)sqrt(n); i++){
      if (n % i == 0){
         return false;
      }
   }
   return true;
}

