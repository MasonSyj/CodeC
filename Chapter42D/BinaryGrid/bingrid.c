#include "bingrid.h"
#define DIFF 0.000000001
#define LINE brd->sz

void test(void);
bool solve_board(board* brd);
// check if the board is filled completely after solving.
bool board_check(board* brd);
// print board in 2D format
void board_print(board* brd);
void board2str(char* str, board* brd);
bool str2board(board* brd, char* str);
// fill in numbers when two adjacent numbers appears
int paris(board* brd);
// fill in number when appears 1_1 or 0_0
int oxo(board* brd);
// fill in nunmber when one line has enought 1 or 0;
int counting(board* brd);

int counting(board* brd){
	int changemade = 0;
	bool newchange = 1;
	int zerocnt, onecnt;
	while (newchange == 1){
		newchange = 0;

		for (int j = 0; j < LINE; j++){
			zerocnt = onecnt = 0;
			for (int i = 0; i < LINE; i++){
				if (brd->b2d[j][i] == '0'){
					zerocnt++;
				}else if (brd->b2d[j][i] == '1'){
					onecnt++;
				}
			}

			if ((zerocnt == LINE / 2 || onecnt == LINE / 2)
			&& onecnt + zerocnt != LINE){
				char fillnumber = '1';
				newchange = 1;
				if (onecnt == LINE / 2){
					fillnumber = '0';
				}

				for (int i = 0; i < LINE; i++){
					if(brd->b2d[j][i] == '.'){
						brd->b2d[j][i] = fillnumber;
						changemade++;
					}
				}
			}
		}


		for (int i = 0; i < LINE; i++){
			zerocnt = onecnt = 0;
			for (int j = 0; j < LINE; j++){
				if (brd->b2d[j][i] == '0'){
					zerocnt++;
				}else if (brd->b2d[j][i] == '1'){
					onecnt++;
				}
			}

			if ((zerocnt == LINE / 2 || onecnt == LINE / 2)
			&& onecnt + zerocnt != LINE){
				char fillnumber = '1';
				newchange = 1;
				if (onecnt == LINE / 2){
					fillnumber = '0';
				}

				for (int j = 0; j < LINE; j++){
					if(brd->b2d[j][i] == '.'){
						brd->b2d[j][i] = fillnumber;
						changemade++;
					}
				}
			}
		}
	}
	return changemade;
}

int oxo(board* brd){
	int changemade = 0;
	bool newchange = 1;
	while (newchange == 1){
		newchange = 0;
		for (int j = 0; j < LINE; j++){
			for (int i = 0; i < LINE - 2; i++){
				if (brd->b2d[j][i]== brd->b2d[j][i+2] && brd->b2d[j][i] != '.'
				&& brd->b2d[j][i+1] == '.'){
					if (brd->b2d[j][i] == '0'){
						brd->b2d[j][i+1] = '1';
					}else {
						brd->b2d[j][i+1] = '0';
					}
					newchange = 1;
					changemade++;
				}
			}
		}

		for (int i = 0; i < LINE; i++){
			for (int j = 0; j < LINE - 2; j++){
				if (brd->b2d[j][i]== brd->b2d[j+2][i] && brd->b2d[j][i] != '.'
				&& brd->b2d[j+1][i] == '.'){
					if (brd->b2d[j][i] == '0'){
						brd->b2d[j+1][i] = '1';
					}else {
						brd->b2d[j+1][i]  = '0';
					}
					newchange = 1;
					changemade++;
				}
			}
		}
	}
	return changemade;
}

int paris(board* brd){
	int changemade = 0;
	bool newchange = 1;
	while (newchange == 1){
		newchange = 0;
		for (int j = 0; j < LINE; j++){
			for (int i = 0; i < LINE - 1; i++){
				if (brd->b2d[j][i] == brd->b2d[j][i+1]
					&& brd->b2d[j][i] != '.'){
					if (i - 1 >= 0 && brd->b2d[j][i-1] == '.'){
						brd->b2d[j][i-1] = '1' - brd->b2d[j][i] + '0';
						newchange = 1;
						changemade++;
					}

					if (i + 2 < LINE && brd->b2d[j][i+2] == '.'){
						brd->b2d[j][i+2] = '1' - brd->b2d[j][i] + '0';
						newchange = 1;
						changemade++;
					}
				}
			}
		}

		for (int i = 0; i < LINE; i++){
			for (int j = 0; j < LINE - 1; j++){
				if (brd->b2d[j][i] == brd->b2d[j+1][i]
					&& brd->b2d[j][i] != '.'){
					if (j - 1 >= 0 && brd->b2d[j-1][i] == '.'){
						brd->b2d[j-1][i] = '1' - brd->b2d[j][i] + '0';
						newchange = 1;
						changemade++;
					}

					if (j + 2 < LINE&& brd->b2d[j+2][i] == '.'){
						brd->b2d[j+2][i] = '1' - brd->b2d[j][i] + '0';
						newchange = 1;
						changemade++;
					}
				}
			}
		}
	}
	return changemade;
}

bool str2board(board* brd, char* str){
	double x = sqrt(strlen(str));
	if (fabs(x - (int)x) > DIFF || strlen(str) == 0){
		return false;
	}

	int y = (int) x;
	if (y % 2 != 0){
		return false;
	}

	for (int j = 0; j < y; j++){
		for (int i = 0; i < y; i++){
			brd->b2d[j][i] = *(str++);
		}
	}

	brd->sz = y;

	return true;
}

void board2str(char* str, board* brd){
	int x = brd->sz;
	for (int j = 0; j < x; j++){
		for (int i = 0; i < x; i++){
			*(str++) = brd->b2d[j][i];
		}
	}
	*str = '\0';
}

void board_print(board* brd){
	printf("************************\n");
	int x = brd->sz;
	for (int j = 0; j < x; j++){
		for (int i = 0; i < x; i++){
			printf("%c", brd->b2d[j][i]);
		}
		// printf("\n");
	}
	printf("************************\n");
}

bool board_check(board* brd){
	int x = brd->sz;
	for (int j = 0; j < x; j++){
		for (int i = 0; i < x; i++){
			if (brd->b2d[j][i] == '.'){
				return false;
			}
		}
	}
	return true;
}

bool solve_board(board* brd){
	int changemade;
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

// check the solvable board

   strcpy(str, ".0....1..00.....0.0..1....0....1...0");
str2board(&b, str);
assert(solve_board(&b) == 1);

strcpy(str,"..0.11...1..0.0........0..0...0....1.......0.00.0...1......0....");
str2board(&b, str);
assert(solve_board(&b) == 1);





// check the unsolvable board
strcpy(str, "00..110....1.0.0..1.00.0......1...00");
str2board(&b, str);
assert(solve_board(&b) == 0);

strcpy(str,"....0.0.0...0.0.............1.1.0..0....0..00..........1.1.1....");
str2board(&b, str);
assert(solve_board(&b) == 0);
}
