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
void newpermu(int* a, int** list, int len);
void transform(node* head, char* origin, const char* after, int* sequnce, char coll[][NUM+1], int len);
//conduct a liner search onto a linked list
int linersearch(node* head, char temp[]);
// insert a word each time into the linked list
void insert(node* head, char temp[]);
// print out the linked list of word
bool isvalidword(node* head, char word[]);
void show(char coll[][NUM+1], int len);
void clear(char coll[][NUM+1]);
int fact(int n);


int main(void){
   test();
   
   FILE* fp = fopen("english_65197.txt", "r");
   if(!fp){
      fprintf(stderr, "Cannot read file");
      exit(EXIT_FAILURE);
   }
   
   node* head = (node*)malloc(sizeof(struct node));
   head->word = (char*)calloc(HEADSIZE, sizeof(char));
   head->next = NULL;
   
   char temp[TEMPSIZE];

   while (fgets(temp, TEMPSIZE, fp) != NULL){
      temp[strlen(temp) - 1] = '\0';
      insert(head, temp);
   }
   
   assert(isvalidword(head, "wasp"));
   assert(isvalidword(head, "wild"));
   assert(isvalidword(head, "bristol"));
   assert(!isvalidword(head, "COME"));
   
   assert(isvalidword(head, "cold"));
   assert(isvalidword(head, "warm"));
   assert(isvalidword(head, "cord"));
   assert(isvalidword(head, "card"));
   assert(isvalidword(head, "warm"));
 
   char origin[NUM+1] = "poke";
   const char after[NUM+1] = "mall";
   //contain the transformation of word ladder
   char coll[NUM+1][NUM+1];
   
   //make sure two words are same length
   assert(strlen(origin) == strlen(after) && strlen(origin) >= 2);
   
   int len = 0;
   for (int i = 0; i < (signed)strlen(origin); i++){
      if (origin[i] != after[i]){
         len++;
      }
   }
   
   //create an array containing indexs that digits of two words diffter
   int* anew = (int*)malloc(len * sizeof(int));
   
   int anewcnt = 0;
   for (int i = 0; i < (signed)strlen(origin); i++){
      if (origin[i] != after[i]){
         anew[anewcnt++] = i;
      }
   }
   
   //create a 2d array containing the permutation of indexs.
   int** listnew = (int**)malloc(sizeof(int*) * fact(len));
   newpermu(anew, listnew, len);

   
   //begin word ladder based on different permutation result
   for (int i = 0; i < fact(len); i++){
      transform(head, origin, after, listnew[i], coll, len);
      // if the word ladder succeed, the final word in coll is the target word.
      if(strcmp(coll[len], after) == 0){
         show(coll, len);
         printf("-------------------\n");
      }
      // reset the coll and origin for next permutaion.
      clear(coll);
      strcpy(origin, "poke");
   }
    
}

bool isvalidword(node* head, char word[]){
   if (linersearch(head, word) != -1){
      return true;
   }else{
      return false;
   }
}

void newpermu(int* a, int** list, int len){
   static int i = 0;
   static int j = 0;
   if (i == len - 1){
      list[j] = (int*)malloc(len * sizeof(int));
      for (int x = 0; x < len; x++){
         list[j][x] = a[x];
      }
      j++;
      return;
   }
   
   for (int x = i; x < len; x++){
      swap(&a[x], &a[i++]);
      newpermu(a, list, len);
      swap(&a[x], &a[--i]);
   }
   return;
}

void transform(node* head, char* origin, const char* after, int* sequnce, char coll[][NUM+1], int len){
    int cntcoll = 0;
    strcpy(coll[cntcoll++], origin);
    for (int i = 0; i < len; i++){
       origin[sequnce[i]] = after[sequnce[i]];
       if (!isvalidword(head, origin)){
          return;
       }else{
          strcpy(coll[cntcoll++], origin);
       }
    }
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

void swap(int* x, int* y){
   int temp = *x;
   *x = *y;
   *y = temp;
}

void test(){
   int x = 3, y = 6;
   swap(&x, &y);
   assert(x == 6);
   assert(y == 3);
}   
   
