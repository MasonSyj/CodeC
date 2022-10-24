#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORDSIZE 20
#define TEMPSIZE 20

typedef struct node{
   char word[WORDSIZE];
   struct node* next;
   // a = 1, b = 2, c = 3...
   int invoice;
}node;

void analist(node* head);
bool isana(char* a, char* b);
int count(char* str, int n);
void insert(node* head, char* temp);
void show(node* head);

int main(void){
   FILE* fp = fopen("34words.txt", "r");
   if(fp == NULL){
     fprintf(stderr, "Cannnot read %s", "34words.txt");
     exit(EXIT_FAILURE);
   }

   struct node* head = (struct node*)malloc(sizeof(struct node));
   struct node copy;
   copy.next = head;
   head->next = NULL;
   strcpy(head->word, "");
   head->invoice = 0;

   char temp[WORDSIZE];
   while (fgets(temp, WORDSIZE, fp) != NULL){
      int length = strlen(temp);
      temp[length - 1] = '\0';
      insert(head, temp);
   }
   
   analist(head);
// show(head);
}

void analist(node* head){
   head = head->next;
// int cnt = head->invoice;
   while(head){
      bool exist = 0;
      struct node* iter = head->next;
      while(iter && iter->invoice == head->invoice){
         if (isana(head->word, iter->word) && strlen(head->word) == strlen(iter->word)){
            if (exist == false){
               printf("%s ", head->word);
               printf("%s ", iter->word);
               exist = 1;
            }else{
               printf("%s ", iter->word);
            }
         }
         
         iter = iter->next;
      }
      if (exist == true){
         printf("\n");
      }
      head = head->next;
   }
}

void insert(node* head, char temp[]){
  node* n = (node*)malloc(sizeof(struct node));
  strcpy(n->word, temp);
  n->invoice = count(temp, strlen(temp));
  n->next = NULL;
  if ((head->next) == NULL){
    head->next = n;
    return;
  }

  if (n->invoice <= head->next->invoice){
     n->next = head->next;
     head->next = n;
     return;
  }
  
  head = head->next;
  while(head->next){
     
     if (n->invoice > head->invoice && n->invoice <= head->next->invoice){
        n->next = head->next;
        head->next = n;
        return;
     }
      
    head = head->next;
  }
   head->next = n;
   return;
}

int count(char* str, int n){
   int count = 0;
   int i = 0;
   while(i <= n){
     
     count += *str - 'a' + 1;
     i++;
   }
// printf("%d\n", count);
   return count;
}

void show(node* head){
   while (head){
      printf("%s,  %d\n", head->word, head->invoice);
      head = head->next;
   }
}

bool isana(char* a, char* b){
   int length = strlen(a);
   int indexa[26] = {0};
   int indexb[26] = {0};
   for (int i = 0; i < length; i++){
      indexa[a[i] - 'a']++;
      indexb[b[i] - 'a']++;
   }
   
   for (int i = 0; i < 26; i++){
      if (indexa[i] == indexb[i]){
         continue;
      }
      else{
         return false;
      }
   }
   return true;
}
