#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define PHIAPPROX 1.61803398875
#define PHI ((1 + sqrt(5)) / 2)

bool fibword_phi(int n);
void test();


int main(void){
   test();
}

bool fibword_phi(int n){
   return 2 + floor(n * PHI) - floor((n + 1) * PHI);
}

void test(){
   assert(fibword_phi(1) == 0);
   assert(fibword_phi(2) == 1);
   assert(fibword_phi(3) == 0);
   assert(fibword_phi(4) == 0);
   assert(fibword_phi(5) == 1);
   assert(fibword_phi(7) == 1);
}
