#include <stdio.h>
#include <stdbool.h>

bool isValid(char * s){
   while(*s){
    if (*s == '('){
      if (*(s++) == ')') {
      printf("here.");
      	return false;  
      }
    } 
    if (*s == '['){
      if (*(s++) == ']'){
       return false;  
      }
    } 
    if (*s == '{'){
      if (*(s++) == '}'){
       return false;
       }  
    } 
       s++;
   }
    return true;
}

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

int main(void){
   printf("%d\n", isValid("()"));
   printf("%d\n", isValid("("));
}
