#include <stdio.h>
#include <stdlib.h>

int main(void){
   int x = 3;
   int* px = &x;
   int* a = (int*)calloc(10, sizeof(int));
   printf("%d %d\n", x, *px);
   for (int i = 0; i < 10; i++){
      printf("%d ", a[i]);
   }
   printf("\n");
   for (int i = 0; i < 10; i++){
      printf("%d ", px[i]);
   }
}
