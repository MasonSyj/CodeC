#include <stdio.h>

bool isBadVersion(int version);
int firstBadVersion(int n);

int main(int argc, char *argv[]) {
   
}

int firstBadVersion(int n){
   int l = 0, r = n - 1;
   while (l <= r){
      int middle = (l + r) / 2;
      if (isBadVersion(middle) && !isBadVersion(middle-1)){
         return middle;
      }else if (!isBadVersion(middle)){
         l = middle + 1;
      }else{
         r = middle - 1;
      }
   }
   return l;
}