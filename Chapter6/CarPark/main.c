#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
   
#define N 100000
#define EMPTY '.'
#define FULL '#'
#define CAPACITY 20
#define CARSIZE 26
#define A 'A'
#define STRSIZE 100

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

//question 2, what does const char*, the const mean?
//question 3, test in the extension.c?


// read from a file initiate the list and the first carpark
void parkinit(list* state);
// main control function to process one carpark's all possible moves 
void movectrl(list* l, int index);
// based on the car, find out the its [y][x] in the 2D array
void carposition(list* l, int index, char car);
// for vertical direction car, do the up and down move
void moveVertical(int y1, int y2, int x, list* l, int index);
// for horizont direction car, do the left and right move
void moveHorizont(int x1, int x2, int y, list* l, int index);
// add the new park to the list
void add2list(list* l, park new);
// when one carpark is solved, count its moves by its parentindex
int solvemovescnt(list* l, int index);
// make a copy of the park
park parkcopy(park p, int index); 
// count the number of cars in a carpark
int carnum(list* l, int index); 
// get the list of cars in a carpark
void carlist(list* l, int index, char* list);
// check if two carparks are same, true if same
bool samepark(park p1, park p2, list* l); 
// show the park
void show(park p);
// check if one car moves vertically reach boundary(also check not bollards)
bool reachVerticalboundary(int y, list* l); 
// check if one car moves horizontally reach boundary(check not bollards)
bool reachHorizontboundary(int x, list* l); 
// for a car moves vertically reach exit, remove it from the park
void carVerticalexit(int y1, int y2, int x, park* p); //
// for a car moves horizontally reach exit, remove it from the park
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
char upsquare(int y, int x, list* l, int index); 
// see what the down square  is, if not bollard, prepare for move up
char downsquare(int y, int x, list* l, int index); 
// see what the left square is, if not bollard, prepare for move up
char leftsquare(int y, int x, list* l, int index); 
// see what the right square is, if not bollard, prepare for move up
char rightsquare(int y, int x, list* l, int index); 
// convert a park into a 1D array for testing
void tostring(park p, int row, int col, char* str);
// check if the park is in right shape which car is connected and length at least 2
bool rightshape(list* l, int index);
// given a car, no other place should apper except its head and tail and between.
bool noother(park p, char car);
// given a car, locate its head and tail, and between all chars are same sign
bool samesign(park p, char car);
// check if the [j][i] is car
bool iscar(park p, int j, int i); 
// check if the park is empty, if empty, then means solved
bool empty(list* l, int index); //
// record the index of the correct moves into a 1D array
void printlist(list* l, int index, int* listint, int len);
// based the array recording parent index, show all carparks
void showlist(list* l, int index, int* listint);
// based on the car in a carpark, get its head and tail(two [y][x] naturally)
void carcoord(int* y1, int* y2, int* x1, int* x2, park p, char car);
// return one park's rowsize
int rowsize(park p);
// return one park's colsize
int colsize(park p);
void test1();
void test2();

/* other than normal situations:
no cars full closed non consec
*/
   
int main(void){
//  test1();
//  test2();
   static list state;
   parkinit(&state);
   bool isshow = true;
   int i = 0;
   int listshow[STRSIZE] = {0};
   while(i <= state.end){
      if (solvemovescnt(&state, i) > 0){
         printf("%d\n", solvemovescnt(&state, i));
         if (isshow == true){
           printlist(&state, i, listshow, solvemovescnt(&state, i) + 1);
           showlist(&state, i, listshow);
         }
         printf("i: %d  %d moves", i, solvemovescnt(&state, i));
         exit(EXIT_SUCCESS);
      }
   
      if (empty(&state, i) == true){
         fprintf(stderr, "No more new carparks, failed to solve.");
         exit(EXIT_FAILURE);
      }
   
      movectrl(&state, i);
      i++;
   }
   
   return 0;
}
   
void parkinit(list* state){
   FILE* fp = fopen("10x7_8c_16t.prk", "r");
   int row, col;
   char x;
   assert(fscanf(fp, "%d%c%d", &row, &x, &col) == 3);
   
   char temp[CAPACITY];
   fgets(temp, CAPACITY, fp);
   state->rowsize = row;
   state->colsize = col;
   
   for (int j = 0; j < row; j++){
      fgets(temp, CAPACITY, fp);
      temp[col] = '\0';
      strncpy(state->p[0].a[j], temp, col);
   }
   state->end = 0;
   
   state->p[0].parentindex = 0;
   
   fclose(fp);
   return;
}
   
void movectrl(list* l, int index){
   char list[CARSIZE];
   carlist(l, index, list);
   unsigned int i = 0;
   while (i < strlen(list)){
      carposition(l, index, list[i]);
      i++;
   }
}

void carcoord(int* y1, int* y2, int* x1, int* x2, park p, char car){
   *y1 = 0;
   for (int j = 1; j < rowsize(p); j++){
      for (int i = 1; i < colsize(p); i++){
         if (p.a[j][i] == car){
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
   
void carposition(list* l, int index, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;

   carcoord(&y1, &y2, &x1, &x2, l->p[index], car);
   
   if (y1 == y2){
      moveHorizont(x1, x2, y1, l, index);
   }else{
      moveVertical(y1, y2, x1, l, index);
   }

}


void moveVertical(int y1, int y2, int x, list* l, int index){
   //move up 
   if (upsquare(y1, x, l, index) == EMPTY){
      park new = parkcopy(l->p[index], index);
      if (reachVerticalboundary(y1, l)){
         carVerticalexit(y1, y2, x, &new);
         add2list(l, new);
      }else{
         moveup(y1, y2, x, &new);
         add2list(l, new);
      }
   }
   //move down
   if (downsquare(y2, x, l, index) == EMPTY){
      park new = parkcopy(l->p[index], index);
      if (reachVerticalboundary(y2, l)){
         carVerticalexit(y1, y2, x, &new);
         add2list(l, new);
      }else{
         movedown(y1, y2, x, &new);
         add2list(l, new);
      }
   }
}

void moveHorizont(int x1, int x2, int y, list* l, int index){
   //move left
   if (leftsquare(y, x1, l, index) == EMPTY){
      park new = parkcopy(l->p[index], index);
      if (reachHorizontboundary(x1, l)){
         carHorizontexit(x1, x2, y, &new);
         add2list(l, new);
      }else{
         moveleft(x1, x2, y, &new);
         add2list(l, new);
      }
   }
   //move right
   if (rightsquare(y, x2, l, index) == EMPTY){
      park new = parkcopy(l->p[index], index);	
      if (reachHorizontboundary(x2, l)){
         carHorizontexit(x1, x2, y, &new);
         add2list(l, new);
      }else{
         moveright(x1, x2, y, &new);
         add2list(l, new);
        }
   }
}
   
park parkcopy(park p, int index){
   park new;
   memcpy(&new, &p, sizeof(park));
   new.parentindex = index;
   return new;
}
   
void add2list(list* l, park new){
   for (int i = 0; i <= l->end; i++){
      if (samepark(l->p[i], new, l)){
         return;
      }
   }
   l->p[++l->end] = new;
   return;
}
   
bool samepark(park p1, park p2, list* l){
   for (int j = 0; j < l->rowsize; j++){
      for (int i = 0; i < l->colsize; i++){
         if (p1.a[j][i] != p2.a[j][i]){
            return false;
         }
      }
   }
   return true;
}
   
void carlist(list* l, int index, char* list){
   int cnt = 0;
   bool temp[CARSIZE] = {0};
   char car[CARSIZE];
   for (int j = 0; j < l->rowsize; j++){
      for (int i = 0; i < l->colsize; i++){
         if (isalpha(l->p[index].a[j][i]) && temp[l->p[index].a[j][i] - A] == 0){
            temp[l->p[index].a[j][i] - A] = 1;
            car[cnt++] = l->p[index].a[j][i];
         }
       }
   }	
   strncpy(list, car, cnt);
}

void show(park p){
   printf("---------------\n");
   for (int j = 0; j < CAPACITY; j++){
      if (p.a[j][0] != FULL && p.a[j][0] != EMPTY){
         return;
      }
      puts(p.a[j]);
   }
   
}
   
int carnum(list* l, int index){
   char list[CARSIZE];
   carlist(l, index, list);
   return strlen(list);
}

bool samesign(park p, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;

   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (y1 == y2){
      for (int i = x1; i <= x2; i++){
         if (p.a[y1][i] != car){
            return false;
         }
      }
   }else{
      for (int j = y1; j <= y2; j++){
         if (p.a[j][x1] != car){
            return false;
         }
      }
   }
   return true;
}

bool noother(park p, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;
   int len = 0;

   carcoord(&y1, &y2, &x1, &x2, p, car);

   if (y1 == y2){
      len = y2 - y1;

   }else{
      len = x2 - x1;
   }

   int cnt = 0;
   for (int j = 1; j < rowsize(p) - 1; j++){
      for (int i = 1; i < colsize(p) - 1; i++){
         if (p.a[j][i] == car){
            cnt++;
         }
      }
   }
   return len == cnt;
}

bool rightshape(list* l, int index){
   char list[STRSIZE];
   carlist(l, index, list);
   int len = strlen(list);
   int i = 0;
   while (i < len){
      char car = list[i];
      if (!samesign(l->p[index], car) || !noother(l->p[index], car)){
         return false;
      }
      i++;
   }
   return true;
}

bool empty(list* l, int index){
   if (carnum(l, index) > 0){
      return false;
   }else{
      return true;
   }
//   return carnum(l, index) == 0;
}

   
int solvemovescnt(list* l, int index){
   if (carnum(l, index) > 0){
      return 0;
   }
   
   int cnt = 0;
   while(index != 0){
      cnt++;
      index = l->p[index].parentindex;
   }
   return cnt;
}


char upsquare(int y, int x, list* l, int index){
   if (y - 1 >= 0){
      return l->p[index].a[y - 1][x];
   }else{
      return FULL;
   }
}

char downsquare(int y, int x, list* l, int index){
   if (y + 1 < l->rowsize){
      return l->p[index].a[y + 1][x];
   }else{
      return FULL;
   }
}

char leftsquare(int y, int x, list* l, int index){
   if (x - 1 >= 0){
      return l->p[index].a[y][x - 1];
   }else{
      return FULL;
   }
}

char rightsquare(int y, int x, list* l, int index){
   if (x + 1 < l->rowsize){
      return l->p[index].a[y][x + 1];
   }else{
      return FULL;
   }
}

bool reachVerticalboundary(int y, list* l){
   return y == 1 || y == l->rowsize - 2;
}

bool reachHorizontboundary(int x, list* l){
   return x == 1 || x == l->colsize - 2;
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

bool iscar(park p, int j, int i){
   if (isalpha(p.a[j][i])){
      return true;
   }else{
      return false;
   }
}


void printlist(list* l, int index, int* listint, int len){
   while (index != 0){
//      printf("index: %d  len: %d\n", index, len);
      listint[--len] = index;
      index = l->p[index].parentindex;
   }
   return;
}

void showlist(list* l, int index, int* listint){
   for (int i = 0; i < solvemovescnt(l, index) + 1; i++){
      show(l->p[listint[i]]);
   }
}

void tostring(park p, int row, int col, char* str){
   strcpy(str, "");
   char* head = str;
   for (int j = 0; j < row; j++){
      for (int i = 0; i < col; i++){
         *head++ = p.a[j][i];
      }
   }
   *head = '\0';
   return;
}

int rowsize(park p){
   int cnt = 0;
   while (p.a[cnt][0] == FULL || p.a[cnt][0] == EMPTY){
      cnt++;
   }
   return cnt;
}
int colsize(park p){
   return strlen(p.a[0]);
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
   assert(carnum(&state, 0) == 4);
   carlist(&state, 0, str1);
   assert(strcmp(str1, "BACD") == 0);

   assert(iscar(state.p[0], 1, 1));
   assert(iscar(state.p[0], 2, 1));
   assert(!iscar(state.p[0], 2, 2));
   assert(!iscar(state.p[0], 3, 3));


   assert(upsquare(1, 1, &state, 0) == EMPTY);
   assert(upsquare(3, 5, &state, 0) == EMPTY);
   assert(downsquare(1, 4, &state, 0) == EMPTY);
   assert(downsquare(5, 5, &state, 0) == FULL);
   assert(leftsquare(5, 3, &state, 0) == EMPTY);
   assert(rightsquare(5, 5, &state, 0) == FULL);
   assert(rightsquare(1, 3, &state, 0) == EMPTY);
   

   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A....##A...C##A...C##..DDC########") == 0);

   moveup(3, 5, 5, &state.p[0]); 
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##..DD.########") == 0);
   moveup(2, 4, 5, &state.p[0]); 
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB.C##A...C##A...C##A....##..DD.########") == 0);
   movedown(1, 3, 5, &state.p[0]); 
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##..DD.########") == 0);
   moveleft(3, 4, 5, &state.p[0]);
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##.DD..########") == 0);
   moveleft(2, 3, 5, &state.p[0]);
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##DD...########") == 0);
   moveright(1, 2, 5, &state.p[0]);
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##A...C##A...C##A...C##.DD..########") == 0);
   movedown(2, 4, 1, &state.p[0]);
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##....C##A...C##A...C##ADD..########") == 0);
   moveleft(1, 3, 1, &state.p[0]);
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####BBB...##....C##A...C##A...C##ADD..########") == 0);
   moveright(0, 2, 1, &state.p[0]);
   tostring(state.p[0], 7, 7, str1);
   assert(strcmp(str1, "#.#####.BBB..##....C##A...C##A...C##ADD..########") == 0);
   assert(!empty(&state, 0));
   
   park closedp;
   strcpy(closedp.a[0], "#######");
   strcpy(closedp.a[1], "#BBB..#");
   strcpy(closedp.a[2], "#A....#");
   strcpy(closedp.a[3], "#A...C#");
   strcpy(closedp.a[4], "#A...C#");
   strcpy(closedp.a[5], "#..DDC#");
   strcpy(closedp.a[6], "#######");
   add2list(&state, closedp);
   assert(state.end == 1);
   assert(carnum(&state, 1) == 4);
   
   park emptyp;
   strcpy(emptyp.a[0], "#######");
   strcpy(emptyp.a[1], "#.....#");
   strcpy(emptyp.a[2], "#.....#");
   strcpy(emptyp.a[3], "#.....#");
   strcpy(emptyp.a[4], "#.....#");
   strcpy(emptyp.a[5], "#.....#");
   strcpy(emptyp.a[6], "#######");
   add2list(&state, emptyp);
   assert(state.end == 2);
   assert(empty(&state, 2));
   assert(carnum(&state, 2) == 0);

   park exitp;

   strcpy(exitp.a[0], "####C##");
   strcpy(exitp.a[1], "AAA.C.#");
   strcpy(exitp.a[2], "#...C.#");
   strcpy(exitp.a[3], ".FFF.DD");
   strcpy(exitp.a[4], "#..E.B#");
   strcpy(exitp.a[5], "#..E.B#");
   strcpy(exitp.a[6], "###.#B#");
   add2list(&state, exitp);
   assert(state.end == 3);
   assert(!empty(&state, 3));
   assert(carnum(&state, 3) == 6);
   carlist(&state, 3, str1);
   assert(strcmp(str1, "CAFDEB") == 0);

   park copy = parkcopy(state.p[3], 3);
   tostring(copy, 7, 7, str1);
   tostring(state.p[3], 7, 7, str2);
   assert(strcmp(str1, str2) == 0);
   // add a same one to the list, thcarpositione same one won't add and will be freed.
   add2list(&state, copy);
   assert(state.end == 3);

   assert(reachVerticalboundary(1, &state));
   assert(reachVerticalboundary(5, &state));
   assert(!reachVerticalboundary(3, &state));
   assert(reachHorizontboundary(1, &state));
   assert(!reachHorizontboundary(4, &state));
   assert(!reachHorizontboundary(2, &state));

   tostring(exitp, 7, 7, str1);
   carVerticalexit(0, 2, 4, &exitp);
   assert(strcmp(str1, "####.##AAA...##.....#.FFF.DD#..E.B##..E.B####.#B#") == 0);
   carHorizontexit(0, 2, 1, &exitp);
   assert(strcmp(str1, "####.##......##.....#.FFF.DD#..E.B##..E.B####.#B#") == 0);
   carHorizontexit(5, 6, 3, &exitp);
   assert(strcmp(str1, "####.##......##.....#.FFF...#..E.B##..E.B####.#B#") == 0);
   carVerticalexit(4, 6, 5, &exitp);
   assert(strcmp(str1, "####.##......##.....#.FFF...#..E..##..E..####.#.#") == 0);
 
   assert(!samepark(state.p[0], state.p[1], &state));
   assert(!samepark(state.p[1], state.p[2], &state));
   assert(samepark(state.p[1], state.p[1], &state));

   park wrongshape;
   
   strcpy(wrongshape.a[0], "####C##");
   strcpy(wrongshape.a[1], "AAA.C.#");
   strcpy(wrongshape.a[2], "#..EC.#");
   strcpy(wrongshape.a[3], ".FF..DD");
   strcpy(wrongshape.a[4], "#.FE.B#");
   strcpy(wrongshape.a[5], "#..E.B#");
   strcpy(wrongshape.a[6], "###.#B#");

   add2list(&state, wrongshape);
   assert(state.end == 4);

   assert(!rightshape(&state, 4));
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
   add2list(&state, p);
   assert(state.end == 0);
   int i = 0;
   int markindex = 0;
   
   while (i <= state.end){
      if (solvemovescnt(&state, i) > 0){
         assert(solvemovescnt(&state, i) == 13);
         markindex = i;
      }
      movectrl(&state, i);
      i++;      
   }

   int listprint[CARSIZE] = {0};
   printlist(&state, markindex, listprint, 14);
   
   assert(listprint[0] == 0);
   assert(listprint[1] == 1);
   assert(listprint[2] == 4);
   assert(listprint[3] == 10);
   assert(listprint[4] == 20);
   assert(listprint[5] == 36);
   assert(listprint[6] == 60);

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
   add2list(&state2, p2);
   
   i = 0;
   moveVertical(2, 4, 1, &state, 0);
   moveHorizont(3, 4, 5, &state, 0);

   char str[STRSIZE];
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######A.....#A....##A....##.....#...DD.#####.##") == 0);
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#.....##A....##A....#.A.DD.#####.##") == 0);
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#A....##A....##A....#..DD..#####.##") == 0);
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#A....##A....##A....#....DD#####.##") == 0);
   
   carposition(&state2, 4, 'A');
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######A.....#A....##A....##.....#....DD#####.##") == 0);
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#.....##A....##A....#.A..DD#####.##") == 0);
   
   movectrl(&state2, 5);
   tostring(state.p[++i], 7, 7, str);
   assert(strcmp(str, "#.######......#.....##.....##.....#....DD#####.##") == 0);
}

