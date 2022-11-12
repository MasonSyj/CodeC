#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STRSIZE 5000

typedef struct node{
   int x;
   struct node* left;
   struct node* right;
}Node;

int degree(Node* t);
int depth(Node* t);
Node* makenode(int x);
void insertrandom(Node* t, Node* n);
void insert(Node* t, int newvalue);
char* printtree(Node* t);
char* _printlisp(Node* t);
int depth(Node* t);
bool same(Node* n1, Node* n2);
void int2str(int value, char* str);
void bst_todot(Node* b, char* fname);
void _todot(Node* t, char* nodes, Node* parent, char plr);

int main(void){
   srand((unsigned)time(NULL));
   
   Node* head = makenode(1911);
   Node* head2 = makenode(1949);
   Node* head3 = makenode(2047);

   printf("same: %d\n", same(head, head2));
   
   for (int x = 1999; x <= 2022; x++){
      Node* n = makenode(x);
      insertrandom(head, n);
   }

   for (int x = 1931; x <= 1967; x++){
      insert(head2, x);
   }

   int value = head3->x;
   for (int x = 2; x <= 20; x+=2){
      insert(head3, value - x);
      insert(head3, value + x);
   }

      for (int x = 1; x <= 20; x++){
      insert(head3, value - x);
      insert(head3, value + x);
   }



   printf("%s\n", printtree(head));
   printf("depth: %d\n", depth(head));
   printf("same: %d\n", same(head, head2));
   assert(degree(head) == 25);
   assert(degree(head2) == 37);
   printf("%s\n", printtree(head2));
   printf("%s\n", _printlisp(head2));
   Node* x = makenode(0);
   Node* x2 = makenode(1);
   Node* x3 = makenode(1);
   x->left = head;
   x2->left = head2;
   x3->left = head3;
   bst_todot(x, "head.dot");
   bst_todot(x2, "head2.dot");
   bst_todot(x3, "head3.dot");

   return 0;
}

Node* makenode(int x){
   Node* new = (Node*)calloc(1, sizeof(Node));
   new->x = x;
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
   
   snprintf(str, STRSIZE, "%d(%s)(%s)", t->x, printtree(t->left), printtree(t->right));
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
   
   if (n1->x != n2->x){
      return false;
   }
   
   bool left = 0;
   bool right = 0;

   if (n1->x == n2->x){
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

void insert(Node* t, int newvalue){
   if (newvalue == t->x){
      return;
   }
   
   if (newvalue < t->x){
      if (!t->left){
         Node* newnode = makenode(newvalue);
         assert(newnode);
         t->left = newnode;
         return;
      }else{
         insert(t->left, newvalue);
      }
   }else{
      if (!t->right){
         Node* newnode = makenode(newvalue);
         assert(newnode);
         t->right = newnode;
         return;
      }else{
         insert(t->right, newvalue);
      }
    }
}

char* _printlisp(Node* t)
{
   char tmp[STRSIZE];
   char *s1, *s2, *p;
   
   if(t==NULL){
      /*  \0 string */
      p = calloc(1,1);
      return p;
   }
   int2str(t->x, tmp);
// snprintf(tmp, STRSIZE, t->x);
   s1 = _printlisp(t->left);
   s2 = _printlisp(t->right);
   p = calloc(1, strlen(s1)+strlen(s2)+strlen(tmp)+
       strlen("()() "));
   snprintf(p, STRSIZE,"%s(%s)(%s)", tmp, s1, s2);
   free(s1);
   free(s2);
   return p;
}

void bst_todot(Node* b, char* fname){

   FILE* fp;
   char* str;
   char* opname;
   if(b==NULL){
      return;
   }
   str = (char*)calloc(1, 10000 * sizeof(char));
   snprintf(str, 1000, "digraph G {\n   node [shape=record, height=0.1];\n");
   _todot(b->left, str, NULL, 'X');
   strcat(str, "}\n");
   opname = calloc(1, strlen(fname)+1000+1);
   snprintf(opname, 1000, "%s%s", "int", fname);
   fp = fopen(opname, "wt"); 
   fprintf(fp, "%s", str);
   fclose(fp);
   free(str);
   free(opname);

}

void _todot(Node* t, char* nodes, Node* parent, char plr){
   char tmp[1000];
   char fstr[1000];
   if(t==NULL){
      return;
   }
   
   int2str(t->x, fstr);
// snprintf(fstr, 1000, t->d);
   snprintf(tmp, 1000, "   node%p [label = \"<l> | <m> %s | <r>\"];\n", (void*)t, fstr);
   strcat(nodes, tmp);
   if(parent != NULL){
      snprintf(tmp, 1000, "   node%p:%c -> node%p:m;\n", (void*)parent, plr, (void*)t);
      strcat(nodes, tmp);
   }
   _todot(t->left,  nodes, t, 'l');
   _todot(t->right, nodes, t, 'r');

}

void int2str(int value, char* str){
   int x = 1;

   while (value > x){
      x *= 10; /* if t->x = 2333, then x = 10000*/
   }
   x /= 10; /* go back to 1000 */
   int cnt = 0;
   
   while (x != 0){
      str[cnt++] = value / x + '0';
      value %= x;
      x /= 10;
   }
    str[cnt] = '\0';
}
