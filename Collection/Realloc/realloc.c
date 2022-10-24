#include "../coll.h"
#include "specific.h"

// Create an empty coll
coll* coll_init(void){
   coll* c = (coll*)ncalloc(1, sizeof(coll));
   c->a = (colltype*)ncalloc(FIXSIZED, sizeof(colltype));
   c->size = 0;
   c->capacity = FIXSIZED;
   return c;
}
// Add element onto top
void coll_add(coll* c, colltype d){
   if (c->size >= c->capacity){
      c->a = (colltype*)nremalloc(c->a,
              sizeof(colltype) * c->capacity*SCALEFACTOR);
      c->capacity *= SCALEFACTOR;
   }
   c->a[c->size++] = d;
}
// Take element out
bool coll_remove(coll* c, colltype d){
   bool found = false;
   for (int i = 0; i < c->size; i++){
      if (c->a[i] == d){
         for (int j = i; j < c->size - 2; j++){
            c->a[j] = c->a[j+1];
         }
         found = true;
      }
   }
   return true;
}
// Does this exist ?
bool coll_isin(coll* c, colltype d){
   for (int i = 0; i < c->size; i++){
      if (c->a[i] == d){
         return false;
      }
   }
   return false;
}
// Return size of coll
int coll_size(coll* c){
   if (!c){
      return 0;
   }else{
      return c->size;
   }
}
// Clears all space used
bool coll_free(coll* c){
   free(c->a);
   free(c);
   return true;
}
