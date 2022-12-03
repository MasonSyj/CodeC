#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

typedef int atomtype;

#define atom(X)       lisp_atom(X)
#define cons(X, Y)    lisp_cons(X, Y)
#define car(L)        lisp_car(L)
#define cdr(L)        lisp_cdr(L)
#define copy(L)       lisp_copy(L)
// #define fromstring(L) lisp_fromstring(L)
// It's more Lisp-like to call it NIL, not NULL
#define NIL NULL

#define LISTSTRLEN 1000

struct lisp{
   atomtype value;
   struct lisp* car;
   struct lisp* cdr;
   bool holdvalue;
};

typedef struct lisp lisp;



// Returns element 'a' - this is not a list, and
// by itelf would be printed as e.g. "3", and not "(3)"
lisp* lisp_atom(const atomtype a){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   assert(this);
   this->value = a;
   this->holdvalue = true;
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

int main(void){
   char str[LISTSTRLEN];
   printf("Test Lisp Start ... \n");

   lisp_tostring(NIL, str);
   assert(lisp_length(NIL)==0);
   assert(strcmp(str, "()")==0);

   lisp* l1 = cons(atom(2), NIL);
   assert(l1);
   assert(lisp_length(l1)==1);
   lisp_tostring(l1, str);
   puts(str);
   assert(strcmp(str, "(2)")==0);
   assert(lisp_getval(car(l1))==2);

   lisp* l2 = cons(atom(1), l1);
   assert(lisp_length(l2)==2);
   lisp_tostring(l1, str);
   lisp_tostring(l2, str);

   assert(strcmp(str, "(1 2)")==0);

   lisp* l3 = cons(atom(3), cons(atom(4), cons(atom(5), NIL)));
   assert(l3);
   assert(lisp_length(l3)==3);
   lisp_tostring(l3, str);
   puts(str);
   assert(strcmp(str, "(3 4 5)")==0);

   lisp* l4 = cons(l2, l3);
   assert(l4);
   assert(lisp_length(l4)==4);
   lisp_tostring(l4, str);
   puts(str);
   assert(strcmp(str, "((1 2) 3 4 5)")==0);

   lisp* l5 = cons(atom(0), l4);
   assert(l5);
   assert(lisp_length(l5)==5);
   lisp_tostring(l5, str);
   puts(str);
   assert(strcmp(str, "(0 (1 2) 3 4 5)")==0);


}

/* ------------- Tougher Ones : Extensions ---------------*/

// Builds a new list based on the string 'str'
lisp* lisp_fromstring(const char* str){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   while (*str != '\0'){
      if (isdigit(*str)){
         this = lisp_cons(atom(*str - '0'), NIL);
      }else if (*str == '('){
         
      }
      str++;
   }
   return this;
}


// Returns a new list from a set of existing lists.
// A variable number 'n' lists are used.
// Data in existing lists are reused, and not copied.
// You need to understand 'varargs' for this.
/*
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
