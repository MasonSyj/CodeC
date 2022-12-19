#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isThree(int n){
  double x = sqrt(n);
  if ((int)x * (int)x == n){
    if ((int)sqrt(x) * (int)sqrt(x) == (int)x){
      return false;
    }else{
      return true;
    }
  }
  return false;
}

int main(void){
  int x = isThree(100);
  printf("%d", x);
}
