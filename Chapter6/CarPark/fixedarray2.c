#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
   
#define N 100000
#define ROW row
#define COL col
   
#define CAPACITY 20

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   int parentindex;
}park;
   
typedef struct list{
   park* p[10000];
   int rowsize;
   int colsize;
   int current;
}list;
   
void parkinit(list* l);
void movectrl(list* l, int index);
void cardirctrl(list* l, int index, char car);
void moveVertical(int y1, int y2, int x, list* l, int index);
void moveHorizont(int y1, int y2, int x, list* l, int index);
park* parkcopy(park* p, int index);
void add2list(list* l, park* new);
int carnum(list* l, int index);
char* carlist(list* l, int index);
bool samepark(park* p1, park* p2, list* l);
int solve(list* l, int index);
void show(park* p);
void test();
   
int main(void){
   test();
   list* l = (list*)calloc(1, sizeof(list));
   parkinit(l);
   
   int i = 0;
   while(i < N){
      show(l->p[i]);
      if (solve(l, i) > 0){
         printf("%d moves", solve(l, i));
         exit(EXIT_SUCCESS);
      }
      movectrl(l, i);
      i++;
 }
 
 
 return 0;
}
   
void parkinit(list* l){
   FILE* fp = fopen("10x8_5c_13t.prk", "r");
   int row, col;
   char x;
   assert(fscanf(fp, "%d%c%d", &row, &x, &col) == 3);
   
   char temp[CAPACITY];
   fgets(temp, CAPACITY, fp);
   l->p[0] = (park*)calloc(1, sizeof(park));

   for (int j = 0; j < row; j++){
      fgets(temp, CAPACITY, fp);
      temp[col] = '\0';
      strncpy(l->p[0]->a[j], temp, col);
   }
   l->rowsize = row;
   l->colsize = col;
   l->current = 0;

// assert(10 == row);
// assert(9 == col);
   
   fclose(fp);
   return;
}
   
void movectrl(list* l, int index){
   char* list = carlist(l, index);
   unsigned int i = 0;
   while (i < strlen(list)){
      cardirctrl(l, index, list[i]);
      i++;
   }
   free(list);
}
   
void cardirctrl(list* l, int index, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;
   for (int j = 1; j < l->rowsize; j++){
      for (int i = 1; i < l->colsize; i++){
         if (l->p[index]->a[j][i] == car){
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
      moveHorizont(x1, x2, y1, l, index);
   }else{
      moveVertical(y1, y2, x1, l, index);
   }
   
}

void moveVertical(int y1, int y2, int x, list* l, int index){
   //move up 
   if (y1 - 1 >= 0 && l->p[index]->a[y1 - 1][x] == '.'){
      park* new = parkcopy(l->p[index], index);
      if (y1 - 1 == 0){
         for (int j = y1; j <= y2; j++){
            new->a[j][x] = '.';
         }
         add2list(l, new);
      }else{
         for (int j = y1 - 1; j < y2; j++){
            new->a[j][x] = new->a[j+1][x];
         }
         new->a[y2][x] = '.';
         add2list(l, new);
      }
   }
   //move down
   if (y2 + 1 < l->rowsize && l->p[index]->a[y2 + 1][x] == '.'){
      park* new = parkcopy(l->p[index], index);
      if (y2 + 1 == l->rowsize - 1){
         for (int j = y1; j <= y2; j++){
            new->a[j][x] = '.';
         }
         add2list(l, new);
      }else{
         for (int j = y2 + 1; j > y1; j--){
            new->a[j][x] = new->a[j-1][x];
         }
         new->a[y1][x] = '.';
         add2list(l, new);
      }
   }
}

void moveHorizont(int x1, int x2, int y, list* l, int index){
   //move left
   if (x1 - 1 >= 0 && l->p[index]->a[y][x1 - 1] == '.'){
      park* new = parkcopy(l->p[index], index);
      if (x1 - 1 == 0){
         for (int i = x1; i <= x2; i++){
            new->a[y][i] = '.';
         }
         add2list(l, new);
      }else{
         for (int i = x1 - 1; i < x2; i++){
            new->a[y][i] = new->a[y][i+1];
         }
         new->a[y][x2] = '.';
         add2list(l, new);	
      }
   }
   //move right
   if (x2 + 1 < l->colsize && l->p[index]->a[y][x2 + 1] == '.'){
      park* new = parkcopy(l->p[index], index);	
      if (x2 + 1 == l->colsize - 1){
         for (int i = x2; i >= x1; i--){
            new->a[y][i] = '.';
         }
         add2list(l, new);
         }else{
            for (int i = x2 + 1; i > x1; i--){
               new->a[y][i] = new->a[y][i-1];
            }
            new->a[y][x1] = '.';
            add2list(l, new);
        }
   }
}
   
park* parkcopy(park* p, int index){
   park* new = (park*)malloc(sizeof(park));
   assert(new);
   memcpy(new, p, sizeof(park));
   new->parentindex = index;
   return new;
}
   
void add2list(list* l, park* new){
   for (int i = 0; i <= l->current; i++){
      if (samepark(l->p[i], new, l) == 0){
         free(new);
         return;
      }
   }
   l->p[++l->current] = new;
   return;
}
   
bool samepark(park* p1, park* p2, list* l){
   for (int j = 0; j < l->rowsize; j++){
      for (int i = 0; i < l->colsize; i++){
         if (p1->a[j][i] != p2->a[j][i]){
            return true;
         }
      }
   }
   return false;
//   return memcmp(p1->a, p2->a, (len + 1) * len);
}
   
char* carlist(list* l, int index){
   int cnt = 0;
   bool temp[26] = {0};
   char car[100];
   for (int j = 1; j < l->rowsize; j++){
      for (int i = 1; i < l->colsize; i++){
         if (isalpha(l->p[index]->a[j][i]) && temp[l->p[index]->a[j][i] - 'A'] == 0){
            temp[l->p[index]->a[j][i] - 'A'] = 1;
            car[cnt++] = l->p[index]->a[j][i];
         }
       }
   }
   char* list = (char*)calloc(cnt + 1, sizeof(char));	
   strncpy(list, car, cnt);
   	
   return list;
}

void show(park* p){
   for (int j = 0; j < 11; j++){
      puts(p->a[j]);
   }
   printf("---------------\n");
}
   
int carnum(list* l, int index){
   return strlen(carlist(l, index));
}
   
int solve(list* l, int index){
   int cnt = 0;
   if (carnum(l, index) == 0){
      while(l->p[index]->parentindex != 0){
         cnt++;
         index = l->p[index]->parentindex;
      }
   }
   return cnt;
}
   
void test(){
   
}
