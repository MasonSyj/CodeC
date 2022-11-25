#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define SCALEFACTOR 4
#define SZ 10
#define STRSIZE 25


int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
bool isprime(int n);
void test();
char** insert(char* s, int* sz, char** a);
char** resize(char** a, int* sz);

int main(){
//   test();
/*
*/
   int size = firstprimeaftern(SZ);
   char** a = (char**)calloc(size, sizeof(char*));
   assert(a);
   FILE* fp = fopen("34words.txt", "r");
   assert(fp);
   char temp[STRSIZE];
   while (fgets(temp, STRSIZE, fp)){
      temp[strlen(temp) - 1] = '\0';
      a = insert(temp, &size, a);
      printf("size: %d\n", size);
   }

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
   a = insert("cba", &size, a);
   a = insert("apple", &size, a);
   a = insert("bristol", &size, a);
   a = insert("shanghai", &size, a);
   a = insert("computer", &size, a);
   a = insert("science", &size, a);
   printf("%p\n", (void*)a);
   puts(a[2]);
   a = insert("england", &size, a);
   puts(a[2]);
   printf("%p\n", (void*)a);
//   int x9 = insert("naruto", x8, a);


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

char** insert(char* s, int* sz, char** a){
   static int inserttimes = 0;
   int i = 0;
   while (a[doublehash(s, *sz, i)]){
      i++;
   }
   a[doublehash(s, *sz, i)] = s;
   inserttimes++;

   if ((double)inserttimes / (double)*sz >= 0.6){
      a = resize(a, sz);
   }
   return a;
}

char** resize(char** a, int* sz){
   int newsz = firstprimeaftern(*sz * SCALEFACTOR);
   a = (char**)realloc(a, sizeof(char*) * newsz);
   *sz = newsz;
   assert(a);
   return a;
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

