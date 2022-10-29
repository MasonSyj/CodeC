#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define HEADSIZE 1
#define TEMPSIZE 20

typedef struct node{
  char* word;
  struct node* next;
} node;

//conduct a liner search onto a linked list
int linersearch(node* head, char temp[]);
// insert a word each time into the linked list
void insert(node* head, char temp[]);
// print out the linked list of word
void show(node* head);

int main(int argc, char* argv[]){

   FILE* fp = fopen(argv[1], "r");
   if(!fp){
      fprintf(stderr, "Cannot read %s", argv[1]);
      exit(EXIT_FAILURE);
   }else if (argc != 2){
      fprintf(stderr, "argument count exception, received %d, expected 2", argc);
      exit(EXIT_FAILURE);
   }
   
   //create the "head" of the linked list which doesn't contain word
   //words begin sorting from head->next;
   node* head = (node*)malloc(sizeof(struct node));
   head->word = (char*)calloc(HEADSIZE, sizeof(char));
   head->next = NULL;

   //create a char array to receive words from the file
   //the size of the word is less than TEMPSIZE 20
   char temp[TEMPSIZE];

   //insert the word one at a time
   while (fgets(temp, TEMPSIZE, fp) != NULL){
      temp[strlen(temp) - 1] = '\0';
      insert(head, temp);
   }
   
   // test the linear search in a sample file
   // assert(linersearch(head, "tofu") == 2535);
   // assert(linersearch(head, "like") == 1429);
   // assert(linersearch(head, "labs") == 1348);
   
   show(head);
   fclose(fp);
   return EXIT_SUCCESS;
}

int linersearch(node* head, char temp[]){
   head = head->next;
   int cnt = 0;
   while (head && strcmp(head->word, temp) != 0){
      head = head->next;
      cnt++;
   }
   return cnt;
}

void insert(node* head, char temp[]){
   //generate a node containing the word
   node* n = (node*)malloc(sizeof(struct node));
   n->word = (char*)malloc((strlen(temp) + 1) * sizeof(char));
   strcpy(n->word, temp);
   n->next = NULL;

   //linked list doesn't have word yet
   if (head->next == NULL){
     head->next = n;
     return;
   }

   //inserting word is smaller than the first one
   if (strcmp(temp, head->next->word) < 0){
      n->next = head->next;
      head->next = n;
      return;
   }
   
   //word is bigger than the first, smaller than the last.
   head = head->next;
   while (head->next){
      if (strcmp(temp, head->word) > 0 && strcmp(temp, head->next->word) < 0){
         n->next = head->next;
         head->next = n;
         return;
      }
      head = head->next;
   }
   //word is bigger than the last
   if (head->next == NULL){
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
