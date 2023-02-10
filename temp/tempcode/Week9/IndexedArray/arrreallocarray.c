#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 100
#define SCALEFACTOR 2

typedef int datatype;

typedef struct arr{
   datatype* data;
   int capacity;
}arr;

/* Creates the empty array */
arr* arr_init(void);
/* Similar to l[n] = i, safely resizing if required */
void arr_set(arr *l, int n, int i);
/* Similar to = l[n] */ 
int arr_get(arr *l, int n);
/*Clears all space used, and sets pointer to NULL */
void arr_free(arr **l);


/*
Similar to l[n] = i, safely resizing if required 
void arr_set(arr *l, int n, int i);
 Similar to = l[n] 
int arr_get(arr *l, int n);
 Clears all space used, and sets pointer to NULL 
void arr_free(arr **l);
*/


int main(void){
   arr* test = arr_init();
   assert(test);
   arr_set(test, 50, 20);
   arr_set(test, 99, 40);
   assert(arr_get(test, 50) == 20);
   assert(arr_get(test, 99) == 40);

   arr_set(test, 200, 80);
   assert(arr_get(test, 50) == 20);
   assert(arr_get(test, 99) == 40);
   assert(arr_get(test, 200) == 80);

   arr_free(&test);
   assert(test == NULL);
}

arr* arr_init(void){
   arr* start = (arr*)calloc(1, sizeof(arr));
   assert(start);
   start->capacity = N;
   start->data = (datatype*)calloc(N, sizeof(datatype));
   assert(start->data);
   return start;
}

void arr_set(arr *l, int n, int i){
   if (n < l->capacity){
      l->data[n] = i;
      return;
   }

   while(l->capacity <= n){
      l->data = (datatype*)realloc(l->data, sizeof(datatype) * l->capacity * SCALEFACTOR);
      assert(l->data);
      l->capacity *= SCALEFACTOR;
   }
   l->data[n] = i;
   return;
}

int arr_get(arr *l, int n){
   if (n >= l->capacity){
      printf("set doesn't hold nth data, return -1.\n");
      return -1;
   }else{
      return l->data[n];
   }
}

void arr_free(arr **l){
   free((*l)->data);
   free(*l);
   return;
}
















