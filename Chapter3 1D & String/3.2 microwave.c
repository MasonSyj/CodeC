#include <stdio.h>
#include <assert.h>

int main(void){
		int a[3] = {10, 60, 600};
		printf("Type the time required\n");
		int time;
		int num = 0;
		scanf("%d", &time);
		assert(time > 0);
		do{
			if (time >= 600){
				time-=600;
			}else if (time >= 60){
				time-=60;
			}else {
				time-=10;
			}
				num++;
		}while (time >= 0);
		printf("%d", num);
}
