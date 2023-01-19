#include "nuclei.h"

sourcecode* token;
lisp** var;
FILE* fp;
lispstack* newlisps;
int printcnt;
newfunccoll* deffunc;
int execode;
int opcode;
recycleset* hashset;
bool interp;
bool notpass;

void test(){

}

void pass(void){
   assert(token->word[token->currentrow][0] == '(');
   notpass = false;
   instrus();
   notpass = true;
}



int main(void){
//   assert(argc == 1);
   #ifdef INTERP
      interp = true;
      notpass = true;
   #endif


   test();
   newlisps = (lispstack*)calloc(1, sizeof(lispstack));
   newlisps->arr = (lisp**)calloc(ROW, sizeof(lisp*));
   token = (sourcecode*)calloc(1, sizeof(sourcecode));
   var = (lisp**)calloc(26, sizeof(lisp*));
   hashset_init();

   deffunc = (newfunccoll*)calloc(1, sizeof(newfunccoll));
   deffunc->funclist = (selffunc**)calloc(26, sizeof(selffunc*));

   fp = fopen("all.ncl", "r");
   Lexer();
   fclose(fp);
   token->currentrow = 0;
   Prog();

   #ifdef INTERP

   exe_recycle();

   free(newlisps->arr);
   free(newlisps);
   free(token);
   free(var);
   free(deffunc->funclist);
   free(deffunc);
   hashset_free();
   #endif


}

void Prog(void){
   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No Begin statement ?");
   }
//   token->currentrow++;
   instrus();
   printf("Parsed OK\n");
}

void instrus(void){
   if (STRSAME(token->word[token->currentrow], ")")){
      return;
   }
   instru();
   token->currentrow++;
   instrus();
}

void instru(void){
   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in instru ?");
   }
//   token->currentrow++;
   func();
   if (!STRSAME(token->word[token->currentrow], ")")){
      ERROR("No ) in instru ?");
   }
}

bool islistfunc(void){
   if (STRSAME(token->word[token->currentrow - 1], "CAR")){
      opcode = CAR;
      listfunc();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "CDR")){
      opcode = CDR;
      listfunc();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "CONS")){
      opcode = CONS;
      listfunc();
      return true;
   }

   return false;
}

bool isintfunc(void){
   if (STRSAME(token->word[token->currentrow - 1], "PLUS")){
      opcode = PLUS;
      intfunc();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "LENGTH")){
      opcode = LENGTH;
      intfunc();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "LESS")){
      opcode = LESS;
      boolfunc();
      return true;
   }
   return false;
}

bool isboolfunc(void){
   if (STRSAME(token->word[token->currentrow - 1], "LESS")){
      opcode = LESS;
      boolfunc();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "GREATER")){
      opcode = GREATER;
      boolfunc();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "EQUAL")){
      opcode = EQUAL;
      boolfunc();
      return true;
   }
   return false;
}

bool isiofunc(void){
   if (STRSAME(token->word[token->currentrow - 1], "SET")){
      opcode = SET;
      set();
      return true;
   }else if (STRSAME(token->word[token->currentrow - 1], "PRINT")){
      opcode = PRINT;
      print();
      return true;
   }
   return false;
}

bool isiffunc(void){
   if (STRSAME(token->word[token->currentrow - 1], "IF")){
      opcode = IF;
      iffunc();
      return true;
   }else{
      return false;
   }
}

bool isloopfunc(void){
   if (STRSAME(token->word[token->currentrow - 1], "WHILE")){
      opcode = WHILE;
      loop();
      return true;
   }else{
      return false;
   }
}

void func(void){

   token->currentrow++;

   if (!islistfunc() && !isintfunc() && !isiofunc() &&
       !isboolfunc() && !isiffunc() && !isloopfunc()){
      ERROR("No appropriate function?");
   }

}

void defun(void){
   deffunc->funclist[deffunc->top] = (selffunc*)calloc(1, sizeof(selffunc));
   strcpy(deffunc->funclist[deffunc->top]->funcname, token->word[token->currentrow++]);


   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in if def function parameter stage.");
   }

   islist();
   token->currentrow++;

   if (!STRSAME(token->word[token->currentrow++], ",")){
      ERROR("No ( in if def function parameter stage.");
   }

   islist();
   token->currentrow++;

   if (!STRSAME(token->word[token->currentrow++], ")")){
      ERROR("No ) in if def function parameter stage.");
   }

   if (!STRSAME(token->word[token->currentrow], "(")){
      ERROR("No ( in if def function execution stage.");
   }

   deffunc->funclist[deffunc->top]->firstrow = token->currentrow;
   pass();
   deffunc->funclist[deffunc->top]->lastrow = token->currentrow;
/*
   int firstrow = token->currentrow;
   pass();
   int lastrow = token->currentrow;
   int row = 0;
   for (int i = firstrow; i < lastrow; i++){
      strcpy(deffunc->funclist[deffunc->top]->word[row++], token->word[i]);
   }
   */
   deffunc->top++;
}

void selffuncexe(void){

   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in if self function execution parameter stage.");
   }

   islist();
   token->currentrow++;
   if (!STRSAME(token->word[token->currentrow++], ",")){
      ERROR("No ( in if self function execution parameter stage.");
   }

   islist();
   token->currentrow++;

   if (!STRSAME(token->word[token->currentrow++], ")")){
      ERROR("No ) in if self function execution parameter stage.");
   }

   int bl = token->currentrow;
   token->currentrow = deffunc->funclist[execode]->firstrow + 1;
   func();
   token->currentrow = bl;
}

bool isselffunc(void){
   printf("Enter selffunc name check\n");
   int i = 0;
   while (i != deffunc->top){
      if (STRSAME(deffunc->funclist[i]->funcname, token->word[token->currentrow - 1])){
         execode = i;
         return true;
      }
      i++;
   }
   return false;
}

void listfunc(void){
   islist();

   if (opcode == CAR){
      if (interp && notpass){
         newlisps->arr[newlisps->top++] = lisp_car(list2lisp());
      }
      token->currentrow++;
      return;
   }else if (opcode == CDR){
      if (interp && notpass){
         newlisps->arr[newlisps->top++] = lisp_cdr(list2lisp());
      }
      token->currentrow++;
      return;
   }else if (opcode == CONS){
      lisp* l1;
      if (interp && notpass){
         l1 = list2lisp();
      }
      token->currentrow++;

      islist();
      lisp* l2;
      if (interp && notpass){
         l2 = list2lisp();
         newlisps->arr[newlisps->top++] = lisp_cons(l1, l2);
         lisp_recycle(newlisps->arr[newlisps->top - 1]);
      }
      token->currentrow++;
   }
}


void intfunc(void){
   islist();

   lisp* l;
   if (interp && notpass){
      l = list2lisp();
   }
   token->currentrow++;
   
   int value1;
   int value2;
   if (opcode == PLUS){
      if (interp && notpass){
         assert(lisp_isatomic(l));
         value1 = lisp_getval(l);
      }
      islist();

      if (interp && notpass){
         lisp* l2 = list2lisp();
         assert(lisp_isatomic(l2));
         value2 = lisp_getval(l2);

         newlisps->arr[newlisps->top++] = lisp_atom(value1 + value2);
         lisp_recycle(newlisps->arr[newlisps->top - 1]);
      }
      token->currentrow++;
   }else{
      if (interp && notpass){
         newlisps->arr[newlisps->top++] = lisp_atom(lisp_length(l));
      }
   }
}

void boolfunc(void){
   islist();
   
   int operand1;
   if (interp && notpass){
      lisp* l1 = list2lisp();
      assert(lisp_isatomic(l1));
      operand1 = lisp_getval(l1);
   }

   token->currentrow++;
   islist();

   if (interp && notpass){
      lisp* l2 = list2lisp();
      assert(lisp_isatomic(l2));
      int operand2 = lisp_getval(l2);

      bool result = conditionjudge(operand1, operand2);

      newlisps->arr[newlisps->top++] = lisp_atom((int)result);
      lisp_recycle(newlisps->arr[newlisps->top - 1]);
   }
   token->currentrow++;
}


void set(void){
   if(!isvar()){
      ERROR("Set function miss var");
   }
   char x;
   if (interp && notpass){
      x = token->word[token->currentrow++][0];
   }else{
      token->currentrow++;
   }


   islist();
   if (interp && notpass){
      var[x - 'A'] = list2lisp();
   }
   token->currentrow++;
}

void print(void){
   if (isliteral() || isnil() || isstring()){
      if (interp && notpass){
         puts(token->word[token->currentrow++]);
      }else{
         token->currentrow++;
      }
      return;
   }else if (isvar()){
      if (interp && notpass){
         char x = token->word[token->currentrow++][0];
         char str[ROW];
         lisp_tostring(var[x - 'A'], str);
         puts(str);
      }else{
         token->currentrow++;
      }
      return;
   }else if (token->word[token->currentrow][0] == '('){
      islist();
      if (interp && notpass){
         char str[ROW];
         lisp_tostring(newlisps->arr[newlisps->top - 1], str);
         newlisps->top--;
         puts(str);
         }
      token->currentrow++;
      return;
   }else{
      ERROR("Print function miss list or string element");
   }

}

void iffunc(void){
   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in if function condition stage.");
   }

   token->currentrow++;
   if (isboolfunc() == false){
      ERROR("No bool function in if function condition stage.");
   }

   if (!STRSAME(token->word[token->currentrow++], ")")){
      ERROR("No ) in if function condition stage.");
   }

   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in if function first action stage.");
   }

   lisp* exeflag;
   if (interp && notpass){
      exeflag = newlisps->arr[--newlisps->top];
      if (lisp_getval(exeflag) == true){
         instrus();
      }else{
         pass();
      }
   }else{
      instrus();
   }


   if (!STRSAME(token->word[++token->currentrow], "(")){
      ERROR("No ( in if function second action stage.");
   }
   token->currentrow++;

   if (interp && notpass){
      if (lisp_getval(exeflag) == false){
         instrus();
      }else{
         pass();
      }
   }else{
      instrus();
   }

   token->currentrow++;
}

void loop(void){
   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in loop function condition stage.");
   }
   int begin;
   if (interp && notpass){
      begin = token->currentrow;
   }
   token->currentrow++;

   if (isboolfunc() == false){
      ERROR("No bool function in loop function condition stage.");
   }
   int tempop;
   if (interp && notpass){
      tempop = opcode;
   }

   if (!STRSAME(token->word[token->currentrow++], ")")){
      ERROR("No ) in loop function condition stage.");
   }

   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in loop function first action stage.");
   }

   if (interp && notpass){
      int end;
      while (lisp_getval(newlisps->arr[--newlisps->top]) == true){
         instrus();
         end = token->currentrow;
         token->currentrow = begin + 1;
         opcode = tempop;
         boolfunc();
         token->currentrow += 2;
      }
      token->currentrow = end + 1;
   }else{
      instrus();
      token->currentrow++;
   }

}

void islist(void){
   bool result1 = isvar() || isliteral() || isnil();
   if (result1 == true){
      return;
   }

////
   if (!STRSAME(token->word[token->currentrow], "(")){
      ERROR("No ( in list( retfunc type)");
   }

   int preop = opcode;
   token->currentrow += 2;

   if (!islistfunc() && !isintfunc() && !isboolfunc()){
      ERROR("invalid list");
   }

   opcode = preop;
////
   if (!STRSAME(token->word[token->currentrow], ")")){
      ERROR("invalid list");
   }

   return;

}

bool isvar(void){
   return (int)strlen(token->word[token->currentrow]) == 1 && isupper(token->word[token->currentrow][0]);
}

bool isliteral(void){
   int lastchar = (int)strlen(token->word[token->currentrow]) - 1;
   return token->word[token->currentrow][0] == '\'' && token->word[token->currentrow][lastchar] == '\'';
}

bool isstring(void){
   int lastchar = (int)strlen(token->word[token->currentrow]) - 1;
   return token->word[token->currentrow][0] == '\"' && token->word[token->currentrow][lastchar] == '\"';
}

bool isnil(void){
   return STRSAME(token->word[token->currentrow], "NIL");
}


lisp* list2lisp(void){
   if (isvar()){
      if (interp && notpass){
      lisp_recycle(var[token->word[token->currentrow][0] - 'A']);
      return var[token->word[token->currentrow][0] - 'A'];
      }
   }else if (isnil()){
      return NIL;
   }else if (isliteral()){
      if (interp && notpass){
      int len = (int)strlen(token->word[token->currentrow]);
      char* str = (char*)calloc(len - 1, sizeof(char));
      strncpy(str, &token->word[token->currentrow][1], len - 2);
      lisp* ret = lisp_fromstring(str);
      lisp_recycle(ret);
      free(str);
      return ret;
      }
   }else{
      if (interp && notpass){
      lisp_recycle(newlisps->arr[newlisps->top - 1]);
      return newlisps->arr[--newlisps->top];
      }
   }
   return NIL;
}



void Lexer(void){
   char* str = (char*)calloc(ROW, sizeof(char));
   assert(str);
   char* head = str;
   char* temp = (char*)calloc(ROW, sizeof(char));
   assert(temp);

   while (fgets(temp, ROW, fp)){
      if (temp[0] != '#'){
         temp[((int)strlen(temp) - 1)] = '\0';
         strcat(str, temp);
      }
   }

   while (*str != '\0'){
      switch (*str){
         case '(': token->word[token->currentrow++][0] = '('; str++; break;
         case ')': token->word[token->currentrow++][0] = ')'; str++; break;
         case '\'': elementLexer(&str, literal); break;
         case '"': elementLexer(&str, string); break;
         case ' ':str++; break;
         default: elementLexer(&str, letter); break;
      }
   }

   int i = 0;

   while (token->word[i][0] != '\0'){
      printf("%d: ", i);
      puts(token->word[i++]);
   }

   printf("---------Separate Line-----------\n");

   free(head);
   free(temp);
}

void ioLexer(char* input){

   while (*input != '\0'){
      switch (*input){
         case '(': token->word[token->currentrow++][0] = '('; input++; break;
         case ')': token->word[token->currentrow++][0] = ')'; input++; break;
         case '\'': elementLexer(&input, literal); break;
         case '"': elementLexer(&input, string); break;
         case ' ':input++; break;
         default: elementLexer(&input, letter); break;
      }
   }
}

void elementLexer(char** pstr, parsetype x){
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
   strncpy(token->word[token->currentrow++], str, i + 1);
   *pstr += i + 1;
}

void lisp_recycle(lisp* newlisp){

   if (newlisp == NULL){
      return;
   }
   if (interp && notpass){
   lisp_recycle(lisp_car(newlisp));
   lisp_recycle(lisp_cdr(newlisp));

   hashset_insert(newlisp);
   }
}

void hashset_init(void){
   hashset = (recycleset*)calloc(1, sizeof(recycleset));
   assert(hashset);
   hashset->list = (lisp**)calloc(SIZE, sizeof(lisp*));
   assert(hashset->list);
   hashset->size = SIZE;
}

void hashset_insert(lisp* singlelisp){
   int i = 0;
   while (hashset->list[doublehash(singlelisp, hashset->size, i)]){
      if (singlelisp == hashset->list[doublehash(singlelisp, hashset->size, i)]){
         return;
      }
      i++;
   }

   hashset->list[doublehash(singlelisp, hashset->size, i)] = singlelisp;
   hashset->usage++;

   if ((double)hashset->usage / (double)hashset->size >= THRESHOLD){
      rehash();
   }
}
void rehash(void){
   int cnt = 0;
   lisp** templist = (lisp**)calloc(hashset->usage, sizeof(lisp*));
   for (int i = 0; i < hashset->size; i++){
      if (hashset->list[i]){
         templist[cnt++] = hashset->list[i];
      }
   }
   assert(cnt == hashset->usage);

   int newsz = firstprimeaftern(hashset->size * SCALEFACTOR);
   free(hashset->list);
   hashset->list = (lisp**)calloc(newsz, sizeof(lisp*));
   assert(hashset->list);
   hashset->usage = 0;
   hashset->size = newsz;

   for (int i = 0; i < cnt; i++){
      hashset_insert(templist[i]);
   }
   free(templist);
}

void hashset_free(void){
   free(hashset->list);
   free(hashset);
}

int hash1(lisp* newlisp, int sz){
   int address = (int)(size_t)newlisp;
   return address % sz;
}
int hash2(lisp* newlisp, int sz){
   int prime = firstprimebeforen(sz);
   return prime - (hash1(newlisp, sz) % prime);
}

int doublehash(lisp* newlisp, int sz, int i){
   int value = (hash1(newlisp, sz) + i * hash2(newlisp, sz)) % sz;
   return value;
}
int firstprimeaftern(int n){
   int i = n + 1;
   while (!isprime(i)){
      i++;
   }
   return i;
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
bool isprime(int n){
   for (int i = 2; i <= (int)sqrt(n); i++){
      if (n % i == 0){
         return false;
      }
   }
   return true;
}

void exe_recycle(void){
   for (int i = 0; i < hashset->size; i++){
      if (hashset->list[i]){
         free(hashset->list[i]);
      }
   }
}

bool conditionjudge(int operand1, int operand2){
   if ((opcode == LESS && operand1 < operand2) || (opcode == GREATER && operand1 > operand2) || (opcode == EQUAL && operand1 == operand2)){
      return true;
   }else{
      return false;
   }
}




//////////////////////Separate Line//////////////////////////////////////////



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
