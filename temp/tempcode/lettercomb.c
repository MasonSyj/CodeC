#include <stdio.h>
#include <string.h>

// line pick and line i
void recur(char letterstore[][4], int i, int pick, char combo[]);

int main(void){
   char digits[] = "1234";
   char letterstore[4][4];
   int i = 0;
   while (digits){
       switch(digits[i]){
           case '2':strcpy(letterstore[i], "abc"); printf("%d", i);i++; break;
           case '3':strcpy(letterstore[i], "def"); i++; break;
           case '4':strcpy(letterstore[i], "ghi"); i++; break;
           case '5':strcpy(letterstore[i], "jkl"); i++; break;
           case '6':strcpy(letterstore[i], "mno"); i++; break;
           case '7':strcpy(letterstore[i], "pqrs"); i++; break;
           case '8':strcpy(letterstore[i], "tuv"); i++; break;
           case '9':strcpy(letterstore[i], "wxyz"); i++; break;
       }
   }
   char combo[4];
   recur(letterstore, i, 0, combo);
}

void recur(char letterstore[][4], int i, int pick, char combo[]){
   printf("i == %d, pick == %d\n", i, pick);
   if (pick == i){
      puts(combo);
   }

   while (pick < i){
//      int a = strlen(letterstore[pick]);
      for (int x = 0; x < strlen(letterstore[pick]); x++){
         combo[pick] = letterstore[pick][x];
         recur(letterstore, i, pick + 1, combo);
      }
   }
}
