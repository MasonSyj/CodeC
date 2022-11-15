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

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   int parentindex;
}park;
   
typedef struct list{
   park p[N];
   int rowsize;
   int colsize;
   int current;
}list;
   
list* parkinit(void);
void movectrl(list* l, int index);
void carposition(list* l, int index, char car);
void moveVertical(int y1, int y2, int x, list* l, int index);
void moveHorizont(int x1, int x2, int y, list* l, int index);
void add2list(list* l, park new);//
int solvemovescnt(list* l, int index);//
park parkcopy(park p, int index); //
int carnum(list* l, int index); //
char* carlist(list* l, int index); //
bool samepark(park p1, park p2, list* l); //
void show(park p); //
bool reachVerticalboundary(int y, list* l); //
bool reachHorizontboundary(int x, list* l); //
void carVerticalexit(int y1, int y2, int x, park* p); //
void carHorizontexit(int x1, int x2, int y, park* p); //
void moveup(int y1, int y2, int x, park* p);  //
void movedown(int y1, int y2, int x, park* p); //
void moveleft(int x1, int x2, int y, park* p); //
void moveright(int x1, int x2, int y, park* p); //
char upsquare(int y, int x, list* l, int index); //
char downsquare(int y, int x, list* l, int index); //
char leftsquare(int y, int x, list* l, int index); //
char rightsquare(int y, int x, list* l, int index); //
char* tostring(park p, int row, int col); //
bool closedcase(park p, int row, int col); //
bool iscar(park p, int j, int i); //
bool samecararound(park p, int j, int i); //
bool consec(park p, int row, int col); //
bool empty(list* l, int index); //
int* printlist(list* l, int index);//
void showlist(list* l, int index);
void test1();
void test2();

/* other than normal situations:
no cars full closed non consec
*/
   
int main(void){
   test1();
   test2();
   
   
   list* l = parkinit();
   bool show = true;
   int i = 0;
   while(i <= l->current){
      if (solvemovescnt(l, i) > 0){
         if (show == true){
           showlist(l, i);
         }
         printf("%d moves", solvemovescnt(l, i));
         exit(EXIT_SUCCESS);
      }
   
      if (empty(l, i) == true){
         fprintf(stderr, "No more new carparks, failed to solve.");
         exit(EXIT_FAILURE);
      }
   
      movectrl(l, i);
      i++;
   }
   
   return 0;
}
   
list* parkinit(void){
   FILE* fp = fopen("10x8_5c_13t.prk", "r");
   int row, col;
   char x;
   assert(fscanf(fp, "%d%c%d", &row, &x, &col) == 3);
   
   char temp[CAPACITY];
   fgets(temp, CAPACITY, fp);
   list* l = (list*)calloc(1, sizeof(list));
   l->rowsize = row;
   l->colsize = col;
   
   
   for (int j = 0; j < row; j++){
      fgets(temp, CAPACITY, fp);
      temp[col] = '\0';
      strncpy(l->p[0].a[j], temp, col);
   }
   l->current = 0;

   if (closedcase(l->p[0], row, col)){
      fprintf(stderr, "This park is fully closed.\n");
   }
   
   l->p[0].parentindex = 0;
   
   
   
   fclose(fp);
   return l;
}
   
void movectrl(list* l, int index){
   char* list = carlist(l, index);
   unsigned int i = 0;
   while (i < strlen(list)){
      carposition(l, index, list[i]);
      i++;
   }
   free(list);
}
   
void carposition(list* l, int index, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;
   for (int j = 1; j < l->rowsize; j++){
      for (int i = 1; i < l->colsize; i++){
         if (l->p[index].a[j][i] == car){
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
   for (int i = 0; i <= l->current; i++){
      if (samepark(l->p[i], new, l)){
         return;
      }
   }
   l->p[++l->current] = new;
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
   
char* carlist(list* l, int index){
   int cnt = 0;
   bool temp[CARSIZE] = {0};
   char car[100];
   for (int j = 0; j < l->rowsize; j++){
      for (int i = 0; i < l->colsize; i++){
         if (isalpha(l->p[index].a[j][i]) && temp[l->p[index].a[j][i] - A] == 0){
            temp[l->p[index].a[j][i] - A] = 1;
            car[cnt++] = l->p[index].a[j][i];
         }
       }
   }
   char* list = (char*)calloc(cnt + 1, sizeof(char));	
   strncpy(list, car, cnt);
   	
   return list;
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
   return strlen(carlist(l, index));
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

bool closedcase(park p, int row, int col){
   for (int j = 0; j < row; j++){
      if (p.a[j][0] != FULL){
         return false;
      }
   
      if (p.a[j][col-1] != FULL){
         return false;
      }
   }

   for (int i = 0; i < col; i++){
      if (p.a[0][i] != FULL){
         return false;
      }
      
      if (p.a[row-1][i] != FULL){
         return false;
      }
   }
   
   return true;
}

bool iscar(park p, int j, int i){
   if (isalpha(p.a[j][i])){
      return true;
   }else{
      return false;
   }
}

bool samecararound(park p, int j, int i){

   if (p.a[j][i] == EMPTY || p.a[j][i] == FULL){
      return false;
   }
   if (p.a[j][i] == p.a[j-1][i] || p.a[j][i] == p.a[j+1][i] 
   || p.a[j][i] == p.a[j][i+1] || p.a[j][i] == p.a[j][i-1]){
      return true;
   }
   return false;  
}

bool consec(park p, int row, int col){
   for (int j = 1; j < row - 1; j++){
      for (int i = 1; i < col - 1; i++){
         if (iscar(p, j, i) && !samecararound(p, j, i)){
            return false;
         }
      }
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

int* printlist(list* l, int index){
   int len = solvemovescnt(l, index);
   int* printl = (int*)calloc(++len, sizeof(int));
   while (index != 0){
      printl[--len] = index;
      //printf("%d %d\n", index, printl[len]);
      index = l->p[index].parentindex;
   }
   return printl;
}

void showlist(list* l, int index){
   int* printl = printlist(l, index);
   for (int i = 0; i < solvemovescnt(l, index) + 1; i++){
      show(l->p[printl[i]]);
   }
}

char* tostring(park p, int row, int col){
   char* str = (char*)calloc(CAPACITY * CAPACITY, sizeof(char));
   char* head = str;
   for (int j = 0; j < row; j++){
      for (int i = 0; i < col; i++){
         *str++ = p.a[j][i];
      }
   }
   *str = '\0';
   return head;
}


void test1(){
   list* l = (list*)calloc(1, sizeof(list));
   l->rowsize = 7;
   l->colsize = 7;
   l->current = 0;

   
   strcpy(l->p[0].a[0], "#.#####");
   strcpy(l->p[0].a[1], ".BBB..#");
   strcpy(l->p[0].a[2], "#A....#");
   strcpy(l->p[0].a[3], "#A...C#");
   strcpy(l->p[0].a[4], "#A...C#");
   strcpy(l->p[0].a[5], "#..DDC#");
   strcpy(l->p[0].a[6], "#######");
   assert(l->current == 0);
   assert(carnum(l, 0) == 4);
   assert(strcmp(carlist(l, 0), "BACD") == 0);

   assert(!closedcase(l->p[0], 7, 7));

   assert(iscar(l->p[0], 1, 1));
   assert(iscar(l->p[0], 2, 1));
   assert(!iscar(l->p[0], 2, 2));
   assert(!iscar(l->p[0], 3, 3));

   assert(samecararound(l->p[0], 1, 1));
   assert(samecararound(l->p[0], 2, 1));
   assert(samecararound(l->p[0], 5, 5));
   assert(!samecararound(l->p[0], 3, 3));

   assert(upsquare(1, 1, l, 0) == EMPTY);
   assert(upsquare(3, 5, l, 0) == EMPTY);
   assert(downsquare(1, 4, l, 0) == EMPTY);
   assert(downsquare(5, 5, l, 0) == FULL);
   assert(leftsquare(5, 3, l, 0) == EMPTY);
   assert(rightsquare(5, 5, l, 0) == FULL);
   assert(rightsquare(1, 3, l, 0) == EMPTY);
   
   char* pstr = tostring(l->p[0], 7, 7);
   assert(strcmp(pstr, "#.#####.BBB..##A....##A...C##A...C##..DDC########") == 0);

   moveup(3, 5, 5, &l->p[0]); 
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##A...C##A...C##A...C##..DD.########") == 0);
   moveup(2, 4, 5, &l->p[0]); 
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB.C##A...C##A...C##A....##..DD.########") == 0);
   movedown(1, 3, 5, &l->p[0]); 
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##A...C##A...C##A...C##..DD.########") == 0);
   moveleft(3, 4, 5, &l->p[0]);
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##A...C##A...C##A...C##.DD..########") == 0);
   moveleft(2, 3, 5, &l->p[0]);
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##A...C##A...C##A...C##DD...########") == 0);
   moveright(1, 2, 5, &l->p[0]);
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##A...C##A...C##A...C##.DD..########") == 0);
   movedown(2, 4, 1, &l->p[0]);
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##....C##A...C##A...C##ADD..########") == 0);
   moveleft(1, 3, 1, &l->p[0]);
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####BBB...##....C##A...C##A...C##ADD..########") == 0);
   moveright(0, 2, 1, &l->p[0]);
   assert(strcmp(tostring(l->p[0], 7, 7), "#.#####.BBB..##....C##A...C##A...C##ADD..########") == 0);
   assert(!empty(l, 0));
   assert(consec(l->p[0], 7, 7));
   
   park closedp;
   strcpy(closedp.a[0], "#######");
   strcpy(closedp.a[1], "#BBB..#");
   strcpy(closedp.a[2], "#A....#");
   strcpy(closedp.a[3], "#A...C#");
   strcpy(closedp.a[4], "#A...C#");
   strcpy(closedp.a[5], "#..DDC#");
   strcpy(closedp.a[6], "#######");
   add2list(l, closedp);
   assert(l->current == 1);
   assert(closedcase(closedp, 7, 7));
   assert(carnum(l, 1) == 4);
   
   park emptyp;
   strcpy(emptyp.a[0], "#######");
   strcpy(emptyp.a[1], "#.....#");
   strcpy(emptyp.a[2], "#.....#");
   strcpy(emptyp.a[3], "#.....#");
   strcpy(emptyp.a[4], "#.....#");
   strcpy(emptyp.a[5], "#.....#");
   strcpy(emptyp.a[6], "#######");
   add2list(l, emptyp);
   assert(l->current == 2);
   assert(empty(l, 2));
   assert(carnum(l, 2) == 0);

   park exitp;

   strcpy(exitp.a[0], "####C##");
   strcpy(exitp.a[1], "AAA.C.#");
   strcpy(exitp.a[2], "#...C.#");
   strcpy(exitp.a[3], ".FFF.DD");
   strcpy(exitp.a[4], "#..E.B#");
   strcpy(exitp.a[5], "#..E.B#");
   strcpy(exitp.a[6], "###.#B#");
   add2list(l, exitp);
   assert(l->current == 3);
   assert(!empty(l, 3));
   assert(carnum(l, 3) == 6);
   assert(strcmp(carlist(l, 3), "CAFDEB") == 0);

   park copy = parkcopy(l->p[3], 3);
   assert(strcmp(tostring(copy, 7, 7), tostring(l->p[3], 7, 7)) == 0);
   // add a same one to the list, thcarpositione same one won't add and will be freed.
   add2list(l, copy);
   assert(l->current == 3);

   assert(reachVerticalboundary(1, l));
   assert(reachVerticalboundary(5, l));
   assert(!reachVerticalboundary(3, l));
   assert(reachHorizontboundary(1, l));
   assert(!reachHorizontboundary(4, l));
   assert(!reachHorizontboundary(2, l));

   carVerticalexit(0, 2, 4, &exitp);
   assert(strcmp(tostring(exitp, 7, 7), "####.##AAA...##.....#.FFF.DD#..E.B##..E.B####.#B#") == 0);
   carHorizontexit(0, 2, 1, &exitp);
   assert(strcmp(tostring(exitp, 7, 7), "####.##......##.....#.FFF.DD#..E.B##..E.B####.#B#") == 0);
   carHorizontexit(5, 6, 3, &exitp);
   assert(strcmp(tostring(exitp, 7, 7), "####.##......##.....#.FFF...#..E.B##..E.B####.#B#") == 0);
   carVerticalexit(4, 6, 5, &exitp);
   assert(strcmp(tostring(exitp, 7, 7), "####.##......##.....#.FFF...#..E..##..E..####.#.#") == 0);
 
   assert(!samepark(l->p[0], l->p[1], l));
   assert(!samepark(l->p[1], l->p[2], l));
   assert(samepark(l->p[1], l->p[1], l));

   park* notconsec = (park*)calloc(1, sizeof(park));
   
   strcpy(notconsec->a[0], "####C##");
   strcpy(notconsec->a[1], "AAA.C.#");
   strcpy(notconsec->a[2], "#...C.#");
   strcpy(notconsec->a[3], ".FF.FDD");
   strcpy(notconsec->a[4], "#..E.B#");
   strcpy(notconsec->a[5], "#..E.B#");
   strcpy(notconsec->a[6], "###.#B#");

   add2list(l, *notconsec);
   assert(l->current == 4);

   assert(!consec(*notconsec, 7, 7));
}

void test2(){
   list* l = (list*)calloc(1, sizeof(list));
   l->rowsize = 10;
   l->colsize = 8;
   l->current = -1;
   park p ;
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
   add2list(l, p);
   assert(l->current == 0);
   int i = 0;
   int markindex = 0;
   
   while (i <= l->current){
      if (solvemovescnt(l, i) > 0){
         assert(solvemovescnt(l, i) == 13);
         markindex = i;
      }
      movectrl(l, i);
      i++;      
   }
   int* printl = printlist(l, markindex);
   
   assert(printl[0] == 0);
   assert(printl[1] == 1);
   assert(printl[2] == 4);
   assert(printl[3] == 10);
   assert(printl[4] == 20);
   assert(printl[5] == 36);
   assert(printl[6] == 60);

   list* l2 = (list*)calloc(1, sizeof(list));
   l2->rowsize = 7;
   l2->colsize = 7;
   l2->current = -1;
   park p2;
   strcpy(p2.a[0], "#.#####");
   strcpy(p2.a[1], "#......");
   strcpy(p2.a[2], "#A....#");
   strcpy(p2.a[3], "#A....#");
   strcpy(p2.a[4], "#A....#");
   strcpy(p2.a[5], "...DD.#");
   strcpy(p2.a[6], "####.##");
   add2list(l2, p2);
   
   i = 0;
   moveVertical(2, 4, 1, l2, 0);
   moveHorizont(3, 4, 5, l2, 0);
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######A.....#A....##A....##.....#...DD.#####.##") == 0);
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######......#.....##A....##A....#.A.DD.#####.##") == 0);
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######......#A....##A....##A....#..DD..#####.##") == 0);
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######......#A....##A....##A....#....DD#####.##") == 0);
   
   carposition(l2, 4, 'A');
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######A.....#A....##A....##.....#....DD#####.##") == 0);
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######......#.....##A....##A....#.A..DD#####.##") == 0);
   
   movectrl(l2, 5);
   assert(strcmp(tostring(l2->p[++i], 7, 7), "#.######......#.....##.....##.....#....DD#####.##") == 0);
}
