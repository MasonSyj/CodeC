#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#define ROW 1000
#define COL 100
#define STRSAME(A,B) (strcmp(A,B) == 0)
#define ERROR(PHARSE) { fprintf(stderr, "Fatal Error %s occurred in %s, line %d, currentrow %d\n"\
	, PHARSE, __FILE__, __LINE__, this->currentrow); exit(EXIT_FAILURE);}
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

/*
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
*/

void Prog(void);
void instrus(void);
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

void test();

void test(){
   this->currentrow = 3;
   assert(isvar());
   this->currentrow = 0;
}

int main(void){

   this = (code*)calloc(1, sizeof(code));
//   fp = fopen("demo2.ncl", "r");
   this->word[this->currentrow++][0] = '(';
   this->word[this->currentrow++][0] = '(';
   strcpy(this->word[this->currentrow++], "PRINT");
   strcpy(this->word[this->currentrow++], "(");
   strcpy(this->word[this->currentrow++], "CONS");
   strcpy(this->word[this->currentrow++], "'1'");
   strcpy(this->word[this->currentrow++], "(");
   strcpy(this->word[this->currentrow++], "CONS");
   strcpy(this->word[this->currentrow++], "'2'");
   strcpy(this->word[this->currentrow++], "NIL");
   strcpy(this->word[this->currentrow++], ")");
   strcpy(this->word[this->currentrow++], ")");
   strcpy(this->word[this->currentrow++], ")");
   strcpy(this->word[this->currentrow++], ")");
   this->currentrow = 0;
   Prog();

/*
(
(
PRINT
(
CONS
'1'
(
CONS
'2'
NIL
)
)
)
)
*/
}

void Prog(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No Begin statement ?");
   }
   this->currentrow++;
   instrus();
   printf("Parsed OK");
}

void instrus(void){
   if (STRSAME(this->word[this->currentrow], ")")){
      return;
   }
   instru();
   this->currentrow++;
   instrus();   
}

void instru(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in instru ?");
   }
   this->currentrow++;
   func();
   if (!STRSAME(this->word[this->currentrow], ")")){
      ERROR("No ) in instru ?");
   }
   
}

void func(void){
   bool flag = false;
   flag = ret();
   if (flag == true){
      return;
   }
   
   flag = iofunc();
   if (flag == true){
      return;
   }
   
   flag = iffunc();
   if (flag == true){
      return;
   }
   
   flag = loop();
   if (flag == true){
      return;
   }
   
   ERROR("No appropriate function?");
}

bool ret(){
   bool flag = false;

   flag = listfunc();
   if (flag == true){
      return true;
   }
   	
   flag = intfunc();
   if (flag == true){
      return true;
   }
   
   flag = boolfunc();
   if (flag == true){
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
      islist();
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "CONS")){
      this->currentrow++;
      islist();
      this->currentrow++;
      islist();
      this->currentrow++;
      return true;
   }
	
   return false;
}
   
bool intfunc(void){
   if (STRSAME(this->word[this->currentrow], "PLUS")){
      this->currentrow++;
      islist();
      this->currentrow++;
      islist();
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "LENGTH")){
      this->currentrow++;
      islist();
      this->currentrow++;
      return true;
   }
   
   return false;
}
   
bool boolfunc(void){
   if (STRSAME(this->word[this->currentrow], "LESS")){
      this->currentrow++;
      islist();
      this->currentrow++;
      islist();
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "GREATER")){
      this->currentrow++;
      islist();
      this->currentrow++;
      islist();
      this->currentrow++;
      return true;
   }

   if (STRSAME(this->word[this->currentrow], "EQUAL")){
      this->currentrow++;
      islist();
      this->currentrow++;
      islist();
      this->currentrow++;
      return true;
   }
	
   return false;
}

bool iofunc(void){
   bool flag = false;
   flag = set();
   if (flag == true){
      return true;
   }


   flag = print();
   if (flag == true){
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
      this->currentrow++;
      return true;
   }
   return false;
}
   
bool print(void){
   if (STRSAME(this->word[this->currentrow], "PRINT")){
      this->currentrow++;
      if(islist()){
         this->currentrow++;
         return true;
      }else if(isstring()){
         this->currentrow++;
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
      if (!STRSAME(this->word[this->currentrow], ")")){
         ERROR("No ) in if function condition stage.");
      }

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in if function first action stage.");
      }

      instrus();

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in if function second action stage.");
      }
      this->currentrow++;
      instrus();

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
      
      if (!STRSAME(this->word[this->currentrow], ")")){
         ERROR("No ) in loop function condition stage.");
      }

      this->currentrow++;
      if (!STRSAME(this->word[this->currentrow], "(")){
         ERROR("No ( in loop function first action stage.");
      }
      this->currentrow++;
      instrus();

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
      if (!STRSAME(this->word[this->currentrow], ")")){
         ERROR("invalid list");
      }
      return true;
   }
   
   return false;
}

bool isvar(){
   return (int)strlen(this->word[this->currentrow]) == 1 && isupper(this->word[this->currentrow][0]);
}

bool isliteral(){
   int lastchar = (int)strlen(this->word[this->currentrow]) - 1;
   return this->word[this->currentrow][0] == '\'' && this->word[this->currentrow][lastchar] == '\'';
}

bool isstring(){
   int lastchar = (int)strlen(this->word[this->currentrow]) - 1;
   return this->word[this->currentrow][0] == '\"' && this->word[this->currentrow][lastchar] == '\"';
}
