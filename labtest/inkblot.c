#include <stdio.h>

#define STARTNUM 3
#define SPACE 1

#define Y 20
#define X 20

int inkblot(int a[Y][X], int sx, int sy, int ex, int ey){
   int currentmove = a[sy][sx] = STARTNUM;
   while (a[ey][ex] == SPACE){
      for (int j = 0; j < Y; j++){
         for (int i = 0; i < X; i++){
            if (a[j][i] == currentmove){
               currentmove++;
               if (j + 1 < Y && a[j+1][i] == SPACE){
                  a[j+1][i] = currentmove;
               }
               if (i + 1 < X && a[j][i+1] == SPACE){
                  a[j][i+1] = currentmove;
               }
               if (j - 1 >= 0 && a[j-1][i] == SPACE){
                  a[j-1][i] = currentmove;
               }
               if (i - 1 >= 0 && a[j][i-1] == SPACE){
                  a[j][i-1] = currentmove;
               }                   
            }
         }
      }    
   }
   return a[ey][ex] - STARTNUM + SPACE;
}
