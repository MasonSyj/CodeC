#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define EMPTY '.'
#define FULL '#'
#define A 'A'
#define SHOWFLAG "-show"
#define CAPACITY 20
#define TEMPSIZE 50

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   struct park* next;
   struct park* previous;
}park;

park* parkinit(int argc, char* argv[]);
int solve(park* p);
int carnum(park* p);
char* carlist(park* p);
void movectrl(park* p);
void movecar(park* p, char car);
void carposition(park* p, char car);
void moveVertical(int y1, int y2, int x, park* p);
void moveHorizont(int x1, int x2, int y, park* p);
void add2next(park* p, park* new);
void add2end(park* p, park* new);
bool samepark(park* p1, park* p2);
park* newpark(park* p);
int rowsize(park* p);
int colsize(park* p);
bool rightshape(park *p);
// based on the car in a carpark, get its head and tail(two [y][x] naturally)
void carcoord(int* y1, int* y2, int* x1, int* x2, park* p, char car);
// given a car, no other place should apper except its head and tail and between.
bool oneplace(park* p, char car);
// given a car, locate its head and tail, and between all chars are same sign
bool straight(park* p, char car);
// check all cars in a park are at least length 2
bool eligiblelength(park* p, char car);
bool solveable(park* p);
bool isexistexit(park* p, char car);
void show(park* p);
bool candown2exit(int y, int x, park* p);
bool canup2exit(int y, int x, park* p);
bool canleft2exit(int y, int x, park* p);
bool canright2exit(int y, int x, park* p);
void up2exit(int y1, int y2, int x, park* p);
void down2exit(int y1, int y2, int x, park* p);
void left2exit(int x1, int x2, int y, park* p);
void right2exit(int x1, int x2, int y, park* p);
char acecar(park* p);
bool straight2exit(park* p, char car);
void clean(park* p);
void test();
// check if the park is empty, if empty, then means solved
bool empty(park* p); //
// show how the carpark is solved in a recursion way.
void showchain(park* p);
   
int main(int argc, char* argv[]){
   clock_t begin = clock();
   park* p = parkinit(argc, argv);
   park* this = p;
   while(this){
      if (empty(this)){
         if (strcmp(argv[1], SHOWFLAG) == 0){
            showchain(this);
         }
         int movescnt = solve(this);
         printf("%d moves\n", movescnt);
         clock_t end = clock();
         double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
         printf("Time Spent: %f\n", time_spent);
         exit(EXIT_SUCCESS);
      }
      movectrl(this);
      this = this->next;
   }
   return 0;
}

park* parkinit(int argc, char* argv[]){
   park* p = (park*)calloc(1, sizeof(park));
   assert(p);
   assert(argc == 2 || argc == 3);
   FILE* fp = fopen(argv[argc - 1], "r");
   int row, col;
   char x;
   assert(fscanf(fp, "%d%c%d", &row, &x, &col) == 3);
   
   char temp[TEMPSIZE];
   fgets(temp, TEMPSIZE, fp);

   for (int j = 0; j < row; j++){
      fgets(temp, TEMPSIZE, fp);
      temp[col] = '\0';
      strncpy(p->a[j], temp, col);
   }
   assert(rowsize(p) == row);
   assert(colsize(p) == col);
   p->previous = p;

   if (!rightshape(p)){
      fprintf(stderr, "carpark is not in right shape.");
      exit(EXIT_FAILURE);
   }

   if (!solveable(p)){
      printf("No solution\n");
      exit(EXIT_SUCCESS);	
   }
   
   fclose(fp);
   return p;
}

bool straight2exit(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (y1 == y2){
      return canleft2exit(y1, x1, p) || canright2exit(y1, x2, p);
   }else{
      return canup2exit(y1, x1, p) || candown2exit(y2, x1, p);
   }
}
   
void movectrl(park* p){
   char car = acecar(p);
   if(isalpha(car)){
      clean(p);
      carposition(p, car);
      return;
   }
   unsigned int i = 0;
   char* list = carlist(p);
   while (i < strlen(list)){
      carposition(p, list[i]);
      i++;
   }
   free(list);
}
   
void carposition(park* p, char car){
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
      if (canup2exit(y1, x, p)){
          up2exit(y1, y2, x, p);
          return;
      }else{
         park* new = newpark(p);
         for (int j = y1 - 1; j < y2; j++){
            new->a[j][x] = new->a[j+1][x];
         }
         new->a[y2][x] = '.';
         add2end(p, new);
      }
   }
   //move down
   if (p->a[y2 + 1][x] == '.'){
       if (candown2exit(y2, x, p)){
          down2exit(y1, y2, x, p);
          return;
      }else{
         park* new = newpark(p);
         for (int j = y2 + 1; j > y1; j--){
            new->a[j][x] = new->a[j-1][x];
         }
         new->a[y1][x] = '.';
         add2end(p, new);
      }
   }
}
   
void moveHorizont(int x1, int x2, int y, park* p){
   //move left
   if (p->a[y][x1 - 1] == '.'){
      if (canleft2exit(y, x1, p)){
         left2exit(x1, x2, y, p);
         return;
      }else{
         park* new = newpark(p);
         for (int i = x1 - 1; i < x2; i++){
            new->a[y][i] = new->a[y][i+1];
         }
         new->a[y][x2] = '.';
         add2end(p, new);
      }
   }
   //move right
      if (p->a[y][x2 + 1] == '.'){
         if (canright2exit(y, x2, p)){
            right2exit(x1, x2, y, p);
            return;
      }else{
         park* new = newpark(p);
         for (int i = x2 + 1; i > x1; i--){
            new->a[y][i] = new->a[y][i-1];
         }
         new->a[y][x1] = '.';
         add2end(p, new);
     }
   }
}

park* allparkcmp(park* p, park* new){
   park* parent = p;
   while (parent && parent->previous && parent->previous != parent){
//      show(parent);
      parent = parent->previous;
   }
   while(parent->next){
      if (samepark(parent, new) == false){
         free(new);
         return p;
      }
      parent = parent->next;
   }
   return parent;
}

void add2end(park* p, park* new){
   if (!p->next){
      p->next = new;
      return;
   }
   park* end = allparkcmp(p, new);
   if (end != p){
      end->next = new;
   }
}

void add2next(park* p, park* new){
   park* head = p;
   while(head->previous != head){
      head = head->previous;
   }
   while(head->next != NULL){
      if (samepark(head, new) == false){
        free(new);
        return;
      }
      head = head->next;
   }
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
   while (p->a[i][0] == EMPTY || p->a[i][0] == FULL){
      i++;
      if (i == CAPACITY){
         return CAPACITY;
      }
   }
   return i;
}

char* carlist(park* p){
   int cnt = 0;
   bool temp[26] = {0};
   char car[100];
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (isalpha(p->a[j][i]) && temp[p->a[j][i] - A] == 0){
            temp[p->a[j][i] - A] = 1;
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
   printf("\n");
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

bool rightshape(park* p){
   char* list = carlist(p);
   int len = strlen(list);
   int i = 0;
   while (i < len){
      char car = list[i];
      if (!straight(p, car)
       || !oneplace(p, car)
       || !eligiblelength(p, car)){
         return false;
      }
      i++;
   }
   return true;
}

bool oneplace(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   int len = 0;

   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (y1 == y2){
      len = x2 - x1;
   }else{
      len = y2 - y1;
   }

   int cnt = 0;
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (p->a[j][i] == car){
            cnt++;
         }
      }
   }
   return ++len == cnt;
}

bool straight(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (y1 == y2){
      for (int i = x1; i <= x2; i++){
         if (p->a[y1][i] != car){
            return false;
         }
      }
   }else{
      for (int j = y1; j <= y2; j++){
         if (p->a[j][x1] != car){
            return false;
         }
      }
   }
   return true;
}

bool eligiblelength(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (x2 == 0 && y2 == 0){
      return false;
   }else{
      return true;
   }
}

void carcoord(int* y1, int* y2, int* x1, int* x2, park* p, char car){
   *y1 = 0;
   for (int j = 1; j < rowsize(p); j++){
      for (int i = 1; i < colsize(p); i++){
         if (p->a[j][i] == car){
            if (*y1 == 0){
               *y1 = j;
               *x1 = i;
            }else{
               *y2 = j;
               *x2 = i;
            }
         }
      }
   }
}


bool candown2exit(int y, int x, park* p){
   for (int j = y + 1; j < rowsize(p); j++){
      if (p->a[j][x] != EMPTY){
         return false;
      }
   }
   return true;
}

bool canup2exit(int y, int x, park* p){
   for (int j = y - 1; j >= 0; j--){
      if (p->a[j][x] != EMPTY){
         return false;
      }
   }
   return true;
}


bool canleft2exit(int y, int x, park* p){
   for (int i = x - 1; i >= 0; i--){
      if (p->a[y][i] != EMPTY){
         return false;
      }
   }
   return true;
}

bool canright2exit(int y, int x, park* p){
   for (int i = x + 1; i < colsize(p); i++){
      if (p->a[y][i] != EMPTY){
         return false;
      }
   }
   return true;
}

park* upop(park* p, int y1, int y2, int x, int updegree){
   char car = p->a[y1][x];
   park* new = newpark(p);
   for (int j = y1; j <= y2; j++){
      new->a[j][x] = EMPTY;
   }
   for(int j = y1 - updegree; j <= y2 - updegree; j++){
      new->a[j][x] = car;
   }

   return new;
}

park* downop(park* p, int y1, int y2, int x, int downdegree){
   char car = p->a[y1][x];
   park* new = newpark(p);
   for (int j = y1; j <= y2; j++){
      new->a[j][x] = EMPTY;
   }
   for(int j = y1 + downdegree; j <= y2 + downdegree; j++){
      new->a[j][x] = car;
   }
   return new;
}

park* leftop(park* p, int x1, int x2, int y, int leftdegree){
   char car = p->a[y][x1];
   park* new = newpark(p);
   for (int i = x1; i <= x2; i++){
      new->a[y][i] = EMPTY;
   }
   for(int i = x1 - leftdegree; i <= x2 - leftdegree; i++){
      new->a[y][i] = car;
   }

   return new;
}

park* rightop(park* p, int x1, int x2, int y, int rightdegree){
   char car = p->a[y][x1];
   park* new = newpark(p);
   for (int i = x1; i <= x2; i++){
      new->a[y][i] = EMPTY;
   }
   for(int i = x1 + rightdegree; i <= x2 + rightdegree; i++){
      new->a[y][i] = car;
   }
   return new;
}

void up2exit(int y1, int y2, int x, park* p){
   int move = y1 - 0;
   park* pre = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = upop(p, y1, y2, x, cnt);
      this->previous = pre;
      pre = this;
   }
   park* new = newpark(p);
   for (int j = y1; j <= y2; j++){
      new->a[j][x] = EMPTY;
   }
   new->previous = pre;
   add2next(p, new);
}

void down2exit(int y1, int y2, int x, park* p){
   int move = rowsize(p) - 1 - y2;
   park* previous = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = downop(p, y1, y2, x, cnt);
      this->previous = previous;
      previous = this;
   }
   park* new = newpark(p);
   for (int j = y1; j <= y2; j++){
      new->a[j][x] = EMPTY;
   }
   new->previous = previous;
   add2next(p, new);
}

void left2exit(int x1, int x2, int y, park* p){
   int move = x1 - 0;
   park* previous = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = leftop(p, x1, x2, y, cnt);
      this->previous = previous;
      previous = this;
   }
   park* new = newpark(p);
   for (int i = x1; i <= x2; i++){
      new->a[y][i] = EMPTY;
   }
   new->previous = previous;
   add2next(p, new);
}
   
void right2exit(int x1, int x2, int y, park* p){
   int move = colsize(p) - 1 - x2;
   park* previous = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = rightop(p, x1, x2, y, cnt);
      this->previous = previous;
      previous = this;
   }
   park* new = newpark(p);
   for (int i = x1; i <= x2; i++){
      new->a[y][i] = EMPTY;
   }
   new->previous = previous;
   add2next(p, new);
   
}
   
char acecar(park* p){
   char* list = carlist(p);
   unsigned int i = 0;
   while (i < strlen(list)){
      char car = list[i];
      if (straight2exit(p, car)){
         return car;
      }
      i++;
   }
   return '1';
}
   
void clean(park* p){
   if (!p->next){
      return;
   }
   park* end = p->next;
   park* tmp;
   while (end){
      tmp = end->next;
      free(end);
      end = tmp;
   }

   p->next = NULL;
}

void showchain(park* p){
   if (p->previous == p){
      show(p);
      return;
   }
   
   showchain(p->previous);
   show(p);
   
}

bool empty(park* p){
   return carnum(p) == 0;
}
   
bool isexistexit(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (y1 == y2){
      return p->a[y1][0] == EMPTY || p->a[y1][colsize(p) - 1] == EMPTY;
   }else{
      return p->a[0][x1] == EMPTY || p->a[rowsize(p) - 1][x1] == EMPTY;
   }
}

bool solveable(park* p){
   char* list = carlist(p);
   unsigned int i = 0;
   while (i < strlen(list)){
      if (!isexistexit(p, list[i])){
         return false;
      }
      i++;
   }
   free(list);
   return true;
}
