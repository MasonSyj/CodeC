#include "../coll.h"
#include "specific.h"

// Create an empty coll
coll* coll_init(void){
  coll* c = (coll*)ncalloc(1, sizeof(call));
  c->size = 0;
  return c;
}
// Add element onto top
void coll_add(coll* c, colltype d){
  if (c->size >= FIXEDSIZE){
    fprintf(stderr, "unable to add new element.\n");
    exit(EXIT_FAILURE);
  }
  c->a[size++] = d;
  return;
}
// Take element out
bool coll_remove(coll* c, colltype d){
  for (int i = 0; i < c->size; i++){
    if (c->a[i] == d){
      for (int j = i; j < c->size - 2; j++){
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
   for (int i = 0; i < c->size; i++){
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
