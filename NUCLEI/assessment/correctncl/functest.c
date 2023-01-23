#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "lisp.h"

#define NIL NULL
#define SIZE 997
#define THRESHOLD 0.7
#define SCALEFACTOR 3
#define STRSAME(A,B) (strcmp(A,B) == 0)
typedef enum libfunc{CAR, CDR, CONS, PLUS, LENGTH, GREATER, LESS, EQUAL, PRINT, SET, IF, WHILE, DEFUN} libfunc;

typedef struct recycleset{
   lisp** list;
   int usage;
   int size;
}recycleset;

typedef struct stack{
   int top;
   lisp** arr;
}lispstack;
///
void exe_recycle(void);
void lisp_recycle(lisp* newlisp);
void hashset_init(void);
void hashset_insert(lisp* singlelisp);
void hashset_free(void);
void rehash(void);
///
int hash1(lisp* newlisp, int sz);
int hash2(lisp* newlisp, int sz); 
int doublehash(lisp* newlisp, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
bool isprime(int n);
///////
void islist();
lisp* list2lisp(char* list);
///////
bool islistfunc(char* str);
bool isintfunc(char* str);
bool isboolfunc(char* str);
bool isiofunc(char* str);
bool isiffunc(char* str);
bool isloopfunc(char* str);
///////
bool isvar(char* list);
bool isliteral(char* list);
bool isstring(char* list);
bool isnil(char* list);
int rowlength(char* str);
bool conditionjudge(int opcode, int operand1, int operand2);

void simpletest();
void hardtest();

recycleset* hashset;
lisp** var;
lispstack* newlisps;

void hardtest(){
   printf("hard test begin...");
   hashset_init();
   
   lisp* temp = lisp_atom(5);
   for (int i = 0; i < 10; i++){
      hashset_insert(temp);
   }
   assert(hashset->usage == 1); 
   lisp* temp2 = lisp_atom(6);
   hashset_insert(temp2);
   assert(hashset->usage == 2);
   lisp* temp3 = lisp_cons(temp, lisp_cons(temp2, NIL));
   hashset_insert(temp3);
   assert(hashset->usage == 3); 
   lisp* temp4a = lisp_atom(15);
   lisp* temp4b = lisp_atom(17);
   lisp* temp4 = lisp_cons(temp4a, lisp_cons(temp4b, NIL));
   hashset_insert(temp4);
   assert(hashset->usage == 4);
   hashset_free();
   hashset_init();
   assert(hashset->usage == 0);
   lisp_recycle(temp);
   assert(hashset->usage == 1);
   lisp_recycle(temp2);
   assert(hashset->usage == 2);
   lisp_recycle(temp3);
   assert(hashset->usage == 4);
   lisp_recycle(temp4);
   assert(hashset->usage == 8);
   
   
   
   for (int i = 0; i < 750; i++){ // usage / size > threshold, hashset will rehash, 
      lisp* temp = lisp_atom(rand() % 50000);
      hashset_insert(temp);
   }

   assert(hashset->size = 2999);
   
   lisp** testlisparr = (lisp**)calloc(10000, sizeof(lisp*));
   assert(testlisparr);
   for (int i = 0; i < 10000; i++){
      testlisparr[i] = (lisp*)calloc(1, sizeof(lisp));
      testlisparr[i]->val = rand() % 5000;
      assert(testlisparr[i]);
   }
   
   lisp** secondlisppointer = (lisp**)calloc(10000, sizeof(lisp*));
   assert(secondlisppointer);
   for (int i = 0; i < 10000; i++){
      secondlisppointer[i] = (lisp*)calloc(1, sizeof(lisp));
      secondlisppointer[i]->val = rand() % 5000;
      assert(secondlisppointer[i]);
   }
   
   
   for (int i = 0; i < 10000; i++){
      int rand1 = rand() % 1000;
      int rand2 = rand() % 1000;
      secondlisppointer[i] = lisp_cons(secondlisppointer[i], lisp_cons(testlisparr[rand1], testlisparr[rand2]));
   }
   
   for(int i = 0; i < 10000; i++){
      lisp_recycle(secondlisppointer[i]);
   }

   var['A' - 'A'] = temp;
   var['E' - 'A'] = temp2;
   var['G' - 'A'] = temp3;
   var['Z' - 'A'] = temp4;
   lisp* receiver1 = list2lisp("'(1 2)'");
   char str[1000];
   lisp_tostring(receiver1, str);
   assert(STRSAME(str, "(1 2)"));
   lisp* receiver2 = list2lisp("'((4 5) 6 7 8 (-1 2999 30))'");
   lisp_tostring(receiver2, str);
   assert(STRSAME(str, "((4 5) 6 7 8 (-1 2999 30))"));
   
   lisp* receiver3 = list2lisp("A");
   lisp_tostring(receiver3, str);
   assert(STRSAME(str, "5"));
   
   lisp* receiver4 = list2lisp("E");
   lisp_tostring(receiver4, str);
   assert(STRSAME(str, "6"));
   
   lisp* receiver5 = list2lisp("G");
   lisp_tostring(receiver5, str);
   assert(STRSAME(str, "(5 6)"));
   
   lisp* receiver6 = list2lisp("Z");
   lisp_tostring(receiver6, str);
   assert(STRSAME(str, "(15 17)"));
   
   lisp* receiver7 = list2lisp("NIL");
   lisp_tostring(receiver7, str);
   assert(STRSAME(str, "()"));

   exe_recycle();
   printf("end.\n");
}

int main(void){
   var = (lisp**)calloc(26, sizeof(lisp*));
   newlisps = (lispstack*)calloc(1, sizeof(lispstack));
   newlisps->arr = (lisp**)calloc(SIZE, sizeof(lisp*));
   simpletest();
   hardtest();
}

bool islistfunc(char* str){
   if (STRSAME(str, "CAR")){
//      opcode = CAR;
//      listfunc();
      return true;
   }else if (STRSAME(str, "CDR")){
//      opcode = CDR;
//      listfunc();
      return true;
   }else if (STRSAME(str, "CONS")){
//      opcode = CONS;
//      listfunc();
      return true;
   }

   return false;
}

bool isintfunc(char* str){
   if (STRSAME(str, "PLUS")){
//    opcode = PLUS;
//    intfunc();
      return true;
   }else if (STRSAME(str, "LENGTH")){
//    opcode = LENGTH;
//    intfunc();
      return true;
   }
   return false;
}
bool isboolfunc(char* str){
   if (STRSAME(str, "LESS")){
//    opcode = LESS;
//    boolfunc();
      return true;
   }else if (STRSAME(str, "GREATER")){
//    opcode = GREATER;
//    boolfunc();
      return true;
   }else if (STRSAME(str, "EQUAL")){
//    opcode = EQUAL;
//    boolfunc();
      return true;
   }
   return false;
}

bool isiofunc(char* str){
   if (STRSAME(str, "SET")){
//    opcode = SET;
//    set();
      return true;
   }else if (STRSAME(str, "PRINT")){
//    opcode = PRINT;
//    print();
      return true;
   }
   return false;
}
bool isiffunc(char* str){
   if (STRSAME(str, "IF")){
//      opcode = IF;
//      iffunc();
      return true;
   }else{
      return false;
   }
}

bool isloopfunc(char* str){
   if (STRSAME(str, "WHILE")){
//      opcode = WHILE;
//      loop();
      return true;
   }else{
      return false;
   }
}

bool conditionjudge(int opcode, int operand1, int operand2){
   if ((opcode == LESS && operand1 < operand2) || (opcode == GREATER && operand1 > operand2) || (opcode == EQUAL && operand1 == operand2)){
      return true;
   }else{
      return false;
   }
}

bool isvar(char* str){
   return (int)strlen(str) == 1 && isupper(str[0]);
}

int rowlength(char* str){
   return (int)strlen(str);
}

bool isliteral(char* str){
   int lastchar = rowlength(str) - 1;
   return str[0] == '\'' && str[lastchar] == '\'';
}

bool isstring(char* str){
   int lastchar = rowlength(str) - 1;
   return str[0] == '\"' && str[lastchar] == '\"';
}

bool isnil(char* str){
   return STRSAME(str, "NIL");
}


lisp* list2lisp(char* str){
   if (isvar(str)){
      return var[*str - 'A'];
   }else if (isnil(str)){
      return NIL;
   }else if (isliteral(str)){
      int rowlen = rowlength(str);
      char* retstr = (char*)calloc(rowlen - 1, sizeof(char));
      strncpy(retstr, &str[1], rowlen - 2);
      lisp* ret = lisp_fromstring(retstr);
      free(retstr);
      return ret;
   }else{
      return newlisps->arr[--newlisps->top];

   }
   return NIL;
}



int hash1(lisp* newlisp, int sz){
   int address = (int)(size_t)newlisp;
   return address % sz;
}
int hash2(lisp* newlisp, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (hash1(newlisp, sz) % prime);
}

int doublehash(lisp* newlisp, int sz, int i){
   int value = (hash1(newlisp, sz) + i * hash2(newlisp, sz)) % sz;
   return value;
}
int firstprimeaftern(int n){
   int i = n + 1;
   while (!isprime(i)){
      i++;
   }
   return i;
}
int firstprimebeforen(int n){
   if (n <= 3){
      return 3;
   }

   int i = n - 1;
   while (!isprime(i)){
      i--;
   }
   return i;
}
bool isprime(int n){
   for (int i = 2; i <= (int)sqrt(n); i++){
      if (n % i == 0){
         return false;
      }
   }
   return true;
}


void simpletest(){
   printf("simple test begin...");
   assert(islistfunc("CAR"));
   assert(islistfunc("CDR"));
   assert(islistfunc("CONS"));
   assert(!islistfunc("APPLE"));
   
   assert(isintfunc("PLUS"));
   assert(isintfunc("LENGTH"));
   assert(!isintfunc("BRISTOL"));
   
   assert(isboolfunc("EQUAL"));
   assert(isboolfunc("LESS"));
   assert(isboolfunc("GREATER"));
   assert(!isboolfunc("*"));
   assert(!isboolfunc(">="));
   
   assert(isiofunc("PRINT"));
   assert(isiofunc("SET"));
   assert(!isiofunc("PIANO"));
   
   assert(isiffunc("IF"));
   assert(!isiffunc("IFS"));
   
   assert(isloopfunc("WHILE"));
   assert(!isloopfunc("LOOP"));

   assert(conditionjudge(GREATER, 4, 2));
   assert(!conditionjudge(GREATER, 4, 5));
   assert(conditionjudge(LESS, 3, 5));
   assert(conditionjudge(EQUAL, 7, 7));
   assert(conditionjudge(GREATER, 1, 0));
   assert(!conditionjudge(LESS, 10, 5));
   assert(!conditionjudge(GREATER, 4, 5));
   
   assert(isvar("A"));
   assert(isvar("X"));
   assert(!isvar("a"));
   
   assert(isnil("NIL"));
   assert(!isnil("NULL"));
   
   assert(isliteral("'(1 2 3)'"));
   assert(isliteral("'(4 (5 6))'"));
   assert(!isliteral("'(2 3 3)"));
   
   assert(isstring("\"HELLO WORLD\""));
   assert(isstring("\"4AN\""));
   assert(isstring("\"STUDY HARD\""));
   assert(!isstring("PASS THE EXAM"));
   
   assert(rowlength("apple") == 5);
   assert(rowlength("") == 0);
   
   assert(isprime(3));
   assert(isprime(5));
   assert(isprime(7));
   assert(!isprime(9));
   assert(!isprime(1000));
   assert(!isprime(999));
   assert(!isprime(998));
   assert(isprime(997));
   
   assert(firstprimeaftern(50) == 53);
   assert(firstprimebeforen(50) == 47);
   
   assert(firstprimeaftern(100) == 101);
   assert(firstprimebeforen(100) == 97);

   assert(firstprimeaftern(500) == 503);
   assert(firstprimebeforen(500) == 499);
   
   assert(firstprimeaftern(1000) == 1009);
   assert(firstprimebeforen(1000) == 997);
   printf("end.\n");

}


void hashset_init(void){
   hashset = (recycleset*)calloc(1, sizeof(recycleset));
   assert(hashset);
   hashset->list = (lisp**)calloc(SIZE, sizeof(lisp*));
   assert(hashset->list);
   hashset->size = SIZE;
}

void hashset_insert(lisp* singlelisp){
   int i = 0;
   while (hashset->list[doublehash(singlelisp, hashset->size, i)]){
      if (singlelisp == hashset->list[doublehash(singlelisp, hashset->size, i)]){
         return;
      }
      i++;
   }

   hashset->list[doublehash(singlelisp, hashset->size, i)] = singlelisp;
   hashset->usage++;

   if ((double)hashset->usage / (double)hashset->size >= THRESHOLD){
      rehash();
   }
}

void rehash(void){
   int cnt = 0;
   lisp** templist = (lisp**)calloc(hashset->usage, sizeof(lisp*));
   for (int i = 0; i < hashset->size; i++){
      if (hashset->list[i]){
         templist[cnt++] = hashset->list[i];
      }
   }
   assert(cnt == hashset->usage);

   int newsz = firstprimeaftern(hashset->size * SCALEFACTOR);
   free(hashset->list);
   hashset->list = (lisp**)calloc(newsz, sizeof(lisp*));
   assert(hashset->list);
   hashset->usage = 0;
   hashset->size = newsz;

   for (int i = 0; i < cnt; i++){
      hashset_insert(templist[i]);
   }
   free(templist);
}

void hashset_free(void){
   free(hashset->list);
   free(hashset);
}

void lisp_recycle(lisp* newlisp){

   if (newlisp == NULL){
      return;
   }
   
   lisp_recycle(lisp_car(newlisp));
   lisp_recycle(lisp_cdr(newlisp));

   hashset_insert(newlisp);
}

void exe_recycle(void){
   for (int i = 0; i < hashset->size; i++){
      if (hashset->list[i]){
         free(hashset->list[i]);
         hashset->list[i] = NIL;
      }
   }
}
