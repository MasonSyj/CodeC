#include "../coll.h"
#include "specific.h"

// Create an empty coll
coll* coll_init(void){
   coll* c = (coll*)ncalloc(1, sizeof(calloc));
   c->start = (element*)ncalloc(1, sizeof(element));
   return c;
}
// Add element onto top
void coll_add(coll* c, colltype d);
// Take element out
bool coll_remove(coll* c, colltype d);
// Does this exist ?
bool coll_isin(coll* c, colltype d);
// Return size of coll
int coll_size(coll* c);
// Clears all space used
bool coll_free(coll* c);
