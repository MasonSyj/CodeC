#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>

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
   int end;
   int capacity;
}coll;

bool isprime(int n);
unsigned long key(char* s);
int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
void rehash(hash* h);
void coll_insert(coll* c, unit* onepostcode);
unit* coll_peek(coll* c, int i);
void hash_insert(hash* h, unit* onepostcode);
bool exist(char* s, hash* h);
int search(char* s, hash* h);
bool coll_exist(char* s, coll* c);
void userinteract(hash* h);
void strformat(char* str);

int main(void){
   clock_t start1, end1;

   hash* h1 = (hash*)calloc(1, sizeof(hash));
   assert(h1);
   assert(h1->usage == 0);
   assert(h1->size == 0);
   int size = firstprimeaftern(SIZE);
   h1->postcode = (unit*)calloc(size, sizeof(unit));
   assert(h1->postcode);
   h1->size = size;
   FILE* fp = fopen("orig_postcodes.csv", "r");
   char str[50];
   fgets(str, 50, fp);
   assert(strncmp(str, "id,postcode,latitude,longitude", 30) == 0);
   unit* tmp = (unit*)calloc(1, sizeof(unit));
   while(fgets(str, 50, fp)){
      char temp2[20];
      char temp3[20];
      char temp4[20];
      char* temp = str;
      int i = 0;
      int firstcomma, secondcomma, thirdcomma;
      firstcomma = secondcomma = thirdcomma = 0;
      while (temp[i]){
         if (temp[i] == ','){
            if (firstcomma == 0){
               firstcomma = i + 1;
            }else if (secondcomma == 0){
               secondcomma = i + 1;
               strncpy(temp2, temp + firstcomma, i - firstcomma);
               temp2[i - firstcomma] = '\0';
            }else{
               thirdcomma = i + 1;
               strncpy(temp3, temp + secondcomma, i - secondcomma);
            }
         }

         i++;
      }
      strncpy(temp4, temp + thirdcomma, i - thirdcomma);
      strcpy(tmp->str, temp2);
      tmp->lati = atof(temp3);
      tmp->loti = atof(temp4);
      hash_insert(h1, tmp);
   }
   fclose(fp);
   free(tmp);
   start1 = clock();
   assert(exist("AB11 6UL", h1));
   assert(exist("YO8 9LX", h1));
   assert(exist("YO8 9PS", h1));
   assert(exist("BS1 5UL", h1));
   assert(exist("ZE2 9FW", h1));
   assert(exist("ZE2 9FW", h1));
   assert(exist("YO62 5FH", h1));
   assert(exist("WS7 0AP", h1));
   assert(exist("WF1 4GQ", h1));
   assert(!exist("abc", h1));
   assert(!exist("def", h1));
   assert(!exist("ggg", h1));
   assert(!exist("hhh", h1));
   end1 = clock();
   double hashtime = (double)(end1 - start1)  / CLOCKS_PER_SEC;
   printf("Total time when use hashing: %f\n", hashtime);
   userinteract(h1);

   FILE* fp2 = fopen("postcodes250.txt", "r");
   assert(fp2);
   strcpy(str, "");
   double sum = 0;
   int cnt = 0;
   while(fgets(str, STRSIZE, fp2)){
      strformat(str);
      int i = search(str, h1);
      printf("i: %d\n", i);
      sum += i;
      cnt++;
   }
   printf("sum: %f, cnt: %d, average: %f", sum, cnt, sum / cnt);
   fclose(fp2);
   free(h1->postcode);
   free(h1);
   return 0;
}

bool exist(char* s, hash* h){
   int i = 0;
   int index;
   do {
      index = doublehash(s, h->size, i);
      if (strcmp(h->postcode[index].str, s) == 0){
         return true;
      }
      i++;
   } while (fabs(h->postcode[index].lati - 0.0) > 0.0001);
   return false;
}

int search(char* s, hash* h){
   int i = 0;
   int index;
   do {
      index = doublehash(s, h->size, i);
      if (strcmp(h->postcode[index].str, s) == 0){
         printf("%s %f %f\n", h->postcode[index].str, h->postcode[index].lati, h->postcode[index].loti);
         return i+1;
      }
      i++;
   } while (fabs(h->postcode[index].lati - 0.0) > 0.0001);
   return 0;
}


void coll_insert(coll* c, unit* onepostcode){
   memcpy(&c->postcode[c->end++], onepostcode, sizeof(unit));
   if (c->end == c->capacity){
      c->postcode = (unit*)realloc(c->postcode, c->capacity * SCALEFACTOR * sizeof(unit));
      c->capacity *= SCALEFACTOR;
      assert(c->postcode);
   }
}

unit* coll_peek(coll* c, int i){
   return &c->postcode[i];
}

void rehash(hash* h){
   coll* presentdata = (coll*)calloc(1, sizeof(coll));
   assert(presentdata);
   presentdata->postcode = (unit*)calloc(h->size, sizeof(unit));
   assert(presentdata->postcode);
   for (int i = 0; i < h->size; i++){
      if (fabs(h->postcode[i].lati - 0.0) > 0.000001){
         coll_insert(presentdata, &h->postcode[i]);
      }
   }
   
   free(h->postcode);
   h->size = firstprimeaftern(h->size * SCALEFACTOR);
   h->postcode = (unit*)calloc(h->size, sizeof(unit));
   h->usage = 0;
   for (int i = 0; i < presentdata->end; i++){
      hash_insert(h, &presentdata->postcode[i]); 
   }

   free(presentdata->postcode);
   free(presentdata);
}

void hash_insert(hash* h, unit* onepostcode){
   int i = 0;
   int index = 0;
   do{
      index = doublehash(onepostcode->str, h->size, i);
      i++;
   }while(fabs(h->postcode[index].lati - 0.0) > 0.000001);
   h->usage++;
   memcpy(&h->postcode[index], onepostcode, sizeof(unit));


   if ((double)h->usage / (double)h->size >= 0.7){
      rehash(h);
   }
   
}
   
int doublehash(char* s, int sz, int i){
   return (hash1(s, sz) + i * hash2(s, sz)) % sz;
}

int hash1(char* s, int sz){
   return key(s) % sz;
}

int hash2(char* s, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (key(s) % prime);
}
   
unsigned long key(char* s){
   unsigned long key = 0;
   while (*s != '\0'){
      key = key * 26 + (*s - 'a');
      s++; 
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


void userinteract(hash* h){
   bool exit = false;
   char str[STRSIZE];
   while (exit == false){
      fgets(str, STRSIZE, stdin);
      int i = 0;
      while(str[i] != '\n'){
         i++;
      }
      str[i] = '\0';
      if (exist(str, h)){
         printf("%s exist\n", str);
      }else{
         printf("%s doesn't exist\n", str);
      }
      if (strcmp(str, "apple") == 0){
        exit = true;
      }
   }
}

bool coll_exist(char* s, coll* c){
   for (int i = 0; i < c->end; i++){
      if (strcmp(s, c->postcode[i].str) == 0){
         return true;
      }
   }
   return false;
}


void strformat(char* str){
   for (int i = 0; i < STRSIZE; i++){
      if (str[i] == '\n'){
         str[i] = '\0';
         return;
      }
   }
}

