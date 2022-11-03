#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAXSIZE 20

typedef int datatype;

struct node{
   datatype* data;
   int top;
   int maxsize;
};

typedef struct node* Stack;


Stack create(int maxsize);
bool isfull(Stack s);
bool isempty(Stack s);
bool push(Stack s, datatype x);
datatype pop(Stack s);
void makeempty(Stack s);

int main(void){
   Stack s = create(MAXSIZE);
   assert(s->top == -1);
   assert(s->maxsize = MAXSIZE);
   assert(isempty(s));
   assert(!isfull(s));
   assert(push(s, 10) == true);
   assert(pop(s) == 10);
   makeempty(s);
   assert(isempty(s));
}

Stack create(int maxsize){
   Stack s = (Stack)malloc(sizeof(struct node));
   s->data = (datatype*)calloc(maxsize, sizeof(datatype));
   s->top = -1;
   s->maxsize = maxsize;
   return s;
}

bool isfull(Stack s){
   return s->top == s->maxsize-1;
}

bool isempty(Stack s){
   return s->top == -1;
}

bool push(Stack s, datatype x){
   if (!isfull(s)){
      s->data[++s->top] = x;
      return true;
   }else{
      printf("stack s full already, unable to push.\n");
      return false;
   }
}

datatype pop(Stack s){
   if (isempty(s)){
      printf("stack has not data to pop.\n");
      return -1;
   }else{
      return s->data[s->top--];
   }
}

void makeempty(Stack s){
   s->top = -1;
}


