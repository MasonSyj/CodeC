#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define ROW 100
#define COL 100
#define STRSAME(A,B) (strcmp(A,B) == 0)
#define ERROR(PHARSE) { fprintf(stderr, "Fatal Error %s occurred in %s, line %d\n", PHARSE, __FILE__, __LINE__); exit(EXIT_FAILURE);}

typedef struct lisp{
   int value;
   struct lisp* car;
   struct lisp* cdr;
}lisp;

typedef struct code{
   char word[ROW][COL];
   int currentrow; //current word
}code;

typedef struct liststack{
   lisp* l1;
   lisp* l2;
}stack;

code* this;

void Prog(void);
void sinstru(void);
void instru(void);
void func(void);
/////
bool ret(void);
bool iofunc(void);
bool iffunc(void);
bool loop(void);
/////
bool listfunc(void);
bool intfunc(void);
bool boolfunc(void);
/////
bool set(void);
bool print(void);

bool islist();
bool isvar();
bool isliteral();



int main(void){
   this = (code*)calloc(1, sizeof(code));
}

void Prog(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No Begin statement ?");
   }
   this->currentrow++;
   instru();
}

void sinstru(void){
   if (STRSAME(this->word[this->currentrow], ")")){
      return;
   }
   this->currentrow++;
   instru();
   this->currentrow++;
   sinstru();   
}

void instru(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in instru ?");
   }
   this->currentrow++;
   func();
   this->currentrow++;
   if (!STRSAME(this->word[this->currentrow], ")")){
      ERROR("No ( in instru ?");
   }
   
}

void func(void){
   bool flag = false;
   flag = ret();
   if (flag == true){
      this->currentrow++;
      return;
   }
   
   flag = iofunc();
   if (flag == true){
      this->currentrow++;
      return;
   }
   
   flag = iffunc();
   if (flag == true){
      this->currentrow++;
      return;
   }
   
   flag = loop();
   if (flag == true){
      this->currentrow++;
      return;
   }
   
   ERROR("No appropriate function?");
}

bool ret(){
   bool flag = false;

   flag = listfunc();
   if (flag == true){
      this->currentrow++;
      return true;
   }
   	
   flag = intfunc();
   if (flag == true){
      this->currentrow++;
      return true;
   }
   
   flag = boolfunc();
   if (flag == true){
      this->currentrow++;
      return true;
   }
   
   return false;
}


bool listfunc(void){
   if (STRSAME(this->word[this->currentrow], "CAR")){
      this->currentrow++;
      islist();
      lisp* current = lispfromstring
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "CDR")){
      this->currentrow++;
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "CONS")){
      this->currentrow++;
      this->currentrow++;
      this->currentrow++;
      return true;
   }
	
   return false;
}
   
bool intfunc(void){
   if (STRSAME(this->word[this->currentrow], "PLUS")){
      this->currentrow++;
      this->currentrow++;
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "LENGTH")){
      this->currentrow++;
      this->currentrow++;
      return true;
   }
   
   return false;
}
   
bool boolfunc(void){
   if (STRSAME(this->word[this->currentrow], "LESS")){
      this->currentrow++;
      this->currentrow++;
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "GREATER")){
      this->currentrow++;
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "EQUAL")){
      this->currentrow++;
      this->currentrow++;
      this->currentrow++;
      return true;
   }
	
   return false;
}

bool set(void){
   if (STRSAME(this->word[this->currentrow], "SET")){
      this->currentrow++;
      assert(isvar(this->word[this->currentrow]));
      this->currentrow++;
      assert(islist(this->word[this->currentrow]));
   }
   return false;
}
   
bool print(void){
   if (STRSAME(this->word[this->currentrow], "PRINT")){
      this->currentrow++;
      assert(isvar(this->word[this->currentrow]));
      this->currentrow++;
      assert(islist(this->word[this->currentrow]));
      return true;
   }
   return false;
}

bool islist(){
   bool result1 = isvar() || isliteral() || STRSAME(this->word[this->currentrow], "NIL");
   if (result1 == true){
      return true;
   }
   
   if (STRSAME(this->word[this->currentrow], "(")){
      this->currentrow++;
      bool retvalue = ret();
      if (retvalue == false){
         ERROR("invalid list");
      }
      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], ")")){
         ERROR("invalid list");
      }
      return true;
   }
   
   ERROR("invalid list");
}

bool isvar(){
   return (int)strlen(this->word[this->currentrow]) && isdigit(this->word[this->currentrow][0]);
}

bool isliteral(){
   return true;
}
