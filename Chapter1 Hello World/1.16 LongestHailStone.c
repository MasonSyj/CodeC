#include <stdio.h>

long HailStone(long n);
long Longest(long max);

int main(void){
	printf("Input maximum number you want end in HailStone. ");
	long n;
	scanf("%ld", &n);
	long k = Longest(n);
	printf("%ld %ld ", k, HailStone(k));
}

long HailStone(long n){
	long length = 0;	
	while (n != 1){	
		if (n % 2 == 0){
			n /= 2;
		}else{
			n = 3 * n + 1;	
		}
		length++;
	}
	return length;
}

long Longest(long max){
	long value = 1;	
	long sequence = 1;
	long i = 1;
	while (i < max){
		if (HailStone(i) > sequence){
			value = i;
			sequence = HailStone(i);
		}
		i++;
	}
	return value;
}
