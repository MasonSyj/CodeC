#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

typedef struct node{
   char x;
   struct node* left;
   struct node* right;
}Node;

void nodecreate(char* str, Node* head);
void _todot(Node* t, char* nodes, Node* parent, char plr);
void bst_todot(Node* b, char* fname);

int main(void) {
   char a[][5] = {{'B', ' ', ' ', '0', '\0'}, {'A',' ', '1', '0', '\0'}, {'E', '1', '1', '0', '\0'}, {'G', '1', '1', '1', '\0'}};
   puts(a[0]);
   Node* head = (Node*)calloc(1, sizeof(Node));
   int i = 0;
   while(i < 4){
      nodecreate(a[i], head);
      i++;
   }

// Node* bst = (Node*)calloc(1, sizeof(Node));
   bst_todot(head, "huffman.dot");
}

void nodecreate(char* str, Node* head){
   assert(isalpha(*str));
   char letter = *str++;
   while(*str == ' '){
      str++;
   }
   
   while(*str != '\0'){
      if (*str == '0'){
         if (!head->left){
            head->left = (Node*)calloc(1, sizeof(Node));
            assert(head->left);
         }
         head = head->left;
      }else{
         if (!head->right){
            head->right = (Node*)calloc(1, sizeof(Node));
            assert(head->right);
         }
         head = head->right;
      }
      str++;
   }
   head->x = letter;
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
