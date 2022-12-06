#pragma once

#define LISPIMPL "Linked"

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
