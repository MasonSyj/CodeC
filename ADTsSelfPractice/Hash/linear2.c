#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define S 10

bool insert(int* a, int num);
/* mark -1 as deleted */
bool delete(int* a, int num);
int search(int* a, int num);
int hashlinear(int num);
void show(int* a);


int main(void) {
   int a[10] = {0};
   int num1 = 50;
   int num2 = 70;
   int num3 = 76;
   int num4 = 93;
   int num5 = 90;
   int num6 = 20;
   insert(a, num1);
   insert(a, num2);
   insert(a, num3);
   insert(a, num4);
   insert(a, num5);
   insert(a, num6);
   
   for (int i = 1; i < 6; i++){
      insert(a, i);
   }
   
   printf("%d  %d\n", search(a, 70), search(a, 93));
   
   delete(a, 14);
   show(a);
   
}

bool insert(int* a, int num){
   int i = 0;
   while (a[(hashlinear(num) + i) % S] != 0 && a[(hashlinear(num) + i) % S] != -1){
      i++;
      if (a[(hashlinear(num) + i) % S] == a[hashlinear(num)]){
         return false;
      }
   }
   a[(hashlinear(num) + i) % S] = num;
   return true;
}

bool delete(int* a, int num){
   int i = 0;
   while (a[(hashlinear(num) + i) % S] != num){
      i++;
      if (a[(hashlinear(num) + i) % S] == a[hashlinear(num)]){
         return false;
      }
   }
   a[(hashlinear(num) + i) % S] = -1;
   return true;
}
   
int search(int* a, int num){
   int i = 0;
   while (a[(hashlinear(num) + i) % S] != num){
      i++;
      if (a[(hashlinear(num) + i) % S] == a[hashlinear(num)]){
         return -1;
      }
   }
   return (hashlinear(num) + i) % S;
}
   
int hashlinear(int num){
   return num % S;
}
   
void show(int* a){
   for (int i = 0; i < 10; i++){
      printf("%d: %d\n", i, a[i]);
   }
}
