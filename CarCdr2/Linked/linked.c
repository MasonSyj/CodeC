#include "../lisp.h"
#include "specific.h"
#include <ctype.h>
#include <stdio.h>

#define NIL NULL

#define LISTSTRLEN 1000

void test(){
   char str[LISTSTRLEN];
   void add2list(lisp** l, lisp* sub);
   char* inp = "((1 (2 3)))";
   lisp* inplisp = lisp_fromstring(inp);
   lisp_tostring(inplisp, str);
   lisp_free(&inplisp);
   char* s1, s2, s3, s4, i1, i2, i3, i4;
   s1 = ()
   assert(strcmp(strsublisp("(4 5)"), "4 5") == 0);
   assert(strcmp(strsublisp("(1 (2 3))"), "1 (2 3)") == 0);
   assert(strcmp(strsublisp("(1 (2 (4 5) 3))"), "1 (2 (4 5) 3)") == 0);
   assert(strcmp(strsublisp("(1 (2 (3 (4))))"), "1 (2 (3 (4)))") == 0);
   assert(strcmp(int2string(1567), "1567") == 0);
   assert(strcmp(int2string(233), "233") == 0);
   assert(strcmp(int2string(0), "0") == 0);
   assert(strcmp(int2string(-9), "-9") == 0);
   assert(firstnumstr("26 95 315") == 26);
   assert(firstnumstr("0 95 315") == 0);
   assert(firstnumstr("-2 66 315") == -2);
   assert(firstnumstr("658 497 666") == 658);
   assert(firstnumstr("-9999 -751 751") == -9999);
   assert(numdigits(10) == 2);
   assert(numdigits(3) == 1);
   assert(numdigits(0) == 1);
   assert(numdigits(-1) == 2);
   assert(numdigits(-12) == 3);
   assert(numdigits(560) == 3);
   assert(numdigits(9999) == 4);
}

bool sublisp(const char* str, int index){
   return index != 0 || indexrightbracket(index, str) != (int)strlen(str) - 1;
}

int indexrightbracket(int leftbracket, const char* str){
   assert(str[leftbracket] == '(');
   char stack[LISTSTRLEN];
   int i = 0;
   stack[i++] = str[leftbracket];
   int index = leftbracket + 1;
   while (str[index] != '\0'){
      if (str[index] == '('){
         stack[i++] = str[index];
      }
      if (str[index] == ')'){
         assert(stack[--i] == '(');
      }
      if (i == 0){
         return index;
      }
      index++;
   }
   return -1;
}

void add2list(lisp** l, lisp* sub){
   if (*l == NIL){
      *l = (lisp*)calloc(1, sizeof(lisp));
        *l = lisp_cons(sub, NIL);
   }else{
      lisp* temp = *l;
      while (lisp_cdr(temp)){
         temp = lisp_cdr(temp);
      }
      temp->cdr = lisp_cons(sub, NIL);
   }
}

char* strsublisp(const char* str){
   int right = indexrightbracket(0, str);
   char* substr = (char*)calloc(right, sizeof(char));
   strncpy(substr, str + 1, right - 1);
   return substr;
}

char* int2string(int value){
   int digit = numdigits(value);
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
int firstnumstr(const char* str){
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

int numdigits(int num){
   int tens = 1;
   if (num < 0){
      return numdigits(-num) + 1;
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
   assert(!lisp_car(this));
   assert(!lisp_cdr(this));
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
   return !lisp_car(l) && !lisp_cdr(l);
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
      l = lisp_cdr(l);
      cnt++;
   }
   return cnt;
}

// Returns stringified version of list
void lisp_tostring(const lisp* l, char* str){
   if (lisp_isatomic(l)){
      char* x = int2string(lisp_getval(l));
      strcpy(str, x);
      free(x);
      return;
   }

   char* tempstr = (char*)calloc(LISTSTRLEN, sizeof(char));
   char* head = tempstr;
   *tempstr++ = '(';
   while(l){
      if (lisp_isatomic(lisp_car(l))){
         int value = lisp_getval(lisp_car(l));
         char* strvalue = int2string(value);
         strcat(tempstr, strvalue);
         free(strvalue);
         tempstr = tempstr + numdigits(value);
      }else if (lisp_car(l)){
         char* substr = (char*)calloc(LISTSTRLEN, sizeof(char));
         lisp_tostring(lisp_car(l), substr);
         strcat(tempstr, substr);
         tempstr = tempstr + strlen(substr);
         free(substr);
      }
      if (lisp_cdr(l)){
         *tempstr++ = ' ';
      }
      l = lisp_cdr(l);
   }
   strcat(tempstr, ")");
   strcpy(str, head);
   free(head);
}

// Clears up all space used
// Double pointer allows function to set 'l' to NULL on success
void lisp_free(lisp** l){
   if (l == NULL || *l == NULL){
      return;
   }

   lisp* car = lisp_car(*l);
   lisp* cdr = lisp_cdr(*l);

   lisp_free(&car);
   lisp_free(&cdr);
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
         int value = firstnumstr(str + index);
         add2list(&this, lisp_atom(value));
         int digit = numdigits(value);
         index = index + digit - 1;
      }else if (str[index] == '(' && sublisp(str, index)){
         char* substr = strsublisp(str + index);
         lisp* sub = lisp_fromstring(substr);
         add2list(&this, sub);
         int len = strlen(substr);
         index = index + len + 1;
         free(substr);
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
      if (lisp_isatomic(lisp_car(l))){
         (*func)(lisp_car(l), acc);
      }else if (lisp_car(l) && !lisp_isatomic(lisp_car(l))){
         lisp_reduce(func, lisp_car(l), acc);
      }
      l = lisp_cdr(l);
   }
}


