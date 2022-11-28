#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define SIZE 11

typedef struct hash{
   int* table1;
   int* table2;
   int sz;
}hash;

int hash1(int num, int sz);
int hash2(int num, int sz);
void test();
void insert(hash* h, int num);
bool emptytable1(hash* h, int num);
bool emptytable2(hash* h, int num);
void show(hash* h);
/*
void inserttable1(hash* h);
void inserttable2(hash* h);
*/


int main(void){
   int a[] = {20, 50, 53, 75, 100, 67, 105, 3, 36, 39};
   test();
   hash* test = (hash*)calloc(1, sizeof(hash));
   assert(test);
   test->sz = SIZE;
   test->table1 = (int*)calloc(test->sz, sizeof(int));
   assert(test->table1);
   test->table2 = (int*)calloc(test->sz, sizeof(int));
   assert(test->table2);
/*    
   insert(test, 20);
   show(test);
   insert(test, 50);
   show(test);
   insert(test, 53);
   show(test);
*/
   for (int i = 0; i < 10; i++){
      insert(test, a[i]);
      show(test);
   }   
   free(test->table1);
   free(test->table2);
   free(test);
   return 0;
}

void insert(hash* h, int num){
   if (emptytable1(h,num)){
      h->table1[hash1(num, h->sz)] = num;
      return;
   }else{
      int old = h->table1[hash1(num, h->sz)];
      h->table1[hash1(num, h->sz)] = num;
      if (emptytable2(h,old)){
         h->table2[hash2(old, h->sz)] = old;
         return;
      }else{
         int secondold = h->table2[hash2(old, h->sz)];
         h->table2[hash2(old, h->sz)] = old;
         insert(h, secondold);
      }
   }
}

void show(hash* h){
   for (int i = 0; i < h->sz; i++){
      printf("%d: %-5d", i, h->table1[i]);
   }
   printf("\n");
   for (int i = 0; i < h->sz; i++){
      printf("%d: %-5d", i, h->table2[i]);
   }
   printf("\n-----------------------\n");

}


int hash1(int num, int sz){
   return num % sz;
}

int hash2(int num, int sz){
   return (num / sz) % sz;
}


bool emptytable1(hash* h, int num){
   return h->table1[hash1(num, h->sz)] == 0;
}
bool emptytable2(hash* h, int num){
   return h->table2[hash2(num, h->sz)] == 0;
}

void test(){
   int size = 11;
   assert(hash1(20, size) == 9);
   assert(hash1(30, size) == 8);
   assert(hash1(40, size) == 7);
   assert(hash1(50, size) == 6);
   assert(hash2(20, size) == 1);
   assert(hash2(30, size) == 2);
   assert(hash2(40, size) == 3);
   assert(hash2(50, size) == 4);
}
