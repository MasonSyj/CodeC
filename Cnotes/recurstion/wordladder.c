#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NUM 4
#define PUERMU 24

int cnt = 0;

void test();
void swap(int* x, int* y);
void permu(int* a, int i, int list[][NUM]);
void transform(char* origin, char* after, int* sequnce);

int main(void){
   test();
   int a[NUM] = {0, 1, 2, 3};
   int list[PUERMU][NUM];
   permu(a, 0, list); 
   for (int j = 0; j < PUERMU; j++){
      for (int i = 0; i < NUM; i++){
         printf("%-3d", list[j][i]);
      }
     printf("\n");
   }
 
    char origin[NUM+1] = "COLD";
    char after[NUM+1] = "WARM";
    for (int i = 0; i < PUERMU; i++){
       transform(origin, after, list[i]);
       strcpy(origin, "COLD");
       printf("---------------------------\n");
    }
    
}

void transform(char* origin, char* after, int* sequnce){
    puts(origin);
    for (int i = 0; i < NUM; i++){
       origin[sequnce[i]] = after[sequnce[i]];
       puts(origin);
    }
}

void swap(int* x, int* y){
   int temp = *x;
   *x = *y;
   *y = temp;
}

void permu(int* a, int i, int list[][NUM]){
   if (i == NUM - 1){
      for (int x = 0; x < NUM; x++){
         list[cnt][x] = *(a++);
      }
      cnt++;
  
    return;
   }

   for (int x = i; x <= NUM - 1; x++){
      swap(&a[x], &a[i]);
      permu(a, i+1, list);
      swap(&a[x], &a[i]);
   }
   return;
}

void test(){
   int x = 3, y = 6;
   swap(&x, &y);
   assert(x == 6);
   assert(y == 3);
}

