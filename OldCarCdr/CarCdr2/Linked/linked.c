#include "../lisp.h"
#include "specific.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define BASETEN 10
#define NIL NULL
#define LISTSTRLEN 1000

void test(){
   char str[LISTSTRLEN];
   // test the indexrightbracket function
   char* brackkettest = "(((0) 1 (2 3)) 4 5 6)";
   assert(indexrightbracket(0, brackkettest) == 20);
   assert(indexrightbracket(1, brackkettest) == 13);
   assert(indexrightbracket(2, brackkettest) == 4);
   assert(indexrightbracket(8, brackkettest) == 12);

   // test the stuff inside the bracket stands for a sublisp
   assert(!sublisp(brackkettest, 0));
   assert(sublisp(brackkettest, 1));
   assert(sublisp(brackkettest, 2));
   assert(sublisp(brackkettest, 8));

   // strsublisp test
   strcpy(str, "(1 2 (7 8) (3 4 (5 6)))");
   char* str1 = strsublisp(str + 5);
   assert(strcmp(str1, "(7 8)") == 0);

   char* str2 = strsublisp(str + 11);
   assert(strcmp(str2, "(3 4 (5 6))") == 0);

   char* str3 = strsublisp(str + 16);
   assert(strcmp(str3, "(5 6)") == 0);
   free(str1);
   free(str2);
   free(str3);


   char* s1, *s2, *s3, *s4, *i1, *i2, *i3, *i4;
   s1 = strsublisp("(4 5)");
   s2 = strsublisp("(1 (2 3))");
   s3 = strsublisp("(1 (2 (4 5) 3))");
   s4 = strsublisp("(1 (2 (3 (4))))");
   assert(strcmp(s1, "(4 5)") == 0);
   assert(strcmp(s2, "(1 (2 3))") == 0);
   assert(strcmp(s3, "(1 (2 (4 5) 3))") == 0);
   assert(strcmp(s4, "(1 (2 (3 (4))))") == 0);


   // int2string test
   i1 = int2string(1567);
   i2 = int2string(233);
   i3 = int2string(0);
   i4 = int2string(-9);
   assert(strcmp(i1, "1567") == 0);
   assert(strcmp(i2, "233") == 0);
   assert(strcmp(i3, "0") == 0);
   assert(strcmp(i4, "-9") == 0);

   free(s1); free(s2); free(s3); free(s4); free(i1); free(i2); free(i3); free(i4);

   // pend test, test atoms and sublisp
   char inp[7][LISTSTRLEN] = {"((1 (2 (3 (4)))))", "5", "((0 1 2) 3 2 1)", "(4 (3) 5)", "(1 2 -3 4 5)", "((1 (2 3)))", "(5)"};
   lisp* main = NIL;
   lisp* sub0 = lisp_fromstring(inp[0]);
   lisp* sub1 = lisp_fromstring(inp[1]);
   lisp* sub2 = lisp_fromstring(inp[2]);
   lisp* sub3 = lisp_fromstring(inp[3]);
   lisp* sub4 = lisp_fromstring(inp[4]);
   lisp* sub5 = lisp_fromstring(inp[5]);
   lisp* sub6 = lisp_fromstring(inp[6]);
   pend(&main, sub0);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))))") == 0);
   pend(&main, sub1);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))) 5)") == 0);
   pend(&main, sub2);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))) 5 ((0 1 2) 3 2 1))") == 0);
   pend(&main, sub3);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))) 5 ((0 1 2) 3 2 1) (4 (3) 5))") == 0);
   pend(&main, sub4);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))) 5 ((0 1 2) 3 2 1) (4 (3) 5) (1 2 -3 4 5))") == 0);
   pend(&main, sub5);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))) 5 ((0 1 2) 3 2 1) (4 (3) 5) (1 2 -3 4 5) ((1 (2 3))))") == 0);
   pend(&main, sub6);
   lisp_tostring(main, str);
   assert(strcmp(str, "(((1 (2 (3 (4))))) 5 ((0 1 2) 3 2 1) (4 (3) 5) (1 2 -3 4 5) ((1 (2 3))) (5))") == 0);

   lisp_free(&main);

   //firstnumstr test
   assert(firstnumstr("26 95 315") == 26);
   assert(firstnumstr("0 95 315") == 0);
   assert(firstnumstr("-2 66 315") == -2);
   assert(firstnumstr("658 497 666") == 658);
   assert(firstnumstr("-9999 -751 751") == -9999);
   assert(firstnumstr("(((-9999)) -751 751)") == -9999);

   //numdigits test
   assert(numdigits(10) == 2);
   assert(numdigits(3) == 1);
   assert(numdigits(0) == 1);
   assert(numdigits(-1) == 2);
   assert(numdigits(-12) == 3);
   assert(numdigits(560) == 3);
   assert(numdigits(9999) == 4);
}


// the str[index] is '(', return false if '(' is at the start and '(' at the end
// needs to separate between the main lisp and sublisp
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
         stack[i++] = str[index]; // when is '(', push into the array(like stack)
      }
      if (str[index] == ')'){
         assert(stack[--i] == '('); // when is ')', pop
      }
      if (i == 0){ //when no element, the correct rightbracket is found
         return index;
      }
      index++;
   }
   return -1;
}

void pend(lisp** l, lisp* sub){
   if (*l == NIL){
      *l = lisp_cons(sub, NIL); // if doesn't exist, build a new one to hold sub
   }else{
      lisp* temp = *l;
      while (lisp_cdr(temp)){
         temp = lisp_cdr(temp); // locate the end to pend the sub
      }
      temp->cdr = lisp_cons(sub, NIL);
   }
}

char* strsublisp(const char* str){
   assert(str[0] == '(');
   int left = 0;
   int right = indexrightbracket(left, str);
   assert(right != -1);
   int len = right - left + 1; // e.g. (0) length is 3, in which case left = 0, right = 2;
   char* substr = (char*)calloc(len + 1, sizeof(char)); // one extra for '\0';
   strncpy(substr, str, right + 1); // cut down the str of the sublisp
   return substr;
}

char* int2string(int value){
   int digit = numdigits(value); 
   char* str = (char*)calloc(digit + 1, sizeof(char)); 
   int absvalue = abs(value);
   while (digit > 0){
      str[--digit] = absvalue % BASETEN + '0'; // add digit backward since mod got digits in reverse order
      absvalue /= BASETEN;
   }
   if (value < 0){
      str[0] = '-'; // negative number case
   }
   return str;
}

//return first num in a very string
int firstnumstr(const char* str){
   int value = 0;
   int flag = 1;
   int index = 0;
   while (str[index] != '\0'){
      if (str[index] == '-'){ // if '-', return the value * -1
         flag = -1;
      }
      if (isdigit(str[index])){ //find the first digit
         while (isdigit(str[index])){ // from the first digit to last digit, calculate the value
            value = value * BASETEN + (str[index] - '0');
            index++;
         }
         return flag * value;
      }
      index++;
   }
   return flag * value;
}

int numdigits(int num){
   if (num < 0){
      return numdigits(-num) + 1; // negative num has one more: '-'
   }
   int i = 0;
   int tens = 1;
   do{
      i++;
      tens *= BASETEN;
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
   if (!l){
      return NIL;
   }
   return l->car;
}

// Returns the cdr (all but the 1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_cdr(const lisp* l){
   if (!l){
      return NIL;
   }
   return l->cdr;
}

// Returns the data/value stored in the cons 'l'
atomtype lisp_getval(const lisp* l){
   assert(l);
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
   if (lisp_isatomic(l)){ // when lisp is atom
      char* x = int2string(lisp_getval(l));
      strcpy(str, x);
      free(x);
      return;
   }
   //this tempstr act as parameter str, prefer to calloc one which is cleaner, str from outside might contain data rendering it difficult to manipulate
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
         char* substr = (char*)calloc(LISTSTRLEN, sizeof(char)); // pass in a calloced new str 
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
   if (l == NULL || *l == NIL){
      return;
   }

   lisp* car = lisp_car(*l);
   lisp* cdr = lisp_cdr(*l);

   lisp_free(&car);
   lisp_free(&cdr);
   free(*l);
   *l = NIL;
   return;
}

/* ------------- Tougher Ones : Extensions ---------------*/

// Builds a new list based on the string 'str'
lisp* lisp_fromstring(const char* str){
   if (numdigits(firstnumstr(str)) == (int)strlen(str)){ //when only a single number
      return lisp_atom(firstnumstr(str));
   }
   
   lisp* this = NIL;
   int index = 0;
   while (index < (int)strlen(str)){
      if (isdigit(str[index]) || str[index] == '-'){
         int value = firstnumstr(str + index);
         pend(&this, lisp_atom(value));
         int digit = numdigits(value);
         index = index + digit - 1;
      }else if (str[index] == '(' && sublisp(str, index)){
         char* substr = strsublisp(str + index);
         lisp* sub = lisp_fromstring(substr);
         pend(&this, sub);
         int len = (int)strlen(substr);
         index = index + len - 1;
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
      pend(&this, new);
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
