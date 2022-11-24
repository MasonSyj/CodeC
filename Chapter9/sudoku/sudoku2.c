#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define N 9
#define TRYTIMES 100
#define CAPACITY 1000000
#define SCALEFACTOR 4

typedef struct cell{
   bool num[N];
   int this;
}cell;

typedef struct oneboard{
   cell board[N][N];
}oneboard;

typedef struct coll{
   oneboard* state;
   int capacity;
   int end;
}coll;

int rowfillctrl(cell board[][N]);
int rowfill(cell board[][N], int row);
int colfillctrl(cell board[][N]);
int colfill(cell board[][N], int col);
void unitselect(int rowmark, int colmark, int* left, int* right, int* up, int* down);
int unitfillctrl(cell board[][N]);
int unitfill(cell board[][N], int row, int col);
int areafill(cell board[][N]);
int sumofbool(cell board[][N], int j, int i);
void setallzero(cell board[][N]);
void rowscan(cell board[][N], int j, int i);
void colscan(cell board[][N], int j, int i);
void unitscan(cell board[][N], int j, int i);
void boardprint(cell board[][N]);
void areascan(cell board[][N]);
void unitboundaryset(int j, int i, int* left, int* right, int* up, int* down);
void cellstatusprint(cell board[][N]);
void boolnumprint(cell onecell);
void oneguess(cell board[][N]);
void solve(cell board[][N]);
coll* coll_init();
void coll_insert(coll* c, oneboard board);
oneboard twod2oneboard(cell board[][N]);


int main(void){
   FILE* fp = fopen("9x9-online.sud", "r");
   if (!fp){
      fprintf(stderr, "cannot open file.\n");
      exit(EXIT_FAILURE);
   }
   
   cell board[N][N];
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         int number = fgetc(fp);
         board[j][i].this = number - '0';
      }
      // every 9 numbers followed by a newline which needs to be addressed.
      int newline = fgetc(fp);
      assert(newline == '\n');
//      int null = fgetc(fp);
//      assert(null == '\0');
   }
   setallzero(board);

//   boardprint(board);
//   cellstatusprint(board);

   coll* c = coll_init();
   oneboard this = twod2oneboard(board);
   coll_insert(c, this);
   oneguess(board);
   boardprint(board);
   this = twod2oneboard(board);
   coll_insert(c, this);   

   boardprint(c->state[0].board);
   boardprint(c->state[1].board);

}

coll* coll_init(){
   coll* c = (coll*)calloc(1, sizeof(coll));
   assert(c);
   c->state = (oneboard*)calloc(CAPACITY, sizeof(oneboard));
   assert(c->state);
   c->capacity = CAPACITY;
   return c;
}

void coll_insert(coll* c, oneboard board){
   if (c->end >= c->capacity){
      c->state = (oneboard*)realloc(c->state, c->capacity * SCALEFACTOR * sizeof(oneboard));
      c->capacity *= SCALEFACTOR;
   }
   c->state[c->end++] = board;
}

oneboard twod2oneboard(cell board[][N]){
   oneboard this;
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         this.board[j][i].this = board[j][i].this;
         for (int cnt = 0; cnt < N; cnt++){
            this.board[j][i].num[cnt] = board[j][i].num[cnt];
         }
      }
   }
   return this;
}

void solve(cell board[][N]){
   int newchange = 1;
   while (newchange > 0){
      newchange = 0;
      newchange += areafill(board);
      newchange += unitfillctrl(board);
      newchange += rowfillctrl(board);
      newchange += colfillctrl(board);
   }  
}

void oneguess(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         if (sumofbool(board,j,i) == 7){
            for (int cnt = 0; cnt < N; cnt++){
               if (board[j][i].num[cnt] == 0){
                  board[j][i].this = cnt + 1;
                  board[j][i].num[cnt] = 1;
                  return;
               }
            }
         }
      }
   }   
}


int rowfillctrl(cell board[][N]){
   int changes = 0;
   for (int row = 0; row < N; row++){
      changes += rowfill(board, row);
   }
   return changes;
}

int rowfill(cell board[][N], int row){
   int changes = 0;
   int unitnum[N] = {0};
   bool unitexist[N] = {0};
   int blanknums = 0;
   for (int col = 0; col < N; col++){
      if (board[row][col].this == 0){
         blanknums++;
         for (int cnt = 0; cnt < N; cnt++){
            unitnum[cnt] += board[row][col].num[cnt];
         }
      }else{
         unitexist[board[row][col].this - 1] = true;
      }
   }
   
   for (int cnt = 0; cnt < N; cnt++){
      if (unitnum[cnt] == blanknums - 1 && unitexist[cnt] == false){
         for (int col = 0; col < N; col++){
            if (board[row][col].this == 0 && board[row][col].num[cnt] == false){
               board[row][col].this = cnt + 1;
               board[row][col].num[cnt] = true;
               changes++;
            }
         }
      }
   }
   return changes;
}

int colfillctrl(cell board[][N]){
   int changes = 0;
   for (int col = 0; col < N; col++){
      changes += colfill(board, col);
   }
   return changes;
}

int colfill(cell board[][N], int col){
   int changes = 0;
   int unitnum[N] = {0};
   bool unitexist[N] = {0};
   int blanknums = 0;
   for (int row = 0; row < N; row++){
      if (board[row][col].this == 0){
         blanknums++;
         for (int cnt = 0; cnt < N; cnt++){
            unitnum[cnt] += board[row][col].num[cnt];
         }
      }else{
         unitexist[board[row][col].this - 1] = true;
      }
   }
   
   for (int cnt = 0; cnt < N; cnt++){
      if (unitnum[cnt] == blanknums - 1 && unitexist[cnt] == false){
         for (int row = 0; row < N; row++){
            if (board[row][col].this == 0 && board[row][col].num[cnt] == false){
               board[row][col].this = cnt + 1;
               board[row][col].num[cnt] = true;
               changes++;
            }
         }
      }
   }
   return changes;
}

void unitselect(int rowmark, int colmark, int* left, int* right, int* up, int* down){
   if (rowmark == 0){
      *up = 2;
      *down = 0;
   }else if (rowmark == 1){
      *up = 5;
      *down = 3;
   }else{
      *up = 8;
      *down = 6;
   }
   
   if (colmark == 0){
      *left = 0;
      *right = 2;
   }else if (colmark == 1){
      *left = 3;
      *right = 5;
   }else{
      *left = 6;
      *right = 8;
   }
}

int unitfillctrl(cell board[][N]){
   int changes = 0;
   for (int j = 0; j < 2; j++){
      for (int i = 0; i < 2; i++){
         changes += unitfill(board, j, i);
      }
   }
   return changes;
}

int unitfill(cell board[][N], int row, int col){
   int changes = 0;
   int left, right, up, down;
   unitselect(row, col, &left, &right, &up, &down);
   int unitnum[N] = {0};
   bool unitexist[N] = {0};
   int blanknums = 0;
   for (int j = left; j <= right; j++){
      for (int i = down; i <= up; i++){
         if (board[j][i].this == 0){
            blanknums++;
            for (int cnt = 0; cnt < N; cnt++){
               unitnum[cnt] += board[j][i].num[cnt];
            }
         }else{
            unitexist[board[j][i].this - 1] = true;
         }
      }
   }
   for (int cnt = 0; cnt < N; cnt++){
      if (unitnum[cnt] == blanknums - 1 && unitexist[cnt] == false){
         for (int j = left; j <= right; j++){
            for (int i = down; i <= up; i++){
               if (board[j][i].this == 0 && board[j][i].num[cnt] == false){
                  board[j][i].this = cnt + 1;
                  board[j][i].num[cnt] = true;
                  changes++;
               }
            }
         }   
      }
   }
   return changes;
}

int sumofbool(cell board[][N], int j, int i){
   int sum = 0;
   for (int boolcnt = 0; boolcnt < N; boolcnt++){
      sum += board[j][i].num[boolcnt];
   }
   return sum;
}

int areafill(cell board[][N]){
   int changes = 0;
   areascan(board);
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         if (sumofbool(board, j, i) == 8 && board[j][i].this != 0){
//            printf("cell [%d] [%d] got 8 of sumofbool\n", j , i);
            int fillnumber;
            for (int boolcnt = 0; boolcnt < N; boolcnt++){
               if (board[j][i].num[boolcnt] == false && board[j][i].this == 0){
                  changes++;
                  fillnumber = boolcnt + 1;
                  board[j][i].this = fillnumber;
                  board[j][i].num[boolcnt] = true;
               }
            }  
         }
      }
   }
   return changes;
}


//board[j][i] will scan [j][0] [j][1] --- [j][8]
void rowscan(cell board[][N], int j, int i){
   for (int row = 0; row < N; row++){
      if (board[j][row].this != 0){
         board[j][i].num[board[j][row].this - 1] = true;
      }
   }
}
void colscan(cell board[][N], int j, int i){
   for (int col = 0; col < N; col++){
      if (board[col][i].this != 0){
         board[j][i].num[board[col][i].this - 1] = true;
      }
   }
}



void unitscan(cell board[][N], int j, int i){
   int left, right, up, down;
   unitboundaryset(j, i ,&left, &right, &up, &down);
   
   for (int row = left; row <= right; row++){
      for (int col = down; col <= up; col++){
         if (board[row][col].this != 0){
            board[j][i].num[board[row][col].this - 1] = true;
         }
      }
   }
}

void areascan(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         if (board[j][i].this != 0){
            continue;
         }else{
            rowscan(board, j, i);
            colscan(board, j, i);
            unitscan(board, j, i);
         }
      }
   }
}


void setallzero(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
//         if (board[j][i].this == 0){
            for (int cnt = 0; cnt < N; cnt++){
               board[j][i].num[cnt] = false;
            }
//         }else{
//            for (int cnt = 0; cnt < N; cnt++){
//               board[j][i].num[cnt] = true;
//            }
//         }
      }
   }
}

void boardprint(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         printf("%d ", board[j][i].this);
      }
      printf("\n");
   }
   printf("\n--------------------\n");
}

void unitboundaryset(int j, int i, int* left, int* right, int* up, int* down){
   if (j <= 2){
      *left = 0;
      *right = 2;
   }else if (j <= 5){
      *left = 3;
      *right = 5;
   }else{
      *left = 6;
      *right = 8;
   }
   
   if (i <= 2){
      *down = 0;
      *up = 2;
   }else if (i <= 5){
      *down = 3;
      *up = 5;
   }else{
      *down = 6;
      *up = 8;
   }
}

void cellstatusprint(cell board[][N]){
   for (int j = 0; j < N; j++){
      for (int i = 0; i < N; i++){
         printf("row: %d, col: %d |", j, i);
         boolnumprint(board[j][i]);
         printf("|,sumofbool: %d\n", sumofbool(board, j, i));
      }
   }
}

void boolnumprint(cell onecell){
   for (int i = 0; i < N; i++){
      printf("%d ", onecell.num[i]);
   }
}
