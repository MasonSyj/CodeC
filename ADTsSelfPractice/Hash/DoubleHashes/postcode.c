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
int coll_insert(coll* c, unit* onepostcode);
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
   
   FILE* fp = fopen("orig_postcodes.csv", "r");
   char code[20];
   double second;
   double third;
   char str[50];
   char temp1[20];
   char temp2[20];
   char temp3[20];
   char temp4[20];
   fgets(str, 50, fp);
   assert(strncmp(str, "id,postcode,latitude,longitude", 30) == 0);
   unit* tmp = (unit*)calloc(1, sizeof(unit));
   while(fgets(str, 50, fp)){
      char* temp = str;
      int i = 0;
      int commacnt = 0;
      int head = 0;
      bool one, two, three;
      one = two = three = false;
      while (temp[i]){
         if (temp[i] == ','){
            commacnt++;
         }
         if (commacnt == 1 && one == false){
            strncpy(temp1, temp + head, i - head);
            head = i + 1;
            one = true;
         }
         if (commacnt == 2 && two == false){
            strncpy(temp2, temp + head, i - head);
            head = i + 1;
            two = true;
         }
         if (commacnt == 3 && three == false){
            strncpy(temp3, temp + head, i - head);
            head = i + 1;
            three = true;
         }
            
         i++;
      }
      strncpy(temp4, temp + head, i - head);
      strcpy(code, temp2);
      second = atof(temp3);
      third = atof(temp4);
      strcpy(tmp->str, code);
      strcat(tmp->str, "\0");
      tmp->lati = second;
      tmp->loti = third;
      hash_insert(h1, tmp);
   }
   
   assert(exist("PO33 3LW", h1));
   assert(exist("PO33 3RJ", h1));
   assert(exist("PO33 2LZ", h1));
   assert(exist("PO33 2RA", h1));
   assert(!exist("abc", h1));
   assert(!exist("def", h1));
   assert(!exist("ggg", h1));
   assert(!exist("hhh", h1));
   
   
   fclose(fp);
   free(tmp);
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

int coll_insert(coll* c, unit* onepostcode){
   memcpy(&c->postcode[c->end++], onepostcode, sizeof(unit));
   return c->end;
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
   
   int newsz = firstprimeaftern(h->size * SCALEFACTOR);
   printf("old size: %d, new size: %d, usage: %d\n", h->size, newsz, h->usage);
   h->size = newsz;
   unit* newpostcode = (unit*)calloc(newsz, sizeof(unit));
   unit* tmp = h->postcode;
   h->postcode = newpostcode;
   free(tmp);
   int tmpusage = h->usage;
   for (int i = 0; i < h->size; i++){
      if (fabs(h->postcode[i].lati - 0.0) > 0.000001){
         hash_insert(h, &presentdata->postcode[i]); 
      }
   }
   h->usage = tmpusage;
   printf("resize finished.\n");
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
   printf("usgae increase to: %d\n", h->usage);
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
