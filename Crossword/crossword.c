#include "crossword.h"

void test(void){

}

/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or '.', black squares 'X' or '*'
*/
bool str2crossword(int sz, char* ip, crossword* cw){
   if (sz * sz != (signed) strlen(ip) || sz <= 0 || ip == NULL || cw == NULL){
      return false;
   }
   
   
   for (int j = 0; j < sz; j++){
      for (int i = 0; i < sz; i++){
         cw->arr[j][i] = *(ip++);
      }
   }
   return true;
}

// Convert crossword to string of across & down numbers
void getcluestring(const crossword* c, char* str){
   strcpy(str, "A-");
   char b[BIGSTR];
   strcpy(b, "|B-");
   int bi = 2;
   int cnt = 1;
   for (int j = 0; j < c->sz; j++){
      for (int i = 0; i < c->sz; i++){
         if (c->arr[j][i] == 'X' || c->arr[j][i] == '*'){
            continue;
         }else if (c->arr[j][i] == ' ' || c->arr[j][i] == '.'){
            if ((j == 0 || c->arr[j-1][i] == 'X' || c->arr[j-1][i] == '*') && (i == 0 || c->arr[j][i-1] == 'X' || c->arr[j][i-1] == '*')){
               *(str++) = cnt + '0';
               *(str++) = '-';
               b[bi++] = cnt + '0';
               b[bi++] = '-';
               cnt++;
            }
         
            else if (j == 0 || c->arr[j-1][i] == 'X' || c->arr[j-1][i] == '*'){
               *(str++) = cnt + '0';
               *(str++) = '-';
               cnt++;
            }
            
            else if (i == 0 || c->arr[j][i-1] == 'X' || c->arr[j][i-1] == '*'){
            	b[bi++] = cnt + '0';
               b[bi++] = '-';
               cnt++;
            }
         }
      }
   }
   b[bi] = '\0';
   strcat(str, b);
}


// Get percentage of empty squares that are shared between two clues
int getchecked(crossword c){
   int cnt = 0;
   for (int j = 0; j < c.sz; j++){
      for (int i = 0; i < c.sz; i++){
         if (c.arr[j][i] == 'X' || c.arr[j][i] == '*'){
            continue;
         }else if (c.arr[j][i] == ' ' || c.arr[j][i] == '.'){
            if ((j == 0 || c.arr[j-1][i] == 'X' || c.arr[j-1][i] == '*') && (i == 0 || c.arr[j][i-1] == 'X' || c.arr[j][i-1] == '*')){
               cnt++;
            }
         }
      }
   }
   return cnt;
}
