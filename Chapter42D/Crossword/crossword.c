#include "crossword.h"

void print(const crossword* c){
   printf("-------------------------\n");
   for (int j = 0; j < c->sz; j++){
      for (int i = 0; i < c->sz; i++){
         printf("%-2c", c->arr[j][i]);
      }
      printf("\n");
   }
   
}

void test(void){

}


/*
   Convert a size (sz) & string (ip) into a crossword*
   White squares are ' ' or '.', black squares 'X' or '*'
*/
bool str2crossword(int sz, char* ip, crossword* cw){
   if (sz <= 0 || ip == NULL || cw == NULL || sz * sz != (signed) strlen(ip)){
      return false;
   }
   
   for (int j = 0; j < sz; j++){
      for (int i = 0; i < sz; i++){
         cw->arr[j][i] = *ip;
         if(cw->arr[j][i] == ' '){
            cw->arr[j][i] = '.';
         }
         if(cw->arr[j][i] == '*'){
            cw->arr[j][i] = 'X';
         }
         ip++;
      }
   }
   cw->sz = sz;
   print(cw);
   return true;
}

// Convert crossword to string of across & down numbers
void getcluestring(const crossword* c, char* str){
   strncpy(str, "A", BIGSTR);
   char b[BIGSTR];
   strncpy(b, "|D", BIGSTR);
   int bi = 2;
   int ai = 1;
   int cnt = 1;
   for (int j = 0; j < c->sz; j++){
      for (int i = 0; i < c->sz; i++){
         if (c->arr[j][i] == 'X'){
            continue;
         }else if (c->arr[j][i] == '.'){
            if (((j == 0 || c->arr[j-1][i] == 'X' ) && j < c->sz - 1 && c->arr[j+1][i] == '.') && ((i == 0 || c->arr[j][i-1] == 'X' ) && i < c->sz - 1 && c->arr[j][i+1] == '.')){
               str[ai++] = '-';
               if (cnt >= 10){
                  str[ai++] = cnt / 10 + '0';
                  str[ai++] = cnt % 10 + '0';
               }else{
                  str[ai++] = cnt + '0';
               }
               b[bi++] = '-';
               if (cnt >= 10){
                  b[bi++] = cnt / 10 + '0';
                  b[bi++] = cnt % 10 + '0';
               }else{
                  b[bi++] = cnt + '0';
               }
               cnt++;
            }
         
            else if ((j == 0 || c->arr[j-1][i] == 'X' ) && j < c->sz - 1 && c->arr[j+1][i] == '.'){
               b[bi++] = '-';
               if (cnt >= 10){
                  b[bi++] = cnt / 10 + '0';
                  b[bi++] = cnt % 10 + '0';
               }else{
                  b[bi++] = cnt + '0';
               }
               cnt++;
            }
            
            else if ((i == 0 || c->arr[j][i-1] == 'X' ) && i < c->sz - 1 && c->arr[j][i+1] == '.'){
               str[ai++] = '-';
               if (cnt >= 10){
                  str[ai++] = cnt / 10 + '0';
                  str[ai++] = cnt % 10 + '0';
               }else{
                  str[ai++] = cnt + '0';
               }
               cnt++;
            }
         }
      }
   }
   b[bi] = '\0';
   strcat(str, b);
   puts(str);
}


// Get percentage of empty squares that are shared between two clues
int getchecked(crossword c){
   int cnt = 0;
   int checked = 0;
   bool horizontal, vertical;
   for (int j = 0; j < c.sz; j++){
      for (int i = 0; i < c.sz; i++){
         if (c.arr[j][i] == 'X'){
            continue;
         }
         horizontal = vertical = 0;
         if ((i - 1 >= 0 && c.arr[j][i - 1] == '.') || (i + 1< c.sz && c.arr[j][i+1] == '.')){
            horizontal = 1;
         }
         
         if ((j - 1 >= 0 && c.arr[j-1][i] == '.') || (j + 1< c.sz  && c.arr[j+1][i] == '.')){
            vertical = 1;
         }
         
         if (horizontal == 1 && vertical == 1){
            checked++;
            printf("j = %d, i = %d\n", j, i);
         }
         cnt++;      
      }
   }
   int x = ((double)checked / (double) cnt ) * 100 + 0.5;
   printf("cnt: %d, checked: %d x: %d\n",cnt, checked, x);
   return x;
}

//if (c.arr[j][i] == 'X' || c.arr[j][i] == '*'){
// continue;
//}else if (c.arr[j][i] == ' ' || c.arr[j][i] == '.'){
// if ((j == 0 || c.arr[j-1][i] == 'X' || c.arr[j-1][i] == '*') && (i == 0 || c.arr[j][i-1] == 'X' || c.arr[j][i-1] == '*')){
