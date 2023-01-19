
#include "nuclei.h"

sourcecode* token;
lisp** var;
char varname;
FILE* fp;
lispstack* newlisps;

int execode;
int opcode;
recycleset* hashset;
bool interp;
bool notpass;

int value1;
int value2;

int rowlen;

lisp* templisp1;
lisp* templisp2;

void test(){

}

void pass(void){
   assert(token->word[token->currentrow][0] == '(');
   notpass = false;
   instrus();
   notpass = true;
}


int main(int argc, char* argv[]){
   assert(argc == 2);

   #ifdef INTERP
      notpass = true;
   #endif

   test();
   newlisps = (lispstack*)calloc(1, sizeof(lispstack));
   newlisps->arr = (lisp**)calloc(ROW, sizeof(lisp*));
   token = (sourcecode*)calloc(1, sizeof(sourcecode));
   var = (lisp**)calloc(26, sizeof(lisp*));
   hashset_init();

   fp = fopen(argv[1], "r");
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
   hashset_free();
   #endif


}

void Prog(void){
   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( statement int Prog Stage?");
   }

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

void listfunc(void){
   islist();

   if (opcode == CAR){

      #ifdef INTERP
      if (notpass){
            newlisps->arr[newlisps->top++] = lisp_car(list2lisp());
      }
      #endif
      token->currentrow++;
      return;
   }else if (opcode == CDR){
      #ifdef INTERP
      if (notpass){
            newlisps->arr[newlisps->top++] = lisp_cdr(list2lisp());
         }
      token->currentrow++;
      #endif
      return;
   }else if (opcode == CONS){

      #ifdef INTERP
      if (notpass){
         templisp1 = list2lisp();
      }
      #endif
      token->currentrow++;

      islist();

      #ifdef INTERP
      if (notpass){
         templisp2 = list2lisp();
         newlisps->arr[newlisps->top++] = lisp_cons(templisp1, templisp2);
         lisp_recycle(newlisps->arr[newlisps->top - 1]);
      }
      #endif
      token->currentrow++;
   }
}


void intfunc(void){
   islist();

   #ifdef INTERP
   if (notpass){
      templisp1 = list2lisp();
   }
   #endif
   token->currentrow++;
   
   if (opcode == PLUS){
      #ifdef INTERP
      if (notpass){
         assert(lisp_isatomic(templisp1));
         value1 = lisp_getval(templisp1);
      }
      #endif
      islist();

      #ifdef INTERP
      if (notpass){
         templisp2 = list2lisp();
         assert(lisp_isatomic(templisp2));
         value2 = lisp_getval(templisp2);

         newlisps->arr[newlisps->top++] = lisp_atom(value1 + value2);
         lisp_recycle(newlisps->arr[newlisps->top - 1]);
      }
      #endif
      token->currentrow++;
   }else{
      #ifdef INTERP
      if (notpass){
         newlisps->arr[newlisps->top++] = lisp_atom(lisp_length(templisp1));
      }
      #endif
   }
}

void boolfunc(void){
   islist();

   #ifdef INTERP
   if (notpass){
      templisp1 = list2lisp();
      assert(lisp_isatomic(templisp1));
      value1 = lisp_getval(templisp1);
   }
   #endif
   
   token->currentrow++;
   islist();

   #ifdef INTERP
   if (notpass){
      templisp2 = list2lisp();
      assert(lisp_isatomic(templisp2));
      value2 = lisp_getval(templisp2);

      bool result = conditionjudge(value1, value2);

      newlisps->arr[newlisps->top++] = lisp_atom((int)result);
      lisp_recycle(newlisps->arr[newlisps->top - 1]);
   }
   #endif
   token->currentrow++;
}


void set(void){
   if(!isvar()){
      ERROR("Set function miss var");
   }

   #ifdef INTERP
   if (notpass){
      varname = token->word[token->currentrow][0];
   }
   #endif
   token->currentrow++;



   islist();
   #ifdef INTERP
   if (notpass){
      var[varname - 'A'] = list2lisp();
   }
   #endif
   token->currentrow++;
}

void print(void){
   if (isliteral() || isnil() || isstring()){
      #ifdef INTERP
      if (notpass){
         puts(token->word[token->currentrow]);
      }
      #endif
      token->currentrow++;
      return;
   }else if (isvar()){
      #ifdef INTERP
      if (notpass){
         char varname = token->word[token->currentrow][0];
         char str[ROW];
         lisp_tostring(var[varname - 'A'], str);
         puts(str);
      }
      #endif
      token->currentrow++;
      return;
   }else if (token->word[token->currentrow][0] == '('){
      islist();
      #ifdef INTERP
      if (notpass){
         char str[ROW];
         lisp_tostring(newlisps->arr[newlisps->top - 1], str);
         newlisps->top--;
         puts(str);
      }
      #endif
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
   
   #ifdef INTERP
   lisp* exeflag = newlisps->arr[--newlisps->top];
   #endif

   #ifdef INTERP
   if (notpass){
      if (lisp_getval(exeflag) == true){
         instrus();
      }else{
         pass();
      }
   }
   #else
      instrus();
   #endif

   if (!STRSAME(token->word[++token->currentrow], "(")){
      ERROR("No ( in if function second action stage.");
   }
   token->currentrow++;

   #ifdef INTERP
   if (notpass){
      if (lisp_getval(exeflag) == false){
         instrus();
      }else{
         pass();
      }
   }
   #else
      instrus();
   #endif

   token->currentrow++;
}

void loop(void){
   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in loop function condition stage.");
   }
   
   #ifdef INTERP
   int begin;
   if (notpass){
      begin = token->currentrow;
   }
   #endif
   token->currentrow++;

   if (isboolfunc() == false){
      ERROR("No bool function in loop function condition stage.");
   }
   
   #ifdef INTERP
   int tempop;
   if (notpass){
      tempop = opcode;
   }
   #endif

   if (!STRSAME(token->word[token->currentrow++], ")")){
      ERROR("No ) in loop function condition stage.");
   }

   if (!STRSAME(token->word[token->currentrow++], "(")){
      ERROR("No ( in loop function first action stage.");
   }

   #ifdef INTERP
   if (notpass){
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
   }
   #else
      instrus();
      token->currentrow++;
   #endif

}

void islist(void){
   bool result1 = isvar() || isliteral() || isnil();
   if (result1 == true){
      return;
   }

   if (!STRSAME(token->word[token->currentrow], "(")){
      ERROR("No ( in list( retfunc type)");
   }

   int preop = opcode;
   token->currentrow += 2;

   if (!islistfunc() && !isintfunc() && !isboolfunc()){
      ERROR("invalid list");
   }

   opcode = preop;

   if (!STRSAME(token->word[token->currentrow], ")")){
      ERROR("No ) in list( retfunc type)");
   }

   return;

}

bool isvar(void){
   return (int)strlen(token->word[token->currentrow]) == 1 && isupper(token->word[token->currentrow][0]);
}

int rowlength(){
   return (int)strlen(token->word[token->currentrow]);
}

bool isliteral(void){
   int lastchar = rowlength() - 1;
   return token->word[token->currentrow][0] == '\'' && token->word[token->currentrow][lastchar] == '\'';
}

bool isstring(void){
   int lastchar = rowlength() - 1;
   return token->word[token->currentrow][0] == '\"' && token->word[token->currentrow][lastchar] == '\"';
}

bool isnil(void){
   return STRSAME(token->word[token->currentrow], "NIL");
}


lisp* list2lisp(void){
   if (isvar()){
      #ifdef INTERP
      if (notpass){
         lisp_recycle(var[token->word[token->currentrow][0] - 'A']);
         return var[token->word[token->currentrow][0] - 'A'];
      }
      #endif
   }else if (isnil()){
      return NIL;
   }else if (isliteral()){
      #ifdef INTERP
      if (notpass){
         rowlen = rowlength();
         char* str = (char*)calloc(rowlen - 1, sizeof(char));
         strncpy(str, &token->word[token->currentrow][1], rowlen - 2);
         lisp* ret = lisp_fromstring(str);
         lisp_recycle(ret);
         free(str);
         return ret;
      }
      #endif
   }else{
      #ifdef INTERP
      if (notpass){
         lisp_recycle(newlisps->arr[newlisps->top - 1]);
         return newlisps->arr[--newlisps->top];
      }
      #endif
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

void elementLexer(char** pstr, parsetype type){
   char* str = *pstr;
   int i = 1;
   if (type == literal){
      while (str[i] != '\''){
         i++;
      }
   }else if (type == string){
      while (str[i] != '"'){
         i++;
      }
   }else if (type == letter){
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
   #ifdef INTERP
   if (notpass){
      lisp_recycle(lisp_car(newlisp));
      lisp_recycle(lisp_cdr(newlisp));

      hashset_insert(newlisp);
   }
   #endif
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

