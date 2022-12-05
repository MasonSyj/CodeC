#include "../lisp.h"
#include "specific.h"
#include <ctype.h>

#define NIL NULL

#define LISTSTRLEN 1000

void test(){

}

void add2list(lisp** l, lisp* sub){
//   lisp* this = *l;
   if (*l == NIL){
      *l = (lisp*)calloc(1, sizeof(lisp));
      (*l)->car = sub;
   }else{
      lisp* temp = *l;
      while (temp->cdr){
         temp = temp->cdr;
      }
      temp->cdr = (lisp*)calloc(1, sizeof(lisp));
      temp->cdr->car = sub;
   }
}

char* substr(const char* str){
   char* newsubstr = NULL;
   assert(*str == '(');
   char stack[LISTSTRLEN];
   int i = 0;
   stack[i++] = *str;
   int index = 1;
   while (str[index] != '\0'){
      if (str[index] == '('){
         stack[i++] = str[index];
      }
      if (str[index] == ')'){
         assert(stack[--i] == '(');
      }
      if (i == 0){
         newsubstr = (char*)calloc(index, sizeof(char));
         strncpy(newsubstr, str + 1, index - 1);
         return newsubstr;
      }
      index++;
   }
   return newsubstr;
}

char* inttostring(int value){
   int digit = digits(value);
   char* str = (char*)calloc(digit + 1, sizeof(char));
   int absvalue = abs(value);
   while (digit > 0){
      str[--digit] = absvalue % 10 + '0';
      absvalue /= 10;
   }
   if (value < 0){
      str[0] = '-';
   }
   return str;
}

//return first num in a very string
int firstnum(const char* str){
   int value = 0;
   int flag = 1;
   int index = 0;
   while (str[index] != '\0'){
      if (str[index] == '-'){
         flag = -1;
      }
      if (isdigit(str[index])){
         while (isdigit(str[index])){
            value = value * 10 + (str[index] - '0');
            index++;
         }
         return flag * value;
      }
      index++;
   }
   return flag * value;
}

int digits(int num){
   int tens = 1;
   if (num < 0){
      return digits(-num) + 1; 
   }
   int i = 0;
   do{
      i++;
      tens *= 10;
   }while (tens <= num);
   return i;
}

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

// Returns a boolean depending up whether l points to an atom (not a list)
bool lisp_isatomic(const lisp* l){
   if (!l){
      return false;
   }
   return l->value != 0;
}

// Returns a deep copy of the list 'l'
lisp* lisp_copy(const lisp* l){
   if (l == NIL){
      return NIL;
   }
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   memcpy(this, l, sizeof(lisp));
   this->cdr = lisp_copy(l->cdr);
   this->car = lisp_copy(l->car);
   return this;
}

// Returns number of components in the list.
int lisp_length(const lisp* l){
   if (!l || lisp_isatomic(l)){
      return 0;
   }

   int cnt = 0;
   while (l){
      l = l->cdr;
      cnt++;
   }
   return cnt;
}

// Returns stringified version of list
void lisp_tostring(const lisp* l, char* str){
   if (l && !l->car){
      char* x = inttostring(l->value);
      strcpy(str, x);
      free(x);
      return;
   }

   char* tempstr = (char*)calloc(LISTSTRLEN, sizeof(char));
   char* head = tempstr;
   *tempstr++ = '(';
   while(l){
      if (l->car && !l->car->car){
         char* strvalue = inttostring(l->car->value);
         strcat(tempstr, strvalue);
         free(strvalue);
         tempstr = tempstr + digits(l->car->value);
//         *tempstr++ = l->car->value + '0';
      }else if (l->car){
         char* substr = (char*)calloc(LISTSTRLEN, sizeof(char));
         lisp_tostring(l->car, substr);
         strcat(tempstr, substr);
         tempstr = tempstr + strlen(substr);
         free(substr);
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
   if (l == NULL || *l == NULL){
      return;
   }
	
   lisp* this = *l;

   lisp_free(&this->car);
   lisp_free(&this->cdr);
   free(*l);
   *l = NULL;
   return;
}

/* ------------- Tougher Ones : Extensions ---------------*/

// Builds a new list based on the string 'str'
lisp* lisp_fromstring(const char* str){
   lisp* this = NIL;
   int index = 0;
   while (str[index] != '\0'){
      if (isdigit(str[index]) || str[index] == '-'){
         int value = firstnum(str + index);
         add2list(&this, lisp_atom(value));
         int digit = digits(value);
         index = index + digit - 1;
      }else if (str[index] == '(' && index != 0){
         char* newsubstr = substr(str + index);
         lisp* sub = lisp_fromstring(newsubstr);
         add2list(&this, sub);
         int len = strlen(newsubstr);
         index = index + len + 1;
         free(newsubstr);
      }
      index++;
   }
   return this;
}

// Returns a new list from a set of existing lists.
// A variable number 'n' lists are used.
// Data in existing lists are reused, and not copied.
// You need to understand 'varargs' for this.
lisp* lisp_list(const int n, ...){
   lisp* this = NIL;
   if (n == 0){
      return this;	
   }
   va_list valist;
   va_start(valist, n);
   for (int i = 0; i < n; i++){
      lisp* new = va_arg(valist, lisp*);
      add2list(&this, new);
   }
   va_end(valist);
   return this;
}

// Allow a user defined function 'func' to be applied to
// each component of the list 'l'.
// The user-defined 'func' is passed a pointer to a cons,
// and will maintain an accumulator of the result.
void lisp_reduce(void (*func)(lisp* l, atomtype* n), lisp* l, atomtype* acc){
   while (l){
      if (lisp_isatomic(l->car)){
         (*func)(l->car, acc);
      }else if (l->car && !lisp_isatomic(l->car)){
         lisp_reduce(func, l->car, acc);
      }
      l = l->cdr;
   }
}
