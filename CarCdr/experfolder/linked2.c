#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

typedef int atomtype;

#define atom(X)       lisp_atom(X)
#define cons(X, Y)    lisp_cons(X, Y)
#define car(L)        lisp_car(L)
#define cdr(L)        lisp_cdr(L)
#define copy(L)       lisp_copy(L)
#define fromstring(L) lisp_fromstring(L)
// It's more Lisp-like to call it NIL, not NULL
#define NIL NULL

#define LISTSTRLEN 1000

struct lisp{
   atomtype value;
   struct lisp* car;
   struct lisp* cdr;
};

typedef struct lisp lisp;

void add2list(lisp** l, lisp* sub);
char* inttostring(int value);
int firstnum(const char* str);
int digits(int num);
atomtype times(lisp* l);
atomtype lisp_reduce(atomtype(*func)(lisp* l), lisp* l);
atomtype atms(lisp* l);


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

void test(){
   char* str = "(1 2 (7 8) (3 4 (5 6)))";
   char* str1 = substr(str + 0);
   assert(strcmp(str1, "1 2 (7 8) (3 4 (5 6))") == 0);

   char* str2 = substr(str + 5);
   assert(strcmp(str2, "7 8") == 0);

   char* str3 = substr(str + 11);
   assert(strcmp(str3, "3 4 (5 6)") == 0);

   char* str4 = substr(str + 16);
   assert(strcmp(str4, "5 6") == 0);
   free(str1);
   free(str2);
   free(str3);
   free(str4);
}

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

int main(void){
   test();
   char str[LISTSTRLEN];
   lisp* testl = (lisp*)calloc(1, sizeof(lisp));
   assert(testl);
   assert(!testl->car);
   assert(!testl->cdr);
   printf("Test Lisp Start ... \n");

   lisp_tostring(NIL, str);
   assert(lisp_length(NIL)==0);
   assert(strcmp(str, "()")==0);

   lisp* l1 = cons(atom(2), NIL);
   assert(l1);
   assert(lisp_length(l1)==1);
   lisp_tostring(l1, str);
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
   assert(strcmp(str, "(3 4 5)")==0);

   lisp* l4 = cons(l2, l3);
   assert(l4);
   assert(lisp_length(l4)==4);
   lisp_tostring(l4, str);
   assert(strcmp(str, "((1 2) 3 4 5)")==0);

   lisp* l5 = cons(atom(0), l4);
   assert(l5);
   assert(lisp_length(l5)==5);
   lisp_tostring(l5, str);
   assert(strcmp(str, "(0 (1 2) 3 4 5)")==0);

   lisp_free(&l5);

//fromstring function test didn't consider negative yet
   char inp[6][LISTSTRLEN] = {"((1 -2) 4 5)", "(1 2 -3 4 5)", "()", "(1 (2 (3 (4 5))))", "(0 1 (-2 3) (4 (5 6)))", "((1 2) (3 4) (5 (-6 7)))"};
   for(int i=0; i<6; i++){
      lisp* f1 = fromstring(inp[i]);
      lisp_tostring(f1, str);
      assert(strcmp(str, inp[i])==0);
      lisp_free(&f1);
      assert(!f1);
   }

   /*--------------------*/
   /* lisp_list() tests  */
   /*--------------------*/

   lisp* g1 = lisp_list(3, atom(6), atom(7), atom(8));
   lisp_tostring(g1, str);
   assert(strcmp(str, "(6 7 8)")==0);
   lisp* g2 = lisp_list(5, g1, atom(-123456), copy(g1), atom(25),
                        fromstring("(1(2(3(4 5))))"));
   lisp_tostring(g2, str);
   assert(strcmp(str, "((6 7 8) -123456 (6 7 8) 25 (1 (2 (3 (4 5)))))")==0);
   // g2 reuses g1, so no need to lisp_free(g1)
   lisp_free(&g2);
   assert(!g2);

   /*----------------------*/
   /* lisp_reduce() tests  */
   /*----------------------*/

   lisp* h1 = lisp_fromstring("(1 2 3 4)");
   assert(lisp_reduce(times, h1)==24);
   lisp_free(&h1);
   h1 = lisp_fromstring("(10 20 (30 40 50))");
   assert(lisp_reduce(atms, h1)==5);
   lisp_free(&h1);
   assert(!h1);

   printf("End\n");
}

/* ------------- Tougher Ones : Extensions ---------------*/

// Allow a user defined function 'func' to be applied to
// each component of the list 'l'.
// The user-defined 'func' is passed a pointer to a cons,
// and will maintain an accumulator of the result.
atomtype lisp_reduce(atomtype(*func)(lisp* l), lisp* l){
   return (*func)(l);
}

atomtype times(lisp* l){
   if (!l){
      return 1;
   }
   
   if (l->value == 0){
      return 1 * times(l->car) * times(l->cdr);
   }else{
      return l->value * times(l->car) * times(l->cdr);
   }
}

atomtype atms(lisp* l){
   if (!l){
      return 0;
   }
   if (l->value != 0){
      return 1 + atms(l->cdr);
   }else{
      return 0 + atms(l->car) + atms(l->cdr);
   }
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
   if (num < 0){
      return digits(-num) + 1; 
   }
   int i = 0;
   do{
      i++;
   }while ((int)pow((double)10, (double)i) <= num);
   return i;
}

/*
         if (this == NIL){
            this = (lisp*)calloc(1, sizeof(lisp));
            this->car = sub;
         }else{
            lisp* temp = this;
            while (temp->cdr){
               temp = temp->cdr;
            }
            temp->cdr = (lisp*)calloc(1, sizeof(lisp));
            temp->cdr->car = sub;
         }
*/
