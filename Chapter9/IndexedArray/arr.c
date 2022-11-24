#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int datatype;

typedef struct node{
   datatype data;
   struct node* left;
   struct node* right;
}node;

typedef struct bst{
   node* headnode;
}arr;

/* Creates the empty array */
arr* arr_init(void);


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
}

arr* arr_init(void){
   arr* start = (arr*)calloc(1, sizeof(arr));
   assert(start);
   start->headnode = (node*)calloc(1, sizeof(node));
   assert(start->headnode);
   return start;
}
