#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#define N 100000
#define EMPTY '.'
#define FULL '#'
#define CAPACITY 20
#define CARSIZE 26
#define A 'A'
#define STRSIZE 401
#define SHOWFLAG "-show"
#define ZERO '0'

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   int parentindex;
}park;

typedef struct list{
   park p[N];
   int rowsize;
   int colsize;
   int end;
}list;

// read from a file initiate the list and the first carpark
void parkinit(list* state, int argc, char* argv[]);
// main control function to process one carpark's all possible moves of all cars
void movectrl(list* state, int index);
// locate car's position to choose move vertically or horizontally 
void carposition(list* state, int index, char car);
// for vertical direction car, do the up and down move, render y1 < y2
void moveVertical(int y1, int y2, int x, list* state, int index);
// for horizont direction car, do the left and right move, render x1 < x2
void moveHorizont(int x1, int x2, int y, list* state, int index);
// add the new park to the list
void add2list(list* state, park* new);
// when one carpark is solved, count its moves by its parentindex
int solvemovescnt(list* state, int index);  
// make a copy of the park
park parkchild(park* p, int index);
// count the number of cars in a carpark
int carnum(park* p); //
// get the list of cars in a carpark
void carlist(park* p, char* listofcar);
// check if two carparks are same, true if same
bool samepark(park* p1, park* p2); 
// show the park
void show(park* p);
// check if one car moves vertically reach exit
bool reachVerticalexit(int y, int rowsize); 
// check if one car moves horizontally reach exit
bool reachHorizontexit(int x, int colsize); 
// for a car moves vertically reach exit, remove it from the park
// render y1 < y2, so y1 will compare to 0, y2 compare to rowsize
void carVerticalexit(int y1, int y2, int x, park* p);
// for a car moves horizontally reach exit, remove it from the park
// render x1 < x2, so x1 will compare to 0, x2 compare to colsize
void carHorizontexit(int x1, int x2, int y, park* p);
// for a car, move up if it can
void moveup(int y1, int y2, int x, park* p);
// for a car, move down if it can
void movedown(int y1, int y2, int x, park* p);
// for a car, move left if it can
void moveleft(int x1, int x2, int y, park* p);
// for a car, move right if it can
void moveright(int x1, int x2, int y, park* p);
// see what the up square  is, if not bollard, prepare for move up
char upsquare(int y, int x, park* p);
// see what the down square  is, if not bollard, prepare for move up
char downsquare(int y, int x, park* p);
// see what the left square is, if not bollard, prepare for move up
char leftsquare(int y, int x, park* p);
// see what the right square is, if not bollard, prepare for move up
char rightsquare(int y, int x, park* p);
// convert a park into a 1D array for testing
void tostring(park* p, int row, int col, char* str);
// check if the park is in right shape which all cars are straight in one place and length at least 2
bool rightshape(park* p);
// given a car, no other place should apper except its head and tail and between.
bool oneplace(park* p, char car);
// given a car, locate its head and tail, and between all chars are same sign
bool straight(park* p, char car);
// assert all cars are in uppercase, false if not
bool uppercase(park* p);
// assert cars are in alphabetaically order.
bool consec(park* p);
// check all cars in a park are at least length 2
bool eligiblelength(park* p, char car);
// check if the park is empty, if empty, then means solved
bool empty(park* p); 
// show how the carpark is solved in a recursion way.
void showchain(list* state, int index);
// based on the car in a carpark, get its head and tail(two [y][x])
void carcoord(int* y1, int* y2, int* x1, int* x2, park* p, char car);
// return one park's rowsize
int rowsize(park* p);
// return one park's colsize
int colsize(park* p);
// clean one park's 2d array to all '0's
void clean(park* p);
void test1();
void test2();

int main(int argc, char* argv[]){
   test1();
   test2();
   static list state;
   parkinit(&state, argc, argv);
   int i = 0;
   // end the loop when all park are addressed.
   while(i <= state.end){
      if (empty(&state.p[i])){
         int movescnt = solvemovescnt(&state, i);
         if (strcmp(argv[1], SHOWFLAG) == 0){
           showchain(&state, i);
         }
         printf("%d moves\n", movescnt);
         exit(EXIT_SUCCESS);
      }
      movectrl(&state, i);
      i++;
   }
   printf("No solution.\n");
   return 0;
}

void parkinit(list* state, int argc, char* argv[]){
   FILE* fp = fopen(argv[argc - 1], "r");
   int row, col;
   char x;
   assert(fscanf(fp, "%d%c%d", &row, &x, &col) == 3);
   assert(argc == 2 || argc == 3);

   char temp[CAPACITY];
   fgets(temp, CAPACITY, fp);
   state->rowsize = row;
   state->colsize = col;
   clean(&state->p[0]);

   for (int j = 0; j < row; j++){
      fgets(temp, CAPACITY, fp);
      temp[col] = '\0';
      strncpy(state->p[0].a[j], temp, col);
   }
   
   if (!rightshape(&state->p[0])){
      fprintf(stderr, "carpark is not in right shape.");
      exit(EXIT_FAILURE);
   }
   
   state->end = 0;
   state->p[0].parentindex = 0;
   
   fclose(fp);
   return;
}
   
void movectrl(list* state, int index){
   char listofcar[CARSIZE];
   carlist(&state->p[index], listofcar);
   unsigned int i = 0;
   // iterate all cars in the park and seek possible moves
   while (i < strlen(listofcar)){
      carposition(state, index, listofcar[i]);
      i++;
   }
}
   
void carposition(list* state, int index, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, &state->p[index], car);

   if (y1 == y2){
      moveHorizont(x1, x2, y1, state, index);
   }else{
      moveVertical(y1, y2, x1, state, index);
   }
} 
   
void moveVertical(int y1, int y2, int x, list* state, int index){
   //if upsquare is empty, then move up
   if (upsquare(y1, x, &state->p[index]) == EMPTY){
      park new = parkchild(&state->p[index], index);
      // when move up, see if reach exit or not, things differ
      if (reachVerticalexit(y1, state->rowsize)){
         carVerticalexit(y1, y2, x, &new);
      }else{
         moveup(y1, y2, x, &new);
         
      }
      add2list(state, &new);
   }
   //move down, similar to move up
   if (downsquare(y2, x, &state->p[index]) == EMPTY){
      park new = parkchild(&state->p[index], index);
      if (reachVerticalexit(y2, state->rowsize)){
         carVerticalexit(y1, y2, x, &new);
      }else{
         movedown(y1, y2, x, &new);
      }
      add2list(state, &new);
   }
}
   
void moveHorizont(int x1, int x2, int y, list* state, int index){
   //if leftsquare is emtpy , then move left
   if (leftsquare(y, x1, &state->p[index]) == EMPTY){
      park new = parkchild(&state->p[index], index);
      // when move left, see if reach exit or not, things differ
      if (reachHorizontexit(x1, state->colsize)){
         carHorizontexit(x1, x2, y, &new);
      }else{
         moveleft(x1, x2, y, &new);
      }
      add2list(state, &new);
   }
   //move right, similar to move left
   if (rightsquare(y, x2, &state->p[index]) == EMPTY){
      park new = parkchild(&state->p[index], index);
      if (reachHorizontexit(x2, state->colsize)){
         carHorizontexit(x1, x2, y, &new);
      }else{
         moveright(x1, x2, y, &new);
        }
      add2list(state, &new);
   }
}
   
park parkchild(park* p, int index){
   park child;
   int row = rowsize(p);
   int col = colsize(p);
   for (int j = 0; j <= row; j++){
      for (int i = 0; i <= col; i++){
         child.a[j][i] = p->a[j][i];
      }
   }
   // child's parentindex is *p's index.
   child.parentindex = index;
   return child;
}
   
void add2list(list* state, park* new){
   for (int i = 0; i <= state->end; i++){
      // the park new is from variable from function, 
      // 
      if (samepark(&state->p[i], new)){
         return;
      }
   }

   state->end = state->end + 1;
   int row = rowsize(new);
   int col = colsize(new);
   for (int j = 0; j <= row; j++){
      for (int i = 0; i <= col; i++){
         state->p[state->end].a[j][i] = new->a[j][i];
      }
   }
   state->p[state->end].parentindex = new->parentindex;

   return;
}
   
bool samepark(park* p1, park* p2){
   if (rowsize(p1) != rowsize(p2)){
      return false;
   }
   if (colsize(p1) != colsize(p2)){
      return false;
   }
   int row = rowsize(p1);
   int col = colsize(p1);
   for (int j = 0; j < row; j++){
      for (int i = 0; i < col; i++){
         if (p1->a[j][i] != p2->a[j][i]){
            return false;
         }
      }
   }
   return true;
}
   
void carlist(park* p, char* listofcar){
   strcpy(listofcar, "");
   int cnt = 0;//count the num of cars
   // make a bool array to record car appearances.
   // A be temp[0], B be temp[1], C be temp[2] and so on
   bool temp[CARSIZE] = {0};
   char car[CARSIZE];
   int row = rowsize(p);
   int col = colsize(p);
   for (int j = 1; j < row - 1; j++){
      for (int i = 1; i < col - 1; i++){
         if (isalpha(p->a[j][i]) && temp[p->a[j][i] - A] == 0){
            temp[p->a[j][i] - A] = true;
            car[cnt++] = p->a[j][i];
         }
       }
   }
   car[cnt++] = '\0';
   strncpy(listofcar, car, cnt);
}
   
void carcoord(int* y1, int* y2, int* x1, int* x2, park* p, char car){
   *y1 = 0;
   int row = rowsize(p);
   int col = colsize(p);
   for (int j = 1; j < row; j++){
      for (int i = 1; i < col; i++){
         if (p->a[j][i] == car){
            // scan the 2D, y1 and x1 will be marked the first time(need set *y1 = 0)
            if (*y1 == 0){
               *y1 = j;
               *x1 = i;
            // y2 and x2 will be marked rest of times, leads to last time assigned.
            }else{
               *y2 = j;
               *x2 = i;
            }
         }
      }
   }
}
   
int carnum(park* p){
   char listofcar[CARSIZE];
   carlist(p, listofcar);
   // if listofcar is "ACBD", then number of car is 4(use strlen).
   return strlen(listofcar); 
}

bool empty(park* p){
   return carnum(p) == 0;
}
   
int solvemovescnt(list* state, int index){
   if (carnum(&state->p[index]) > 0){
      return 0;
   }

   int cnt = 0;
   while(index != 0){
      cnt++;
      index = state->p[index].parentindex;
   }
   return cnt;
}
   
bool straight(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, p, car);
   // make sure between head and tail are connected.
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
   
bool oneplace(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   int len = 0;

   carcoord(&y1, &y2, &x1, &x2, p, car);
   // count the length of car
   if (y1 == y2){
      len = x2 - x1;
   }else{
      len = y2 - y1;
   }

   int cnt = 0;
   int row = rowsize(p);
   int col = colsize(p);
   // count the number of sign appearance for a car
   for (int j = 1; j < row; j++){
      for (int i = 1; i < col; i++){
         if (p->a[j][i] == car){
            cnt++;
         }
      }
   }
   // if not equal, means other place appear the sign.
   return ++len == cnt;
}

bool eligiblelength(park* p, char car){
   int y1 = 0, x1 = 0, y2 = 0, x2 = 0;
   carcoord(&y1, &y2, &x1, &x2, p, car);
   // if length is 1, x2 and y2 will stay defaulted value 0.
   if (x2 == 0 && y2 == 0){
      return false;
   }else{
      return true;
   }
}

// assert all cars are in uppercase, false if not
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
// assert cars are in alphabetaically order.
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

bool rightshape(park* p){
   if (!uppercase(p) || !consec(p)){
      return false;
   }
   
   char listofcar[CARSIZE];
   carlist(p, listofcar);
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
   
bool reachVerticalexit(int y, int rowsize){
   return y == 1 || y == rowsize - 2;
}

bool reachHorizontexit(int x, int colsize){
   return x == 1 || x == colsize - 2;
}

void carVerticalexit(int y1, int y2, int x, park* p){
   for (int j = y1; j <= y2; j++){
      p->a[j][x] = EMPTY;
   }
}
   
void carHorizontexit(int x1, int x2, int y, park* p){
   for (int i = x1; i <= x2; i++){
      p->a[y][i] = EMPTY;
   }
}

//if out of range, return FULL (sensible)    
char upsquare(int y, int x, park* p){
   if (y - 1 >= 0){
      return p->a[y - 1][x];
   }else{
      return FULL;
   }
}
   
char downsquare(int y, int x, park* p){
   if (y + 1 < rowsize(p)){
      return p->a[y + 1][x];
   }else{
      return FULL;
   }
}

char leftsquare(int y, int x, park* p){
   if (x - 1 >= 0){
      return p->a[y][x - 1];
   }else{
      return FULL;
   }
}

char rightsquare(int y, int x, park* p){
   if (x + 1 < colsize(p)){
      return p->a[y][x + 1];
   }else{
      return FULL;
   }
}

void moveup(int y1, int y2, int x, park* p){
   for (int j = y1 - 1; j < y2; j++){
      p->a[j][x] = p->a[j+1][x];
   }
   p->a[y2][x] = EMPTY;
}

void movedown(int y1, int y2, int x, park* p){
   for (int j = y2 + 1; j > y1; j--){
      p->a[j][x] = p->a[j-1][x];
   }
   p->a[y1][x] = EMPTY;
}

void moveleft(int x1, int x2, int y, park* p){
   for (int i = x1 - 1; i < x2; i++){
      p->a[y][i] = p->a[y][i+1];
   }
   p->a[y][x2] = EMPTY;
}

void moveright(int x1, int x2, int y, park* p){
   for (int i = x2 + 1; i > x1; i--){
      p->a[y][i] = p->a[y][i-1];
   }
   p->a[y][x1] = EMPTY;
}

int rowsize(park* p){
   int cnt = 0;
   while (p->a[cnt][0] == FULL || p->a[cnt][0] == EMPTY){
      cnt++;
      // in case it's a 20x20 CARPARK
      if (cnt == CAPACITY){
         return CAPACITY;
      }
   }
   return cnt;
}
   
int colsize(park* p){
   return strlen(p->a[0]);
}
   
   
void show(park* p){
   for (int j = 0; j < CAPACITY; j++){
      if (p->a[j][0] != FULL && p->a[j][0] != EMPTY){
         printf("\n");
         return;
      }
      puts(p->a[j]);
   }
}
   
void showchain(list* state, int index){
   if (index == 0){
      show(&state->p[0]);
   }else{
      showchain(state, state->p[index].parentindex);
      show(&state->p[index]);
   }
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

void clean(park* p){
   for (int j = 0; j < CAPACITY; j++){
      for (int i = 0; i < CAPACITY; i++){
         p->a[j][i] = ZERO;
      }
   }
}


void test1(){
   static list state;
   state.rowsize = 7;
   state.colsize = 7;
   state.end = 0;
   char str1[STRSIZE];
   char str2[STRSIZE];

   strcpy(state.p[0].a[0], "#.#####");
   strcpy(state.p[0].a[1], ".BBB..#");
   strcpy(state.p[0].a[2], "#A....#");
   strcpy(state.p[0].a[3], "#A...C#");
   strcpy(state.p[0].a[4], "#A...C#");
   strcpy(state.p[0].a[5], "#..DDC#");
   strcpy(state.p[0].a[6], "#######");
   assert(state.end == 0);
   assert(carnum(&state.p[0]) == 4);
   carlist(&state.p[0], str1);
   assert(strcmp(str1, "BACD") == 0);

   assert(upsquare(1, 1, &state.p[0]) == EMPTY);
   assert(upsquare(3, 5, &state.p[0]) == EMPTY);
   assert(downsquare(1, 4, &state.p[0]) == EMPTY);
   assert(downsquare(5, 5, &state.p[0]) == FULL);
   assert(leftsquare(5, 3, &state.p[0]) == EMPTY);
   assert(rightsquare(5, 5, &state.p[0]) == FULL);
   assert(rightsquare(1, 3, &state.p[0]) == EMPTY);


   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A....##A...C##A...C##..DDC########") == 0);

   moveup(3, 5, 5, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##..DD.########") == 0);
   moveup(2, 4, 5, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB.C##A...C##A...C##A....##..DD.########") == 0);
   movedown(1, 3, 5, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##..DD.########") == 0);
   moveleft(3, 4, 5, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##.DD..########") == 0);
   moveleft(2, 3, 5, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##DD...########") == 0);
   moveright(1, 2, 5, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##.DD..########") == 0);
   movedown(2, 4, 1, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##....C##A...C##A...C##ADD..########") == 0);
   moveleft(1, 3, 1, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####BBB...##....C##A...C##A...C##ADD..########") == 0);
   moveright(0, 2, 1, &state.p[0]);
   tostring(&state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##....C##A...C##A...C##ADD..########") == 0);
   assert(!empty(&state.p[0]));

   park closedp;
   strcpy(closedp.a[0], "#######");
   strcpy(closedp.a[1], "#BBB..#");
   strcpy(closedp.a[2], "#A....#");
   strcpy(closedp.a[3], "#A...C#");
   strcpy(closedp.a[4], "#A...C#");
   strcpy(closedp.a[5], "#..DDC#");
   strcpy(closedp.a[6], "#######");
   add2list(&state, &closedp);
   assert(state.end == 1);
   assert(carnum(&state.p[1]) == 4);
   assert(rightshape(&state.p[1]));

   park emptyp;
   strcpy(emptyp.a[0], "#######");
   strcpy(emptyp.a[1], "#.....#");
   strcpy(emptyp.a[2], "#.....#");
   strcpy(emptyp.a[3], "#.....#");
   strcpy(emptyp.a[4], "#.....#");
   strcpy(emptyp.a[5], "#.....#");
   strcpy(emptyp.a[6], "#######");
   add2list(&state, &emptyp);
   assert(state.end == 2);
   assert(empty(&state.p[2]));
   assert(carnum(&state.p[2]) == 0);

   park exitp;

   strcpy(exitp.a[0], "####.##");
   strcpy(exitp.a[1], ".AA.C.#");
   strcpy(exitp.a[2], "#...C.#");
   strcpy(exitp.a[3], ".FFF...");
   strcpy(exitp.a[4], "#..E.B#");
   strcpy(exitp.a[5], "#..E.B#");
   strcpy(exitp.a[6], "###.#.#");
   add2list(&state, &exitp);
   assert(state.end == 3);
   assert(!empty(&state.p[3]));
   assert(carnum(&state.p[3]) == 5);
   carlist(&state.p[3], str1);
   assert(strncmp(str1, "ACFEB", 5) == 0);
   assert(uppercase(&state.p[3]));
   assert(!consec(&state.p[3]));
   assert(!rightshape(&state.p[3]));

   park copy = parkchild(&state.p[3], 3);
   tostring(&copy, 7, 7, str1);
   tostring(&state.p[3], 7, 7, str2);
   assert(strcmp(str1, str2) == 0);
   // add a same one to the list, assert same one won't add
   add2list(&state, &copy);
   assert(state.end == 3);

   assert(reachVerticalexit(1, state.rowsize));
   assert(reachVerticalexit(5, state.rowsize));
   assert(!reachVerticalexit(3, state.rowsize));
   assert(reachHorizontexit(1, state.colsize));
   assert(!reachHorizontexit(4, state.colsize));
   assert(!reachHorizontexit(2, state.colsize));
   tostring(&exitp, 7, 7, str1);
   carVerticalexit(0, 2, 4, &exitp);
   assert(strcmp(str1, "####.##.AA.C.##...C.#.FFF...#..E.B##..E.B####.#.#") == 0);
   carHorizontexit(0, 2, 1, &exitp);
   assert(strcmp(str1, "####.##.AA.C.##...C.#.FFF...#..E.B##..E.B####.#.#") == 0);
   carHorizontexit(5, 6, 3, &exitp);
   assert(strcmp(str1, "####.##.AA.C.##...C.#.FFF...#..E.B##..E.B####.#.#") == 0);
   carVerticalexit(4, 6, 5, &exitp);
   assert(strcmp(str1, "####.##.AA.C.##...C.#.FFF...#..E.B##..E.B####.#.#") == 0);

   assert(!samepark(&state.p[0], &state.p[1]));
   assert(!samepark(&state.p[1], &state.p[2]));
   assert(samepark(&state.p[1], &state.p[1]));

   park wrongshape;

   strcpy(wrongshape.a[0], "####.##");
   strcpy(wrongshape.a[1], ".AAEC.#");
   strcpy(wrongshape.a[2], "#..EC.#");
   strcpy(wrongshape.a[3], ".FFHHD.");
   strcpy(wrongshape.a[4], "#.FE.B#");
   strcpy(wrongshape.a[5], "#C.E.B#");
   strcpy(wrongshape.a[6], "###.#.#");

   add2list(&state, &wrongshape);
   assert(state.end == 4);
   assert(straight(&wrongshape, 'A'));
   assert(!straight(&wrongshape, 'F'));
   assert(!eligiblelength(&wrongshape, 'D'));
   assert(eligiblelength(&wrongshape, 'A'));
   assert(!oneplace(&wrongshape, 'E'));
   assert(!oneplace(&wrongshape, 'C'));
   assert(oneplace(&wrongshape, 'B'));
   assert(!rightshape(&state.p[4]));
   assert(!consec(&state.p[4]));
}

void test2(){
   static list state;
   state.rowsize = 10;
   state.colsize = 8;
   state.end = -1;

   park p;
   strcpy(p.a[0], "########");
   strcpy(p.a[1], "#DBBBE..");
   strcpy(p.a[2], "#D.A.E.#");
   strcpy(p.a[3], "#D.A.E.#");
   strcpy(p.a[4], "#D.A.E.#");
   strcpy(p.a[5], "#D.A.E.#");
   strcpy(p.a[6], ".DCCCE.#");
   strcpy(p.a[7], "#D...E.#");
   strcpy(p.a[8], "#......#");
   strcpy(p.a[9], "#.#.#.##");
   add2list(&state, &p);
   assert(state.end == 0);
   int i = 0;

   while (i <= state.end){
      int movescnt = solvemovescnt(&state, i);
      if (movescnt > 0){
//       printf("movescnt: %d\n", movescnt);
//         assert(movescnt == 13);
      }
      movectrl(&state, i);
      i++;
   }

   static list state2;
   state2.rowsize = 7;
   state2.colsize = 7;
   state2.end = -1;

   park p2;
   strcpy(p2.a[0], "#.#####");
   strcpy(p2.a[1], "#......");
   strcpy(p2.a[2], "#A....#");
   strcpy(p2.a[3], "#A....#");
   strcpy(p2.a[4], "#A....#");
   strcpy(p2.a[5], "...DD.#");
   strcpy(p2.a[6], "####.##");
   add2list(&state2, &p2);
   assert(state2.end == 0);
   i = 0;
   moveVertical(2, 4, 1, &state2, 0);
   moveHorizont(3, 4, 5, &state2, 0);

   char str[STRSIZE];
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######A.....#A....##A....##.....#...DD.#####.##") == 0);
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#.....##A....##A....#.A.DD.#####.##") == 0);
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#A....##A....##A....#..DD..#####.##") == 0);
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#A....##A....##A....#....DD#####.##") == 0);

   carposition(&state2, 4, 'A');
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######A.....#A....##A....##.....#....DD#####.##") == 0);
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#.....##A....##A....#.A..DD#####.##") == 0);

   movectrl(&state2, 5);
   tostring(&state2.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#.....##.....##.....#....DD#####.##") == 0);
}
