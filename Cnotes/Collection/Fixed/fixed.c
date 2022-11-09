#include "../coll.h"
#include "specific.h"

// Create an empty coll
coll* coll_init(void){
  coll* c = (coll*)ncalloc(1, sizeof(coll));
  c->size = 0;
  return c;
}
// Add element onto top
void coll_add(coll* c, colltype d){
  if (!c || coll_size(c) >= FIXEDSIZE){
//  printf("unable to add new element.\n");
    return;
  }
  c->a[c->size++] = d;
  return;
}
// Take element out
bool coll_remove(coll* c, colltype d){
  for (int i = 0; i < coll_size(c); i++){
    if (c->a[i] == d){
      for (int j = i; j < coll_size(c); j++){
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
  if(c == NULL){
    return 0;
  }
  return c->size;
}
// Clears all space used
bool coll_free(coll* c){
   free(c);
   return true;
}
