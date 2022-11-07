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

//conduct a liner search onto a linked list
int linersearch(node* head, char temp[]);
// insert a word each time into the linked list
void insert(node* head, char temp[]);
// print out the linked list of word
void show(node* head);

int main(){

   FILE* fp = fopen("34words.txt", "r");
   if(!fp){
      fprintf(stderr, "Cannot read %s", "word.txt");
      exit(EXIT_FAILURE);
   }
   
   //create the "head" of the linked list which doesn't contain word
   //words begin sorting from head->next;
   node* head = (node*)malloc(sizeof(struct node));
   strcpy(head->word, "Head of the Linked List");
   head->next = NULL;

   int i = 0;
   //create a char array to receive words from the file
   //the size of the word is less than TEMPSIZE 20
   char temp[TEMPSIZE];

   while (fgets(temp, TEMPSIZE, fp) != NULL){
      temp[strlen(temp) - 1] = '\0';
      insert(head, temp);
   }

   assert(linersearch(head, "tofu") == 2535);
   assert(linersearch(head, "like") == 1429);
   assert(linersearch(head, "labs") == 1348);
// assert(linersearch(head, "hhhhhhhhhhh") == 0);
   
   fclose(fp);
   return EXIT_SUCCESS;
}

int linersearch(node* head, char temp[]){
   int cnt = 0;
   while (head->next && strcmp(head->next->word, temp) != 0){
      head = head->next;
      cnt++;
   }
   return cnt;
}

void insert(node* head, char temp[]){
   node* n = (node*)malloc(sizeof(struct node));
   strcpy(n->word, temp);
   n->next = NULL;

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
