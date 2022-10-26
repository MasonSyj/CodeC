#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEMPSIZE 20
#define WORDSIZE 20

typedef struct node{
  char word[WORDSIZE];
  struct node* next;
} node;

int linersearch(node* head, char temp[]);
void insert(node* head, char temp[]);
void show(node* head);

int main(){

   FILE* fp = fopen("34words.txt", "r");
   if(!fp){
      fprintf(stderr, "Cannot read %s", "word.txt");
      exit(EXIT_FAILURE);
   }
   node* head = (node*)malloc(sizeof(struct node));
   strcpy(head->word, "Head of the Linked List");
   head->next = NULL;

   char temp[TEMPSIZE];

   while (fgets(temp, TEMPSIZE, fp) != NULL){
      temp[strlen(temp) - 1] = '\0';
      insert(head, temp);
   }

   assert(linersearch(head, "tofu") == 2535);
   assert(linersearch(head, "like") == 1429);
   assert(linersearch(head, "labs") == 1348);
   show(head);
   fclose(fp);
   return EXIT_SUCCESS;
}

int linersearch(node* head, char temp[]){
   int cnt = 0;
   while (strcmp(head->next->word, temp) != 0){
      head = head->next;
      cnt++;
   }
   return cnt;
}

void insert(node* head, char temp[]){
   node* n = (node*)malloc(sizeof(struct node));
   strcpy(n->word, temp);
   n->next = NULL;

   if (head == NULL){
     head->next = n;
     return;
   }

   if (strcmp(temp, head->word) < 0){
      n->next = head->next;
      head = n;
      return;
   }

   while (head->next){
      if (strcmp(temp, head->word) > 0 && strcmp(temp, head->next->word) < 0){
         n->next = head->next;
         head->next = n;
         return;
      }
      head = head->next;
   }

   if ((head->next) == NULL){
     head->next = n;
     return;
   }
}

void show(node* head){
   while (head){
      printf("%s\n", head->word);
      head = head->next;
   }
}
