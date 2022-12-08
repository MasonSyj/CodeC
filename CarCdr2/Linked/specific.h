#pragma once

#define LISPIMPL "Linked"

//check if the cdr and car part holds a sublisp rather than the atom
bool sublisp(const char* str, int index);
//in a str, for a left bracket, find index for the corresponding right bracket
int indexrightbracket(int leftbracket, const char* str);
// for a lisp, pend new things either it's atom or sublisp
void pend(lisp** l, lisp* sub);
//when a lisp has a sublisp, return the str of this sublisp, and ignore brackets as well
char* strsublisp(const char* str);
//turn integer into string, which use exact space for an integer
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
