#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#define SIZE 10

typedef struct queue{
   int* list;
   int head;
   int tail;
}queue;

typedef struct coll{
   queue** table;
   int row;
   int col;
}coll;

queue* queue_init(int size);
void enqueue(queue* this, int value);
int dequeue(queue* this);
coll* coll_init(int row, int col);
void coll_show(coll* this);
void array_print(int* a, int size);
void arr2coll(coll* collection, int* arr, int arrsize, int ithdigit);
void coll2arr(coll* collection, int* arr);
int ithdigit(int num, int i);
void test();
void queue_free(queue** pointer2queue);
void coll_free(coll** pointer2coll);

void queue_free(queue** pointer2queue){
   queue* this = *pointer2queue;
   free(this->list);
   free(this);
   *pointer2queue = NULL;
}

void coll_free(coll** pointer2coll){
   coll* this = *pointer2coll;
   for (int j = 0; j < this->row; j++){
      queue_free(&this->table[j]);
   }
   free(this->table);
   free(this);
   *pointer2coll = NULL;
}

void coll_show(coll* this){
   for (int j = 0; j < this->row; j++){
      for (int i = 0; i < this->col ; i++){
         if (this->table[j]->list[i] != 0){
            printf("%d  ", this->table[j]->list[i]);
         }
      }
      printf("\n");
   }
}

queue* queue_init(int size){
   queue* this = (queue*)calloc(1, sizeof(queue));
   assert(this);
   this->list = (int*)calloc(size, sizeof(int));
   assert(this->list);
   return this;
}

void enqueue(queue* this, int value){
   this->list[this->tail++] = value;
}

int dequeue(queue* this){
   int value = this->list[this->head];
   this->list[this->head++] = 0;

   if (value == 0){
      this->head = this->tail;
   }
   return value;
}

void test(){
   int testnum = 4578;
   assert(ithdigit(testnum, 0) == 8);
   assert(ithdigit(testnum, 1) == 7);
   assert(ithdigit(testnum, 2) == 5);
   assert(ithdigit(testnum, 3) == 4);
   assert(ithdigit(testnum, 4) == 0);
}

int ithdigit(int num, int i){
   int digit = 0;
   
   for (int cnt = 0; cnt <= i; cnt++){
      digit = num % 10;
      num /= 10;
   }
   return digit;
}

int main(void){
   srand((unsigned)time(NULL));

   test();
 
   int a[SIZE];
   
   for (int i = 0; i < SIZE; i++){
      a[i] = rand() % 899 + 100;
   }
   
   coll* c = coll_init(10, 10);

   array_print(a, SIZE);

   for (int i = 0; i < 3; i++){
      arr2coll(c, a, SIZE, i);
      coll2arr(c, a);
      array_print(a, SIZE);     
   }

   coll_free(&c);
}

void arr2coll(coll* collection, int* arr, int arrsize, int ith){
   for (int i = 0; i < arrsize; i++){
      int index = ithdigit(arr[i], ith);
      enqueue(collection->table[index], arr[i]);
   }
}

void coll2arr(coll* collection, int* arr){
   int arrcnt = 0;
   for (int j = 0; j < collection->row; j++){
      int value = 0;
      while ((value = dequeue(collection->table[j])) != 0){
         arr[arrcnt++] = value;
     }
   }
}

coll* coll_init(int row, int col){
   coll* this = (coll*)calloc(1, sizeof(coll));
   assert(this);
   this->table = (queue**)calloc(row, sizeof(queue*));
   assert(this->table);
   for (int i = 0; i < row; i++){
      this->table[i] = queue_init(col);
      assert(this->table[i]);
   }
   this->row = row;
   this->col = col;
   return this;
}

void array_print(int* a, int size){
   for (int i = 0; i < size; i++){
      printf("%d  ", a[i]);
   }
   printf("\n");
}
