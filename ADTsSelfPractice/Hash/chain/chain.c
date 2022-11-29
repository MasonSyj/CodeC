#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define ARRSIZE 5
#define STRSIZE 50
//when a chain have elements more than 5, then rehash
#define THRESHOLD 5
#define SCALEFACTOR 4

typedef struct cell{
   char str[STRSIZE];
   double lati;
   double loti;
   struct cell* next;
}cell;

typedef struct chain{
   cell* arr;
   int size;
   int cellcnt;
}chain;

typedef struct coll{
   cell* arr;
   int cellcnt;
   int end;
}coll;

unsigned long sum(char* s);
int hash(char* s, int sz);
void insert(chain* list, cell* c);
void search(char* str, chain* list);
void rehash(chain* list);
void hash_free(chain* list);
bool isprime(int n);
int firstprimeaftern(int n);
coll* coll_init(int size);
void coll_insert(coll* collection, cell* c);
void show(chain* list);

void show(chain* list){
   for (int i = 0; i < list->size; i++){
      if (fabs(list->arr[i].lati - 0.0) > 0.00001){
         printf(" |first: %s| ", list->arr[i].str);
      }
      cell* temp = list->arr[i].next;
      while (temp){
         printf(" |%s| ", temp->str);
         temp = temp->next;
      }
      printf("\n-----------\n");
   }
   printf("\n");
}

int main(void) {
   chain* chain1 = (chain*)calloc(1, sizeof(chain));
   assert(chain1);
   chain1->arr = (cell*)calloc(ARRSIZE, sizeof(cell));
   assert(chain1->arr);
   chain1->size = ARRSIZE;

   FILE* fp = fopen("exper.txt", "r");
   assert(fp);
   char str[50];
   fgets(str, 50, fp);
   assert(strncmp(str, "id,postcode,latitude,longitude", 30) == 0);
   cell* tmp = (cell*)calloc(1, sizeof(cell));
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
      tmp->next = NULL;
      insert(chain1, tmp);
   }
   free(tmp);
   printf("%d\n", chain1->cellcnt);
   hash_free(chain1);   
   /*
   int cnt = 0;
   for (int i = 0; i < chain1->size; i++){
      cell* temp = &chain1->arr[i];

      while(temp){
         printf(" |%s| ", temp->str);
         temp = temp->next;
         cnt++;
      }
      printf("\n----------------------------------\n");
   }
   printf("TOTAL %d CELLS", cnt);
*/
}

void search(char* str, chain* list){
   int index = 0;
   index = hash(str, list->size);
   cell* temp = &list->arr[index];
   while(temp){
      if(strcmp(str, temp->str) == 0){
         printf("%s %f %f\n",str, temp->lati, temp->loti);
         return;
      }
      temp = temp->next;
   }
   printf("Not found.\n");
   return;
}

coll* coll_init(int size){
   coll* collection = (coll*)calloc(1, sizeof(coll));
   assert(collection);
   collection->arr = (cell*)calloc(size * 2, sizeof(cell));
   assert(collection->arr);
   collection->cellcnt = size * 2;
   return collection;
}

void coll_insert(coll* collection, cell* c){
   collection->arr[collection->end++] = *c;
}

void coll_free(coll** c){
   coll* this = *c;
   free(this->arr);
   free(this);
   return;
}

void insert(chain* list, cell* c){
   int index = 0;
   index = hash(c->str, list->size);
   if (fabs(list->arr[index].lati - 0.0) < 0.00001){
      memcpy(&list->arr[index], c, sizeof(cell));
      (&list->arr[index])->next = NULL;
      list->cellcnt++;
      return;
   }

   int i = 0;
   cell* temp = &list->arr[index];
   cell* previous = temp;
   while (temp){
      previous = temp;
      temp = temp->next;
      i++;
   }
   temp = (cell*)calloc(1, sizeof(cell));
   previous->next = temp;
   memcpy(temp, c, sizeof(cell));
   temp->next = NULL;
   list->cellcnt++;

   if (i == 5){
      show(list);
      printf("this hash table got %d elements\n", list->cellcnt);
      rehash(list);
   }

   return;
}

void rehash(chain* list){
   coll* collection = coll_init(list->cellcnt);
   assert(collection);
   for (int i = 0; i < list->size; i++){
      if (fabs(list->arr[i].lati - 0.0) > 0.0){
         coll_insert(collection, &list->arr[i]);
      }
      cell* temp = (&list->arr[i])->next;
      while(temp){
         coll_insert(collection, temp);
         temp = temp->next;
      }
   }
   
   printf("coll now has %d elements.\n", collection->end);
   free(list->arr);
   int newsize = firstprimeaftern(list->size * SCALEFACTOR);
   list->arr = (cell*)calloc(newsize, sizeof(cell));
   assert(list->arr);
   list->size = newsize;
   list->cellcnt = 0; 
   
   for (int i = 0; i < collection->end; i++){
      insert(list, &collection->arr[i]);
   }
   coll_free(&collection);
}

int hash(char* s, int sz){
   return sum(s) % sz;
}

unsigned long sum(char* s){
   unsigned long sum = 0;
   while (*s != '\0'){
      sum = sum * 26 + (*s - 'a');
      s++; 
   }
   return sum;
}

void hash_free(chain* list){
   for (int i = 0; i < list->size; i++){
      cell* temp = list->arr[i].next;
      cell* previous;
      while(temp){
         previous = temp;
         temp = temp->next;
         free(previous);
      }
//      free(&list->arr[i]);
   }
   free(list->arr);
   free(list);
}

bool isprime(int n){
   for (int i = 2; i <= (int)sqrt(n); i++){
      if (n % i == 0){
         return false;
      }
   }
   return true;
}

int firstprimeaftern(int n){
   int i = n + 1;
   while (!isprime(i)){
      i++;
   }
   return i;
}

/*
   search("AB11 6UL", chain1);
   search("YO8 9LX", chain1);
   search("YO8 9PS", chain1);
   search("BS1 5UL", chain1);
   search("ZE2 9FW", chain1);
   search("ZE2 9FW", chain1);
   search("YO62 5FH", chain1);
   search("WS7 0AP", chain1);
   search("WF1 4GQ", chain1);
   search("abc", chain1);
   search("def", chain1);
   search("ggg", chain1);
   search("hhh", chain1);
*/
/*
   cell* temp = &chain1->arr[50];
   while (temp){
      printf("%s\n", temp->str);
      temp = temp->next;      
   }
*/

