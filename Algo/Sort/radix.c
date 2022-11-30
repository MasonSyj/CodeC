#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define SIZE 10

typedef struct coll{
   int** table;
}coll;

coll* coll_init(int row, int col);
void array_print(int* a, int size);
void arr2coll(coll* collection, int* arr, int arrsize);

int main(void){
   srand((unsigned)time(NULL));

   int a[SIZE];
   
   for (int i = 0; i < SIZE; i++){
      a[i] = rand() % 899 + 100;
   }
   
   coll* c = coll_init(10, 10);
   assert(c);
   array_print(a, SIZE);
}

void arr2coll(coll* collection, int* arr, int arrsize, int ithdigit){
   for (int i = 0; i < arrsize; i++){
      
   }
}

coll* coll_init(int row, int col){
   coll* this = (coll*)calloc(1, sizeof(coll));
   assert(this);
   this->table = (int**)calloc(row, sizeof(int*));
   assert(this->table);
   for (int i = 0; i < row; i++){
      this->table[i] = (int*)calloc(col, sizeof(int));
      assert(this->table[i]);
   }
   return this;
}

void array_print(int* a, int size){
   for (int i = 0; i < size; i++){
      printf("%d  ", a[i]);
   }
   printf("\n");
}
