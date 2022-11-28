#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define ARRSIZE 100
#define STRSIZE 50

typedef struct cell{
   char str[STRSIZE];
   double lati;
   double loti;
   struct cell* next;
}cell;

typedef struct chain{
   cell* arr;
   int size;
}chain;

unsigned long sum(char* s);
int hash(char* s, int sz);

int main(void) {
   chain* chain1 = (chain*)calloc(1, sizeof(chain));
   assert(chain1);
   chain1->arr = (cell*)calloc(ARRSIZE, sizeof(cell));
   assert(chain1->arr);
   chain1->size = ARRSIZE;
}

void insert(chain* list, cell* c){
   int index = 0;
   index = hash(c->str, list->size);
   cell* temp = &list->arr[index];
   while (fabs(temp->lati - 0.0) > 0.00001){
      temp = temp->next;
   }
   temp = c;
   return;
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
