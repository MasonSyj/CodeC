#include <stdio.h>
#include <assert.h>

void timeDifference(int h1, int m1, int h2, int m2);

int main(void){
	timeDifference(23, 00, 04, 15);
	timeDifference(23, 40, 22, 50);
}

void timeDifference(int h1, int m1, int h2, int m2){
	int h3 = h2 - h1;
	if (h3 < 0){
		h3 += 24;
	}
	
	int m3 = m2 - m1;
	if (m3 < 0){
		m3 += 60;
		h3 -=1;
	}

	printf("%02d:%02d\n", h3, m3);
}


// 10:15 12:30
// 2:15 21:45
