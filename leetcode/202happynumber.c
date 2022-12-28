#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define SIZE 1000
#define SCALEFACTOR 3

typedef struct hash{
   int* list;
   int size;
   int usage;
}hash;

typedef struct coll{
   int* list;
   int end;
   int capacity;
}coll;

int hash1(int val, int sz);
int hash2(int val, int sz);
bool hash_insert(hash* h, int val);
int firstprimebeforen(int n);
int firstprimeaftern(int n);

int new(int n){
   int newnum = 0;
   while (n > 0){
      int digit = n % 10;
      newnum += digit * digit;
      n /= 10;
   }
   return newnum;
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

int doublehash(int val, int sz, int i){
   return (hash1(val, sz) + i * hash2(val, sz)) % sz;
}

int hash1(int val, int sz){
   return val % sz;
}

int hash2(int val, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (val % prime);
}

void coll_insert(coll* c, int val){
   c->list[c->end++] = val;
   if (c->end == c->capacity){
      c->list = (int*)realloc(c->list, c->capacity * SCALEFACTOR * sizeof(int));
      c->capacity *= SCALEFACTOR;
      assert(c->list);
   }
}

void rehash(hash* h){
   coll* presentdata = (coll*)calloc(1, sizeof(coll));
   presentdata->list = (int*)calloc(h->size, sizeof(int));
   for (int i = 0; i < h->size; i++){
      if (h->list[i] != 0){
         coll_insert(presentdata, h->list[i]);
      }
   }
   
   free(h->list);
   h->size = firstprimeaftern(h->size * SCALEFACTOR);
   h->list = (int*)calloc(h->size, sizeof(int));
   h->usage = 0;
   for (int i = 0; i < presentdata->end; i++){
      hash_insert(h, presentdata->list[i]); 
   }

   free(presentdata->list);
   free(presentdata);
}

bool hash_insert(hash* h, int val){
   int i = 0;
   int index = 0;

   do{
      index = doublehash(val, h->size, i);
      i++;
   }while(h->list[index] != 0);
   h->usage++;
   h->list[index] = val;

   if ((double)h->usage / (double)h->size >= 0.7){
      rehash(h);
   }
   if (i == 1){
      return true;
   }else{
      return false;
   }
}

bool isHappy(int n){
   hash* h = (hash*)calloc(1, sizeof(hash));
   h->list = (int*)calloc(SIZE, sizeof(int));
   h->size = SIZE;

   while (n != 1){
      bool isduplicate = hash_insert(h, n);
      if (isduplicate == false){
         return false;
      }
      n = new(n);
   }
   return true;
}

int main(void){
   printf("%d\n", new(19));
   printf("%d\n", new(82));
   printf("%d\n", new(68));
   printf("%d\n", new(100));
}

int firstprimeaftern(int n){
   int i = n + 1;
   while (!isprime(i)){
      i++;
   }
   return i;
}
