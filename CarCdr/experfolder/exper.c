#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STRSIZE 20

typedef union exper{
   int x;
   double y;
}exper;

int main(void){
/*
   exper test1; 
   test1.x = 3;
   printf("%d %f\n",  test1.x, test1.y);
   test1.y = 4.4;
   printf("%d %f\n",  test1.x, test1.y);
*/   
   int x = 436874;
   int y = 13;
   char s1[STRSIZE];
   char s2[STRSIZE];
   
   snprintf(s1, STRSIZE, "%d", x);
   snprintf(s2, STRSIZE, "%d", y);
   puts(s1);
   puts(s2);
   int z = 4;
   char value = z + '0';
   char s3[STRSIZE];
   strcpy(s3, value);
   puts(s3);
}
