#include <stdio.h>

typedef union exper{
   int x;
   double y;
}exper;

int main(void){
   exper test1; 
   test1.x = 3;
   printf("%d %f\n",  test1.x, test1.y);
   test1.y = 4.4;
   printf("%d %f\n",  test1.x, test1.y);
}
