#include <stdio.h>

static inline int min(int a, int b);

int main(void){
	printf("please input two numbers");
	int a,  b;
	scanf("%d %d", &a, &b);
	int x= min(a, b);
	printf("The smaller one is %d\n", x);
}

inline int min(int a, int b){
	int min;
	if (a <= b){
		min = a;
	}else{
		min = b;
	}
	return min;
}
