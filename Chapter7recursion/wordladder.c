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
void newpermu(int* a, int i, int** list, int len);
void transform(node* head, char* origin, char* after, int* sequnce, char coll[][NUM+1], int len);
//conduct a liner search onto a linked list
int linersearch(node* head, char temp[]);
// insert a word each time into the linked list
void insert(node* head, char temp[]);
// print out the linked list of word
bool isword(node* head, char word[]);
void show(char coll[][NUM+1], int len);
void clear(char coll[][NUM+1]);
int fact(int n);


int main(void){
   test();
   
   int a[NUM] = {0, 1, 2, 3};
   int list[PUERMU][NUM];
   permu(a, 0, list);
   char coll[NUM+1][NUM+1];
   
   
   FILE* fp = fopen("english_65197.txt", "r");
   if(!fp){
      fprintf(stderr, "Cannot read file");
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
   
   assert(isword(head, "wasp"));
   assert(isword(head, "wild"));
   assert(isword(head, "bristol"));
   assert(!isword(head, "COME"));
   
   assert(isword(head, "cold"));
   assert(isword(head, "warm"));
   assert(isword(head, "cord"));
   assert(isword(head, "card"));
   assert(isword(head, "warm"));
 
    char origin[NUM+1] = "cold";
    char after[NUM+1] = "warm";
   
   assert(strlen(origin) == strlen(after));
   int len = 0;
   
   for (int i = 0; i < (signed)strlen(origin); i++){
      if (origin[i] != after[i]){
         len++;
      }
   }
   
// assert(len == 3);
   
   int* anew = (int*)malloc(len * sizeof(int));
   
   
   
   int anewcnt = 0;
   for (int i = 0; i < (signed)strlen(origin); i++){
      if (origin[i] != after[i]){
         anew[anewcnt++] = i;
      }
   }
   
   assert(anew[0] == 0);
   assert(anew[1] == 1);
   
   int** listnew = (int**)malloc(sizeof(int*) * fact(len));
   
   newpermu(anew, 0, listnew, len);

   
   for (int i = 0; i < fact(len); i++){
      transform(head, origin, after, listnew[i], coll, len);
      if(strcmp(coll[len], after) == 0){
         show(coll, len);
         printf("-------------------\n");
      }
      clear(coll);
      strcpy(origin, "cold");
      
   }
    
}

bool isword(node* head, char word[]){
   if (linersearch(head, word) != -1){
      return true;
   }else{
      return false;
   }
}

void newpermu(int* a, int i, int** list, int len){
   static int cnt = 0;
   if (i == len - 1){
      list[cnt] = (int*)malloc(len * sizeof(int));
      for (int x = 0; x < len; x++){
         list[cnt][x] = a[x];
      }
      cnt++;
      return;
   }
   
   for (int x = i; x < len; x++){
      swap(&a[x], &a[i]);
      newpermu(a, i+1, list, len);
      swap(&a[x], &a[i]);
   }
   return;
}

void transform(node* head, char* origin, char* after, int* sequnce, char coll[][NUM+1], int len){
    int cntcoll = 0;
    strcpy(coll[cntcoll++], origin);
    for (int i = 0; i < len; i++){
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
   if (!head->word){
      head->word = (char*)realloc(head->word, strlen(temp) + 1);
      strcpy(head->word, temp);
      return;
   }
   
   node* n = (node*)malloc(sizeof(struct node));
   n->word = (char*)malloc((strlen(temp) + 1) * sizeof(char));
   strcpy(n->word, temp);
   n->next = NULL;
   
   while(head->next){
      head = head->next;
   }
   head->next = n;
}

void show(char coll[][NUM+1], int len){
   for (int i = 0; i < len + 1; i++){
      puts(coll[i]);
   }
}
void clear(char coll[][NUM+1]){
   for (int i = 0; i < NUM + 1; i++){
      strcpy(coll[i], "");
   }
}

int fact(int n){
   if (n == 1){
      return 1;
   }else{
      return n * fact (n - 1);
   }
}

void test(){
   int x = 3, y = 6;
   swap(&x, &y);
   assert(x == 6);
   assert(y == 3);
   assert(fact(3) == 6);
   assert(fact(4) == 24);
}

