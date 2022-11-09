#include <stdio.h>
#include <stdbool.h>

#define ROW 3
#define COL 3

void explore(int y, int x, int phone[][COL], int cnt);
void show(int phone[][COL]);

int main(void) {
	int phone[ROW][COL] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	int cnt = 1;
	explore(0, 0, phone, cnt);
}

void explore(int y, int x, int phone[][COL], int cnt){
	phone[y][x] = cnt;
	
	if (cnt == 7){
	   show(phone);
	   return;
	}
	
	if (y + 1 < ROW && phone[y+1][x] == 0){
		explore(y+1, x, phone, ++cnt);
		cnt--;
		phone[y+1][x] = 0;
	}
	
	if (x + 1 < COL && phone[y][x+1] == 0){
		explore(y, x+1, phone, ++cnt);
		cnt--;
		phone[y][x+1] = 0;
	}
	
	
	if (x - 1 >= 0 && phone[y][x-1] == 0){
		explore(y, x-1, phone, ++cnt);
		cnt--;
		phone[y][x-1] = 0;
	}
	
	if (y - 1 >= 0 && phone[y-1][x] == 0){
		explore(y-1, x, phone, ++cnt);
		phone[y-1][x] = 0;
		cnt--;
	}
	
	/*
	if (cnt == ROW * COL) {
		show(phone);
		return;
	}
	
	*/
	
	return;
}

void show(int phone[][COL]){
	for (int j = 0; j < ROW; j++){
		for (int i = 0; i < COL; i++){
			printf("%-3d", phone[j][i]);
		}
		printf("\n");
	}
	printf("************\n");
}
