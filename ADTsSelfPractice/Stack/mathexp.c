#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define SCALEFACTOR 2
#define MAXSIZE 30

typedef int datatype;

struct node{
   datatype* data;
   int top;
   int maxsize;
};

typedef struct node* Stack;


int suffixcal(char* exp);
void test();
Stack create(int maxsize);
bool isempty(Stack s);
bool push(Stack s, datatype x);
datatype pop(Stack s);
void makeempty(Stack s);

int main(void){
   test();
   char exp[] = "9 3 1 - 3 x + 10 2 / +";
   int value = suffixcal(exp);
   printf("%d", value);
}

int suffixcal(char* exp){
   Stack s = create(MAXSIZE);
   while(*exp){
      int tempnum = 0;
      if (*exp == ' '){
         exp++;
         continue;
      }else if (*exp == '-' || *exp == 'x' || *exp == '+' || *exp == '/'){
         int num1, num2;
         num2 = pop(s);
         num1 = pop(s);
         switch(*exp){
            case '-': push(s, num1 - num2); break;
            case 'x': push(s, num1 * num2); break;
            case '+': push(s, num1 + num2); break;
            case '/': push(s, num1 / num2); break;
         }
         exp++;
      }else{
         while (*exp >= '0' && *exp <= '9'){
            tempnum = tempnum * 10 + (*exp - '0');
            exp++;
         }
 //        printf("tempnum: %d\n", tempnum);
         push(s, tempnum);
      }
   }
   return pop(s);
}

Stack create(int maxsize){
   Stack s = (Stack)malloc(sizeof(struct node));
   s->data = (datatype*)calloc(maxsize, sizeof(datatype));
   s->top = -1;
   s->maxsize = maxsize;
   return s;
}


bool isempty(Stack s){
   return s->top == -1;
}

bool push(Stack s, datatype x){
   if(s->top == s->maxsize - 1){
      s->data = (datatype*)realloc(s->data, s->maxsize * SCALEFACTOR);
      if (!s->data){
         return false;
      }
      s->maxsize *= SCALEFACTOR;
      s->data[++s->top] = x;
   }
   s->data[++s->top] = x;
   return true;
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

void test(){
   Stack s = create(MAXSIZE);
   assert(s->top == -1);
   assert(s->maxsize = MAXSIZE);
   assert(isempty(s));
   assert(push(s, 10) == true);
   assert(push(s, 10) == true);
   assert(push(s, 10) == true);
   assert(push(s, 10) == true);
   assert(push(s, 10) == true);
   assert(push(s, 10) == true);
   assert(pop(s) == 10);
   makeempty(s);
   assert(isempty(s));
}
