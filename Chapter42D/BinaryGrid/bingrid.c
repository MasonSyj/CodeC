#include "bingrid.h"
#define DIFF 0.000000001
#define LINE brd->sz
#define ZERO '0'
#define ONE '1'
#define DOT '.'

// check if the board is solved by scan, true if there 
// are only ZERO and ONE, false otherwise.
bool board_check(board* brd);
// print board in 2D format
void board_print(board* brd);
// fill in numbers when two adjacent numbers appears
// return number of changes by the rule
int paris(board* brd);
// fill in number when appears in way of 1_1 or 0_0
// return number of changes by the rule
int oxo(board* brd);
// fill in nunmber when one line has enough 1 or 0;
// return number of changes by the rule
int counting(board* brd);

int counting(board* brd){
   int changemade = 0;
   bool newchange;
   int zerocnt, onecnt;
   //jump out of the loop when no new change is made.
   do{
      newchange = 0;
      // scan row by row and count
      for (int j = 0; j < LINE; j++){
         zerocnt = onecnt = 0;
         for (int i = 0; i < LINE; i++){
            if (brd->b2d[j][i] == ZERO){
               zerocnt++;
            }else if (brd->b2d[j][i] == ONE){
               onecnt++;
            }
         }
         // apply rule by cnt
         if ((zerocnt == LINE / 2 || onecnt == LINE / 2)
         && onecnt + zerocnt != LINE){
            char fillnumber = ONE;
            newchange = 1;
            if (onecnt == LINE / 2){
               fillnumber = ZERO;
            }

            for (int i = 0; i < LINE; i++){
               if(brd->b2d[j][i] == DOT){
                  brd->b2d[j][i] = fillnumber;
                  changemade++;
               }
            }
		   }
      }

      // scan col by col and count
      for (int i = 0; i < LINE; i++){
         zerocnt = onecnt = 0;
         for (int j = 0; j < LINE; j++){
            if (brd->b2d[j][i] == ZERO){
               zerocnt++;
            }else if (brd->b2d[j][i] == ONE){
               onecnt++;
            }
         }
         // apply rule by cnt
         if ((zerocnt == LINE / 2 || onecnt == LINE / 2)
			&& onecnt + zerocnt != LINE){
            char fillnumber = ONE;
            newchange = 1;
            if (onecnt == LINE / 2){
               fillnumber = ZERO;
            }

            for (int j = 0; j < LINE; j++){
               if(brd->b2d[j][i] == DOT){
                  brd->b2d[j][i] = fillnumber;
                  changemade++;
               }
            }
         }
      }
   }while (newchange == 1);
	
   return changemade;
}

int oxo(board* brd){
   int changemade = 0;
   bool newchange = 1;
   //jump out of the loop when no new change is made.
   do{
      newchange = 0;
      //scan row by row and fill in number if oxo appears
      for (int j = 0; j < LINE; j++){
         for (int i = 0; i < LINE - 2; i++){
            if (brd->b2d[j][i] == brd->b2d[j][i+2] 
				&& brd->b2d[j][i] != DOT && brd->b2d[j][i+1] == DOT){
               if (brd->b2d[j][i] == ZERO){
                  brd->b2d[j][i+1] = ONE;
               }else {
                  brd->b2d[j][i+1] = ZERO;
					}
               newchange = 1;
               changemade++;
            }
         }
      }
      //scan col by col and fill in number if rule is satisifed
      for (int i = 0; i < LINE; i++){
         for (int j = 0; j < LINE - 2; j++){
            if (brd->b2d[j][i]== brd->b2d[j+2][i] 
				&& brd->b2d[j][i] != DOT && brd->b2d[j+1][i] == DOT){
					if (brd->b2d[j][i] == ZERO){
					   brd->b2d[j+1][i] = ONE;
					}else {
					   brd->b2d[j+1][i]  = ZERO;
					}
					newchange = 1;
					changemade++;
            }
         }
      }
   }while (newchange == 1);
   return changemade;
}

int paris(board* brd){
   int changemade = 0;
   bool newchange = 1;
   //jump out of the loop when no new change is made.
   do{
      newchange = 0;
      //scan row by row and fill in numbers if two same appear
      for (int j = 0; j < LINE; j++){
         for (int i = 0; i < LINE - 1; i++){
            if (brd->b2d[j][i] == brd->b2d[j][i+1]
					&& brd->b2d[j][i] != DOT){
               if (i - 1 >= 0 && brd->b2d[j][i-1] == DOT){
                  brd->b2d[j][i-1] = ONE - brd->b2d[j][i] + ZERO;
                  newchange = 1;
                  changemade++;
               }

               if (i + 2 < LINE && brd->b2d[j][i+2] == DOT){
                  brd->b2d[j][i+2] = ONE - brd->b2d[j][i] + ZERO;
                  newchange = 1;
                  changemade++;
               }
            }
         }
      }
      //scan col by col and fill in numbers if two same appear
      for (int i = 0; i < LINE; i++){
         for (int j = 0; j < LINE - 1; j++){
            if (brd->b2d[j][i] == brd->b2d[j+1][i]
					&& brd->b2d[j][i] != DOT){
               if (j - 1 >= 0 && brd->b2d[j-1][i] == DOT){
                  brd->b2d[j-1][i] = ONE - brd->b2d[j][i] + ZERO;
                  newchange = 1;
                  changemade++;
               }

               if (j + 2 < LINE&& brd->b2d[j+2][i] == DOT){
                  brd->b2d[j+2][i] = ONE - brd->b2d[j][i] + ZERO;
                  newchange = 1;
                  changemade++;
               }
            }
         }
      }
   }while (newchange == 1);
   return changemade;
}

bool str2board(board* brd, char* str){
   double x = sqrt(strlen(str));
   if (fabs(x - (int)x) > DIFF || 
   strlen(str) == 0 || (int)x % 2 != 0){
      return false;
   }

   LINE = (int) x;

   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         brd->b2d[j][i] = *(str++);
      }
   }


   return true;
}

void board2str(char* str, board* brd){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         *(str++) = brd->b2d[j][i];
      }
   }
   *str = '\0';
}

void board_print(board* brd){
   printf("************************\n");
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         printf("%c", brd->b2d[j][i]);
      }
      printf("\n");
   }
   printf("************************\n");
}

bool board_check(board* brd){
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
         if (brd->b2d[j][i] == DOT){
            return false;
         }
      }
   }
   return true;
}

bool solve_board(board* brd){
   int changemade;
// endthe loop if all three rules(functions) return 0 changemde
   do{
      changemade = 0;
      changemade += counting(brd) + oxo(brd) + paris(brd);
   }while (changemade > 0);
   return board_check(brd);
}


void test(void){
   board b;
   char str[1000];

   // test the pairs function
   strcpy(str, ".0....1..00.....0.0..1....0....1...0");
   str2board(&b, str);
   paris(&b);
   board2str(str, &b);
   assert(strcmp("1001101.10010.1.0.0.01101.0...0110.0", str) == 0);

   strcpy(str,"..0.11...1..0.0........0..0...0....1.......0.00.0...1......0....");
   str2board(&b, str);
   paris(&b);
   board2str(str, &b);
   assert(strcmp(".100110..1..0.0..0....10..0...0....10......010010...1.....1001..", str) == 0);

   // test the oxo function
   strcpy(str, "00..110....1.0.0..1.00.0......11..00");
   str2board(&b, str);
   oxo(&b);
   board2str(str, &b);
   assert(strcmp("00..1101...1.010..1.00100....111..00", str) == 0);

   strcpy(str, ".0....1..00.....0.0..1....0....1...0");
   str2board(&b, str);
   oxo(&b);
   board2str(str, &b);
   assert(strcmp(".0....1..00.....0.0..1....0....1...0", str) == 0);

   strcpy(str,"....0.0.0.0.0.0.............1.1.0..0....0..00..........1.1.1....");
   str2board(&b, str);
   oxo(&b);
   board2str(str, &b);
   assert(strcmp("....010.0101010.............101.0..0....0..00..........1.101....", str) == 0);

   // test the counting function
   strcpy(str, "00..110....1.0.0..1.00.0......11..00");
   str2board(&b, str);
   counting(&b);
   board2str(str, &b);
   assert(strcmp("00..110....1.0.0..110010......11..00", str) == 0);

   strcpy(str,"..0.11...1..0.0........0..0...0....1.......0.00.0...1......0....");
   str2board(&b, str);
   counting(&b);
   board2str(str, &b);
   assert(strcmp("..0.11...1..0.0........0..0...0....1.......0.00.0...1......0....", str) == 0);

   strcpy(str,"....0.0.0.0.0.0.............1.1.0..0....0..00..........1.1.1....");
   str2board(&b, str);
   counting(&b);
   board2str(str, &b);
   assert(strcmp("....0.0.01010101............1.1.0..0....0..00..........1.1.1....", str) == 0);

   // check the board_check function driven by solve_board function(solvable board)
   strcpy(str, ".0....1..00.....0.0..1....0....1...0");
   str2board(&b, str);
   assert(solve_board(&b) == 1);

   strcpy(str,"..0.11...1..0.0........0..0...0....1.......0.00.0...1......0....");
   str2board(&b, str);
   assert(solve_board(&b) == 1);

   // check the board_check function driven by solve_board function(unsolvable board)
   strcpy(str, "00..110....1.0.0..1.00.0......1...00");
   str2board(&b, str);
   assert(solve_board(&b) == 0);

   strcpy(str,"....0.0.0...0.0.............1.1.0..0....0..00..........1.1.1....");
   str2board(&b, str);
   assert(solve_board(&b) == 0);
}
