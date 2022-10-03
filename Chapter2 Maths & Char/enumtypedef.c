#include <stdio.h>
#include <assert.h>

enum day{mon, tue, wed, thu, fri, sat, sun};
typedef enum day day;

day find_next_day(day d);

int main(void){
	assert(find_next_day(sun) == mon);
	assert(find_next_day(mon) == tue);
	assert(find_next_day(thu) == fri);
	assert(find_next_day(fri) == sat);	
}

day find_next_day(day d){
	day next_day;
	switch(d){
		case sun:
			next_day = mon; break;
		case mon:
			next_day = tue; break;
		case tue:
			next_day = wed; break;
		case wed:
			next_day = thu; break;
		case thu:
			next_day = fri; break;
		case fri:
			next_day = sat; break;
		case sat:
			next_day = sun; break;
		defualt:
			printf("I wasn't expecting that! \n");
	}
	return next_day;
}
