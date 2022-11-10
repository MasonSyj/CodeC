#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CAPACITY 20

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   struct park* next;
}park;

typedef struct list{
   park* p;
   int parksize;
   int carsize;
}list;

int parksize(list* l){
   return l->parksize;
}


int main(void){
   //assert exist
   list* l = (list*)calloc(1, sizeof(struct list));
   assert(l);
   assert(parksize(l) == 0);
   //assert exist
   l->p = (park*)calloc(1, sizeof(park));
   assert(l->p);
   char cmp[CAPACITY][CAPACITY+1];
   for (int i = 0; i < CAPACITY; i++){
      strcpy(cmp[i], "");
   }
   assert(memcmp(l->p->a, cmp, CAPACITY * (CAPACITY + 1)) == 0);


   l->parksize = 6;
   strcpy(l->p->a[0], "#.####");
   strcpy(l->p->a[1], ".BBB.#");
   strcpy(l->p->a[2], "#A...#");
   strcpy(l->p->a[3], "#A...#");
   strcpy(l->p->a[4], "#A...#");
   strcpy(l->p->a[5], "######");
}
