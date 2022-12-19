#include <stdio.h>

bool isValid(char *s) {
   
   char *q=s;
   
   for (char *p=s; *p; p++) 
      switch(*p) {
         case '(': *q++ = ')'; continue;
         case '{': *q++ = '}'; continue;
         case '[': *q++ = ']'; continue;
         default: if (q==s || *p != *--q) return false;
      }
   
   return q==s;
}

int main(int argc, char *argv[]) {
   
}