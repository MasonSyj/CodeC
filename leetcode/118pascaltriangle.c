#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int c(int m, int n);
int fact(int num);
void display(int** a, int n);
int P(int m, int n);
int pascal(int row, int col);

int main(void) {
   int n = 30;
   int** a = (int**)calloc(n, sizeof(int*)); // n stands for n rows
   assert(a);
   for (int i = 0; i < n; i++){
      a[i] = (int*)calloc(n + 1, sizeof(int));
   }
   for (int j = 0; j < n; j++){
      for (int i = 0; i <= j; i++){
//         a[j][i] = c(j, i);
		
/*
         if (i == 0 || i == j){
            a[j][i] = 1;
         }else{
            a[j][i] = a[j-1][i-1] + a[j-1][i];
         }
*/
		
         a[j][i] = pascal(j, i);
//         printf("%d %d\n", j, i);
      }
   }
   display(a, n);
}

int pascal(int row, int col){ // row >= 0, col >= 0
   if (col == 0 || col == row || row == 0){
      return 1;	
   }
   return pascal(row - 1, col - 1) + pascal(row - 1, col);
}

int fact(int num){
   if (num <= 1){
      return num;
   }
   
   return num * fact(num - 1);
}

int P(int m, int n){
   int sum = 1;
   for (int i = n + 1; i <= m; i++){
      sum *= i;
   }
   return sum;
}

int c(int m, int n){
   if (n == 0 || m == n){
      return 1;
   }
   return P(m, n) / fact(m - n);
}

void display(int** a, int n){
   for (int j = 0; j < n; j++){
      for (int i = 0; i <= j; i++){
         printf("%d  ", a[j][i]);
      }
      printf("\n");
   }
   printf("--------------------------\n");
}

