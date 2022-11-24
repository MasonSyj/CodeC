#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define N 1000
#define SCALEFACTOR 2

typedef int datatype;

typedef struct set{
   datatype* data;
   int end;
   int capacity;
}set;

/* Create empty set */
set* set_init(void){
   set* s = (set*)calloc(1, sizeof(set));
   assert(s);
   s->data = (datatype*)calloc(N, sizeof(datatype));
   assert(s->data);
   s->capacity = N;
   return s;
}
/* Create new set, copied from another */
set* set_copy(set* s){
   set* new = (set*)calloc(1, sizeof(set));
   assert(new);
   new->data = (datatype*)calloc(N, sizeof(datatype));
   assert(new->data);
   memcpy(new->data, s->data, sizeof(datatype) * s->capacity);
   new->capacity = s->capacity;
   new->end = s->end; 
   return new;
}

/* Returns true if l is in the array, false elsewise */
int set_contains(set* s, int l){
   if(!s){
      return 0;
   }
   for(int i = 0; i < s->end; i++){
      if(s->data[i] == l){
          return 1;
      }
   }
   return 0;
}

/* Basic Operations */
/* Add one element into the set */
void set_insert(set* s, int l){
   if(!s){
      return;
   }
   
   if (set_contains(s, l) == 1){
      return;
   }
   if (s->end < s->capacity){
      s->data[s->end++] = l;
      return;
   }else{
      s->data = (datatype*)realloc(s->data, sizeof(datatype) * s->capacity * SCALEFACTOR);
      s->capacity *= SCALEFACTOR;
      s->data[s->end++] = l;
      return;
   }
}

/* Create new set, copied from an array of length n*/
set* set_fromarray(int* a, int n){
   set* s = (set*)calloc(1, sizeof(set));
   assert(s);
   int capacity = N;
   
   while (capacity < n){
      capacity = capacity << 1;
   }
   s->capacity = capacity;
   s->data = (datatype*)calloc(capacity, sizeof(datatype));
   assert(s->data);
   for (int i = 0; i < n; i++){
      set_insert(s,a[i]);
   }
   
   
   return s;
}


/* Return size of the set */
int set_size(set* s){
   if(!s){
      return 0;
   }
   return s->end;
}

/* Remove l from the set (if it's in) */
void set_remove(set* s, int l){
   if(!s){
      return;
   }

   if (!set_contains(s, l)){
      return;
   }
   
   for(int i = 0; i < s->end; i++){
      if(s->data[i] == l){
         for(int j = i; j < s->end - 1; j++){
            s->data[j] = s->data[j+1];
         }
         s->end--;
         return;
      }
   }
}
/* Remove one element from the set - there's no
   particular order for the elements, so any will do */
int set_removeone(set* s){
   int value = s->data[--s->end];
   s->data[s->end]= 0;
   return value;
}

/* Operations on 2 sets */
/* Create a new set, containing all elements from s1 & s2 */
set* set_union(set* s1, set* s2){
   set* s = (set*)calloc(1, sizeof(set));
   assert(s);
   
   int capacity = N;
   if (s1 && s2){
      while (s1->end + s2->end > capacity){
         capacity *= SCALEFACTOR;
      }
   }else{
      if(s1){
         capacity = s1->capacity;
      }else if (s2){
         capacity = s2->capacity;
      }else{
         capacity = 0;
      }
   }
   s->data = (datatype*)calloc(capacity, sizeof(datatype));
   s->capacity = capacity;
   
   if(s1){
      for (int i = 0; i < s1->end; i++){
         set_insert(s,s1->data[i]);
      }
   }

   if(s2){
      for (int i = 0; i < s2->end; i++){
         set_insert(s,s2->data[i]);
      }
   }
   return s;
}
/* Create a new set, containing all elements in both s1 & s2 */
set* set_intersection(set* s1, set* s2){
   int capacity;
   if(!s1 || !s2){
      capacity = 0;
   }else{
      capacity = s1->end>s2->end?s2->end:s1->end;
   }

   
   set* s = (set*)calloc(1, sizeof(set));
   assert(s);
   s->data = (datatype*)calloc(capacity, sizeof(datatype));
   s->capacity = capacity;
   int cnt = 0;
   
   if(s1){
      for (int i = 0; i < s1->end; i++){
         if (set_contains(s2, s1->data[i])){
            set_insert(s, s1->data[i]);
            cnt++;
         }
      }
   }
   s->end = cnt;
   return s;
}

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void set_free(set** s){
   if(!s){
      return;
   }
   
   free((*s)->data);
   free(*s);
   *s = NULL;
}
