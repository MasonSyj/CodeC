#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int datatype;

typedef struct node{
   datatype data;
   struct node* left;
   struct node* right;
}node;

typedef struct bst{
   node* root;
}arr;

/* Creates the empty array */
arr* arr_init(void);

void arr_insert(arr* bst, datatype data);
node* insert(node* n, datatype data);
bool arr_isexist(arr* bst, datatype data);
bool isexist(node* n, datatype data);

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
   arr_insert(test, 10);
   arr_insert(test, 20);
   arr_insert(test, 10);
   arr_insert(test, 30);
   arr_insert(test, 40);
   assert(arr_isexist(test, 10));
   assert(arr_isexist(test, 20));
   assert(arr_isexist(test, 30));
   assert(!arr_isexist(test, 50));
   assert(!arr_isexist(test, 70));
}

arr* arr_init(void){
   arr* start = (arr*)calloc(1, sizeof(arr));
   assert(start);

   return start;
}

void arr_insert(arr* bst, datatype data){
   if(!bst->root){
      bst->root = (node*)calloc(1, sizeof(node));
      assert(bst->root);   
      bst->root->data = data;
      return;
   }
   
   node* n = bst->root;
   insert(n, data);
}

node* insert(node* n, datatype data){
   if (!n){
      n = (node*)calloc(1, sizeof(node));
      assert(n);
      n->data = data;
      printf("insert %d\n", data);
      return n;
   }

   if(n->data == data){
      printf("Duplicate data, return.\n");
      return n;
   }else if (n->data < data){
      n->right = insert(n->right, data);
   }else{
      n->left = insert(n->left, data);
   }
   
   return n;
}

bool arr_isexist(arr* bst, datatype data){
   if(!bst->root){
      printf("ADT doesn't hold any data, return.\n");
      return false;
   }
   
   node* n = bst->root;
   if(!n){
      return false;
   }
   return isexist(n, data);
}

bool isexist(node* n, datatype data){
   if(!n){
      printf("Data: %d Not exist. Return False.\n", data);
      return false;
   }

   if (n->data == data){
      printf("Data %d exist in the ADT. Return True.\n",data);
      return true;
   }

   if (n->data < data && n->right){
      return isexist(n->right, data);
   }else if (n->data > data && n->left){
      return isexist(n->left, data);
   }else{
      return false;
   }
}
