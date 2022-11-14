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
void add2list(park* p, park* new);
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
   while(this){
      show(this);
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

   FILE* fp = fopen("11x9_10c_26t.prk", "r");
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
   if (p->a[y1 - 1][x] == '.'){
      if (y1 - 1 == 0){
         park* new = newpark(p);
         for (int j = y1; j <= y2; j++){
            new->a[j][x] = '.';
         }
         add2list(p, new);
      }else{
         park* new = newpark(p);
         for (int j = y1 - 1; j < y2; j++){
            new->a[j][x] = new->a[j+1][x];
         }
         new->a[y2][x] = '.';
         add2list(p, new);
      }
   }
   //move down
   if (p->a[y2 + 1][x] == '.'){
      if (y2 + 1 == rowsize(p) - 1){
         park* new = newpark(p);         
         for (int j = y1; j <= y2; j++){
            new->a[j][x] = '.';
         }
         add2list(p, new);
      }else{
         park* new = newpark(p);
         for (int j = y2 + 1; j > y1; j--){
            new->a[j][x] = new->a[j-1][x];
         }
         new->a[y1][x] = '.';
         add2list(p, new);
      }
   }
}

void moveHorizont(int x1, int x2, int y, park* p){
   //move left
   if (p->a[y][x1 - 1] == '.'){
      if (x1 - 1 == 0){
         park* new = newpark(p);
         for (int i = x1; i <= x2; i++){
            new->a[y][i] = '.';
         }
         add2list(p, new);
      }else{
         park* new = newpark(p);		
         for (int i = x1 - 1; i < x2; i++){
            new->a[y][i] = new->a[y][i+1];
         }
         new->a[y][x2] = '.';
         add2list(p, new);	
      }
   }
   //move right
   if (p->a[y][x2 + 1] == '.'){
      if (x2 + 1 == colsize(p) - 1){
         park* new = newpark(p);
         for (int i = x2; i >= x1; i--){
            new->a[y][i] = '.';
         }
         add2list(p, new);
         }else{
            park* new = newpark(p);
            for (int i = x2 + 1; i > x1; i--){
               new->a[y][i] = new->a[y][i-1];
            }
            new->a[y][x1] = '.';
            add2list(p, new);
        }
   }
}



void add2list(park* p, park* new){


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
//   printf("move forward\n");
   }
   parent->next = new;
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
   for (int j = 0; j < rowsize(p); j++){
      puts(p->a[j]);
   }
   printf("---------------\n");
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

