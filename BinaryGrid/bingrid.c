#include "bingrid.h"
#define DIFF 0.000000001

int counting(board* brd){
	int changemade = 0;
	int line = brd->sz;
	bool newchange = 1;
	int zerocnt, onecnt;
	while (newchange == 1){
		newchange = 0;
		
		for (int i = 0; i < line; i++){
			zerocnt = onecnt = 0;
			for (int j = 0; j < line; j++){
				if (brd->b2d[i][j] == '0'){
					zerocnt++;
				}else if (brd->b2d[i][j] == '1'){
					onecnt++;
				}
			}
			
			if ((zerocnt == line / 2 || onecnt == line / 2) && onecnt + zerocnt != line){
				char fillnumber = '1';
				newchange = 1;
				if (onecnt == line / 2){
					fillnumber = '0';
				}
				
				for (int j = 0; j < line; j++){
					if(brd->b2d[i][j] == '.'){
						brd->b2d[i][j] = fillnumber;
						changemade++;
					}
				}
			}
		}
		
		
		for (int j = 0; j < line; j++){
			zerocnt = onecnt = 0;
			for (int i = 0; i < line; i++){
				if (brd->b2d[i][j] == '0'){
					zerocnt++;
				}else if (brd->b2d[i][j] == '1'){
					onecnt++;
				}
			}
			
			if ((zerocnt == line / 2 || onecnt == line / 2) && onecnt + zerocnt != line){
				char fillnumber = '1';
				newchange = 1;
				if (onecnt == line / 2){
					fillnumber = '0';
				}
				
				for (int i = 0; i < line; i++){
					if(brd->b2d[i][j] == '.'){
						brd->b2d[i][j] = fillnumber;
						changemade++;
					}
				}
			}
		}
			
	}
	printboard(brd);
	return changemade;
}

int oxo(board* brd){
	int changemade = 0;
	int line = brd->sz;
	bool newchange = 1;
	while (newchange == 1){
		newchange = 0;
		for (int i = 0; i < line; i++){
			for (int j = 0; j < line - 2; j++){
				if (brd->b2d[i][j] == brd->b2d[i][j+2] && brd->b2d[i][j] != '.' && brd->b2d[i][j+1] == '.'){
					if (brd->b2d[i][j] == '0'){
						brd->b2d[i][j+1] = '1';
					}else {
						brd->b2d[i][j+1] = '0';
					}
					newchange = 1;
					changemade++;
				}
			}
		}
		
		for (int j = 0; j < line; j++){
			for (int i = 0; i < line - 2; i++){
				if (brd->b2d[i][j] == brd->b2d[i+2][j] && brd->b2d[i][j] != '.' && brd->b2d[i+1][j] == '.'){
					if (brd->b2d[i][j] == '0'){
						brd->b2d[i+1][j] = '1';
					}else {
						brd->b2d[i+1][j] = '0';
					}
					newchange = 1;
					changemade++;
				}
			}
		}
	}
	printboard(brd);
	return changemade;
}

int paris(board* brd){
	int changemade = 0;
	int line = brd->sz;
	bool newchange = 1;
	while (newchange == 1){
		newchange = 0;
		for (int i = 0; i < line; i++){
			for (int j = 0; j < line - 1; j++){
				if (brd->b2d[i][j] == brd->b2d[i][j+1] && brd->b2d[i][j] != '.'){
					
					
					if (j - 1 >= 0 && brd->b2d[i][j-1] == '.'){
						brd->b2d[i][j-1] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}
					
					if (j + 2 < line && brd->b2d[i][j+2] == '.'){
						brd->b2d[i][j+2] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}
				}
			}
		}
		
		for (int j = 0; j < line; j++){
			for (int i = 0; i < line - 1; i++){
				if (brd->b2d[i][j] == brd->b2d[i+1][j] && brd->b2d[i][j] != '.'){
					
					if (i - 1 >= 0 && brd->b2d[i-1][j] == '.'){
						brd->b2d[i-1][j] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}
					
					if (i + 2 < line && brd->b2d[i+2][j] == '.'){
						brd->b2d[i+2][j] = '1' - brd->b2d[i][j] + '0';
						newchange = 1;
						changemade++;
					}
				}
			}
		}
	}
	printboard(brd);
	return changemade;
}

bool str2board(board* brd, char* str){
	
	double x = sqrt(strlen(str));
	printf("strlen = %f\n", x);
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

void printboard(board* brd){
	int x = brd->sz;
	for (int j = 0; j < x; j++){
		for (int i = 0; i < x; i++){
			printf("%-3c", brd->b2d[j][i]);
		}
		printf("\n");
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
	
}
