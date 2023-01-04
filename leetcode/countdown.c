#include <stdio.h>
#include <assert.h>


// maybe more advanced mode
void test(){
   const char* table[] = {"abc", "def", "pqrs"};
   int arrsize[ROW];
   int arrcnt[ROW] = {0};
   int total = 1;
   for (int i = 0; i < ROW; i++){
      arrsize[i] = strlen(table[i]);
      total *= arrsize[i];
      printf("arrsize[%d], %d\n", i, arrsize[i]);
   }
   printf("total: %d\n", total);
   int i = 0;
   while (i < total){
      for (int index = ROW - 1; index >= 0; index--){
         if (arrcnt[index] == arrsize[index]){
            arrcnt[index] = 0;
            arrcnt[index - 1]++;
         }else{
            break;
         }
      }
      printf("%d: %d %d %d. %c%c%c\n", i, arrcnt[0], arrcnt[1], arrcnt[2], table[0][arrcnt[0]], table[1][arrcnt[1]], table[2][arrcnt[2]]);

      arrcnt[ROW - 1]++;
      
      i++;
   }
}

int main(void) {
   int x = 0; // 4
   int y = 0; // 9
   int z = 0; // 5
   // 4 * 9 * 5 == 180
   int i = 0;
   while (i++ < 180){
      printf("%d %d %d\n", x, y, z);
      z++;
      if (z == 5){
         z = 0;
         y++;
      }
      if (y == 9){
         y = 0;
         x++;
      }
   }
}
