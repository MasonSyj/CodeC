#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool evendigit(int num){
    char str[7];
    sprintf(str, "%d", num);
    return !(strlen(str) % 2);
}


int main(void){
   assert(!evendigit(1));
   assert(!evendigit(9));
   assert(!evendigit(999));
   assert(!evendigit(100));
   assert(evendigit(5555));
   assert(evendigit(9999));
   assert(!evendigit(99999));
   assert(!evendigit(10000));
}


/*
bool evendigit(int num){
    int i = 0;
    while (num >= pow(10, i)){
        i++;
    }

    if (i % 2 == 0){
        return true;
    }else{
        return false;
    }
}
*/
int findNumbers(int* nums, int numsSize){
   int cnt = 0;
   for (int i = 0; i < numsSize; i++){
       if (evendigit(nums[i])){
           cnt++;
       }
   }
   return cnt;
}
