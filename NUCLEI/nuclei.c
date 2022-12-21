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
#define CODESIZE 1000

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
FILE* fp;

void parse(){
   char* str = (char*)calloc(CODESIZE, sizeof(char));
   char* temp = (char*)calloc(ROW, sizeof(char));
   assert(str);
   assert(temp);

   while (fgets(temp, fp, ROW) == 1){
      strcat(str, temp);
   }

   while (*str != '\0'){
      switch (*str){
         case '(': this->word[this->currentword++][0] = '('; break;
         case ')': this->word[this->currentword++][0] = ')'; break;
         case '\'': literalparse(str); break;
         case '\"': literalparse(str); break;
         case ' ':str++; break;
  
         default: digitparse(str); break;      
      }
   }
}
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
bool isstring();

int main(void){
   this = (code*)calloc(1, sizeof(code));
   fp = fopen("demo2.ncl", "r");
}

void Prog(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No Begin statement ?");
   }
   this->currentrow++;
   sinstru();
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

bool iofunc(void){
   bool flag = false;
   flag = set();
   if (flag == true){
      this->currentrow++;
      return true;
   }


   flag = print();
   if (flag == true){
      this->currentrow++;
      return true;
   }

   return false;
}

bool set(void){
   if (STRSAME(this->word[this->currentrow], "SET")){
      this->currentrow++;
      if(!isvar(this->word[this->currentrow])){
         ERROR("Set function miss var");
      }
      this->currentrow++;
      if(!islist(this->word[this->currentrow])){
         ERROR("Set function miss list");
      }
   }
   return false;
}
   
bool print(void){
   if (STRSAME(this->word[this->currentrow], "PRINT")){
      this->currentrow++;
      if(islist()){
         return true;
      }else if(isstring()){
         return true;
      }else{
         ERROR("Print function miss list or string element");
      }
   }
   return false;
}

bool iffunc(void){
   if (STRSAME(this->word[this->currentrow], "IF")){
      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in if function condition stage.");
      }

      this->currentrow++;
      bool boolf = boolfunc();
      if (!boolf){
         ERROR("No boolfunctionb in if function condition stage.");
      }

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ) in if function condition stage.");
      }

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in if function first action stage.");
      }

      sinstru();

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in if function second action stage.");
      }

      sinstru();

      return true;
   }
   return false;
}
bool loop(void){
   if (STRSAME(this->word[this->currentrow], "WHILE")){
      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in loop function condition stage.");
      }

      this->currentrow++;
      bool boolf = boolfunc();
      if (!boolf){
         ERROR("No boolfunctionb in loop function condition stage.");
      }

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ) in loop function condition stage.");
      }

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in loop function first action stage.");
      }

      sinstru();

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
   int lastchar = (int)strlen(this->word[this->currentrow]) - 1;
   return this->word[this->currentrow][0] == '\'' && this->word[this->currentrow][lastchar] == '\'';
}

bool isstring(){
   int lastchar = (int)strlen(this->word[this->currentrow]) - 1;
   return this->word[this->currentrow][0] == '\"' && this->word[this->currentrow][lastchar] == '\"';
}


