#pragma once

#define LISPIMPL "Linked"

void add2list(lisp** l, lisp* sub);
char* substr(const char* str);
char* inttostring(int value);
int firstnum(const char* str);
int digits(int num);

struct lisp{
   atomtype value;
   struct lisp* car;
   struct lisp* cdr;
};
