#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define STRSIZE 20
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

bool isprime(int n);
unsigned long sum(char* s);
int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);

int main(void){
   hash* h1 = (hash*)calloc(1, sizeof(hash));
   assert(h1);
   assert(h1->usage == 0);
   assert(h1->size == 0);
   h1->postcode = (unit*)calloc(SIZE, sizeof(unit));
   assert(h1->postcode);
}

void hash_insert(hash* h, unit* onepostcode){
   int i = 0;
   int index = 0;

   do{
      index = doublehash(onepostcode->str, h->size, i);
      i++;
   }while(h->postcode[index].str);
   
   memcpy(&h->postcode[index], onepostcode, sizeof(unit));
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
