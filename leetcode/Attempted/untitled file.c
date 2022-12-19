#include <stdio.h>
#include <string.h>

// line pick and line i
void recur(char letterstore[][5], int i, int pick, char combo[]);

int main(void){
   char digits[] = "6789";
   char letterstore[4][5];
   int i = 0;
   while (digits[i]){
       switch(digits[i]){
           case '2':strcpy(letterstore[i], "abc"); i++; break;
           case '3':strcpy(letterstore[i], "def"); i++; break;
           case '4':strcpy(letterstore[i], "ghi"); i++; break;
           case '5':strcpy(letterstore[i], "jkl"); i++; break;
           case '6':strcpy(letterstore[i], "mno"); i++; break;
           case '7':strcpy(letterstore[i], "pqrs"); i++; break;
           case '8':strcpy(letterstore[i], "tuv"); i++; break;
           case '9':strcpy(letterstore[i], "wxyz"); i++; break;
       }
   }
   char combo[10];
   recur(letterstore, i, 0, combo);
}

void recur(char letterstore[][5], int i, int pick, char combo[]){
   if (pick == i){
      printf("%s\n", combo);
      return;
   }

   while (pick < i){
      for (int x = 0; x < (int) strlen(letterstore[pick]); x++){
         combo[pick] = letterstore[pick][x];
         recur(letterstore, i, pick + 1, combo);
      }
      return;
   }
}
