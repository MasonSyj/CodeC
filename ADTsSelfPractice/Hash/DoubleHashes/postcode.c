#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define STRSIZE 50
#define SIZE 1000
#define SCALEFACTOR 4

typedef struct unit{
   char str[STRSIZE];
   double lati;
   double loti;
}unit;

typedef struct hash{
   unit* postcode;
   int usage;
   int size;
}hash;

typedef struct coll{
   unit* postcode;
}coll;

bool isprime(int n);
unsigned long sum(char* s);
int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
void resize(hash* h);
int coll_insert(coll* c, unit* onepostcode);
unit* coll_peek(coll* c, int i);
void hash_insert(hash* h, unit* onepostcode);

int main(void){
   hash* h1 = (hash*)calloc(1, sizeof(hash));
   assert(h1);
   assert(h1->usage == 0);
   assert(h1->size == 0);
   h1->postcode = (unit*)calloc(SIZE, sizeof(unit));
   assert(h1->postcode);
   h1->size = SIZE;
   
   FILE* fp = fopen("orig_postcodes.csv", "r");
   char temp[STRSIZE];
   while (fgets(temp, STRSIZE, fp) == 1){
      fs
   }
   
}

int coll_insert(coll* c, unit* onepostcode){
   int i = 0;
   while (strcmp(c->postcode[i].str, "") != 0){
      i++;
   }
   memcpy(&c->postcode[i], onepostcode, sizeof(unit));
   return i;
}

unit* coll_peek(coll* c, int i){
   return &c->postcode[i];
}

void resize(hash* h){
   coll* presentdata = (coll*)calloc(1, sizeof(coll));
   assert(presentdata);
   presentdata->postcode = (unit*)calloc(h->size, sizeof(unit));
   assert(presentdata->postcode);
   for (int i = 0; i < h->size; i++){
      if (strcmp(h->postcode[i].str, "") != 0){
         coll_insert(presentdata, &h->postcode[i]);
      }
   }
   
   int newsz = firstprimeaftern(h->size);
   unit* newpostcode = (unit*)calloc(newsz, sizeof(unit));
//   h->size = newsz;
   unit* tmp = h->postcode;
   h->postcode = newpostcode;
   free(tmp);
   int tmpusage = h->usage;
   for (int i = 0; i < h->size; i++){
      if (strcmp(presentdata->postcode[i].str, "") != 0){
         hash_insert(h, &presentdata->postcode[i]); 
      }
   }
   h->usage = tmpusage;
}

void hash_insert(hash* h, unit* onepostcode){
   int i = 0;
   int index = 0;

   do{
      index = doublehash(onepostcode->str, h->size, i);
      i++;
//   }while(fabs(h->postcode[index].lati - 0.0) < 0.000001);
   }while(strcmp(h->postcode[index].str, "") != 0);
   h->usage++;
   memcpy(&h->postcode[index], onepostcode, sizeof(unit));
   
   if (h->usage / h->size >= 0.7){
      resize(h);
   }
   
}
   
int doublehash(char* s, int sz, int i){
   return (hash1(s, sz) + i * hash2(s, sz)) % sz;
}

int hash1(char* s, int sz){

   return (int)(sum(s) % sz);
}

int hash2(char* s, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (sum(s) % prime);
}
   
unsigned long sum(char* s){
   unsigned long sum = 0;
   while (*s != '\0'){
      sum = sum * 26 + (*s - 'a');
      s++; 
   }
   return sum;
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
