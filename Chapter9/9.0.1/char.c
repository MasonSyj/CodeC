#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INITSIZE 32

typedef struct str{
   char s[50];
}str;

typedef struct arr{
   str* data;
   int index;
}arr;

arr* arr_init(void);
void arr_set(arr* l, int nth, str element);
str* arr_get(arr* l, int nth);
void arr_free(arr** pointerofarr);

int main(void){

   str str1 = {"bristol"};
   str str2 = {"london"};
   str str3 = {"shanghai"};
   str str4 = {"japan"};

   arr* a1 = arr_init();
   arr_set(a1, 0, str1);
   arr_set(a1, 1, str2);
   arr_set(a1, 2, str3);
   puts(arr_get(a1, 0)->s);
   puts(arr_get(a1, 1)->s);
   puts(arr_get(a1, 2)->s);
   // printf("%d\n", arr_get(a1, 32));
   arr_set(a1, 32, str4);
   puts(arr_get(a1, 32)->s);
}


arr* arr_init(void){
   arr* a = (arr*)malloc(sizeof(arr));
   if (!a){
      fprintf(stderr, "arr malloc failed.");
      exit(EXIT_FAILURE);
   }

   a->data = (str*)calloc(INITSIZE, sizeof(str));
   if (!a->data){
      fprintf(stderr, "a->data calloc failed.");
      exit(EXIT_FAILURE);
   }

   a->index = INITSIZE;
   return a;
}

void arr_set(arr* l, int nth, str element){
   if (nth < 0){
      fprintf(stderr, "cannvoidot set element to a position indexed negative");
      exit(EXIT_FAILURE);
   }
   if (nth >= l->index){
      l->data = (str*)realloc(l->data, (nth+1) * sizeof(str));
      if (!l->data){
         fprintf(stderr, "a->data realloc failed.");
         exit(EXIT_FAILURE);
      }
      l->index = nth+1;
   }
   l->data[nth] = element;
}

str* arr_get(arr* l, int nth){
   if (nth < 0 || nth >= l->index){
      fprintf(stderr, "index out of range");
      exit(EXIT_FAILURE);
   }
   return &l->data[nth];
}
void arr_free(arr** pointerofarr){
   arr* l = *pointerofarr;
   free(l->data);
   free(l);
   *pointerofarr = NULL;
}
