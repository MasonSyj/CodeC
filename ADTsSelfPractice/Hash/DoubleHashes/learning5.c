#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define SCALEFACTOR 5
#define SZ 10
#define STRSIZE 25

int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
bool isprime(int n);
void test();
char** insert(char* s, int* sz, char** a, bool increment, int* collison);
char** resize(char** a, int* sz, int* collison);

int main(){
//   test();

   int size = firstprimeaftern(SZ);
   char** a = (char**)calloc(size, sizeof(char*));
   assert(a);
   FILE* fp = fopen("34words.txt", "r");
   assert(fp);
   char temp[STRSIZE];
   int collison = 0;
   while (fgets(temp, STRSIZE, fp)){
      temp[strlen(temp) - 1] = '\0';
      a = insert(temp, &size, a, 1, &collison);
   }
   printf("MAXIMUM collison: %d\n", collison);

   for (int i = 0; i < size; i++){
      if (a[i]){
         for (int j = i + 1; j < size; j++){
            if (a[j]){
               if (hash1(a[i], size) == hash1(a[j], size)){
                  printf("%s and %s are equal in hash1.\n", a[i], a[j]);
                  if (hash2(a[i], size) == hash2(a[j], size)){
                     printf("also equal in hash2\n-----------------\n"); 
                  }
               }
            }
         }
      }
   }
}

unsigned long sum(char* s){
   unsigned long sum = 0;
   while (*s != '\0'){
      sum = sum * 26 + (*s - 'a');
      s++; 
   }
   return sum;
}

int hash1(char* s, int sz){

   return (int)(sum(s) % sz);
}

int hash2(char* s, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (sum(s) % prime);
}

char** insert(char* s, int* sz, char** a, bool increment, int* collison){
   static int inserttimes = 0;
   int i = 0;
   while (a[doublehash(s, *sz, i)]){
      i++;
   }
   *collison = i > *collison ? i : *collison;
   int len = strlen(s);
   len++;
   a[doublehash(s, *sz, i)] = (char*)calloc(len, sizeof(char));
   strcpy(a[doublehash(s, *sz, i)], s);
   
   if (increment == true){
      inserttimes++;
   }else{
      return a;
   }

   if ((double)inserttimes / (double)*sz >= 0.7){
      a = resize(a, sz, collison);
   }
   return a;
}

char** resize(char** a, int* sz, int* collison){

   int newsz = firstprimeaftern(*sz * SCALEFACTOR);
   char** newa = (char**)calloc(newsz, sizeof(char*));
   assert(newa);
   for (int i = 0; i < *sz; i++){
      if (a[i]){
         newa = insert(a[i], &newsz, newa, 0, collison);
      }
   }
   *sz = newsz;
   free(a);
   return newa;
}

int doublehash(char* s, int sz, int i){
   int value = (hash1(s, sz) + i * hash2(s, sz)) % sz;
   return value;
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
   int collison = 0;
   a = insert("cba", &size, a, true, &collison);
   a = insert("apple", &size, a, true, &collison);
   a = insert("bristol", &size, a, true, &collison);
   a = insert("shanghai", &size, a, true, &collison);
   a = insert("computer", &size, a, true, &collison);
   a = insert("science", &size, a, true, &collison);
   printf("%p\n", (void*)a);
   puts(a[2]);
   a = insert("england", &size, a, true, &collison);
   puts(a[2]);
   printf("%p\n", (void*)a);

}
