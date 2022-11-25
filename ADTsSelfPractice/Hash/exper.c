#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
   int* a = (int*)calloc(10, sizeof(int));
   for (int i = 0; i < 10; i++){
      printf("%d ", a[i]);
   }
   printf("\n");
   printf("%p\n", (void*)a);
   a = (int*)realloc(a, 20 * sizeof(int));
   for (int i = 0; i < 20; i++){
      printf("%d ", a[i]);
   }
   printf("%p\n", (void*)a);

   char** b = (char**)malloc(10 * sizeof(char*));
   for (int i = 0; i < 10; i++){
      if (b[i]){
         printf("b %d exist\n", i);
      }
   }
	
   char** c = (char**)calloc(10, sizeof(char*));
   for (int i = 0; i < 10; i++){
      if (c[i]){
         printf("c %d exist\n", i);
      }
   }
}
