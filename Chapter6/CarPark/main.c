#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CAPACITY 20

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   struct park* next;
}park;

typedef struct list{
   park* p;
   int parksize;
}list;

int parksize(list* l);
int carnum(park* p, int parksize);
int movectrl(park* p, int parksize);
int movecar(park* p, char car, int parksize);
int cardirctrl(park* p, char car, int parksize);
int moveVertical(int y1, int y2, int x, park* p);
int moveHorizont(int x1, int x2, int y, park* p);
park* newpark(park* p);

int main(void){
   //assert exist
   list* l = (list*)calloc(1, sizeof(struct list));
   assert(l);
   assert(parksize(l) == 0);
   //assert exist
   l->p = (park*)calloc(1, sizeof(park));
   assert(l->p);
   char cmp[CAPACITY][CAPACITY+1];
   for (int i = 0; i < CAPACITY; i++){
      strcpy(cmp[i], "");
   }
// assert(memcmp(l->p->a, cmp, CAPACITY * (CAPACITY + 1)) == 0);
   
   l->parksize = 6;
   strcpy(l->p->a[0], "#.####");
   strcpy(l->p->a[1], ".BBB.#");
   strcpy(l->p->a[2], "#A...#");
   strcpy(l->p->a[3], "#A...#");
   strcpy(l->p->a[4], "#A...#");
   strcpy(l->p->a[5], "######");
   assert(carnum(l->p, parksize(l)) == 3);
// printf("%d", carnum(l->p, parksize(l)));
   park* p2 = newpark(l->p);
   
   
   assert(strcmp(p2->a[0], "#.####") == 0);
   assert(strcmp(p2->a[1], ".BBB.#") == 0);
   assert(strcmp(p2->a[2], "#A...#") == 0);
   assert(strcmp(p2->a[3], "#A...#") == 0);
   assert(strcmp(p2->a[4], "#A...#") == 0);
   assert(strcmp(p2->a[5], "######") == 0);
}

int parksize(list* l){
   return l->parksize;
}

int carnum(park* p, int parksize){
   char cnt = 'A';
   
   for (int j = 1; j < parksize - 1; j++){
      for (int i = 1; i < parksize - 1; i++){
         if (p->a[j][i] >= cnt && p->a[j][i] != '.'){
            cnt = p->a[j][i];
         }
      }
   }
   
   return cnt - 'A' + 1;
}

int movectrl(park* p, int parksize){
   int movecnt = 0;
   char car = 'A';
   int cnt = carnum(p, parksize);
   for (int i = 0; i < cnt; i++){
      movecnt += movecar(p, i + car, parksize);
   }
   return movecnt;
}

int cardirctrl(park* p, char car, int parksize){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;
   for (int j = 1; j < parksize - 1; j++){
      for (int i = 1; i < parksize - 1; i++){
         if (p->a[j][i] == car){
            if (y1 == 0){
               y1 = j;
               x1 = i;
            }else{
               y2 = j;
               x2 = j;
            }
         }
      }
   }
   
   if (y1 == y2){
      return moveVertical(y1, y2, x1, p);
   }else{
      return moveHorizont(x1, x2, y1, p);
   }
   
}

int moveVertical(int y1, int y2, int x, park* p){
   //move up 
   if (p->a[y1 - 1][x] == '.'){
      if (y1 - 1 == 0){
         for (int j = y1; j <= y2; j++){
            p->a[j][x] = '.';
         }
         return 1;
      }else{
			park* new = newpark(p);
			p->next = new;
         for (int j = y1 - 1; j < y2; j++){
            new->a[j][x] = new->a[j+1][x];
         }
         new->a[y2][x] = '.';
         
      }
   }
   //move down
   if (p->a[y2 + 1][x] == '.'){
      if (y2 + 1 == 0){
         for (int j = y1; j <= y2; j++){
            p->a[j][x] = '.';
         }
         return 1;
      }else{
         for (int j = y2 + 1; j > y1; j--){
            p->a[j][x] = p->a[j-1][x];
         }
         p->a[y1][x] = '.';
         
      }
   }      
   
   return 0;
}

int moveHorizont(int x1, int x2, int y, park* p){
   
   return 0;
}

park* newpark(park* p){
   park* new = (park*)malloc(sizeof(park));
   assert(new);
   memcpy(new, p, sizeof(park));
   return new;
}
