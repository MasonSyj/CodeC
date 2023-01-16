#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>
#include "lisp.h"

#define ROW 10000
#define COL 100
#define NIL NULL
#define LISTSTRLEN 1000
#define BASETEN 10
#define STRSAME(A,B) (strcmp(A,B) == 0)
#define ERROR(PHARSE) { fprintf(stderr, "Fatal Error %s occurred in %s, line %d, currentrow %d\n"\
	, PHARSE, __FILE__, __LINE__, this->currentrow); exit(EXIT_FAILURE);}
#define CODESIZE 1000
#define LEFTBRACKET '(' //maybe unnecessary, in case it maybe other type like [] or {}
#define RIGHTBRACKET ')'

typedef enum libfunc{CAR, CDR, CONS, PLUS, LENGTH, GREATER, LESS, EQUAL, PRINT, SET, IF, WHILE, DEFUN} libfunc;
typedef enum parsetype{literal, string, letter} parsetype;

typedef struct code{
   char word[ROW][COL];
   int currentrow; //current word
}code;

typedef struct liststack{
   int top;
   lisp* l[ROW];
}stack;

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

void Prog(void);
void instrus(void);
void instru(void);
void func(void);
/////
void islistfun(void);
void isintfun(void);
void isboolfun(void);
void isiofun(void);
/////
void listfunc();
void intfunc();
void boolfunc();
/////
void set(void);
void print(void);
void iffunc(void);
void loop();

void islist();
bool isvar();
bool isliteral();
bool isstring();
bool isnil();
void pass();

void parse();
void elementparse(char** pstr, parsetype x);
void ioparse(char* input);

lisp* list2lisp(int beginrow);

void defun();
void selffuncexe();
bool isselffunc();

void test();


