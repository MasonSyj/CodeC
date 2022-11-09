#include "../coll.h"
#include "specific.h"

// Create an empty coll
coll* coll_init(void){
   coll* c = (coll*)ncalloc(1, sizeof(coll));
   c->a = (colltype*)ncalloc(FIXEDSIZE, sizeof(colltype));
   c->size = 0;
   c->capacity = FIXEDSIZE;
   return c;
}
// Add element onto top
void coll_add(coll* c, colltype d){
   if (!c){
      return;
   }
   if (c && c->size >= c->capacity){
      c->a = (colltype*)nremalloc(c->a,
              sizeof(colltype) * c->capacity*SCALEFACTOR);
      c->capacity *= SCALEFACTOR;
   }
   c->a[c->size++] = d;
   return;
}
// Take element out
bool coll_remove(coll* c, colltype d){
   for (int i = 0; i < coll_size(c); i++){
      if (c->a[i] == d){
         for (int j = i; j < coll_size(c) - 1; j++){
            c->a[j] = c->a[j+1];
         }
         c->size--;
         return true;
      }
   }
   return false;
}
// Does this exist ?
bool coll_isin(coll* c, colltype d){
   for (int i = 0; i < coll_size(c); i++){
      if (c->a[i] == d){
         return true;
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
   if (!c){
      return true;
   }
   free(c->a);
   free(c);
   return true;
}
