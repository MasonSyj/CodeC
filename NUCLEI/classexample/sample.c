#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ROW 100
#define COL 20
#define STRSAME(A, B) (strcmp(A, B) == 0)
#define ONERROR(PHARSE) {fprintf(stderr, "Fatal Error %s in %s, line: %d", PHARSE, __FILE__, __LINE__);\
                         exit(EXIT_FAILURE);}

typedef struct code{
   char word[ROW][COL];
   int currentrow;
}code;

code* c1;

void Prog();
void Code();
void Statement();

int main(void){
   c1 = (code*)calloc(1, sizeof(code));
   strcpy(c1->word[c1->currentrow++], "BEGIN");
   strcpy(c1->word[c1->currentrow++], "ONE");
   strcpy(c1->word[c1->currentrow++], "NOUGHT");
   strcpy(c1->word[c1->currentrow++], "END");
   c1->currentrow = 0;
   Prog();
}


void Prog(){
   if (!STRSAME(c1->word[c1->currentrow], "BEGIN")){
      ONERROR("No Begin?");
   }
   c1->currentrow++;
   Code();
   printf("Parsed ok");
}

void Code(){
   if (STRSAME(c1->word[c1->currentrow], "END")){
      return;
   }

   Statement();
   c1->currentrow++;
   Code();
   
}

void Statement(){
   if (STRSAME(c1->word[c1->currentrow], "ONE")){
      return;
   }
   if (STRSAME(c1->word[c1->currentrow], "NOUGHT")){
      return;
   }
   ONERROR("No ONE or NOUGHT");
}
