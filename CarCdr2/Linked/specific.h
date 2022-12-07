#pragma once

#define LISPIMPL "Linked"

bool sublisp(const char* str, int index);
int indexrightbracket(int leftbracket, const char* str);
void add2list(lisp** l, lisp* sub);
char* strsublisp(const char* str);
char* int2string(int value);
int firstnumstr(const char* str);
int numdigits(int num);

struct lisp{
   atomtype value;
   struct lisp* car;
   struct lisp* cdr;
};
