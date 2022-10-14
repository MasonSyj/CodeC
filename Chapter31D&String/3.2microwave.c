#include <stdio.h>
#include <assert.h>

typedef enum time{ten_min = 600, one_min = 60, ten_sec = 10} time;

int main(void){
		printf("Type the time required\n");
		int time;
		int num = 0;
		scanf("%d", &time);
		assert(time > 0);
		do{
			if (time >= ten_min){
				time-=ten_min;
			}else if (time >= one_min){
				time-=one_min;
			}else {
				time-=ten_sec;
			}
				num++;
		}while (time >= 0);
		printf("Number of button presses = %d", num);
}
