#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "arr.h"

int main(void)
{

   arr *a;
   printf("Basic Array Tests ... Start\n");
   /* Set up empty array */
   a = arr_init();
   assert(a != NULL);

   /* Some simple sets & gets */
   arr_set(a, 0, 1);
   assert(arr_get(a, 0) == 1);
   arr_set(a, 1, 2);
   assert(arr_get(a, 1) == 2);
   /* Force a resize/realloc (depending on initial size) */
   arr_set(a, 32, 17);
   assert(arr_get(a, 32) == 17);
   /* Huge (re)alloc */
   arr_set(a, 512000, 3);
   assert(arr_get(a, 512000) == 3);
   /* The 'unset' gaps in the array should return zero */
   assert(arr_get(a, 2) == 0);

   /* Free it all */
   arr_free(&a);
   assert(a==NULL);
   printf("Basic Array Tests ... Stop\n");

   arr* test = arr_init();
   assert(test);
   arr_set(test, 50, 20);
   arr_set(test, 99, 40);
   assert(arr_get(test, 50) == 20);
   assert(arr_get(test, 99) == 40);

   arr_set(test, 200, 80);
   assert(arr_get(test, 50) == 20);
   assert(arr_get(test, 99) == 40);
   assert(arr_get(test, 200) == 80);

   arr_free(&test);
   assert(test == NULL);
   return 0;
}
