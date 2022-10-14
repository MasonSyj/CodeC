#include "bingrid.h"

#define BOARDSTR (MAX*MAX+1)

int main(void)
{

   test();

   board b;
   char str[BOARDSTR];

   // String Invalid
   assert(str2board(&b, "")==false);
   // Not a square board
   assert(str2board(&b, "...1.0...")==false);

   // An empty board still gives a 'sensible' string
   b.sz = 0;
   board2str(str, &b);
   assert(strcmp(str, "")==0);
   
   // Solvable 2x2 Board
   assert(str2board(&b, ".0.."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "1001")==0);

   // Solvable 4x4 Board
   assert(str2board(&b, "...1.0......1..1"));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "0101101001101001")==0);

   // Solvable4x4 Board
   assert(str2board(&b, "....0.0....1..0."));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "1010010100111100")==0);

   // Unsolvable 4x4 Board
   assert(str2board(&b, "...1.0.........1"));
   assert(solve_board(&b)==false);

   // Solvable 6x6 Board
   assert(str2board(&b, "1...1...0.....00...1................"));
   assert(solve_board(&b)==true);
   board2str(str, &b);
   assert(strcmp(str, "101010100101010011011010101100010101")==0);

   // Unsolvable 6x6 Board
   assert(str2board(&b, "....0...1.....11...0................"));
   assert(solve_board(&b)==false);

   // Solvable 8x8 Board
   assert(str2board(&b, "..0...........0....11.1....1...0....0.1...1................1...."));
   assert(solve_board(&b)==false);
   board2str(str, &b);
   assert(strcmp(str, "1100101010100101010110111101010010100110001010110101100110110100") != 0);


   return 0;
}

//1100  1010
//1010  0101
//0101  1011
//1101  0100
//1010  0110
//0010  1011
//0101  1001
//1011  0100

//..0.....
//......0.
//...11.1.
//...1...0
//....0.1.
//..1.....
//........
//...1....
