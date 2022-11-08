#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM 4
#define PUERMU 24
#define HEADSIZE 1
#define TEMPSIZE 20

typedef struct node{
  char* word;
  struct node* next;
}node;

void test();
void swap(int* x, int* y);
void permu(int* a, int i, int list[][NUM]);
void transform(node* head, char* origin, char* after, int* sequnce, char coll[][NUM+1]);
//conduct a liner search onto a linked list
int linersearch(node* head, char temp[]);
// insert a word each time into the linked list
void insert(node* head, char temp[]);
// print out the linked list of word
bool isword(node* head, char word[]);
void show(char coll[][NUM+1]);
void clear(char coll[][NUM+1]);


int main(int argc, char* argv[]){
   test();
   int a[NUM] = {0, 1, 2, 3};
   int list[PUERMU][NUM];
   permu(a, 0, list); 
  
/*   
   for (int j = 0; j < PUERMU; j++){
      for (int i = 0; i < NUM; i++){
         printf("%-3d", list[j][i]);
      }
     printf("\n");
   }
*/   
   
   char coll[NUM+1][NUM+1];
   
   
   FILE* fp = fopen(argv[1], "r");
   if(!fp){
      fprintf(stderr, "Cannot read file");
      exit(EXIT_FAILURE);
   }else if (argc != 2){
      fprintf(stderr, "parameter number incorrect.");
      exit(EXIT_FAILURE);
   }
   
   node* head = (node*)malloc(sizeof(struct node));
   head->word = (char*)calloc(HEADSIZE, sizeof(char));
   head->next = NULL;
   
   char temp[TEMPSIZE];

   //insert the word one at a time
   while (fgets(temp, TEMPSIZE, fp) != NULL){
      temp[strlen(temp) - 1] = '\0';
      insert(head, temp);
   }
   
   assert(isword(head, "tale"));
   assert(isword(head, "wild"));
   assert(!isword(head, "bristol"));
   assert(!isword(head, "COME"));
 
    char origin[NUM+1] = "wild";
    char after[NUM+1] = "tame";
    for (int i = 0; i < PUERMU; i++){
       transform(head, origin, after, list[i], coll);
       if(strcmp(coll[NUM], after) == 0){
          show(coll);
          printf("-------------------\n");
       }
       clear(coll);
       strcpy(origin, "wild");
       
    }
    

    
}

bool isword(node* head, char word[]){
   if (linersearch(head, word) != -1){
      return true;
   }else{
      return false;
   }
}

void transform(node* head, char* origin, char* after, int* sequnce, char coll[][NUM+1]){
    int cntcoll = 0;
    strcpy(coll[cntcoll++], origin);
    for (int i = 0; i < NUM; i++){
       origin[sequnce[i]] = after[sequnce[i]];
       if (!isword(head, origin)){
          return;
       }
       strcpy(coll[cntcoll++], origin);
    }
    
}

void swap(int* x, int* y){
   int temp = *x;
   *x = *y;
   *y = temp;
}

void permu(int* a, int i, int list[][NUM]){
   static int cnt = 0;
   if (i == NUM - 1){
      for (int x = 0; x < NUM; x++){
         list[cnt][x] = *(a++);
      }
      cnt++;
  
    return;
   }

   for (int x = i; x <= NUM - 1; x++){
      swap(&a[x], &a[i]);
      permu(a, i+1, list);
      swap(&a[x], &a[i]);
   }
   return;
}

int linersearch(node* head, char temp[]){
   head = head->next;
   int cnt = 0;
   while (head && strcmp(head->word, temp) != 0){
      head = head->next;
      cnt++;
   }
   
   if (head){
      return cnt;
   }else{
      return -1;
   }
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

void show(char coll[][NUM+1]){
   for (int i = 0; i < NUM + 1; i++){
      puts(coll[i]);
   }
}
void clear(char coll[][NUM+1]){
   for (int i = 0; i < NUM + 1; i++){
      strcpy(coll[i], "");
   }
}

void test(){
   int x = 3, y = 6;
   swap(&x, &y);
   assert(x == 6);
   assert(y == 3);
   
}

