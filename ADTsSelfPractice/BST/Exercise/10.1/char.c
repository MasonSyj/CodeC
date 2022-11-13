#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STRSIZE 5000

typedef struct node{
   char x;
   struct node* left;
   struct node* right;
}Node;

int degree(Node* t);
int depth(Node* t);
Node* makenode(int x);
void insertrandom(Node* t, Node* n);
void insert(Node* t, char newvalue);
char* printtree(Node* t);
char* _printlisp(Node* t);
int depth(Node* t);
bool same(Node* n1, Node* n2);
void int2str(int value, char* str);
void bst_todot(Node* b, char* fname);
void _todot(Node* t, char* nodes, Node* parent, char plr);
Node* search(Node* t, char c);
void preorder(Node* t);
void inorder(Node* t);
void afterorder(Node* t);
void levelorder(Node* t, char* q);
void test();

int main(void){
   srand((unsigned)time(NULL));

   test();

   return 0;
}



void preorder(Node* t){
   printf("%c ", t->x);
   if (t->left){
      preorder(t->left);
   }
   
   if (t->right){
      preorder(t->right);
   }
}

void inorder(Node* t){
   if (t->left){
      inorder(t->left);
   }
   
   printf("%c ", t->x);
   
   if (t->right){
      inorder(t->right);
   }
}
void afterorder(Node* t){
   if (t->left){
      afterorder(t->left);
   }
   
   
   if (t->right){
      afterorder(t->right);
   }
   
   printf("%c ", t->x);
}

void levelorder(Node* t, char* q){
   q[0] = t->x;
   int i = 0;
   int cnt = 0;
   while (cnt < degree(t) && i < degree(t)){
      if (search(t, q[i])->left)
      {q[cnt++] = search(t, q[i])->left->x;}
      if (search(t, q[i])->right)
      {q[cnt++] = search(t, q[i])->right->x;}
      i++;
   }
}

Node* search(Node* t, char c){

   if (!t){
      return NULL;
   }

   if (t->x == c){
      return t;
   }


   if (t->x != c){
      if (t->left){
         return search(t->left, c);
      }

      if (t->right){
         return search(t->right, c);
      }
   }

   return NULL;
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
   
   snprintf(str, STRSIZE, "%c(%s)(%s)", t->x, printtree(t->left), printtree(t->right));
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

void insert(Node* t, char newvalue){
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
   }else if (newvalue > t->x){
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
   _todot(b, str, NULL, 'X');
   strcat(str, "}\n");
   opname = calloc(1, strlen(fname)+1000+1);
   snprintf(opname, 1000, "%s%s", "char", fname);
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
   
// int2str(t->x, fstr);
// snprintf(fstr, 1000, t->x);
   fstr[0] = t->x;
   fstr[1] = '\0';
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


void test(){
   Node* head = makenode('A');

   head->left = makenode('B');
	head->right = makenode('C');
	head->left->left = makenode('D');
	head->left->right = makenode('F');
   head->left->right->left = makenode('E');
	head->right->left = makenode('G');
	head->right->right = makenode('I');
	head->right->left->right = makenode('H');
	
   printf("%s\n", printtree(head));
   printf("depth: %d\n", depth(head));

   assert(degree(head) == 9);
   Node* x = makenode(0);
   x->left = head;
   bst_todot(x, "head.dot");


   printf("\npreorder:");
   preorder(head);
   printf("\ninorder:");
   inorder(head);
   printf("\nafterorder:");
   afterorder(head);
	
   char* q = (char*)calloc(degree(head) + 1, sizeof(int));
   levelorder(head, q);
   puts(q);
}
