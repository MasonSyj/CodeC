#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 20
#define TEMPSIZE 20

typedef struct node{
   char word[WORDSIZE];
   struct node* next;
   // a = 1, b = 2, c = 3...
   int invoice;
}node;

int count(char* str);
void insert(node* head, char* temp);
void show(node* head);

int main(void){
   FILE* fp = fopen("34words.txt", "r");
   if(fp == NULL){
     fprintf(stderr, "Cannnot read %s", "34words.txt");
     exit(EXIT_FAILURE);
   }

   struct node* head = (struct node*)malloc(sizeof(struct node));
   head->next = NULL;
   strcpy(head->word, "");
   head->invoice = 0;

   char temp[WORDSIZE];
   while (fgets(temp, WORDSIZE, fp) != NULL){
      int length = strlen(temp);
      temp[length - 1] = '\0';
      puts(temp);
      insert(head, temp);
   }

   show(head);
}

void insert(node* head, char temp[]){
  node* n = (node*)malloc(sizeof(struct node));
  strcpy(n->word, temp);
  n->invoice = count(temp);

  if ((head->next) == NULL){
    head->next = n;
    return;
  }

  if (n->invoice < head->next->invoice){
     n->next = head->next;
     head->next = n;
     return;
  }

  while(head){
     if (n->invoice >= head->invoice){
        n->next = head->next;
        head->next = n;
        return;
     }
    head = head->next;
  }
}

int count(char* str){
   int count = 0;
   while(str != '\0'){
     printf("%d\n", count);
     count += *str - 'a' + 1;
     str += 1;
   }

   return count;
}

void show(node* head){
   while (head){
      printf("%s\n", head->word);
      head = head->next;

   }
}
