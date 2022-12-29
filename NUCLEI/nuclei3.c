#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>

#define ROW 10000
#define COL 100
#define NIL NULL
#define LISTSTRLEN 1000
#define BASETEN 10
#define STRSAME(A,B) (strcmp(A,B) == 0)
#define ERROR(PHARSE) { fprintf(stderr, "Fatal Error %s occurred in %s, line %d, currentrow %d\n"\
	, PHARSE, __FILE__, __LINE__, this->currentrow); exit(EXIT_FAILURE);}
#define CODESIZE 1000
#define LEFTBRACKET '(' //maybe unnecessary, in case it maybe other type like [] or {}
#define RIGHTBRACKET ')'

typedef enum libfunc{CAR, CDR, CONS, PLUS, LENGTH, GREATER, LESS, EQUAL, PRINT, SET, IF, WHILE} libfunc;
typedef enum parsetype{literal, string, letter} parsetype;

typedef int atomtype;

typedef struct lisp{
   int val;
   struct lisp* car;
   struct lisp* cdr;
}lisp;

typedef struct code{
   char word[ROW][COL];
   int currentrow; //current word
}code;

typedef struct liststack{
   int top;
   lisp* l[ROW];
}stack;

code* this;
lisp* var[26];
FILE* fp;
stack* s;
int printcnt;

void Prog(void);
void instrus(void);
void instru(void);
void func(void);
/////
void ret(void);
void iofunc(void);
void iffunc(void);
void loop(void);
/////
void listfunc(int operand);
void intfunc(int operand);
void boolfunc(int operand);
/////
void set(void);
void print(void);

void islist();
bool isvar();
bool isliteral();
bool isstring();
bool isnil();
void pass();

void parse();
void literalparse(char** pstr);
void stringparse(char** pstr);
void letterparse(char** pstr);
void elementparse(char** pstr, parsetype x);
lisp* list2lisp(int beginrow);
char* list2str();

//check if lisp's cdr or car part holds a sublisp rather than the atom
//begining check from str[index]
bool issublisp(const char* str, int index);
// build from cons, for a lisp, pend new things either it's atom or sublisp at the end
// only use at extension part for better readability
void lisp_pend(lisp** l, lisp* sub);
//when a lisp has a sublisp, return the str of this sublisp
char* sublisp_tostring(const char* str);
//turn integer into string, which calloc a string for exact space then use snprintf
char* int2string(int value);
//in a str, for a left bracket, find index for the corresponding right bracket
int indexrightbracket(int leftbracket, const char* str);
//for a str which stands for lisp, locate its first num and use sscanf to make it an int type
int firstnumstr(const char* str);
//count how many digits a num has, negative add 1 for '-' mark
int numdigits(int num);
//isnum check, in a char array, first char needs to be digit or '-'
bool isnum(char x);

// Returns element 'a' - this is not a list, and
// by itself would be printed as e.g. "3", and not "(3)"
lisp* lisp_atom(const atomtype a);

// Returns a list containing the car as 'l1'
// and the cdr as 'l2'- data in 'l1' and 'l2' are reused,
// and not copied. Either 'l1' and/or 'l2' can be NULL
lisp* lisp_cons(const lisp* l1,  const lisp* l2);

// Returns the car (1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_car(const lisp* l);

// Returns the cdr (all but the 1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_cdr(const lisp* l);

// Returns the data/value stored in the cons 'l'
atomtype lisp_getval(const lisp* l);

// Returns a boolean depending up whether l points to an atom (not a list)
bool lisp_isatomic(const lisp* l);

// Returns a deep copy of the list 'l'
lisp* lisp_copy(const lisp* l);

// Returns number of components in the list.
int lisp_length(const lisp* l);

// Returns stringified version of list
void lisp_tostring(const lisp* l, char* str);

// Clears up all space used
// Double pointer allows function to set 'l' to NULL on success
void lisp_free(lisp** l);

/* ------------- Tougher Ones : Extensions ---------------*/

// Builds a new list based on the string 'str'
lisp* lisp_fromstring(const char* str);

// Returns a new list from a set of existing lists.
// A variable number 'n' lists are used.
// Data in existing lists are reused, and not copied.
// You need to understand 'varargs' for this.
lisp* lisp_list(const int n, ...);

// Allow a user defined function 'func' to be applied to
// each atom in the list l.
// The user-defined 'func' is passed a pointer to a cons,
// and will maintain an accumulator of the result.
void lisp_reduce(void (*func)(lisp* l, atomtype* n), lisp* l, atomtype* acc);

void test();

void test(){
   strcpy(this->word[this->currentrow], "'0'");
   strcpy(this->word[this->currentrow], "'1'");
   
   this->currentrow = 0;
}


int main(void){

   s = (stack*)calloc(1, sizeof(stack));
   this = (code*)calloc(1, sizeof(code));
   for (int i = 0; i < 26; i++){
      var[i] = (lisp*)calloc(1, sizeof(lisp));
   }
//   test();
   fp = fopen("all.ncl", "r");
   parse();
   this->currentrow = 0;
   Prog();


}

void Prog(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No Begin statement ?");
   }
   this->currentrow++;
   instrus();
   printf("Parsed OK");
}

void instrus(void){
   if (STRSAME(this->word[this->currentrow], ")")){
      return;
   }
   instru();
   this->currentrow++;
   instrus();   
}

void instru(void){
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in instru ?");
   }
   this->currentrow++;
   func();
   if (!STRSAME(this->word[this->currentrow], ")")){
      ERROR("No ) in instru ?");
   }
   
}

void func(void){
   
   this->currentrow++;
   
   if (STRSAME(this->word[this->currentrow - 1], "CAR")){
      listfunc(CAR);
   }else if (STRSAME(this->word[this->currentrow - 1], "CDR")){
      listfunc(CDR);
   }else if (STRSAME(this->word[this->currentrow - 1], "CONS")){
      listfunc(CONS);
   }else if (STRSAME(this->word[this->currentrow - 1], "PLUS")){
      intfunc(PLUS);
   }else if (STRSAME(this->word[this->currentrow - 1], "LENGTH")){
      intfunc(LENGTH);
   }else if (STRSAME(this->word[this->currentrow - 1], "LESS")){
      boolfunc(LESS);
   }else if (STRSAME(this->word[this->currentrow - 1], "GREATER")){
      boolfunc(GREATER);
   }else if (STRSAME(this->word[this->currentrow - 1], "EQUAL")){
      boolfunc(EQUAL);
   }else if (STRSAME(this->word[this->currentrow - 1], "SET")){
      set();
   }else if (STRSAME(this->word[this->currentrow - 1], "PRINT")){
      print();
   }else if (STRSAME(this->word[this->currentrow - 1], "IF")){
      iffunc();
   }else if (STRSAME(this->word[this->currentrow - 1], "WHILE")){
      loop();
   }else{
      ERROR("No appropriate function?");
   }
}

void listfunc(int operand){

   islist();
      
   if (operand == CAR){
      s->l[s->top++] = lisp_car(list2lisp(this->currentrow++));
      return;
   }else if (operand == CDR){
      s->l[s->top++] = lisp_cdr(list2lisp(this->currentrow++));
      return;
   }else if (operand == CONS){
      lisp* l1 = list2lisp(this->currentrow++);
      
      islist();
      lisp* l2 = list2lisp(this->currentrow++);
      
      s->l[s->top++] = lisp_cons(l1, l2);
   }
}

   
void intfunc(int operand){
   
//   lisp* l = list2lisp(this->currentrow);
   
   int temp = this->currentrow;
   islist();
   this->currentrow++;
   lisp* l = list2lisp(temp);
   
   if (operand == PLUS){
      assert(lisp_isatomic(l));
      int value1 = lisp_getval(l);
      
      temp = this->currentrow;
      islist();
      this->currentrow++;
      lisp* l2 = list2lisp(temp);
      assert(lisp_isatomic(l2));
      int value2 = lisp_getval(l2);
      s->l[s->top++] = lisp_atom(value1 + value2);      
   }else{
      int len = lisp_length(l);
      s->l[s->top++] = lisp_atom(len);
   }
}   
   
void boolfunc(int operand){
      
   int temp = this->currentrow;
   islist();
   this->currentrow++;
   lisp* l1 = list2lisp(temp);
   assert(lisp_isatomic(l1));
   int value1 = lisp_getval(l1);
      
   temp = this->currentrow;
   islist();
   this->currentrow++;
   lisp* l2 = list2lisp(temp);
   assert(lisp_isatomic(l2));
   int value2 = lisp_getval(l2);
   
   int result = 0;
   
   if ((operand == LESS && value1 < value2) || (operand == GREATER && value1 > value2) || (operand == EQUAL && value1 == value2)){
      result = 1;
   }
   
   s->l[s->top++] = lisp_atom(result);
}


void set(void){
   if(!isvar(this->word[this->currentrow])){
      ERROR("Set function miss var");
   }
   char x = this->word[this->currentrow][0];
      
   this->currentrow++;
   int beginrow = this->currentrow;
      
   islist();
      
   var[x - 'A'] = list2lisp(beginrow);
   
   this->currentrow++;
}
   
void print(void){  
   if (isliteral() || isnil() || isstring()){
      puts(this->word[this->currentrow++]);
   }else if (isvar()){
      char x = this->word[this->currentrow++][0];
      char str[ROW];
      lisp_tostring(var[x - 'A'], str);
      puts(str);
   }else if (this->word[this->currentrow][0] == '('){
      islist();
      char str[ROW];
      lisp_tostring(s->l[s->top - 1], str);
      s->top--;
      puts(str);
      this->currentrow++;
   }else{
      ERROR("Print function miss list or string element");
   }
   
}

void iffunc(void){
   if (!STRSAME(this->word[this->currentrow++], "(")){
      ERROR("No ( in if function condition stage.");
   }
   
   this->currentrow++;
   if (STRSAME(this->word[this->currentrow - 1], "LESS")){
      boolfunc(LESS);
   }else if (STRSAME(this->word[this->currentrow - 1], "GREATER")){
      boolfunc(GREATER);
   }else if (STRSAME(this->word[this->currentrow - 1], "EQUAL")){
      boolfunc(EQUAL);
   }else {
      ERROR("No bool function in if function condition stage.");
   }

   if (!STRSAME(this->word[this->currentrow++], ")")){
      ERROR("No ) in if function condition stage.");
   }

   if (!STRSAME(this->word[this->currentrow++], "(")){
      ERROR("No ( in if function first action stage.");
   }
      
   if (lisp_getval(s->l[s->top - 1]) == true){
      instrus();
   }else{
      pass();
   }

   if (!STRSAME(this->word[++this->currentrow], "(")){
      ERROR("No ( in if function second action stage.");
   }
   this->currentrow++;
      
   if (lisp_getval(s->l[--s->top]) == false){
      instrus();
   }else{
      pass();
   }
   
   this->currentrow++;
}

void loop(void){
   if (!STRSAME(this->word[this->currentrow++], "(")){
      ERROR("No ( in loop function condition stage.");
   }

   int begin = this->currentrow;
   int operand;
   this->currentrow++;
   if (STRSAME(this->word[this->currentrow - 1], "LESS")){
      operand = LESS;
      boolfunc(LESS);
   }else if (STRSAME(this->word[this->currentrow - 1], "GREATER")){
      operand = GREATER;
      boolfunc(GREATER);
   }else if (STRSAME(this->word[this->currentrow - 1], "EQUAL")){
      operand = EQUAL;
      boolfunc(EQUAL);
   }else {
      ERROR("No bool function in if function condition stage.");
   }
   
   if (!STRSAME(this->word[this->currentrow++], ")")){
      ERROR("No ) in loop function condition stage.");
   }
      

   if (!STRSAME(this->word[this->currentrow++], "(")){
      ERROR("No ( in loop function first action stage.");
   }
      
   int end;
   while (lisp_getval(s->l[--s->top]) == true){
      instrus();
      end = this->currentrow;
      this->currentrow = begin + 1;
      boolfunc(operand);
      this->currentrow += 2;
   }
      
   this->currentrow = end + 1;
}

void islist(){
   bool result1 = isvar() || isliteral() || STRSAME(this->word[this->currentrow], "NIL");
   if (result1 == true){
      return;
   }
   
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in list");
   }
   
   this->currentrow += 2;
   if (STRSAME(this->word[this->currentrow - 1], "CAR")){
      listfunc(CAR);
   }else if (STRSAME(this->word[this->currentrow - 1], "CDR")){
      listfunc(CDR);
   }else if (STRSAME(this->word[this->currentrow - 1], "CONS")){
      listfunc(CONS);
   }else if (STRSAME(this->word[this->currentrow - 1], "PLUS")){
      intfunc(PLUS);
   }else if (STRSAME(this->word[this->currentrow - 1], "LENGTH")){
      intfunc(LENGTH);
   }else if (STRSAME(this->word[this->currentrow - 1], "LESS")){
      boolfunc(LESS);
   }else if (STRSAME(this->word[this->currentrow - 1], "GREATER")){
      boolfunc(GREATER);
   }else if (STRSAME(this->word[this->currentrow - 1], "EQUAL")){
      boolfunc(EQUAL);
   }else{
      ERROR("invalid list");
   }
      
   if (!STRSAME(this->word[this->currentrow], ")")){
      ERROR("invalid list");
   }

   return;

}

bool isvar(){
   return (int)strlen(this->word[this->currentrow]) == 1 && isupper(this->word[this->currentrow][0]);
}

bool isliteral(){
   int lastchar = (int)strlen(this->word[this->currentrow]) - 1;
   return this->word[this->currentrow][0] == '\'' && this->word[this->currentrow][lastchar] == '\'';
}

bool isstring(){
   int lastchar = (int)strlen(this->word[this->currentrow]) - 1;
   return this->word[this->currentrow][0] == '\"' && this->word[this->currentrow][lastchar] == '\"';
}

bool isnil(){
   return STRSAME(this->word[this->currentrow], "NIL");
}


lisp* list2lisp(int beginrow){
   
   // is variable
   if ((int)strlen(this->word[beginrow]) == 1 && isupper(this->word[beginrow][0])){
      return var[this->word[beginrow][0] - 'A'];
   }else if (STRSAME(this->word[beginrow], "NIL")){
      return NIL;
   }else if (this->word[beginrow][0] == '\''){
      int len = (int)strlen(this->word[beginrow]);
      char* str = (char*)calloc(len - 1, sizeof(char));
      strncpy(str, &this->word[beginrow][1], len - 2);
      return lisp_fromstring(str);
   }else{ //(this->word[beginrow][0] == '(')
      return s->l[--s->top];
   }
}


char* list2str(){
   char* str = (char*)calloc(LISTSTRLEN, sizeof(char));
   assert(str);
   
   // is variable
   if (isvar()){
      strcpy(str, this->word[this->currentrow]);
   }else if (isliteral()){
      int len = (int)strlen(this->word[this->currentrow]);
      strncpy(str, &this->word[this->currentrow][1], len - 2);
   }else if (this->word[this->currentrow][0] == '('){
      lisp_tostring(s->l[--s->top], str);
   }
   
   return str;
}

void pass(){
   assert(this->word[this->currentrow][0] == '(');
   int top = 1;
   while (top != -1){
      this->currentrow++;
      if (this->word[this->currentrow][0] == '('){
         top++;
      }else if (this->word[this->currentrow][0] == ')'){
         top--;
      }
   }
}

void parse(){
   char* str = (char*)calloc(ROW, sizeof(char));
   char* temp = (char*)calloc(ROW, sizeof(char));
   assert(str);
   assert(temp);

   while (fgets(temp, ROW, fp)){
      if (temp[0] != '#'){
         temp[((int)strlen(temp) - 1)] = '\0';
         strcat(str, temp);
      }
   }

   while (*str != '\0'){
      switch (*str){
         case '(': this->word[this->currentrow++][0] = '('; str++; break;
         case ')': this->word[this->currentrow++][0] = ')'; str++; break;
         case '\'': elementparse(&str, literal); break;
         case '"': elementparse(&str, string); break;
         case ' ':str++; break;
         default: elementparse(&str, letter); break;
      }
   }
/*
   int i = 0;
   while (this->word[i][0] != '\0'){
      printf("%d: ", i);
      puts(this->word[i++]);
   }
*/
   printf("---------Separate Line-----------\n");
}

void elementparse(char** pstr, parsetype x){
   char* str = *pstr;
   int i = 1;
   if (x == literal){
      while (str[i] != '\''){
         i++;
      }
   }else if (x == string){
      while (str[i] != '"'){
         i++;
      }   
   }else if (x == letter){
      while (isupper(str[i])){
         i++;
      }
      i--;
   }
   strncpy(this->word[this->currentrow++], str, i + 1);
   *pstr += i + 1;
}

void literalparse(char** pstr){
   char* str = *pstr;
   int i = 1;
   while (str[i] != '\''){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i + 1);
   *pstr += i + 1;
}

void stringparse(char** pstr){
   char* str = *pstr;
   int i = 1;
   while (str[i] != '"'){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i + 1);
   *pstr += i + 1;
}

void letterparse(char** pstr){
   char* str = *pstr;
   int i = 1;
   while (isupper(str[i])){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i);

   *pstr += i;
}

//////////////////////Separate Line//////////////////////////////////////////


// Returns element 'a' - this is not a list, and
// by itelf would be printed as e.g. "3", and not "(3)"
lisp* lisp_atom(const atomtype a){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   assert(this);
   this->val = a;
   assert(!lisp_car(this));
   assert(!lisp_cdr(this));
   return this;
}

// Returns a list containing the car as 'l1'
// and the cdr as 'l2'- data in 'l1' and 'l2' are reused,
// and not copied. Either 'l1' and/or 'l2' can be NULL
lisp* lisp_cons(const lisp* l1,  const lisp* l2){
   lisp* this = (lisp*)calloc(1, sizeof(lisp));
   assert(this);
   this->car = (lisp*)l1;
   this->cdr = (lisp*)l2;
   return this;
}

// Returns the car (1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_car(const lisp* l){
   if (!l){
      return NIL;
   }
   return l->car;
}

// Returns the cdr (all but the 1st) component of the list 'l'.
// Does not copy any data.
lisp* lisp_cdr(const lisp* l){
   if (!l){
      return NIL;
   }
   return l->cdr;
}

// Returns the data/value stored in the cons 'l'
atomtype lisp_getval(const lisp* l){
   assert(l);
   return l->val;
}

// Returns a boolean depending up whether l points to an atom (not a list)
bool lisp_isatomic(const lisp* l){
   if (!l){
      return false;
   }
   return !lisp_car(l) && !lisp_cdr(l);
}
   
// Returns a deep copy of the list 'l'
lisp* lisp_copy(const lisp* l){
   if (l == NIL){
      return NIL;
   }
   lisp* copy = (lisp*)calloc(1, sizeof(lisp));
   assert(copy);
   copy->val = lisp_getval(l);
   copy->cdr = lisp_copy(l->cdr);
   copy->car = lisp_copy(l->car);
   return copy;
}
   
// Returns number of components in the list.
int lisp_length(const lisp* l){
   if (!l || lisp_isatomic(l)){
      return 0;
   }
   
   int cnt = 0;
   while (l){
      l = lisp_cdr(l);
      cnt++;
   }
   return cnt;
}

// Returns stringified version of list
void lisp_tostring(const lisp* l, char* str){
   if (lisp_isatomic(l)){ // when lisp is atom
      char* x = int2string(lisp_getval(l));
      strcpy(str, x);
      free(x);
      return;
   }
   //this tempstr act as parameter str, prefer to calloc one which is cleaner, str from outside might contain data rendering it difficult to manipulate
   char* tempstr = (char*)calloc(LISTSTRLEN, sizeof(char)); 
   assert(tempstr);
   char* head = tempstr;
   *tempstr++ = LEFTBRACKET;
   while(l){
      if (lisp_isatomic(lisp_car(l))){
         int value = lisp_getval(lisp_car(l));
         char* strvalue = int2string(value);
         strcat(tempstr, strvalue);
         free(strvalue);
         tempstr = tempstr + numdigits(value);
      }else if (lisp_car(l)){
         char substr[LISTSTRLEN];
         lisp_tostring(lisp_car(l), substr);
         strcat(tempstr, substr);
         tempstr = tempstr + strlen(substr);
      }
      if (lisp_cdr(l)){
         *tempstr++ = ' ';
      }
      l = lisp_cdr(l);
   }
   strcat(tempstr, ")");
   strcpy(str, head);
   free(head);
}

// Clears up all space used
// Double pointer allows function to set 'l' to NULL on success
void lisp_free(lisp** l){
   if (l == NULL || *l == NIL){
      return;
   }

   lisp* car = lisp_car(*l);
   lisp* cdr = lisp_cdr(*l);

   lisp_free(&car);
   lisp_free(&cdr);
   free(*l);
   *l = NIL;
   return;
}

/* ------------- Tougher Ones : Extensions ---------------*/

// Builds a new list based on the string 'str'
lisp* lisp_fromstring(const char* str){
   if (isupper(str[0])){
      return var[str[0] - 'A'];
   }else if (isnum(*str)){ //when only a single number
      return lisp_atom(firstnumstr(str)); // treat as atom
   }
   
   lisp* this = NIL;
   int index = 0;
   while (index < (int)strlen(str)){
      if (isnum(str[index])){
         int value = firstnumstr(str + index);
         lisp_pend(&this, lisp_atom(value));
         int digit = numdigits(value);
         index = index + digit - 1;
      }else if (str[index] == LEFTBRACKET && issublisp(str, index)){
         char* substr = sublisp_tostring(str + index);
         lisp* sub = lisp_fromstring(substr);
         lisp_pend(&this, sub);
         int len = (int)strlen(substr);
         index = index + len - 1;
         free(substr);
      }
      index++;
   }
   return this;
}

// Returns a new list from a set of existing lists.
// A variable number 'n' lists are used.
// Data in existing lists are reused, and not copied.
// You need to understand 'varargs' for this.
lisp* lisp_list(const int n, ...){
   lisp* this = NIL;
   if (n == 0){
      return this;
   }
   va_list valist;
   va_start(valist, n);
   for (int i = 0; i < n; i++){
      lisp* new = va_arg(valist, lisp*);
      lisp_pend(&this, new);
   }
   va_end(valist);
   return this;
}

// Allow a user defined function 'func' to be applied to
// each component of the list 'l'.
// The user-defined 'func' is passed a pointer to a cons,
// and will maintain an accumulator of the result.
void lisp_reduce(void (*func)(lisp* l, atomtype* n), lisp* l, atomtype* acc){
   while (l){
      if (lisp_isatomic(lisp_car(l))){
         (*func)(lisp_car(l), acc);
      }else if (lisp_car(l) && !lisp_isatomic(lisp_car(l))){
         lisp_reduce(func, lisp_car(l), acc);
      }
      l = lisp_cdr(l);
   }
}


// the str[index] is '(', return false if '(' is at the start and '(' at the end
// needs to separate between the main lisp and sublisp
bool issublisp(const char* str, int index){
   return index != 0 || indexrightbracket(index, str) != (int)strlen(str) - 1;
}

int indexrightbracket(int leftbracket, const char* str){
   assert(str[leftbracket] == LEFTBRACKET);
   char stack[LISTSTRLEN];
   int i = 0;
   stack[i++] = str[leftbracket];
   int index = leftbracket + 1;
   while (str[index] != '\0'){
      if (str[index] == LEFTBRACKET){
         stack[i++] = str[index]; // when is LEFTBRACKET '(', push into the array(like stack)
      }
      if (str[index] == RIGHTBRACKET){
         assert(stack[--i] == LEFTBRACKET); // when is ')', pop
      }
      if (i == 0){ //when no element, the correct rightbracket is found
         return index;
      }
      index++;
   }
   return -1;
}

void lisp_pend(lisp** l, lisp* sub){
   if (*l == NIL){
      *l = lisp_cons(sub, NIL); // if doesn't exist, build a new one to hold sub
   }else{
      lisp* temp = *l;
      while (lisp_cdr(temp)){
         temp = lisp_cdr(temp); // locate the end to pend the sub
      }
      temp->cdr = lisp_cons(sub, NIL);
   }
}

char* sublisp_tostring(const char* str){
   assert(str[0] == LEFTBRACKET);
   int left = 0;
   int right = indexrightbracket(left, str);
   assert(right != -1);
   int len = right - left + 1; // e.g. (0) length is 3, in which case left = 0, right = 2;
   char* substr = (char*)calloc(len + 1, sizeof(char)); // one extra for '\0';
   assert(substr);
   strncpy(substr, str, right + 1); // cut down the str of the sublisp
   return substr;
}

char* int2string(int value){
   int digit = numdigits(value); 
   char* str = (char*)calloc(digit + 1, sizeof(char));
   assert(str);
   assert(snprintf(str, digit + 1, "%d", value) == digit);
   return str;
}

//return first num in a string, only call this function when str begins with number
int firstnumstr(const char* str){
   int value = 0;
   assert(sscanf(str, "%d", &value) == 1);
   return value;
}

bool isnum(char x){
   return isdigit(x) || x == '-';
}

int numdigits(int num){
   if (num < 0){
      return numdigits(-num) + 1; // negative num has one more: '-'
   }
   int i = 0;
   int tens = 1;
   do{
      i++;
      tens *= BASETEN;
   }while (tens <= num);
   return i;
}

