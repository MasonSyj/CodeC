#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#define BIAS (-3 * 'a' + 3)

void test();
bool isvowel(char c);
bool iscvc(char a, char b, char c);
bool isvcv(char a, char b, char c);
bool isequal(char a, char c);
bool isprime(char a, char b, char c);

int main(void){
   test();
   int step = 0;
   int cnt = 1;
   for (char a = 'a'; a <= 'z'; a++){
      for (char b = 'a'; b <= 'z'; b++){
         for (char c = 'a'; c <= 'z'; c++){
            step++;
            if ((iscvc(a, b, c) || isvcv(a, b, c))
				&& isequal(a, c) && isprime (a, b, c)){
               printf("%2d %c%c%c\n", cnt++, a, b, c);
            }
         }
      }
   }
   printf("%d", step);
}

void test(){
   assert(isvowel('u'));
   assert(!isvowel('z'));
   assert(iscvc('z', 'i', 'c'));
   assert(!iscvc('i', 'a', 'm'));
   assert(isvcv('i', 'x', 'e'));
   assert(!isvcv('n', 'n', 'o'));
   assert(isequal('a', 'a'));
   assert(isequal('z', 'z'));
   assert(!isequal('a', 'x'));
   assert(isprime('y', 'i', 'y'));
   assert(!isprime('a', 'b', 'a'));
}

bool isvowel(char c){
   if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ){
      return true;
   }
   return false;
}

   /* consonant-vowel-consonant. */
bool iscvc(char a, char b, char c){
   if (!isvowel(a) && isvowel(b) && !isvowel(c)){
      return true;		
   }
   return false;
}
   /* vowel-consonant-vowel. */
bool isvcv(char a, char b, char c){
   if (isvowel(a) && !isvowel(b) && isvowel(c)){
      return true;		
   }
   return false;
}
   /* first letter equal to third letter */
bool isequal(char a, char c){
   return a == c;
}

bool isprime(char a, char b, char c){
   /* 'a' = 1, 'b' = 2 */
   int value = a + b + c + BIAS;
   for (int i = 2; i <= sqrt(value); i++){
      if (value % i == 0){
      return false;		
      }
   }
   return true;
}
