#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMPSIZE 20
#define WORDSIZE 20

typedef struct node{
  char word[WORDSIZE];
  struct node* next;
} node;

void insert(node* head, char temp[]);
void show(node* head);

int main(){
   FILE* fp = fopen("34words.txt", "r");
   if(fp == NULL){
      fprintf(stderr, "Cannot read %s", "word.txt");
      exit(EXIT_FAILURE);
   }
   node* head = (node*)malloc(sizeof(struct node));
   strcpy(head->word, "head");
   head->next = NULL;

   int i = 0;
   char c;
   char temp[TEMPSIZE + 1];
   while ((c = fgetc(fp)) != EOF){
      if (c == '\n'){
         if (i > TEMPSIZE){
           continue;
         }
         temp[i] = '\0';
         i = 0;
         insert(head, temp);
         strcpy(temp, "");
      }else{
         temp[i++] = c;
      }
   }
   printf("------------\n");
   show(head);

   fclose(fp);
   return EXIT_SUCCESS;
}

void insert(node* head, char temp[]){
   node* n = (node*)malloc(sizeof(struct node));
   strcpy(n->word, temp);
   n->next = NULL;
   // node** p = (node*)malloc(sizeof(struct node));
   // *p = head;

   if ((head->next) == NULL){
     head->next = n;
     return;
   }

   if (strcmp(temp, head->next->word) < 0){
      n->next = head->next;
      head->next = n;
      return;
   }

   head = head->next;
   while (head->next){
      if (strcmp(temp, head->word) > 0 && strcmp(temp, head->next->word) < 0){
         n->next = head->next;
         head->next = n;
         return;
      }

      if ((head->next) == NULL){
        head->next = n;
        return;
      }
      head = head->next;
   }
}

void show(node* head){
   while (head){
      printf("%s\n", head->word);
      head = head->next;
   }
}
