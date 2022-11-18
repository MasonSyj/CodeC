#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define EMPTY '.'
#define FULL '#'
#define A 'A'
#define SHOWFLAG "-show"
#define CAPACITY 20
#define TEMPSIZE 50
#define CARSIZE 26
#define NOACECAR '0'
#define STRSIZE 401

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   struct park* next;
   struct park* parent;
}park;

// read from a file initiate the list and the first carpark
park* parkinit(int argc, char* argv[]);
// // when one carpark is solved, count its moves by its parentindex
int solvemovescnt(park* p);
// return number of cars in a park
int carnum(park* p);
// generate a char array containg all cars for a park
char* carlist(park* p);
// main control function to process one carpark's all possible moves of all cars
void movectrl(park* p);
// locate car's position to choose move vertically or horizontally 
void carposition(park* p, char car);
// for vertical direction car, do the up and down move, render y1 < y2
void moveVertical(int y1, int y2, int x, park* p);
// for horizont direction car, do the left and right move, render x1 < x2
void moveHorizont(int x1, int x2, int y, park* p);
// make new = p->next
void add2next(park* p, park* new);
// for a linked list, make new the end of list
void add2end(park* p, park* new);
// check if the samepark
bool samepark(park* p1, park* p2);
// generate a newpark and return its address
// if it's a duplicate one, will be freed, else it will in the list
park* newpark(park* p);
// return rowsize of a park
int rowsize(park* p);
// return colsize of a park
int colsize(park* p);
// check a park is in rightshape
bool rightshape(park *p);
// based on the car in a carpark, get its head and tail(two [y][x] naturally)
void carcoord(int* y1, int* y2, int* x1, int* x2, park* p, char car);
// given a car, no other place should apper except its head and tail and between.
bool oneplace(park* p, char car);
// given a car, locate its head and tail, and between all chars are same sign
bool straight(park* p, char car);
// check all cars in a park are at least length 2
bool eligiblelength(park* p, char car);
// assert all cars are in uppercase, false if not
bool uppercase(park* p);
// assert cars are in alphabetaically order.
bool consec(park* p);
// return end of linked list of park, 
// meanwhile check if new one is same to any of the existing parks
park* allparkcmp(park* p, park* new);
// at the beginning, check if the park is solvable
bool solveable(park* p);
// for each car, check in a park, it has exit
bool hasexit(park* p, char car);
void show(park* p);
// check if no obstacles between car and exit(when down)
bool candown2exit(int y, int x, park* p);
bool canup2exit(int y, int x, park* p);
bool canleft2exit(int y, int x, park* p);
bool canright2exit(int y, int x, park* p);
// when no obstacles, make several moves for a car to exit
void up2exit(int y1, int y2, int x, park* p);
void down2exit(int y1, int y2, int x, park* p);
void left2exit(int x1, int x2, int y, park* p);
void right2exit(int x1, int x2, int y, park* p);
park* upop(park* p, int y1, int y2, int x, int updegree);
park* downop(park* p, int y1, int y2, int x, int updegree);
park* leftop(park* p, int x1, int x2, int y, int updegree);
park* rightop(park* p, int x1, int x2, int y, int updegree);
// a car in park which can straightly go to exit
char acecar(park* p);
// find a car in park which can straightly go to exit
// can be all directions return true if the parameter car can do the stuff
bool straight2exit(park* p, char car);
// clean useless and reduntant carparks.
void clean(park* p);
void test();
// check if the park is empty, if empty, then means solved
bool empty(park* p); //
// show how the carpark is solved in a recursion way.
void showchain(park* p);
void tostring(park* p, int row, int col, char* str);
   
int main(int argc, char* argv[]){
   test();
   park* p = parkinit(argc, argv);
   park* this = p;
   while(this){
      if (empty(this)){
         if (strcmp(argv[1], SHOWFLAG) == 0){
            showchain(this);
         }
         int movescnt = solvemovescnt(this);
         printf("%d moves\n", movescnt);
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
   p->parent = p;

   if (!rightshape(p)){
      fprintf(stderr, "carpark is not in right shape.");
      exit(EXIT_FAILURE);
   }

   if (!solveable(p)){
      printf("No solution?\n");
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
   // is no acecar, return a sensible no alpha char to avoid further operation.
   if(isalpha(car)){
      clean(p);
      carposition(p, car);
      return;
   }
   unsigned int i = 0;
   char* listofcar = carlist(p);
   while (i < strlen(listofcar)){
      carposition(p, listofcar[i]);
      i++;
   }
   free(listofcar);
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
   // when deciding which car to work on, find out its head and tail
   // head and tail will decide the move horizontally or vertically
   if (y1 == y2){
      moveHorizont(x1, x2, y1, p);
   }else{
      moveVertical(y1, y2, x1, p);
   }
   
}
   
void moveVertical(int y1, int y2, int x, park* p){
   //first square needs to be EMPTY, then consider two different situations.
   if (p->a[y1 - 1][x] == EMPTY){
      // see if can go up straight to exit.
      if (canup2exit(y1, x, p)){
          up2exit(y1, y2, x, p);
          return;
      // if not, just move up one square
      }else{
         park* new = newpark(p);
         for (int j = y1 - 1; j < y2; j++){
            new->a[j][x] = new->a[j+1][x];
         }
         new->a[y2][x] = EMPTY;
         add2end(p, new);
      }
   }
   //move down
   if (p->a[y2 + 1][x] == EMPTY){
       if (candown2exit(y2, x, p)){
          down2exit(y1, y2, x, p);
          return;
      }else{
         park* new = newpark(p);
         for (int j = y2 + 1; j > y1; j--){
            new->a[j][x] = new->a[j-1][x];
         }
         new->a[y1][x] = EMPTY;
         add2end(p, new);
      }
   }
}
   
void moveHorizont(int x1, int x2, int y, park* p){
   //move left
   if (p->a[y][x1 - 1] == EMPTY){
      if (canleft2exit(y, x1, p)){
         left2exit(x1, x2, y, p);
         return;
      }else{
         park* new = newpark(p);
         for (int i = x1 - 1; i < x2; i++){
            new->a[y][i] = new->a[y][i+1];
         }
         new->a[y][x2] = EMPTY;
         add2end(p, new);
      }
   }
   //move right
      if (p->a[y][x2 + 1] == EMPTY){
         if (canright2exit(y, x2, p)){
            right2exit(x1, x2, y, p);
            return;
      }else{
         park* new = newpark(p);
         for (int i = x2 + 1; i > x1; i--){
            new->a[y][i] = new->a[y][i-1];
         }
         new->a[y][x1] = EMPTY;
         add2end(p, new);
     }
   }
}

park* allparkcmp(park* p, park* new){
   park* tmp = p;
   while (tmp && tmp->parent && tmp->parent != tmp){
//      show(parent);
      tmp = tmp->parent;
   }
   while(tmp->next){
      if (samepark(tmp, new)){
         free(new);
         return p;
      }
      tmp = tmp->next;
   }
   return tmp;
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

// only when a new car is gone, then I use this function to make records.
// so doesn't need to same the linked list if exist same carpark
void add2next(park* p, park* new){
   new->next = p->next;
   p->next = new;
}

park* newpark(park* p){
   park* new = (park*)malloc(sizeof(park));
   assert(new);
   memcpy(new, p, sizeof(park));
   new->parent = p;
   new->next = NULL;
   return new;
}

bool samepark(park* p1, park* p2){
   for (int j = 1; j < rowsize(p2) - 1; j++){
      for (int i = 1; i < colsize(p2) - 1; i++){
         if (p1->a[j][i] != p2->a[j][i]){
            return false;
         }
      }
   }
   return true;
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
   
   int j = 0;
   while (p->a[j][0] == EMPTY || p->a[j][0] == FULL){
      j++;
      if (j == CAPACITY){
         return CAPACITY;
      }
   }
   return j;
}

char* carlist(park* p){
   int cnt = 0;
   bool temp[26] = {0};
   char car[CARSIZE];
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (isalpha(p->a[j][i]) && temp[p->a[j][i] - A] == 0){
            temp[p->a[j][i] - A] = 1;
            car[cnt++] = p->a[j][i];
         }
       }
   }
   char* listofcar = (char*)calloc(cnt + 1, sizeof(char));	
   strncpy(listofcar, car, cnt);
   	
   return listofcar;
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

int solvemovescnt(park* p){
   int cnt = 0;
   if (carnum(p) == 0){
      while(p->parent && p->parent != p){
         cnt++;
         p = p->parent;
      }
   }
   return cnt;
}

bool rightshape(park* p){
   if (!uppercase(p) || !consec(p)){
      return false;
   }
   char* listofcar = carlist(p);
   int len = strlen(listofcar);
   int i = 0;
   while (i < len){
      char car = listofcar[i];
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

bool uppercase(park* p){
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (islower(p->a[j][i])){
            return false;
         }
      }
   }
   return true;
}

bool consec(park* p){
   int numofcar = carnum(p);

   if (numofcar == 0){
      return true;
   }   

   char biggestcar = 'A';
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (isalpha(p->a[j][i])){
            biggestcar = biggestcar>p->a[j][i]?biggestcar:p->a[j][i];
         }
      }
   }

   return biggestcar - A + 1 == numofcar;
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

// actually the following two functions can be merged to one,
// but I still use two to make it more readable
// also functions are called by other functions which are also separated 
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

// same idea
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

// between the car and exit, there are (move - 1) moves
// each move needs to appear on a new carpark, but not become part of the linked list
// the parent and child relationship(link of pointers) remains when needs to trace back.
void up2exit(int y1, int y2, int x, park* p){
   int move = y1 - 0;
   park* pre = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = upop(p, y1, y2, x, cnt);
      this->parent = pre;
      pre = this;
   }
   park* new = newpark(p);
   for (int j = y1; j <= y2; j++){
      new->a[j][x] = EMPTY;
   }
   new->parent = pre;
   add2next(p, new);
}

void down2exit(int y1, int y2, int x, park* p){
   int move = rowsize(p) - 1 - y2;
   park* previous = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = downop(p, y1, y2, x, cnt);
      this->parent = previous;
      previous = this;
   }
   park* new = newpark(p);
   for (int j = y1; j <= y2; j++){
      new->a[j][x] = EMPTY;
   }
   new->parent = previous;
   add2next(p, new);
}

void left2exit(int x1, int x2, int y, park* p){
   int move = x1 - 0;
   park* previous = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = leftop(p, x1, x2, y, cnt);
      this->parent = previous;
      previous = this;
   }
   park* new = newpark(p);
   for (int i = x1; i <= x2; i++){
      new->a[y][i] = EMPTY;
   }
   new->parent = previous;
   add2next(p, new);
}
   
void right2exit(int x1, int x2, int y, park* p){
   int move = colsize(p) - 1 - x2;
   park* previous = p;
   for (int cnt = 1; cnt < move; cnt++){
      park* this = rightop(p, x1, x2, y, cnt);
      this->parent = previous;
      previous = this;
   }
   park* new = newpark(p);
   for (int i = x1; i <= x2; i++){
      new->a[y][i] = EMPTY;
   }
   new->parent = previous;
   add2next(p, new);
   
}

char acecar(park* p){
   char* listofcar = carlist(p);
   unsigned int i = 0;
   while (i < strlen(listofcar)){
      char car = listofcar[i];
      if (straight2exit(p, car)){
         return car; // as long as I find one acecar, I return this car.
      }
      i++;
   }
   return NOACECAR; 
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
   if (p->parent == p){
      show(p);
      return;
   }
   
   showchain(p->parent);
   show(p);
   
}

bool empty(park* p){
   return carnum(p) == 0;
}
   
bool hasexit(park* p, char car){
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
      if (!hasexit(p, list[i])){
         return false;
      }
      i++;
   }
   free(list);
   return true;
}

void tostring(park* p, int row, int col, char* str){
   strcpy(str, "");
   char* head = str;
   for (int j = 0; j < row; j++){
      for (int i = 0; i < col; i++){
         *head++ = p->a[j][i];
      }
   }
   *head = '\0';
   return;
}

void test(){

   park testp1;
   strcpy(testp1.a[0], "#.#####");
   strcpy(testp1.a[1], "#......");
   strcpy(testp1.a[2], "#A....#");
   strcpy(testp1.a[3], "#A....#");
   strcpy(testp1.a[4], "#A....#");
   strcpy(testp1.a[5], "...DD.#");
   strcpy(testp1.a[6], "####.##");
   strcpy(testp1.a[7], "");


   park testp2;
   strcpy(testp2.a[0], "########");
   strcpy(testp2.a[1], "#DBBBE..");
   strcpy(testp2.a[2], "#D.A.E.#");
   strcpy(testp2.a[3], "#D.A.E.#");
   strcpy(testp2.a[4], "#D.A.E.#");
   strcpy(testp2.a[5], "#D.A.E.#");
   strcpy(testp2.a[6], ".DCCCE.#");
   strcpy(testp2.a[7], "#D...E.#");
   strcpy(testp2.a[8], "#......#");
   strcpy(testp2.a[9], "#.#.#.##");
   strcpy(testp2.a[10], "");

   park wrongshapep;
   strcpy(wrongshapep.a[0], "#####");
   strcpy(wrongshapep.a[1], "#DBB.");
   strcpy(wrongshapep.a[2], "#D.A#");
   strcpy(wrongshapep.a[3], "#D.A#");
   strcpy(wrongshapep.a[4], "###.#");
   strcpy(wrongshapep.a[5], "");

   assert(solveable(&testp1));
   assert(solveable(&testp2));
   assert(!solveable(&wrongshapep));

   assert(hasexit(&testp1, 'D'));
   assert(hasexit(&testp2, 'B'));
   assert(!hasexit(&wrongshapep, 'D'));
 
   assert(candown2exit(7, 5, &testp2));
   assert(!candown2exit(3, 1, &wrongshapep));
   assert(canup2exit(2, 1, &testp1));
   assert(!canup2exit(1, 5, &testp2));
   assert(canleft2exit(5, 3, &testp1));
   assert(!canleft2exit(1, 2, &testp2));
   assert(canright2exit(1, 3, &wrongshapep));

   assert(acecar(&testp1) == 'A');
   assert(acecar(&testp2) == 'D');
   assert(straight2exit(&testp1, 'A'));
   assert(straight2exit(&testp1, 'D'));
   assert(!straight2exit(&testp2, 'C'));

   char teststr[STRSIZE];
   down2exit(1, 7, 5, &testp2);
   tostring(&testp2, 10, 8, teststr);
   assert(strcmp(teststr, "#########DBBBE..#D.A.E.##D.A.E.##D.A.E.##D.A.E.#.DCCCE.##D...E.##......##.#.#.##") == 0);
   tostring(testp2.next, 10, 8, teststr);
   assert(strcmp(teststr, "#########DBBB...#D.A...##D.A...##D.A...##D.A...#.DCCC..##D.....##......##.#.#.##") == 0);
   tostring(testp2.next->parent, 10, 8, teststr);
   assert(strcmp(teststr, "#########DBBB...#D.A.E.##D.A.E.##D.A.E.##D.A.E.#.DCCCE.##D...E.##....E.##.#.#.##") == 0);


   left2exit(3, 4, 5, &testp1);
   tostring(&testp1, 7, 7, teststr);
   assert(strcmp(teststr, "#.######......#A....##A....##A....#...DD.#####.##") == 0);
   tostring(testp2.next, 7, 7, teststr);
   assert(strcmp(teststr, "########DBBB..#D.A...#D.A...#D.A...#D.A....DCCC..") == 0);
   tostring(testp2.next->parent, 7, 7, teststr);
   assert(strcmp(teststr, "########DBBB..#D.A.E.#D.A.E.#D.A.E.#D.A.E..DCCCE.") == 0);

   right2exit(2, 3, 1, &wrongshapep);
   tostring(&wrongshapep, 5, 5, teststr);
   assert(strcmp(teststr, "######DBB.#D.A##D.A####.#") == 0);
   tostring(wrongshapep.next, 5, 5, teststr);
   assert(strcmp(teststr, "######D...#D.A##D.A####.#") == 0);

   tostring(upop(&testp1, 2, 4, 1, 1), 7, 7, teststr);
   assert(strcmp(teststr, "#.######A.....#A....##A....##.....#...DD.#####.##") == 0);
   tostring(leftop(&testp1, 3, 4, 5, 2), 7, 7, teststr);
   assert(strcmp(teststr, "#.######......#A....##A....##A....#.DD...#####.##") == 0);
   // invalid carpark actually, but to assert function works as expected.
   tostring(downop(&testp2, 1, 7, 1, 1), 10, 8, teststr);
   assert(strcmp(teststr, "#########.BBBE..#D.A.E.##D.A.E.##D.A.E.##D.A.E.#.DCCCE.##D...E.##D.....##.#.#.##") == 0);
   tostring(downop(&testp2, 2, 8, 1, 1), 10, 8, teststr);
   assert(strcmp(teststr, "#########DBBBE..#..A.E.##D.A.E.##D.A.E.##D.A.E.#.DCCCE.##D...E.##D.....##D#.#.##") == 0);
}

