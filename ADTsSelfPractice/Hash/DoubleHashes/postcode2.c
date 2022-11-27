#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define STRSIZE 50
#define SIZE 100
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
}coll;

bool isprime(int n);
unsigned long sum(char* s);
int hash1(char* s, int sz);
int hash2(char* s, int sz);
int doublehash(char* s, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
void resize(hash* h);
void coll_insert(coll* c, unit* onepostcode);
unit* coll_peek(coll* c, int i);
void hash_insert(hash* h, unit* onepostcode);
bool exist(char* s, hash* h);

int main(void){
   hash* h1 = (hash*)calloc(1, sizeof(hash));
   assert(h1);
   assert(h1->usage == 0);
   assert(h1->size == 0);
   int size = firstprimeaftern(SIZE);
   h1->postcode = (unit*)calloc(size, sizeof(unit));
   assert(h1->postcode);
   h1->size = size;
//"orig_postcodes.csv"
   FILE* fp = fopen("exper.txt", "r");
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

   assert(exist("AB11 6UL", h1));
   assert(exist("YO8 9LX", h1));
   assert(exist("YO8 9PS", h1));
   assert(!exist("BS1 5UL", h1));
   assert(!exist("abc", h1));
   assert(!exist("def", h1));
   assert(!exist("ggg", h1));
   assert(!exist("hhh", h1));

   fclose(fp);
   free(tmp);
   free(h1->postcode);
   free(h1);
   return 0;
}

bool exist(char* s, hash* h){
   int i = 0;
   while (fabs(h->postcode[doublehash(s, h->size, i)].lati - 0.0) > 0.0001){
      if (strcmp(h->postcode[doublehash(s, h->size, i)].str, s) == 0){
         return true;
      }
      i++;
   }
   return false;
}

void coll_insert(coll* c, unit* onepostcode){
   memcpy(&c->postcode[c->end++], onepostcode, sizeof(unit));
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
      resize(h);
   }
   
}
   
int doublehash(char* s, int sz, int i){
   return (hash1(s, sz) + i * hash2(s, sz)) % sz;
}

int hash1(char* s, int sz){
   return sum(s) % sz;
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
