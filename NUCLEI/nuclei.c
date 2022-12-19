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

typedef struct prog{
   char words[ROW][COL];
   int cw; //current word
}prog;

void Prog(prog* this);
void sinstru(prog* this);
void instru(prog* this);
void func(prog* this);
void ret(prog* this);
void listfunc(prog* this);
void intfunc(prog* this);
void boolfunc(prog* this);
void iofunc(prog* this);
void set(prog* this);
void print(prog* this);
void judge(prog* this);
void loop(prog* this);

bool isvar(char c);
bool islist(lisp* l);
void print(lisp* l);

int main(void){
   
}

void Prog(prog* this){
   if (!strsame(this->words[p->cw], "(")){
      ERROR("No Begin statement ?");
   }
   p->cw++;
   instru(this);
}

void sinstru(prog* this){
   if (!strsame(this->words[p->cw], ")")){
      return;
   }

   
   p->cw++;
   instru(this);   
}

void instru(prog* this){
   int len = (int)strlen(this->word[p->cw]);
   if (this->word[p->cw][0] != '(' || this->word[p->cw][len - 1] != ')'){
      ERROR("INSTRCT Invalid.");
   }
   func(this);
}

void func(prog* this){
   if ()
}
