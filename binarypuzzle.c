#include <stdio.h>
#include <stdbool.h>


#define RLINE 6
#define CLINE 6
#define LINE 6

void fillbyadjecentsamecell(char puzzle[][CLINE + 1]);
//void fillbyacrosscell(char puzzle[][CLINE + 1]);
void fillbylinecell(char puzzle[][CLINE + 1]);
void create(char puzzle[][CLINE + 1]);
void show(char puzzle[][CLINE + 1]);

int main(void){
	char puzzle[RLINE][CLINE + 1];
	create(puzzle);
	show(puzzle);
	fillbyadjecentsamecell(puzzle);
	show(puzzle);
	fillbylinecell(puzzle);
	show(puzzle);
	
}

void fillbylinecell(char puzzle[][CLINE + 1]){
	int cnt = 0;
	bool newchange = 1;
	while (newchange == 1){
		newchange = 0;
		for (int i = 0; i < RLINE; i++){
			cnt = 0;
			for (int j = 0; j < CLINE; j++){
				if (puzzle[i][j] == '0' || puzzle[i][j] == '1'){
					cnt++;
				}
			}
			if (cnt == LINE - 1){
				int fillj;
				int sum = 0;
				for (int j = 0; j < CLINE; j++){
					if(!(puzzle[i][j] == ' ')){
						sum += puzzle[i][j] - '0';
					}else{
						fillj = j;
					}
				}
				puzzle[i][fillj] = 3 - sum + '0';
				newchange = 1;
			}	
		}
		
		for (int j = 0; j < CLINE; j++){
			cnt = 0;
			for (int i = 0; i < RLINE; i++){
				if (puzzle[i][j] == '0' || puzzle[i][j] == '1'){
					cnt++;
				}
			}
			if (cnt == LINE - 1){
				int filli;
				int sum = 0;
				for (int i = 0; i < CLINE; i++){
					if(!(puzzle[i][j] == ' ')){
						sum += puzzle[i][j] - '0';
					}else{
						filli = i;
					}
				}
				puzzle[filli][j] = 3 - sum + '0';
				newchange = 1;
			}	
		}
		
		
	}
}

//void fillbyacrosscell(char puzzle[][CLINE + 1]){}


void fillbyadjecentsamecell(char puzzle[][CLINE + 1]){
	bool newchange = 1;
	while (newchange == 1){
		newchange = 0;
		for (int i = 0; i < RLINE; i++){
			for (int j = 0; j < CLINE - 1; j++){
				if (puzzle[i][j] == puzzle[i][j+1] && puzzle[i][j] != ' '){
					if (j - 1 >= 0 && puzzle[i][j-1] == ' '){
						puzzle[i][j-1] = '1' - puzzle[i][j] + '0';
						newchange = 1;
					}
					
					if (j + 2 < CLINE && puzzle[i][j+2] == ' '){
						puzzle[i][j+2] = '1' - puzzle[i][j] + '0';
						newchange = 1;
					}
				}
			}
		}
		
		for (int j = 0; j < CLINE; j++){
			for (int i = 0; i < RLINE - 1; i++){
				if (puzzle[i][j] == puzzle[i+1][j] && puzzle[i][j] != ' '){
					if (i - 1 >= 0 && puzzle[i-1][j] == ' '){
						puzzle[i-1][j] = '1' - puzzle[i][j] + '0';
						newchange = 1;
					}
					
					if (i + 2 < CLINE && puzzle[i+2][j] == ' '){
						puzzle[i+2][j] = '1' - puzzle[i][j] + '0';
						newchange = 1;
					}
				}
			}
		}
	}
	
	
}

void show(char puzzle[][CLINE + 1]){
	printf("\n");
	for (int i = 0; i < RLINE; i++){
		for (int j = 0; j < CLINE; j++){
				printf("%-3c", puzzle[i][j]);
		}
		printf("\n");
	}	
	printf("***************************");
}

void create(char puzzle[][CLINE + 1]){
	//initalisation
	for (int i = 0; i < RLINE; i++){
		for (int j = 0; j < CLINE; j++){
			puzzle[i][j] = ' ';
		}
	}
	
	//table set
	puzzle[0][0] = '1';
	puzzle[1][5] = '1';
	puzzle[2][5] = '1';
	puzzle[4][3] = '1';
	puzzle[5][1] = '1';
	puzzle[0][3] = '0';
	puzzle[1][3] = '0';
	puzzle[1][2] = '0';
	puzzle[2][2] = '0';
	puzzle[2][1] = '0';	
	puzzle[4][1] = '0';	
	puzzle[4][0] = '0';	
	puzzle[5][5] = '0';
	puzzle[5][4] = '0';	
}

