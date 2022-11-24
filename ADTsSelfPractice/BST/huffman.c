#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char datatype;

typedef struct node{
   datatype data;
   struct node* left;
   struct node* right;
}node;

typedef struct bst{
   node* root;
}bst;

node* huffman(bst* t, datatype x);

int main(void){
   char s[] = "fickjza";
   bst* bst1 = (bst*)calloc(1, sizeof(bst));
   bst1->root = (node*)calloc(1, sizeof(node));
   int len = strlen(s);
   int i = 0;
   while (i < len){
      huffman(bst1, s[i]);
      i++;
   }
}

node* huffman(bst* t, datatype x){
   if (!t->root->right){
         t->root->right = (node*)calloc(1, sizeof(node));
         t->root->right->data = x;
         return t->root;
   }

   if (!t->root->left){
         t->root->left = (node*)calloc(1, sizeof(node));
         t->root->left->data = x;
         return t->root;
   }   
   
   node* new = (node*)calloc(1, sizeof(node));
   new->data =x;
   node* newroot = (node*)calloc(1, sizeof(node));
   newroot->left = new;
   newroot->right = t->root;
   return newroot;
   
}
