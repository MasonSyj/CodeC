#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STRSIZE 5000

typedef struct node{
   char c;
   struct node* left;
   struct node* right;
}Node;

int degree(Node* t);
int depth(Node* t);
Node* makenode(char c);
void insertrandom(Node* t, Node* n);
char* printtree(Node* t);
int depth(Node* t);
bool same(Node* n1, Node* n2);

int main(void){
   srand((unsigned)time(NULL));
   
   Node* head = makenode('A');
   Node* head2 = makenode('A');

   printf("same: %d\n", same(head, head2));
   
   for (char c = 'B'; c <= 'G'; c++){
      Node* n = makenode(c);
      Node* n2 = makenode(c);
      insertrandom(head, n);
      insertrandom(head2, n2);
   }

   printf("%s\n", printtree(head));

   printf("depth: %d\n", depth(head));


   printf("same: %d\n", same(head, head2));

   assert(degree(head) == 7);
   return 0;

}

Node* makenode(char c){
   Node* new = (Node*)calloc(1, sizeof(Node));
   new->c = c;
   //unnecessary
   new->left = NULL;
   new->right = NULL;
   return new;
}

void insertrandom(Node* t, Node* n){
   if (rand() % 2 == 0){
      if (t->left == NULL){
         t->left = n;
         return;
      }else{
         insertrandom(t->left, n);
      }
         
   }else{
      if (t->right == NULL){
         t->right = n;
      }else{
         insertrandom(t->right, n);
      }
   }
}

char* printtree(Node* t){
   char* str = (char*)calloc(STRSIZE, sizeof(char));
   assert(str);
   
   if (t == NULL){
      strcpy(str, "*");
      return str;
   }
   
   snprintf(str, STRSIZE, "%c(%s)(%s)", t->c, printtree(t->left), printtree(t->right));
   return str;
}

int depth(Node* t){
   if (!t->left && !t->right){
      return 0;
   }
   
   int left = 0, right = 0;
   if (t->left){
      left += depth(t->left);
   }else{
      left = 0;
   }
  
   if (t->right){
      right = depth(t->right);
   }else{
      right = 0;
   }

   return (left>right?left:right) + 1;
}

bool same(Node* n1, Node* n2){
   
   if (n1->c != n2->c){
      return false;
   }
   
   bool left = 0;
   bool right = 0;

   if (n1->c == n2->c){
      if (n1->left && n2->left){
         left = same(n1->left, n2->left);
      }else if (!n1->left && !n2->left){
         left = true;
      }else{
         left = false;
      }

      if (n1->right && n2->right){
         right = same(n1->right, n2->right);
      }else if (!n1->right && !n2->right){
         right = true;
      }else{
         right = false;
      }
   }

   return left && right;
}

int degree(Node* t){
   if (!t->left && !t->right){
      return 1;
   }
   
   int left = 0;
   if (t->left){
      left = degree(t->left);
   }

   int right = 0;
   if (t->right){
      right = degree(t->right);
   }
   return 1 + left + right;

}




























