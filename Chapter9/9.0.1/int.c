#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INITSIZE 32

typedef struct arr{
   int* data;
   int index;
}arr;

typedef struct testp{
   int data;
   struct testp* next;
}p;

arr* arr_init(void);
void arr_set(arr* l, int nth, int element);
int arr_get(arr* l, int nth);
void arr_free(arr** pointerofarr);
void smalltest(p* pp);

int main(void){
   p p3 = {3, NULL};
   p p2 = {2, &p3};
   p p1 = {1, &p2};
   printf("%d\n", p1.next->data);
   smalltest(&p1);
   printf("%d\n", p1.next->data);

   arr* a1 = arr_init();
   arr_set(a1, 0, 3);
   arr_set(a1, 1, 6);
   arr_set(a1, 2, 9);
   printf("%d\n", arr_get(a1, 0));
   printf("%d\n", arr_get(a1, 1));
   printf("%d\n", arr_get(a1, 2));
   printf("%d\n", arr_get(a1, 3));
   printf("%d\n", arr_get(a1, 31));
   // printf("%d\n", arr_get(a1, 32));
   arr_set(a1, 32, 32);
   printf("%d\n", arr_get(a1, 32));
}

void smalltest(p* pp){
   pp->next = pp->next->next;
}

arr* arr_init(void){
   arr* a = (arr*)malloc(sizeof(arr));
   if (!a){
      fprintf(stderr, "arr malloc failed.");
      exit(EXIT_FAILURE);
   }

   a->data = (int*)calloc(INITSIZE, sizeof(int));
   if (!a->data){
      fprintf(stderr, "a->data calloc failed.");
      exit(EXIT_FAILURE);
   }

   a->index = INITSIZE;
   return a;
}
void arr_set(arr* l, int nth, int element){
   if (nth < 0){
      fprintf(stderr, "cannvoidot set element to a position indexed negative");
      exit(EXIT_FAILURE);
   }
   if (nth >= l->index){
      l->data = (int*)realloc(l->data, (nth+1) * sizeof(int));
      if (!l->data){
         fprintf(stderr, "a->data realloc failed.");
         exit(EXIT_FAILURE);
      }
      l->index = nth+1;
   }
   l->data[nth] = element;
}

int arr_get(arr* l, int nth){
   if (nth < 0 || nth >= l->index){
      fprintf(stderr, "index out of range");
      exit(EXIT_FAILURE);
   }
   return l->data[nth];
}
void arr_free(arr** pointerofarr){
   arr* l = *pointerofarr;
   free(l->data);
   free(l);
   *pointerofarr = NULL;
}
