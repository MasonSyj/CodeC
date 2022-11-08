#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define LEN strlen(word)

void test(void);
void swap(char* a, char* b);
void permu(char word[], int i);

int main(void){
   test();
   char word[] = "ABCD";
   permu(word,0);
}

void swap(char* a, char* b){
   char temp = *a;
   *a = *b;
   *b = temp;   
}

void permu(char word[], int i){
   static int cnt = 0;
   if (i == LEN - 1){
      cnt++;
      puts(word);
      printf("cnt: %d\n------------------\n", cnt);
      return;
   }
   
   for (int s = i; s < LEN; s++){
      swap(&word[i], &word[s]);
      permu(word, i+1);
      swap(&word[i], &word[s]);
   }
}

void test(void){
   char a = 'a';
   char b = 'b';
   swap(&a, &b);
   assert(a == 'b');
   assert(b == 'a');
}
