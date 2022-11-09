#include "../coll.h"
#include "specific.h"

// Create an empty coll
coll* coll_init(void){
   coll* c = (coll*)ncalloc(1, sizeof(coll));
   c->start = NULL;
   c->size = 0;
   return c;
}
// Add element onto top
void coll_add(coll* c, colltype d){
   if(!c){
      return;
   }
   
   dataframe* new = (dataframe*)ncalloc(1, sizeof(dataframe));
   new->i = d;
   new->next = NULL;
   
   if (!c->start){
      c->start = new;
		c->size++;
      return;
   }else{
      new->next = c->start;
      c->start = new;
		c->size++;
      return;
   }
}
// Take element out
bool coll_remove(coll* c, colltype d){
   dataframe *f1, *f2;
   if(!c){
      return false;
   }
   
   if (c->start->i == d){
      f1 = c->start;
      c->start = c->start->next;
      free(f1);
      c->size--;
      return true;
   }
   
	f2 = c->start;
   for (int i = 0; i < coll_size(c); i++){
      if (f2->i == d){
         f1->next = f2->next;
         free(f2);
         c->size--;
         return true;
      }
      f1 = f2;
      f2 = f2->next;
   }
   
   return false;
}
// Does this exist ?
bool coll_isin(coll* c, colltype d){
   if (!c){
      return false;
   }
   
	dataframe* f = c->start;
   for (int i = 0; i < coll_size(c); i++){
      if (f->i == d){
			return true;
		}
		f = f->next;
   }
   return false;
}
// Return size of coll
int coll_size(coll* c){
	if (!c){
		return 0;
	}
   return c->size;
}
// Clears all space used
bool coll_free(coll* c){
	if(!c){
		return true;
	}
	
	dataframe *previous, *current = c->start;
	for (int i = 0; i < coll_size(c); i++){
		previous = current;
		current = current->next;
		free(previous);
	}
	free(c);
	return true;
}
