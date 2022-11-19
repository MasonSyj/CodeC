#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 20
#define BALLCHAR '0'

typedef enum dir{topright, topleft, downleft, downright} dir;

typedef struct ball{
   char board[HEIGHT][WIDTH];
   int y;
   int x;
   dir direction;
}ball;

void boardset(char board[HEIGHT][WIDTH]);
void boardshow(char board[HEIGHT][WIDTH]);
void ballset(int y, int x, char board[HEIGHT][WIDTH]);
void onemove(ball* b);
void movectrl(ball* b);
bool reachrowboundary(ball* b);
bool reachcolboundary(ball* b);
void rowdirectionchange(dir* direction);
void coldirectionchange(dir* direction);

int main(void) {
   srand((unsigned)time(NULL));
   ball b1;
   boardset(b1.board);
   do{
      b1.y = rand() % HEIGHT;
      b1.x = rand() % WIDTH;
   }while(b1.y == 0 && b1.y == HEIGHT - 1 && b1.x == 0 && b1.x == WIDTH - 1);
   
   b1.direction = topright;
   ballset(b1.y, b1.x, b1.board);
   int i = 0;
   while (i < 80){
      movectrl(&b1);
      boardshow(b1.board);
//    boardset(b1.board);
      ballset(b1.y, b1.x, b1.board);
      i++;
   }
}

void boardset(char board[HEIGHT][WIDTH]){
   for (int j = 0; j < HEIGHT; j++){
      for (int i = 0; i < WIDTH; i++){
         board[j][i] = ' ';
         if (j == 0 || j == HEIGHT - 1 || i == 0 || i == WIDTH - 1){
            board[j][i] = '#';
         }
      }
   }
}

void boardshow(char board[HEIGHT][WIDTH]){
   for (int j = 0; j < HEIGHT; j++){
      for (int i = 0; i < WIDTH; i++){
         printf("%-2c", board[j][i]);
      }
      printf("\n");
   }
}

void ballset(int y, int x, char board[HEIGHT][WIDTH]){
   board[y][x] = BALLCHAR;
}

void onemove(ball* b){
   switch(b->direction){
      case topright: b->y--; b->x++; break;
      case topleft: b->y--; b->x--; break;
      case downleft: b->y++; b->x--; break;
      case downright: b->y++; b->x++; break;
   }
}

void movectrl(ball* b){
   if (reachrowboundary(b)){
      rowdirectionchange(&b->direction);
   }else if (reachcolboundary(b)){
      coldirectionchange(&b->direction);
   }
   onemove(b);
}

bool reachrowboundary(ball* b){
   return b->y == 1 || b->y == HEIGHT - 2;
}

bool reachcolboundary(ball* b){
   return b->x == 1 || b->x == WIDTH - 2;
}

void rowdirectionchange(dir* direction){
   if (*direction == topleft){
      *direction = downleft;
   }else if (*direction == topright){
      *direction = downright;
   }else if (*direction == downleft){
      *direction = topleft;
   }else if (*direction == downright){
      *direction = topright;
   }
}

void coldirectionchange(dir* direction){
   if (*direction == topleft){
      *direction = topright;
   }else if (*direction == topright){
      *direction = topleft;
   }else if (*direction == downleft){
      *direction = downright;
   }else if (*direction == downright){
      *direction = downleft;
   }
}
