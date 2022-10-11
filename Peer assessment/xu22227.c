#include<stdio.h>

int is_valid(char a, char b);
int is_prime(char c, char d);

int main(void)
{
      

      char j, k,i=1,cnt=0;
          for (j = 'a'; j <= 'z'; ++j){
              for (k = 'a'; k <= 'z'; ++k){
                  if (is_valid(j, k) == 1){
                      if (is_prime(j, k) == 1){
                          cnt++;
                              printf("%2i %c%c%c\n", cnt, j, k, j);
                        }
                  }
            }
      }
      return 0;
}

int is_valid(char a, char b)
{
      if ((a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') && (b != 'a' && b != 'e' && b != 'i' &&b != 'o' && b != 'u'))
            return 1;
      else if ((a != 'a' &&a != 'e' && a != 'i' && a != 'o'&& a != 'u') && (b == 'a' || b == 'e' || b == 'i' || b == 'o' || b == 'u'))
            return 1;
      else
            return 0;
}

int is_prime(char c, char d)
{
      int sum,i;
      sum = ((c - 'a' + 1) * 2 + (d - 'a' + 1));
      for (i = 2; i < sum; i++){
            if ((sum%i) == 0)
                  return 0;
      }
                  return 1;
}