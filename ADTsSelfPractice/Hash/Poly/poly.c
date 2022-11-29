#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define FIRSTSIZE 97
#define SCALEFACTOR 3

typedef struct cell{
   void* value;
}cell;

typedef struct hash{
   void* table;
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
   this->table = (void*)calloc(FIRSTSIZE, elementsize);
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

   do{
     index = doublehash(newelement, this->size, i, this->elementsize);
     i++;
     
   }while (this->isfilled[index] == 1);
   if (i > 1){
   }
   this->isfilled[index] = 1;

   void* temp = (char*)this->table + index * this->elementsize; 
   memcpy(temp, (char*)newelement, this->elementsize);
}

bool hash_exist(hash* this, void* element){
   int index;
   int i = 0;
   do{
     index = doublehash(element, this->size, i, this->elementsize);
     void* temp = (char*)this->table + index * this->elementsize; 
     if (memcmp(temp, (char*)element, this->elementsize) == 0){
        return true;
     }
     i++;
   }while (this->isfilled[index] == 1);
   return false;
}


int main(void){
   hash* tableofint = hash_init(sizeof(int));
   int a[] = {42, 31, 85, 614, 750, 59, 13, 22, 66, 130};
   for (int i = 0; i < 10; i++){
      hash_insert(tableofint, &a[i]);
   }
   for (int i = 0; i < tableofint->size; i++){
      void* temp = (char*)tableofint->table + i * sizeof(int); 
      printf("%-4d", *(int*)temp);
   }
   printf("\n----------------\n");
   for (int i = 0; i < 10; i++){
      printf("%d\n", hash_exist(tableofint, &a[i]));
   }
////////////////////////////////////////////////////////////////////////////
   printf("--------------------Separate Line---------------------\n");//////
////////////////////////////////////////////////////////////////////////////
   hash* tableofdouble = hash_init(sizeof(double));
   double b[] = {42.5, 33.1, 85.9, 6.14, 750.46, 5.5, 13.432, 2.622, 66.8, 140.5};
   for (int i = 0; i < 10; i++){
      hash_insert(tableofdouble, &b[i]);
   }
   for (int i = 0; i < tableofint->size; i++){
      void* temp = (char*)tableofdouble->table + i * sizeof(double); 
      printf("%-4f\n", *(double*)temp);
   }
   printf("\n----------------\n");
   for (int i = 0; i < 10; i++){
      printf("%d\n", hash_exist(tableofint, &b[i]));
   }

////////////////////////////////////////////////////////////////////////////
   printf("--------------------Separate Line---------------------\n");//////
////////////////////////////////////////////////////////////////////////////
   hash* tableofchar = hash_init(sizeof(char));
   char c[] = "abcdefghij";
   for (int i = 0; i < 10; i++){
      hash_insert(tableofchar, &c[i]);
   }
   for (int i = 0; i < tableofchar->size; i++){
      void* temp = (char*)tableofchar->table + i * sizeof(char); 
      printf("%-4c\n", *(char*)temp);
   }
   printf("\n----------------\n");
   for (int i = 0; i < 10; i++){
      printf("%d\n", hash_exist(tableofchar, &c[i]));
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

