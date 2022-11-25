#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define SCALEFACTOR 3
#define SZ 10


int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
bool isprime(int n);
void test();
int insert(char* s, int sz, char** a);
int resize(char** a, int sz);

int main(void){
   test();

}

void test(){
   assert(isprime(3));
   assert(!isprime(4));
   assert(isprime(5));
   assert(!isprime(6));
   assert(isprime(7));
   assert(firstprimeaftern(6) == 7);
   assert(firstprimeaftern(7) == 11);
   assert(firstprimebeforen(7) == 5);
   assert(firstprimebeforen(9) == 7);
   int size = firstprimeaftern(SZ);
   char** a = (char**)calloc(size, sizeof(char*));
   assert(a);

/*
   assert(hash1("cba", size) == 2081);
   printf("%d\n", hash2("cba", size));
   printf("%d\n", hash2("apple", size));
   printf("%d\n", hash2("bristol", size));
   printf("%d\n", hash2("shanghai", size));
   printf("%d\n", doublehash("cba", size, 0));
   printf("%d\n", doublehash("apple", size, 0));
   printf("%d\n", doublehash("bristol", size, 0));
   printf("%d\n", doublehash("shanghai", size, 0));
*/
   int x1 = insert("cba", size, a);
   int x2 = insert("apple", size, a);
   int x3 = insert("bristol", size, a);
   int x4 = insert("shanghai", size, a);
   int x5 = insert("computer", size, a);
   int x6 = insert("science", size, a);
   int x7 = insert("england", size, a);
   printf("%d %d %d %d %d %d %d", x1, x2, x3, x4, x5, x6, x7);
}

int hash1(char* s, int sz){
   unsigned long sum = 0;
   while (*s != '\0'){
      sum = sum * 26 + (*s - 'a' + 1);
      s++; 
   }

   return (int)(sum % sz);
}

int hash2(char* s, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (hash1(s, sz) % prime);
}

int insert(char* s, int sz, char** a){
   static int inserttimes = 0;
   int i = 0;
   while (a[doublehash(s, sz, i)] != NULL){
      i++;
   }
   a[doublehash(s, sz, i)] = s;
   inserttimes++;

   if ((double)inserttimes / (double)sz >= 0.6){
      sz = resize(a, sz);
   }
   return sz;
}

int resize(char** a, int sz){
   int newsz = firstprimeaftern(sz * SCALEFACTOR);
   a = (char**)realloc(a, sizeof(char*) * newsz);
   return newsz;
}

int doublehash(char* s, int sz, int i){
   return (hash1(s, sz) + i * hash2(s, sz)) % sz;
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

