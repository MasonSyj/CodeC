#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>

#define ROW 1000
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
#define PRIME 997
#define SZ 1009

typedef enum libfunc{CAR, CDR, CONS, PLUS, LENGTH, GREATER, LESS, EQUAL, PRINT, SET, IF, WHILE} libfunc;

typedef int atomtype;

typedef struct hash{
   char** list;
   int size;
   int usage;
}hash;

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
hash* hashtable;

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

bool islist();
bool isvar();
bool isliteral();
bool isstring();
bool isnil();
void pass();

void parse();
void literalparse(char** pstr);
void stringparse(char** pstr);
void letterparse(char** pstr);
lisp* list2lisp(int beginrow);

lisp* literal2lisp(int row);
char* list2str(int beginrow);

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

int doublehash(char* sstr, int sz, int i);
int str2val(char* str);
int hash1(char* str, int sz);
int hash2(char* str, int sz);
hash* hash_init();
void hash_insert(hash* h, char* str);
int  hash_search(hash* h, char* str);
bool isprime(int n);
int firstprimebeforen(int n);
int firstprimeaftern(int n);
void insert();
void test();

void test(){
   
}


int main(void){
   s = (stack*)calloc(1, sizeof(stack));
   this = (code*)calloc(1, sizeof(code));
   hashtable = hash_init();
   for (int i = 0; i < 26; i++){
      var[i] = (lisp*)calloc(1, sizeof(lisp));
   }
   fp = fopen("printset.ncl", "r");
   parse();
   insert();
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
   int index = hash_search(hashtable, this->word[this->currentrow]);
   if (index == -1){
      ERROR("No appropriate function?");
   }
   
   if (index == hash_search(hashtable, "CAR")){
      listfunc(CAR);
   }else if (index == hash_search(hashtable, "CDR")){
      listfunc(CDR);
   }else if (index == hash_search(hashtable, "CONS")){
      listfunc(CONS);
   }else if (index == hash_search(hashtable, "PLUS")){
      intfunc(PLUS);
   }else if (index == hash_search(hashtable, "LENGTH")){
      intfunc(LENGTH);
   }else if (index == hash_search(hashtable, "LESS")){
      boolfunc(LESS);
   }else if (index == hash_search(hashtable, "GREATER")){
      boolfunc(GREATER);
   }else if (index == hash_search(hashtable, "EQUAL")){
      boolfunc(EQUAL);
   }else if (index == hash_search(hashtable, "SET")){
      set();
   }else if (index == hash_search(hashtable, "PRINT")){
      print();
   }else if (index == hash_search(hashtable, "IF")){
      iffunc();
   }else if (index == hash_search(hashtable, "WHILE")){
      loop();
   }   
}

void listfunc(int operand){
   this->currentrow++;
   int temp = this->currentrow;
   islist();
   char* tempstr = list2str(temp);
      
   if (operand == CAR){
      s->l[s->top++] = lisp_car(lisp_fromstring(tempstr));
      this->currentrow++;
      return;
   }else if (operand == CDR){
      s->l[s->top++] = lisp_cdr(lisp_fromstring(tempstr));
      this->currentrow++;
      return;
   }else if (operand == CONS){
      this->currentrow++;
      lisp* l1 = list2lisp(temp);
      
      temp = this->currentrow;
      islist();
      this->currentrow++;
      lisp* l2 = list2lisp(temp);
      
      s->l[s->top++] = lisp_cons(l1, l2);
   }
}

   
void intfunc(int operand){
   this->currentrow++;
   
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
   
   this->currentrow++;
      
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
   this->currentrow++;
   if(!isvar(this->word[this->currentrow])){
      ERROR("Set function miss var");
   }
   char x = this->word[this->currentrow][0];
      
   this->currentrow++;
   int beginrow = this->currentrow;
      
   if(!islist(this->word[this->currentrow])){
      ERROR("Set function miss list");
   }
      
   if (isvar(this->word[beginrow])){
      var[x - 'A'] = var[this->word[beginrow][0] - 'A'];
   }else if (STRSAME(this->word[beginrow], "NIL")){
      var[x - 'A'] = NIL;
   }else if (this->word[beginrow][0] == '\''){
      var[x - 'A'] = literal2lisp(beginrow);
   }else{
      var[x - 'A'] = s->l[s->top - 1];
   }
      
   this->currentrow++;
}
   
void print(void){
   this->currentrow++;
   int beginrow = this->currentrow;
   if(islist()){ // VAR LITERAL NIL (RETFUNC)
      if (isvar()){
         char str[1000];
         lisp_tostring(var[this->word[this->currentrow][0] - 'A'], str);
         printf("var:%c, %s\n", this->word[this->currentrow][0], str);
      }else if (isliteral()){
         puts(this->word[beginrow]);
      }else if (isnil()){
         puts(this->word[beginrow]);
      }else if (this->word[this->currentrow][0] == ')'){
         char str[1000];
         lisp_tostring(s->l[s->top - 1], str);
         s->top--;
         puts(str);
      }
   this->currentrow++;
   }else if(isstring()){
      puts(this->word[this->currentrow]);
      this->currentrow++;
   }else{
      ERROR("Print function miss list or string element");
   }
}

void iffunc(void){
   this->currentrow++;
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in if function condition stage.");
   }

   this->currentrow++;
   int index = hash_search(hashtable, this->word[this->currentrow]);
   if (index == hash_search(hashtable, "LESS")){
      boolfunc(LESS);
   }else if (index == hash_search(hashtable, "GREATER")){
      boolfunc(GREATER);
   }else if (index == hash_search(hashtable, "EQUAL")){
      boolfunc(EQUAL);  
   }else {
      ERROR("No bool function in if function condition stage.");
   }

   if (!STRSAME(this->word[this->currentrow], ")")){
      ERROR("No ) in if function condition stage.");
   }
   this->currentrow++;

   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in if function first action stage.");
   }
   this->currentrow++;
      
   if (lisp_getval(s->l[s->top - 1]) == true){
      instrus();
   }else{
      pass();
   }

   this->currentrow++;
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in if function second action stage.");
   }
   this->currentrow++;
      
   if (lisp_getval(s->l[s->top - 1]) == false){
      instrus();
   }else{
      pass();
   }
   
   s->top--;
      
   this->currentrow++;
}

void loop(void){
   this->currentrow++;
   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in loop function condition stage.");
   }
      
   this->currentrow++;
   int begin = this->currentrow;
   int index = hash_search(hashtable, this->word[this->currentrow]);
   int operand;
   if (index == hash_search(hashtable, "LESS")){
      boolfunc(LESS);
      operand = LESS;
   }else if (index == hash_search(hashtable, "GREATER")){
      boolfunc(GREATER);
      operand = GREATER;
   }else if (index == hash_search(hashtable, "EQUAL")){
      boolfunc(EQUAL);  
      operand = EQUAL;
   }else {
      ERROR("No bool function in if function condition stage.");
   }
      
   this->currentrow++;

   if (!STRSAME(this->word[this->currentrow], "(")){
      ERROR("No ( in loop function first action stage.");
   }
   this->currentrow++;
      
   int end;
   while (lisp_getval(s->l[--s->top]) == true){
      instrus();
      end = this->currentrow;
      this->currentrow = begin;
      boolfunc(operand);
      this->currentrow += 2;
   }
      
   this->currentrow = end;
   this->currentrow++;
}

bool islist(){
   bool result1 = isvar() || isliteral() || STRSAME(this->word[this->currentrow], "NIL");
   if (result1 == true){
      return true;
   }
   
   if (STRSAME(this->word[this->currentrow], "(")){
      this->currentrow++;
      
      int index = hash_search(hashtable, this->word[this->currentrow]);
      if (index == hash_search(hashtable, "CAR")){
         listfunc(CAR);
      }else if (index == hash_search(hashtable, "CDR")){
         listfunc(CDR);
      }else if (index == hash_search(hashtable, "CONS")){
         listfunc(CONS);
      }else if (index == hash_search(hashtable, "PLUS")){
         intfunc(PLUS);
      }else if (index == hash_search(hashtable, "LENGTH")){
         intfunc(LENGTH);
      }else if (index == hash_search(hashtable, "LESS")){
         boolfunc(LESS);
      }else if (index == hash_search(hashtable, "GREATER")){
         boolfunc(GREATER);
      }else if (index == hash_search(hashtable, "EQUAL")){
         boolfunc(EQUAL);
      }else{
         ERROR("invalid list");
      }
      
      if (!STRSAME(this->word[this->currentrow], ")")){
         ERROR("invalid list");
      }
      return true;
   }
   
   return false;
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
      return literal2lisp(beginrow);
   }else{ //(this->word[beginrow][0] == '(')
      s->top--;
      return s->l[s->top];
   }
}


char* list2str(int beginrow){
   char* str = (char*)calloc(LISTSTRLEN, sizeof(char));
   assert(str);
   
   // is variable
   if ((int)strlen(this->word[beginrow]) == 1 && isupper(this->word[beginrow][0])){
      strcpy(str, this->word[beginrow]);
   }else if (this->word[beginrow][0] == '\''){
      int len = (int)strlen(this->word[beginrow]);
      strncpy(str, &this->word[beginrow][1], len - 2);
   }else if (this->word[beginrow][0] == '('){
      lisp_tostring(s->l[--s->top], str);

   }
   return str;
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
         case '\'': literalparse(&str); break;
         case '"': stringparse(&str); break;
         case ' ':str++; break;
         default: letterparse(&str); break;
      }
   }

   int i = 0;
   while (this->word[i][0] != '\0'){
      printf("%d: ", i);
      puts(this->word[i++]);
   }
   
   printf("---------Separate Line-----------\n");
}

void literalparse(char** pstr){
   char* str = *pstr;
   int i = 0;
   assert(str[i++] == '\'');
   while (str[i] != '\''){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i + 1);
   *pstr += i + 1;
}

void stringparse(char** pstr){
   char* str = *pstr;
   int i = 0;
   assert(str[i++] == '"');
   while (str[i] != '"'){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i + 1);
   *pstr += i + 1;
}

void letterparse(char** pstr){
   char* str = *pstr;
   int i = 0;
   assert(isupper(str[i++]));
   while (isupper(str[i])){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i);
   *pstr += i;
}

lisp* literal2lisp(int row){
   int len = (int)strlen(this->word[row]);
   if (this->word[row][len - 1] == '\''){
      this->word[row][len - 1] = '\0';
   }
   return lisp_fromstring(&this->word[row][1]);
}

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

/*
char* list2str(int endrow){
   char* str = (char*)calloc(LISTSTRLEN, sizeof(char));
   assert(str);
   
   // is variable
   if ((int)strlen(this->word[endrow]) == 1 && isupper(this->word[endrow][0])){
      strcpy(str, this->word[endrow]);
   }else if (STRSAME(this->word[endrow], "NIL")){
      
   }else if (this->word[endrow][0] == '\''){
      int len = (int)strlen(this->word[endrow]);
      strncpy(str, &this->word[endrow][1], len - 2);
   }else if (this->word[endrow][0] == ')'){
      int top = 0;
      top++;
      int beginrow = endrow;
      while (top != 0){
         beginrow--;
         if (this->word[beginrow][0] == ')'){
            top++;
         }else if (this->word[beginrow][0] == '('){
            top--;
         }
      }
      for (int i = beginrow; i <= endrow; i ++){
      }
      
   }
   return str;
}
*/

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


int doublehash(char* str, int sz, int i){
   return (hash1(str, sz) + i * hash2(str, sz)) % sz;
}

int str2val(char* str){
   int val = 0;
   while (*str != '\0'){
      val = val * 10 + (*str - 'A');
      str++;
   }
   return val;
}

int hash1(char* str, int sz){
   return str2val(str) % sz;
}
int hash2(char* str, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (str2val(str) % prime);
}

hash* hash_init(){
   hash* this = (hash*)calloc(1, sizeof(hash));
   this->list = (char**)calloc(SZ, sizeof(char*));
   this->size = SZ; 
   return this;
}

void hash_insert(hash* h, char* str){
   int i = 0;
   int index = 0;
   do{
      index = doublehash(str, h->size, i);
      i++;
   }while(h->list[index]);
//   printf("Str: %s, index: %d, i: %d\n", str, index, i);
   h->usage++;
   h->list[index] = str;
}

int hash_search(hash* h, char* str){
   int i = 0;
   int index;
   do {
      index = doublehash(str, h->size, i);
      if (h->list[index] && strcmp(h->list[index], str) == 0){
         return index;
      }
      i++;
   } while (h->list[index]);
   return -1;
}

bool isprime(int n){
   for (int i = 2; i <= (int)sqrt(n); i++){
      if (n % i == 0){
         return false;
      }
   }
   return true;
}

int firstprimebeforen(int n){
   if (n <= 3){
      return 3;
   }

   int i = n - 1;
   while (!isprime(i)){
      i--;
   }
   return i;   
}

int firstprimeaftern(int n){
   int i = n + 1;
   while (!isprime(i)){
      i++;
   }
   return i;
}

void insert(){
   hash_insert(hashtable, "PRINT");
   hash_insert(hashtable, "GREATER");
   hash_insert(hashtable, "SET");
   hash_insert(hashtable, "EQUAL");
   hash_insert(hashtable, "CAR");
   hash_insert(hashtable, "CDR");
   hash_insert(hashtable, "CONS");
   hash_insert(hashtable, "PLUS");
   hash_insert(hashtable, "LENGTH");
   hash_insert(hashtable, "IF");
   hash_insert(hashtable, "WHILE");
}
