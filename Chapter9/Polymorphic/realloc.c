#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 20
#define SCALEFACTOR 3

typedef struct arr{
   void** a;
   int end;
   int capacity;
   int elementsize;
}arr;

/* Creates the empty array */
arr* arr_init(int elementsize){
   arr* this = (arr*)calloc(1, sizeof(arr));
   assert(this);
   this->capacity = SIZE;
   this->elementsize = elementsize;
   this->a = (void**)calloc(this->capacity, sizeof(void*));
   assert(this->a);
   for (int i = 0; i < this->capacity; i++){
      this->a[i] = (void*)calloc(1, sizeof(elementsize));
      assert(this->a[i]);
   }
   return this;
}
/* Similar to l[n] = i, safely resizing if required */
/* data from v is copied and stored into array */
void arr_set(arr *l, int n, void* v){
   while (n >= l->capacity){
      l->a = (void**)realloc(l->a, l->capacity * SCALEFACTOR * sizeof(void*));
      assert(l->a);
      for (int i = l->capacity; i < l->capacity * SCALEFACTOR; i++){
         l->a[i] = (void*)calloc(1, sizeof(l->elementsize));
         assert(l->a[i]);
      }
      l->capacity *= SCALEFACTOR;
   }

   memcpy(l->a[n], v, l->elementsize);

}
/* Similar to = l[n] */
/* pointer into array is returned */
void* arr_get(arr *l, int n){
   if (n >= l->capacity || l->a[n] == NULL){
      return NULL;
   }
   
   return l->a[n];
   
}
/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l){
   if (*l == NULL){
      return;
   }
   for (int i = 0; i < (*l)->capacity; i++){
      if ((*l)->a[i]){
         free((*l)->a[i]);
      }
   }
   free(*l);
   *l = NULL;
   return;
}


