#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

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
void insert(chain* list, cell* c);
void search(char* str, chain* list);

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
/*
   for (int i = 0; i < chain1->size; i++){
      cell* temp = &chain1->arr[i];
      while(temp){
         printf("%s ", temp->str);
         temp = temp->next;
      }
      printf("\n----------------------------------\n");
   }
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

void insert(chain* list, cell* c){
   int index = 0;
   index = hash(c->str, list->size);
   cell* temp = &list->arr[index];
   cell* previous;
   while (temp){
      previous = temp;
      temp = temp->next;
   }
   previous->next = (cell*)calloc(1, sizeof(cell));
   memcpy(previous->next, c, sizeof(cell));
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
