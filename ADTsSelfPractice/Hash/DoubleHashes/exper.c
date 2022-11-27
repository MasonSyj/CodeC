#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void test();

int main(void) {
   printf("%ld", sizeof(int));
}

void test(){
   FILE* fp = fopen("exper.txt", "r");
   int first;
   char code[20];
   double second;
   double third;
   char str[50];
   char temp1[20];
   char temp2[20];
   char temp3[20];
   char temp4[20];
   fgets(str, 50, fp);
   assert(strncmp(str, "id,postcode,latitude,longitude", 30) == 0);
   while(fgets(str, 50, fp)){
      char* temp = str;
      int i = 0;
      int commacnt = 0;
      int head = 0;
      bool one, two, three;
      one = two = three = false;
      while (temp[i]){
         if (temp[i] == ','){
            commacnt++;
         }
         if (commacnt == 1 && one == false){
            strncpy(temp1, temp + head, i - head);
            head = i + 1;
            one = true;
         }
         if (commacnt == 2 && two == false){
            strncpy(temp2, temp + head, i - head);
            head = i + 1;
            two = true;
         }
         if (commacnt == 3 && three == false){
            strncpy(temp3, temp + head, i - head);
            head = i + 1;
            three = true;
         }
            
         i++;
      }
      strncpy(temp4, temp + head, i - head);
      first = atoi(temp1);
      strcpy(code, temp2);
      second = atof(temp3);
      third = atof(temp4);
      printf("%d %s %f %f\n", first, code, second, third);
   }
   fclose(fp);
}
