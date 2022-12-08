#pragma once

#define LISPIMPL "Linked"

//check if lisp's cdr or car part holds a sublisp rather than the atom
//begining check from str[index]
bool sublisp(const char* str, int index);
//in a str, for a left bracket, find index for the corresponding right bracket
int indexrightbracket(int leftbracket, const char* str);
// for a lisp, pend new things either it's atom or sublisp at the end
void pend(lisp** l, lisp* sub);
//when a lisp has a sublisp, return the str of this sublisp
char* strsublisp(const char* str);
//turn integer into string, which use exact alloced spaces for an integer
// if use sprintf, need to pass in an fixed-size huge char array, and i don't like that
// each has pros and cons
char* int2string(int value);
//for a str which stands for lisp, locate its first num 
int firstnumstr(const char* str);
//count how many digits a num has, negative add 1 for '-' mark
int numdigits(int num);

struct lisp{
   atomtype value;
   struct lisp* car;
   struct lisp* cdr;
};
