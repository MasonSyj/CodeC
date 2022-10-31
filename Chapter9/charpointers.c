// try to build pointers array containing strings of different length
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

int main(void) {
   char* city[N];
   city[0] = (char*)malloc(sizeof(char) * 2);
// *city[0] = "Bristol";
   char temp1[N] = "Bristol";
   char temp2[N] = "Shanghai";
   city[0] = temp1;
   puts(city[0]);
   strcpy(temp1, "london");
   puts(city[0]);
   city[1] = temp2;
   puts(city[1]);
   
}

