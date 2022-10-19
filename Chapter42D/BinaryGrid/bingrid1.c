#include "bingrid.h"
#define DIFF 0.000000001
#define LINE brd->sz

typedef enum direction{ROW, COL} dir;

void printboard(board* brd);
bool board_check(board* brd);
int countingline(board* brd, bool flag);
int oxoline(board* brd, bool flag, int line);
int parisline(board* brd, bool flag, int line);

int oxoline(board* brd, bool flag, int line){
	 int changemade = 0;
	 if (flag == ROW){
	    for (int j = 0; j < LINE - 2; j++){
		 	   if (brd->b2d[line][j] == brd->b2d[line][j+2] && brd->b2d[line][j] != '.' && brd->b2d[line][j+1] == '.'){
		 		   if (brd->b2d[line][j] == '0'){
		 			   brd->b2d[line][j+1] = '1';
		 		   }else {
		 			   brd->b2d[line][j+1] = '0';
		 		   }
		 		   changemade++;
		 	   }
			}
	  }else{
			for (int i = 0; i < LINE - 2; i++){
				if (brd->b2d[i][line] == brd->b2d[i+2][line] && brd->b2d[i][line] != '.' && brd->b2d[i+1][line] == '.'){
					if (brd->b2d[i][line] == '0'){
						brd->b2d[i+1][line] = '1';
					}else {
						brd->b2d[i+1][line] = '0';
					}
					changemade++;
				}
			}
	 }
	 return changemade;
}

int oxo(board* brd){
	int changemade = 0;
	bool newchange = 1;
	int thischange;
	while (newchange == 1){
		newchange = 0;
		thischange = 0;
		for (int i = 0; i < LINE; i++){
			thischange += oxoline(brd, ROW, i);
			changemade += thischange;
		}

		for (int j = 0; j < LINE; j++){
			thischange += oxoline(brd, COL, j);
			changemade += thischange;
		}
		if (thischange > 0){
			newchange = 1;
		}
	}
	return changemade;
}
int counting(board* brd){
	int changemade = 0;
	bool newchange = 1;
	int zerocnt, onecnt;
	while (newchange == 1){
		newchange = 0;
		for (int i = 0; i < LINE; i++){
			zerocnt = onecnt = 0;
			for (int j = 0; j < LINE; j++){
				if (brd->b2d[i][j] == '0'){
					zerocnt++;
				}else if (brd->b2d[i][j] == '1'){
					onecnt++;
				}
			}

			if ((zerocnt == LINE / 2 || onecnt == LINE / 2) && onecnt + zerocnt != LINE){
				char fillnumber = '1';
				newchange = 1;
				if (onecnt == LINE / 2){
					fillnumber = '0';
				}

				for (int j = 0; j < LINE; j++){
					if(brd->b2d[i][j] == '.'){
						brd->b2d[i][j] = fillnumber;
						changemade++;
					}
				}
			}
		}


		for (int j = 0; j < LINE; j++){
			zerocnt = onecnt = 0;
			for (int i = 0; i < LINE; i++){
				if (brd->b2d[i][j] == '0'){
					zerocnt++;
				}else if (brd->b2d[i][j] == '1'){
					onecnt++;
				}
			}

			if ((zerocnt == LINE / 2 || onecnt == LINE / 2) && onecnt + zerocnt != LINE){
				char fillnumber = '1';
				newchange = 1;
				if (onecnt == LINE / 2){
					fillnumber = '0';
				}

				for (int i = 0; i < LINE; i++){
					if(brd->b2d[i][j] == '.'){
						brd->b2d[i][j] = fillnumber;
						changemade++;
					}
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
		for (int i = 0; i < LINE; i++){
			for (int j = 0; j < LINE - 1; j++){
				if (brd->b2d[i][j] == brd->b2d[i][j+1] && brd->b2d[i][j] != '.'){

					if (j - 1 >= 0 && brd->b2d[i][j-1] == '.'){
						brd->b2d[i][j-1] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}

					if (j + 2 < LINE && brd->b2d[i][j+2] == '.'){
						brd->b2d[i][j+2] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}
				}
			}
		}

		for (int j = 0; j < LINE; j++){
			for (int i = 0; i < LINE - 1; i++){
				if (brd->b2d[i][j] == brd->b2d[i+1][j] && brd->b2d[i][j] != '.'){

					if (i - 1 >= 0 && brd->b2d[i-1][j] == '.'){
						brd->b2d[i-1][j] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}

					if (i + 2 < LINE && brd->b2d[i+2][j] == '.'){
						brd->b2d[i+2][j] = '1' - brd->b2d[i][j] + '0';
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
	for (int j = 0; j < LINE; j++){
		for (int i = 0; i < LINE; i++){
			*(str++) = brd->b2d[j][i];
		}
	}
	*str = '\0';
}

bool solve_board(board* brd){
	int changemade;
	do{
		changemade = 0;
		changemade += counting(brd) + oxo(brd) + paris(brd);
	}while (changemade > 0);

	return board_check(brd);
}

bool board_check(board* brd){
	for (int j = 0; j < LINE; j++){
		for (int i = 0; i < LINE; i++){
			if (brd->b2d[j][i] == '.'){
				return false;
			}
		}
	}
	return true;
}

void printboard(board* brd){
	printf("************************\n");
	int x = brd->sz;
	for (int j = 0; j < x; j++){
		for (int i = 0; i < x; i++){
			printf("%-3c", brd->b2d[j][i]);
		}
		printf("\n");
	}
	printf("************************\n");
}


void test(void){

}
