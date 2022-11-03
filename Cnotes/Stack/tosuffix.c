#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define SCALEFACTOR 2
#define MAXSIZE 30

typedef char datatype;

struct node{
   datatype* data;
   int top;
   int maxsize;
};

typedef struct node* Stack;


int opcmp(char a, char b);
char* tosuffix(char* exp);
int suffixcal(char* exp);
void test();
Stack create(int maxsize);
bool isempty(Stack s);
bool push(Stack s, datatype x);
datatype pop(Stack s);
void makeempty(Stack s);

int main(void){
   test();
// char exp[] = "(/3-5)+4";
// char exp[] = "2x(9+6/3-5)+4";
   char exp[] = "(3+4)x5-6";
   char* suffix = tosuffix(exp);
   puts(suffix);

}

char* tosuffix(char* exp){
   Stack s = create(MAXSIZE);
   char* suffix = (char*)calloc(20, sizeof(char));
   char* start = suffix;
   while(*exp){
      if (*exp >= '0' && *exp <= '9'){
         *suffix++ = *exp;
         exp++;
      }else if (*exp == '('){
         push(s, *exp);
         exp++;
      }else if (*exp == ')'){
         char temp;
         while ((temp = pop(s)) != '('){
            *suffix++ = temp;
         }
         assert(temp == '(');
         exp++;
      }else if (*exp == 'x' || *exp == '/' || *exp == '+' || *exp == '-'){
         
         if (isempty(s)){
            push(s, *exp);
            exp++;
            continue; 
         }
         
         char temp = pop(s);
         push(s,temp);
         
         if (opcmp(*exp, temp) > 0){
            printf("push: %c\n", *exp);
            push(s, *exp);
         }else{
            while(opcmp(*exp, temp) <= 0 && !isempty(s)){
               printf("*exp: %c temp: %c\n", *exp, temp);
               temp = pop(s);
               *suffix++ = temp;
               printf("pop out new:%c\n", temp);
            }
            if (temp == '('){
               push(s, temp);
            }
            push(s, *exp);
         }
         exp++;
      }
      
   }
   
   while (!isempty(s)){
      *suffix++ = pop(s);
   }
   
   return start;
}

int opcmp(char a, char b){
   if (b == '('){
      return 1;  
   }
   if (a == 'x' || a == '/'){
      if (b == 'x' || b == '/'){
         return 0;
      }else if (b == '+' || b == '-'){
         return 1;
      }
   }else if (a == '+' || a == '-'){
      if (b == 'x' || b == '/'){
         return -1;
      }else if (b == '+' || b == '-'){
         return 0;
      }
   }
}

int suffixcal(char* exp){
   Stack s = create(MAXSIZE);
   while(*exp){
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
         int tempnum = 0;
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
   assert(opcmp('x','/') == 0);
   assert(opcmp('x','-') == 1);
   assert(opcmp('+','+') == 0);
   assert(opcmp('+','/') == -1);
   Stack t = create(MAXSIZE);
   push(t, 'a');
   push(t, 'b');
   push(t, 'c');
   assert(pop(t) == 'c');
   assert(pop(t) == 'b');
   assert(pop(t) == 'a');
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
