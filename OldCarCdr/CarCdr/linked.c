#include "specific.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

#define LISTSTRLEN 1000

struct lisp{
   atomtype value;
   struct lisp* car;
   struct lisp* cdr;
   bool holdvalue;
};

// Returns element 'a' - this is not a list, and
// by itelf would be printed as e.g. "3", and not "(3)"
lisp* lisp_atom(const atomtype a){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   assert(this);
   this->value = a;
   assert(!this->car);
   assert(!this->cdr);
   return this;
}

// Returns a list containing the car as 'l1'
// and the cdr as 'l2'- data in 'l1' and 'l2' are reused,
// and not copied. Either 'l1' and/or 'l2' can be NULL
lisp* lisp_cons(const lisp* l1,  const lisp* l2){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   assert(this);
   this->holdvalue = true;
   this->car = (lisp*)l1;
   this->cdr = (lisp*)l2;
   return this;   
}

// Returns the car (1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_car(const lisp* l){
   return l->car;
}

// Returns the cdr (all but the 1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_cdr(const lisp* l){
   return l->cdr;
}

// Returns the data/value stored in the cons 'l'
atomtype lisp_getval(const lisp* l){
   return l->value;
}

// Returns a deep copy of the list 'l'
lisp* lisp_copy(const lisp* l){
   lisp* this = lisp_atom(l->value);
   this->car = l->car;
   this->cdr = l->cdr;
   return this;
}

// Returns number of components in the list.
int lisp_length(const lisp* l){
   if (!l){
      return 0;
   }
   int cnt = 0;
   if (l->car){
      cnt++;
   }
   do{
      l = l->cdr;
      if (l){
         cnt++;
      }
   }while (l);
   return cnt;
}

// Returns stringified version of list
void lisp_tostring(const lisp* l, char* str){
   char* tempstr = (char*)calloc(LISTSTRLEN, sizeof(char));
   char* head = tempstr;
   *tempstr++ = '(';
   while(l){
      if (l->car->holdvalue == true){
         *tempstr++ = l->car->value + '0';
      }else{
         char* substr = (char*)calloc(LISTSTRLEN, sizeof(char));
         lisp_tostring(l->car, substr);
         strcat(tempstr, substr);
         tempstr = tempstr + strlen(substr);
      }
      if (l->cdr != NULL){
         *tempstr++ = ' ';
      }
      l = l->cdr;
   }
   *tempstr++ = ')';
   *tempstr++ = '\0';
   strcpy(str, head);
   free(head);
}

// Clears up all space used
// Double pointer allows function to set 'l' to NULL on success
void lisp_free(lisp** l){
   lisp* this = *l;
   if (this == NULL){
      return;
   }
   lisp_free(&this->car);
   lisp_free(&this->cdr);
   free(this);
   *l = NULL;
   return;
}


/* ------------- Tougher Ones : Extensions ---------------*/
/*
// Builds a new list based on the string 'str'
lisp* lisp_fromstring(const char* str){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   return this;
}

// Returns a new list from a set of existing lists.
// A variable number 'n' lists are used.
// Data in existing lists are reused, and not copied.
// You need to understand 'varargs' for this.
lisp* lisp_list(const int n, ...){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   return this;
}

// Allow a user defined function 'func' to be applied to
// each component of the list 'l'.
// The user-defined 'func' is passed a pointer to a cons,
// and will maintain an accumulator of the result.
atomtype lisp_reduce(atomtype(*func)(lisp* l), lisp* l){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   return this;
}
*/
