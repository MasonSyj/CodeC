#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define N 100000

#define CAPACITY 20

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   struct park* next;
   struct park* previous;
}park;

park* parkinit(void);
int solve(park* p);
int carnum(park* p);
char* carlist(park* p);
void movectrl(park* p);
void movecar(park* p, char car);
void cardirctrl(park* p, char car);
void moveVertical(int y1, int y2, int x, park* p);
void moveHorizont(int x1, int x2, int y, park* p);
void add2next(park* p, park* new);
void add2end(park* p, park* new);
bool samepark(park* p1, park* p2);
park* newpark(park* p);
int rowsize(park* p);
int colsize(park* p);
void panel(park* p);
void show(park* p);
void test();

int main(void){
   //test();
   clock_t begin = clock();
   park* p = parkinit();

   park* this = p;
   int i = 0;
   while(i++ < 10){
      show(this);
      printf("main here.\n");
      if (solve(this) > 0){
         printf("%d moves", solve(this));
         clock_t end = clock();
         double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
         printf("%f", time_spent);
         exit(EXIT_SUCCESS);
      }
      movectrl(this);
      this = this->next;
   }
   
   
   return 0;
}

park* parkinit(void){
   park* p = (park*)calloc(1, sizeof(park));
   assert(p);

   FILE* fp = fopen("6x6_2c_3t.prk", "r");
   int row, col;
   char x;
   assert(fscanf(fp, "%d%c%d", &row, &x, &col) == 3);
   
   char temp[CAPACITY];
   fgets(temp, CAPACITY, fp);

   for (int j = 0; j < row; j++){
      fgets(temp, CAPACITY, fp);
      temp[col] = '\0';
      strncpy(p->a[j], temp, col);
   }

   assert(rowsize(p) == row);
   assert(colsize(p) == col);
   
   fclose(fp);
   return p;
}


void panel(park* p){
   while(p){
      movectrl(p);
      p = p->next;
   }
}

void movectrl(park* p){
   char* list = carlist(p);
   unsigned int i = 0;
   while (i < strlen(list)){
      cardirctrl(p, list[i]);
      i++;
   }
   free(list);
}
   
void cardirctrl(park* p, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;
   for (int j = 1; j < rowsize(p); j++){
      for (int i = 1; i < colsize(p); i++){
         if (p->a[j][i] == car){
            if (y1 == 0){
               y1 = j;
               x1 = i;
            }else{
               y2 = j;
               x2 = i;
            }
         }
      }
   }
   
   if (y1 == y2){
      moveHorizont(x1, x2, y1, p);
   }else{
      moveVertical(y1, y2, x1, p);
   }
   
}

void moveVertical(int y1, int y2, int x, park* p){
   //move up
   char car = p->a[y1][x];

   park* new = newpark(p);
   bool upexit = 0;
   int up = y1;
   int i = 0;
   while (up - i >= 0 && p->a[y1 - i][x] == '.'){
      i++;
   }
   int newy1 = up - i;

   for (int j = y1; j <= y2; j++){
      new->a[j][x] = '.';
   }

   if (newy1 != 0){
      for (int j = newy1; j <= newy1 + y2 - y1; j++){
         new->a[j][x] = car;
      }
   }else{
      upexit = 1;
   }



   if (upexit == 1){
      add2next(p, new);
      return;
   }else{
      add2end(p, new);
   }

   park* new2 = newpark(p);
   int down = y2;
   bool downexit = 0;
   i = 0;
   while (down + i < rowsize(p) && p->a[y2 + i][x] == '.'){
      i++;
   }
   int newy2 = down + i;

   for (int j = y1; j <= y2; j++){
      new2->a[j][x] = '.';
   }
   if (newy2 != rowsize(p) - 1){
      for (int j = newy2; j >= newy2 + y1 - y2; j--){
         new->a[j][x] = car;
      }
   }else{
      downexit = 1;
   }

   if (downexit == 1){
      add2next(p, new2);
      return;
   }else{
      add2end(p, new2);
   }

}

void moveHorizont(int x1, int x2, int y, park* p){

   //move left
   char car = p->a[y][x1];

   park* new = newpark(p);
   bool leftexit = 0;
   int left = x1;
   int i = 0;
   while (left - i >= 0 && p->a[y][x1 - i] == '.'){
      i++;
   }
   int newleft = left - i;

   for (int i = x1; i <= x2; i++){
      new->a[y][i] = '.';
   }

   if (newleft != 0){
      for (int i = newleft; i <= newleft + x2 - x1; i++){
         new->a[y][i] = car;
      }
   }else{
      leftexit = 1;
   }


   if (leftexit == 1){
      add2next(p, new);
      return;
   }else{
      add2end(p, new);
   }

   // move right
   park* new2 = newpark(p);
   int right = x2;
   bool rightexit = 0;
   i = 0;
   while (right + i < colsize(p) && p->a[y][x2 + i] == '.'){
      i++;
   }
   int newx2 = right + i;

   for (int i = x1; i <= x2; i++){
      new2->a[y][i] = '.';
   }
   if (newx2 != colsize(p) - 1){
      for (int i = newx2; i >= newx2 + x1 - x2; i--){
         new->a[y][i] = car;
      }
   }else{
      rightexit = 1;
   }


   if (rightexit == 1){
      add2next(p, new2);
      return;
   }else{
      add2end(p, new2);
   }
}



void add2end(park* p, park* new){
   park* parent = p;
   while (parent->previous && parent->previous != parent){
      parent = parent->previous;
   }
   if (!parent){
      parent = p;
   }
   	
   while(parent->next){
      if (samepark(parent, new) == false){
         free(new);
         return;
      }
      parent = parent->next;
   }
   parent->next = new;
}

void add2next(park* p, park* new){
   new->next = p->next;
   p->next = new;
}

park* newpark(park* p){
   park* new = (park*)malloc(sizeof(park));
   assert(new);
   memcpy(new, p, sizeof(park));
   new->previous = p;
   new->next = NULL;
   return new;
}

bool samepark(park* p1, park* p2){
   for (int j = 0; j < rowsize(p1); j++){
      for (int i = 0; i < colsize(p1); i++){
         if (p1->a[j][i] != p2->a[j][i]){
            return true;
         }
      }
   }
   return false;
//	return memcmp(p1->a, p2->a, (len + 1) * len);
}
   
int colsize(park* p){
   if (!p){
      return 0;
   }
   return strlen(p->a[0]);
}

int rowsize(park* p){
   if (!p){
      return 0;
   }
   
   int i = 0;
   while (p->a[i][0] == '#' || p->a[i][0] == '.'){
      i++;
   }
   return i;
}

char* carlist(park* p){
   int cnt = 0;
   bool temp[26] = {0};
   char car[100];
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (isalpha(p->a[j][i]) && temp[p->a[j][i] - 'A'] == 0){
            temp[p->a[j][i] - 'A'] = 1;
            car[cnt++] = p->a[j][i];
         }
       }
   }
   char* list = (char*)calloc(cnt + 1, sizeof(char));	
   strncpy(list, car, cnt);
   	
   return list;
}

void show(park* p){
   printf("---------------\n");
   for (int j = 0; j < rowsize(p); j++){
      puts(p->a[j]);
   }

}

int carnum(park* p){
   return strlen(carlist(p));
}

int solve(park* p){
   int cnt = 0;
   if (carnum(p) == 0){
      while(p->previous && p->previous != p){
         cnt++;
         p = p->previous;
      }
   }
   return cnt;
}

void test(){

}

