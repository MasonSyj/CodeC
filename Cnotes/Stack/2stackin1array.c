#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAXSIZE 20

typedef int datatype;

struct node{
   datatype* data;
   int lefttop;
   int righttop;
   int maxsize;
};

typedef struct node* Stack;


Stack create(int maxsize);
bool isfull(Stack s);
bool isempty(Stack s);
bool leftpush(Stack s, datatype x);
bool rightpush(Stack s, datatype x);
datatype leftpop(Stack s);
datatype rightpop(Stack s);
void makeempty(Stack s);

int main(void){
   Stack s = create(MAXSIZE);
   assert(!isfull(s));
   assert(isempty(s));
   assert(leftpush(s, 20));
   assert(rightpush(s, 30));
   assert(leftpop(s) == 20);
   assert(rightpop(s) == 30);
}

Stack create(int maxsize){
   Stack s = (Stack)malloc(sizeof(struct node));
   s->data = (datatype*)calloc(maxsize, sizeof(datatype));
   s->lefttop = -1;
   s->righttop = maxsize;
   s->maxsize = maxsize;
   return s;
}

bool isfull(Stack s){
   return s->lefttop == s->righttop;
}

bool isempty(Stack s){
   return s->lefttop == -1 && s->righttop == s->maxsize;
}

bool leftpush(Stack s, datatype x){
   if (!isfull(s)){
      s->data[++s->lefttop] = x;
      return true;
   }else{
      printf("stack s full already, unable to push.\n");
      return false;
   }
}

bool rightpush(Stack s, datatype x){
   if (!isfull(s)){
      s->data[--s->righttop] = x;
      return true;
   }else{
      printf("stack s full already, unable to push.\n");
      return false;
   }
}

datatype leftpop(Stack s){
   if (isempty(s)){
      printf("stack has not data to pop.\n");
      return -1;
   }else{
      return s->data[s->lefttop--];
   }
}

datatype rightpop(Stack s){
   if (isempty(s)){
      printf("stack has not data to pop.\n");
      return -1;
   }else{
      return s->data[s->righttop++];
   }
}

void makeempty(Stack s){
   s->lefttop = -1;
   s->righttop = s->maxsize;
}


