#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>
#include "lisp.h"
#include "general.h"

#define EXE
#define ROW 10000
#define COL 100
#define NIL NULL
#define LISTSTRLEN 1000
#define BASETEN 10
#define STRSAME(A,B) (strcmp(A,B) == 0)
#define ERROR(PHARSE) { fprintf(stderr, "Fatal Error %s occurred in %s, line %d, currentrow %d\n"\
	, PHARSE, __FILE__, __LINE__, token->currentrow); exit(EXIT_FAILURE);}
#define CODESIZE 1000
#define LEFTBRACKET '(' //maybe unnecessary, in case it maybe other type like [] or {}
#define RIGHTBRACKET ')'
#define SIZE 1000
#define SCALEFACTOR 3
#define THRESHOLD 0.7

typedef enum libfunc{CAR, CDR, CONS, PLUS, LENGTH, GREATER, LESS, EQUAL, PRINT, SET, IF, WHILE, DEFUN} libfunc;
typedef enum parsetype{literal, string, letter} parsetype;

typedef struct sourcecode{
   char word[ROW][COL];
   int currentrow; //current word
}sourcecode;

typedef struct stack{
   int top;
   lisp** arr;
}lispstack;

typedef struct recycleset{
   lisp** list;
   int usage;
   int size;
}recycleset;


typedef struct selffunc{
   char funcname[20];
   char word[ROW][COL];
   int firstrow;
   int lastrow;
}selffunc;

typedef struct newfunccoll{
   selffunc** funclist;
   int top;

}newfunccoll;

typedef struct funcstack{
   int top;
   lisp* l[ROW];
}funcstack;

void pass(void);
void defagain(void);
void exe_recycle(void);
void lisp_recycle(lisp* newlisp);
void hashset_init(void);
void hashset_insert(lisp* singlelisp);
void hashset_free(void);
void rehash(void);
int hash1(lisp* newlisp, int sz);
int hash2(lisp* newlisp, int sz); 
int doublehash(lisp* newlisp, int sz, int i);
int firstprimeaftern(int n);
int firstprimebeforen(int n);
bool isprime(int n);

void Prog(void);
void instrus(void);
void instru(void);
void func(void);
/////
bool islistfunc(void);
bool isintfunc(void);
bool isboolfunc(void);
bool isiofunc(void);
bool isiffunc(void);
bool isloopfunc(void);
/////
void listfunc(void);
void intfunc(void);
void boolfunc(void);
bool conditionjudge(int operand1, int operand2);

void set(void);
void print(void);
void iffunc(void);
void loop(void);
/////
lisp* list2lisp(void);
/////
void islist(void);
bool isvar(void);
bool isliteral(void);
bool isstring(void);
bool isnil(void);

int rowlength();

/////
void Lexer(void);
void elementLexer(char** pstr, parsetype type);
void ioLexer(char* input);  //extension
/////
void test();
/////

void defun(); //extension
void selffuncexe(); //extension
bool isselffunc(); //extension



