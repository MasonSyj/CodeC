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
   park* p[10000];
   int rowsize;
   int colsize;
   int current;
}list;
   
list* parkinit(void);
void movectrl(list* l, int index);
void carposition(list* l, int index, char car);
void moveVertical(int y1, int y2, int x, list* l, int index);
void moveHorizont(int y1, int y2, int x, list* l, int index);
park* parkcopy(park* p, int index);
void add2list(list* l, park* new);
int carnum(list* l, int index);
char* carlist(list* l, int index);
bool samepark(park* p1, park* p2, list* l);
int solve(list* l, int index);
void show(park* p);
char upsquare(int y, int x, list* l, int index);
char downsquare(int y, int x, list* l, int index);
char leftsquare(int y, int x, list* l, int index);
char rightsquare(int y, int x, list* l, int index);
bool reachVerticalboundary(int y, list* l);
bool reachHorizontboundary(int x, list* l);
void carVerticalexit(int y1, int y2, int x, park* p);
void carHorizontexit(int x1, int x2, int y, park* p);
void moveup(int y1, int y2, int x, park* p);
void movedown(int y1, int y2, int x, park* p);
void moveleft(int x1, int x2, int y, park* p);
void moveright(int x1, int x2, int y, park* p);
char* tostring(park* p, int row, int col);
bool closedcase(park* p, int row, int col);
bool iscar(park* p, int j, int i);
bool existcararound(park* p, int j, int i);
bool empty(park* p);
bool consec(park* p, int row, int col);
void test();

char* tostring(park* p, int row, int col){
   char* str = (char*)calloc(CAPACITY * CAPACITY, sizeof(char));
   char* head = str;
   for (int j = 0; j < row; j++){
      for (int i = 0; i < col; i++){
         *str++ = p->a[j][i];
      }
   }
   *str = '\0';
   return head;
}

void test(){
   park* p = (park*)calloc(1, sizeof(park));
   strcpy(p->a[0], "#.#####");
   strcpy(p->a[1], ".BBB..#");
   strcpy(p->a[2], "#A....#");
   strcpy(p->a[3], "#A...C#");
   strcpy(p->a[4], "#A...C#");
   strcpy(p->a[5], "#..DDC#");
   strcpy(p->a[6], "#######");
   
   char* pstr = tostring(p, 7, 7);
   assert(strcmp(pstr, "#.#####.BBB..##A....##A...C##A...C##..DDC########") == 0);
   show(p);
/*
   moveup(3, 5, 5, p); // show(p);
   assert(strcmp(tostring(p, 7, 7), "#.#####.BBB..##A...C##A...C##A....##..DDC########") == 0);
   moveup(2, 4, 5, p); // show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB.C##A...C##A....##A....##..DDC########") == 0);
   movedown(1, 3, 5, p); // show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB..##A...C##A...C##A....##..DDC########") == 0);
   moveleft(5, 6, 5, p);//show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB..##A...C##A...C##A....##..DC#.#######") == 0);
   moveleft(4, 5, 5, p);//show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB..##A...C##A...C##A....##..C#..#######") == 0);
   moveright(4, 5, 5, p);//show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB..##A...C##A...C##A....##..C.#.#######") == 0);
   movedown(2, 4, 1, p);//show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB..##....C##A...C##A....##A.C.#.#######") == 0);
   moveleft(1, 3, 1, p);//show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#BBB...##....C##A...C##A....##A.C.#.#######") == 0);
   moveright(0, 2, 1, p);//show(p);
   assert(strcmp(tostring(p, 7, 7), "#.###.#.BBB..##....C##A...C##A....##A.C.#.#######") == 0);
   show(p);
*/
   assert(!empty(p));
   assert(consec(p, 7, 7));
}

/* other than normal situations:
no cars full closed non consec
*/
   
int main(void){
   test();
   
   list* l = parkinit();
   
   int i = 0;
   while(i < N){
 //     show(l->p[i]);
      if (empty(l->p[i]) == true){
         fprintf(stderr, "No more new carparks, failed to solve.");
         exit(EXIT_FAILURE);
      }
      if (solve(l, i) > 0){
         printf("%d moves", solve(l, i));
         exit(EXIT_SUCCESS);
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
   l->p[0] = (park*)calloc(1, sizeof(park));

   for (int j = 0; j < row; j++){
      fgets(temp, CAPACITY, fp);
      temp[col] = '\0';
      strncpy(l->p[0]->a[j], temp, col);
   }

   if (closedcase(l->p[0], row, col)){
      fprintf(stderr, "This park is fully closed.\n");
   }
   l->p[0]->parentindex = 0;

   l->rowsize = row;
   l->colsize = col;
   l->current = 0;
   
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
   if (upsquare(y1, x, l, index) == EMPTY){
      park* new = parkcopy(l->p[index], index);
      if (reachVerticalboundary(y1, l)){
         carVerticalexit(y1, y2, x, new);
         add2list(l, new);
      }else{
         moveup(y1, y2, x, new);
         add2list(l, new);
      }
   }
   //move down
   if (downsquare(y2, x, l, index) == EMPTY){
      park* new = parkcopy(l->p[index], index);
      if (reachVerticalboundary(y2, l)){
         carVerticalexit(y1, y2, x, new);
         add2list(l, new);
      }else{
         movedown(y1, y2, x, new);
         add2list(l, new);
      }
   }
}

void moveHorizont(int x1, int x2, int y, list* l, int index){
   //move left
   if (leftsquare(y, x1, l, index) == EMPTY){
      park* new = parkcopy(l->p[index], index);
      if (reachHorizontboundary(x1, l)){
         carHorizontexit(x1, x2, y, new);
         add2list(l, new);
      }else{
         moveleft(x1, x2, y, new);
         add2list(l, new);	
      }
   }
   //move right
   if (rightsquare(y, x2, l, index) == EMPTY){
      park* new = parkcopy(l->p[index], index);	
      if (reachHorizontboundary(x2, l)){
         carHorizontexit(x1, x2, y, new);
         add2list(l, new);
         }else{
            moveright(x1, x2, y, new);
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
   bool temp[CARSIZE] = {0};
   char car[100];
   for (int j = 0; j < l->rowsize; j++){
      for (int i = 0; i < l->colsize; i++){
         if (isalpha(l->p[index]->a[j][i]) && temp[l->p[index]->a[j][i] - A] == 0){
            temp[l->p[index]->a[j][i] - A] = 1;
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
   if (carnum(l, index) > 0){
      return 0;
   }
   
   int cnt = 0;
   while(index != 0){
      cnt++;
      index = l->p[index]->parentindex;
   }
   return cnt;
}


char upsquare(int y, int x, list* l, int index){
   if (y - 1 >= 0){
      return l->p[index]->a[y - 1][x];
   }else{
      return FULL;
   }
}

char downsquare(int y, int x, list* l, int index){
   if (y + 1 < l->rowsize){
      return l->p[index]->a[y + 1][x];
   }else{
      return FULL;
   }
}

char leftsquare(int y, int x, list* l, int index){
   if (x - 1 >= 0){
      return l->p[index]->a[y][x - 1];
   }else{
      return FULL;
   }
}

char rightsquare(int y, int x, list* l, int index){
   if (x + 1 < l->rowsize){
      return l->p[index]->a[y][x + 1];
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

bool closedcase(park* p, int row, int col){
   for (int j = 0; j < row; j++){
      if (p->a[j][0] != FULL){
         return false;
      }
   
      if (p->a[j][col-1] != FULL){
         return false;
      }
   }

   for (int i = 0; i < col; i++){
      if (p->a[0][i] != FULL){
         return false;
      }
      
      if (p->a[row-1][i] != FULL){
         return false;
      }
   }
   
   return true;
}

bool iscar(park* p, int j, int i){
   if (isalpha(p->a[j][i])){
      return true;
   }else{
      return false;
   }
}

bool existcararound(park* p, int j, int i){
   return iscar(p, j-1, i) || iscar(p, j, i-1) || iscar(p, j+1, i) || iscar(p, j, i+1);  
}

bool consec(park* p, int row, int col){
   for (int j = 1; j < row - 1; j++){
      for (int i = 1; i < col - 1; i++){
         if (iscar(p, j, i) && existcararound(p, j, i)){
            if (!(existcararound(p, j, i))){
               return false;
            }
         }
      }
   }
   return true;
}


bool empty(park* p){
   park* cmp = (park*)calloc(1, sizeof(park));
   bool result = memcmp(p, cmp, sizeof(park));
   free(cmp);
   return !result;
}

