#include "../stack.h"
#include "specific.h"

#define DOTFILE 5000

stack* stack_init(void)
{
  stack* s = (stack*)calloc(1, sizeof(stack));
  if(!s){
     fprintf(stderr, "stack allocation failed.\n");
     exit(EXIT_FAILURE);
  }
  s->a = (stacktype*)calloc(FIXEDSIZE, sizeof(stacktype));
  if(!s->a){
     fprintf(stderr, "realloc array allocation failed.\n");
     exit(EXIT_FAILURE);
  }
  
  s->size = 0;
  s->capacity = FIXEDSIZE;
  
  return s;
}

void stack_push(stack* s, stacktype d)
{
   if (!s){
      return;
   }
   
   if (s->size == s->capacity){
      s->a = (stacktype*)realloc(s->a, sizeof(stacktype)* s->capacity * SCALEFACTOR);
      if (!s->a){
         fprintf(stderr, "realloc array allocation failed.\n");
         exit(EXIT_FAILURE);
      }
      s->capacity *= SCALEFACTOR;
   }
   s->a[s->size++] = d;
}

bool stack_pop(stack* s, stacktype* d)
{
   if(!s){
      return false;
   }else if (s->size == 0){
      return false;
   }
   
   *d = s->a[--s->size];
   return true;
}


// just look at the top, not pop it.
bool stack_peek(stack* s, stacktype* d)
{
   if(!s){
      return false;
   }else if (s->size == 0){
      return false;
   }
   
   *d = s->a[s->size - 1];
   return true;
}

bool stack_free(stack* s)
{
   free(s);
   return true;
}

// every element to string and cat together into a char*
void stack_tostring(stack* s, char* str)
{
   char tmp[ELEMSIZE];
   str[0] = '\0';
   if((s==NULL) || (s->size <1)){
      return;
   }
   for(int i=s->size-1; i>=0; i--){
      sprintf(tmp, FORMATSTR, s->a[i]); 
      strcat(str, tmp);
      strcat(str, "|");
   }
   str[strlen(str)-1] = '\0';
}































 
 
void stack_todot(stack* s, char* fname)
{
   char tmp[DOTFILE];
   char str[DOTFILE];
   FILE* fp;
   stack_tostring(s, str);
   sprintf(tmp, "digraph structs\n{\n rankdir = LR;\n node [shape=record];\n stack [label=\"");
   strcat(tmp, str);
   strcat(tmp, "\"];\n}\n");
   sprintf(str, "%s%s", STACKTYPE, fname);
   fp = nfopen(str, "wt");
   fprintf(fp, "%s\n", tmp);
   fclose(fp);
}
