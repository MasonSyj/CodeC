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

typedef struct anode{
  char word[WORDSIZE];
  struct anode* next;
}anode;

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
   show(head);
   analist(head);

}

void analist(node* head){
   head = head->next;
   anode* ahead;
   while(head){
      if (head->invoice == 0){
         head = head->next;
         continue;
      }
      int cnt = 0;
      bool exist = 0;
      struct node* iter = head->next;
      anode* a = (anode*)malloc(sizeof(struct anode));
      ahead = a;
      a->next = NULL;
      while(iter && iter->invoice == head->invoice){
         if (strlen(head->word) == strlen(iter->word) && isana(head->word, iter->word)){
            if (exist == 0){
               strcpy(a->word, head->word);
               a->next = (anode*)malloc(sizeof(struct anode));
               a = a->next;
               strcpy(a->word, iter->word);
               strcpy(iter->word, "");
               iter->invoice = 0;
               a->next = NULL;
               exist = 1;
               cnt += 2;
           }else{
             a->next = (anode*)malloc(sizeof(struct anode));
             a = a->next;
             strcpy(a->word, iter->word);
             a->next = NULL;
             cnt++;
           }

         }
         iter = iter->next;
         if (iter && iter->invoice != head->invoice && exist){
              a = ahead;
              printf("%d ", cnt);
              while (a){
                 printf("%s ", a->word);
                 a = a->next;
              }
              printf("\n--------------------\n");
         }
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
   while(i < n){
     count += str[i++] - 'a' + 1;
   }
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


