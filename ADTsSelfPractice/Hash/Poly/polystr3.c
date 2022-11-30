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
void hash_insert(hash** pthis, void* newelement);
bool hash_exist(hash* this, void* element);
void hash_free(hash** point2hash);
void hash_show(hash* this);

void hash_free(hash** pointofhash){
   hash* this = *pointofhash;
   if (this == NULL){
      return;
   }

   free(this->isfilled);
   free(this->table);
   free(this);
   *pointofhash = NULL;
   return;
}

hash* hash_init(int elementsize){
   hash* this = (hash*)calloc(1, sizeof(hash));
   assert(this);
   this->table = (void*)calloc(FIRSTSIZE, sizeof(char*));
   assert(this->table);
   this->isfilled = (bool*)calloc(FIRSTSIZE, sizeof(bool));
   assert(this->isfilled);
   this->size = FIRSTSIZE;
   this->elementsize = elementsize;
   hash_show(this);
   return this;
}

void hash_insert(hash** pthis, void* newelement){
   hash* this = *pthis;
   int index;
   int i = 0;
   int looptimes = strlen((char*)newelement);
   do{
     index = doublehash(newelement, this->size, i, looptimes);
     i++;
   }while (this->isfilled[index] == 1);
   this->isfilled[index] = 1;
   printf("%d: ", index);
   puts((char*)newelement);
/*
   char* storage = (char*)calloc(1, looptimes + 1);
   strcpy(storage, newelement);
   puts(storage);
*/
   char* temp = (char*)this->table + index;
   temp = (char*)calloc(looptimes + 1, sizeof(char));
   printf("address of temp: %p\n", temp);
   strncpy(temp, newelement, looptimes + 1);
   printf("above element inserted.\n");
}

bool hash_exist(hash* this, void* element){
   int index;
   int i = 0;
   puts((char*)element);
   int len = (int)strlen((char*)element);
   printf("%d", len);
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

void hash_show(hash* this){
   for (int i = 0; i < this->size; i++){
      printf("%d: %s, address: %p\n", i, this->table[i], this->table[i]);
   }
   printf("-------------------\n");
}


int main(void){
   hash* tableofstr = hash_init(sizeof(char*));
   char* a[] = {"applejfsal", "hello", "bristol", "china", "different", "computer", "xjx", "miyuki", "england", "mason"};
   for (int i = 0; i < 10; i++){
      hash_insert(&tableofstr, (void*)(*(a + i)));
   }
   printf("\n----------------\n");
   hash_show(tableofstr);
   printf("%p\n", tableofstr->table + 10);

   hash_free(&tableofstr);
   assert(tableofstr == NULL);
   return 0;
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

