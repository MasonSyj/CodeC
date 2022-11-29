#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "varr.h"

int main(void)
{

   arr *a;
   printf("Basic Array Tests ... Start\n");
   /* Set up empty array */
   a = arr_init((int)sizeof(int));
   assert(a != NULL);

   /* Some simple sets & gets */
   int x,y,c,d;
   x = 1;
   y = 2;
   c = 17;
   d = 3;
   arr_set(a, 0, &x);
   assert(*(int*)arr_get(a, 0) == 1);
   arr_set(a, 1, &y);
   assert(*(int*)arr_get(a, 1) == 2);
   /* Force a resize/realloc (depending on initial size) */
   arr_set(a, 32, &c);
   assert(*(int*)arr_get(a, 32) == 17);
   /* Huge (re)alloc */
   arr_set(a, 512000, &d);
   assert(*(int*)arr_get(a, 512000) == 3);
   /* The 'unset' gaps in the array should return zero */
   assert(*(int*)arr_get(a, 2) == 0);

   /* Free it all */
   arr_free(&a);
   assert(a==NULL);

 
   arr *b;

   b = arr_init((int)sizeof(char));
   assert(b);

   char c1, c2, c3, c4;
   c1 = 'x';
   c2 = 'y';
   c3 = 'j';
   c4 = 'k';
   arr_set(b,0,&c1);
   arr_set(b,10,&c2);
   arr_set(b,100,&c3);
   arr_set(b,1000,&c4);

   assert(*(char*)arr_get(b, 0) == 'x');
   assert(*(char*)arr_get(b, 10) == 'y');
   assert(*(char*)arr_get(b, 100) == 'j');
   assert(*(char*)arr_get(b, 1000) == 'k');
   arr_free(&b);
   assert(b==NULL);

   printf("Basic Array Tests ... Stop\n");
   return 0;
}

