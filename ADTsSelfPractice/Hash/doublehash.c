#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>


int hash1(char* s, int sz);
int hash2(char* s, int sz);
void doublehash(char* s, int sz, char** a);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
bool isprime(int n);
void test();

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
   int size = firstprimeaftern(3000);
   char** a = (char**)calloc(size, sizeof(char));
   assert(a);

   assert(hash1("cba", size) == 2081);
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

void doublehash(char* s, int sz, char** a){
   int i = 0;
   while (a[hash1(s, sz) + i * hash2(s, sz)]){
      i++;
   }
   a[hash1(s, sz) + i * hash2(s, sz)] = s;
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




