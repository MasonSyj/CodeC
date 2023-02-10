#include <stdio.h>
#include <stdbool.h>

#define Y 20
#define X 20

int inkblot(int a[Y][X], int sx, int sy, int ex, int ey)
{
   a[sy][sx] = 3;
   int currentmove = a[sy][sx];
   bool newmove = 1;
   while (newmove == 1){
      newmove = 0;
      for (int j = 0; j < Y; j++){
         for (int i = 0; i < X; i++){
            if (j == ey && i == ex && a[j][i] != 1){
               return a[j][i] - 2; 
            }

            if (a[j][i] == currentmove){
               currentmove++;
               if (j + 1 < Y && a[j+1][i] == 1){
                  newmove = 1;
                  a[j+1][i] = currentmove;
               }

               if (i + 1 < X && a[j][i+1] == 1){
                  newmove = 1;
                  a[j][i+1] = currentmove;
               }

               if (j - 1 >= 0 && a[j-1][i] == 1){
                  newmove = 1;
                  a[j-1][i] = currentmove;
               }
               if (i - 1 >= 0 && a[j][i-1] == 1){
                  newmove = 1;
                  a[j][i-1] = currentmove;
               }
                        
            }
         }
      }    
   }
   return a[ey][ex] - 2;
}
