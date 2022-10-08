#include <stdio.h>
#include <stdbool.h>

bool fibword_subs(int n);
void test();

int main(void){
	test();
}

bool fibword_subs(int n){
	bool a[2 * n];
	a[0] = 0;
	int i = 0;
	int cnt = 0;
	while (cnt < n){
		if (a[cnt] == 0){
			a[++i] = 1;
			a[++i] = 0;
		}else if (a[cnt] == 1){
			a[++i] = 0;
		}
		cnt++;
	}
	for (int x = 0; x <= i; x++){
		printf("%d  ", a[x]);
	}
	return a[i];
}

void test(){
	fibword_subs(20);
}
