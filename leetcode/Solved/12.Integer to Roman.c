#include <stdio.h>

void iteration(int num);
char * intToRoman(int num);

char a[20];

int main(void) {
	int num = 3999;
	iteration(num);
	printf("\n");
	puts(intToRoman(58));
}

void iteration(int num){
	while (num != 0){
		if (num >= 1000){
			putchar('M');
			num -= 1000;
		}else if (num >= 900){
			printf("%s", "CM");
			num -= 900;
		}else if (num >= 500){
			putchar('D');
			num -= 500;
		}else if (num >= 400){
			printf("%s", "CD");
			num -= 400;
		}else if (num >= 100){
			putchar('C');
			num -= 100;
		}else if (num >= 90){
			printf("%s", "XC");
			num -= 90;
		}else if (num >= 50){
			putchar('L');
			num -= 50;
		}else if (num >= 40){
			printf("%s", "XL");
			num -= 40;
		}else if (num >= 10){
			putchar('X');
			num -= 10;
		}else if (num == 9){
			printf("%s", "IX");
			num -= 9;
		}else if (num >= 5){
			num -= 5;
		}else if (num == 4){
			printf("%s", "IV");
			num -= 4;
		}else if (num >= 0){
			num--;
			putchar('I');
		}
	}	
}

char * intToRoman(int num){
	char a[20];
	int i = 0;
	while (num != 0){
		if (num >= 1000){
			a[i++] = 'M';
//			putchar('M');
			num -= 1000;
		}else if (num >= 900){
//			printf("%s", "CM");
			a[i++] = 'C';
			a[i++] = 'M';
			num -= 900;
		}else if (num >= 500){
			a[i++] = 'D';
			num -= 500;
		}else if (num >= 400){
//			printf("%s", "CD");
			a[i++] = 'C';
			a[i++] = 'D';
			num -= 400;
		}else if (num >= 100){
			a[i++] = 'C';
//			putchar('C');
			num -= 100;
		}else if (num >= 90){
//			printf("%s", "XC");
			a[i++] = 'X';
			a[i++] = 'C';
			num -= 90;
		}else if (num >= 50){
//			putchar('L');
			a[i++] = 'L';
			num -= 50;
		}else if (num >= 40){
//			printf("%s", "XL");
			a[i++] = 'X';
			a[i++] = 'L';
			num -= 40;
		}else if (num >= 10){
			a[i++] = 'X';
			num -= 10;
		}else if (num == 9){
			a[i++] = 'I';
			a[i++] = 'X';
//			printf("%s", "IX");
			num -= 9;
		}else if (num >= 5){
			a[i++] = 'V';
//			putchar('V');
			num -= 5;
		}else if (num == 4){
			a[i++] = 'I';
			a[i++] = 'V';
//			printf("%s", "IV");
			num -= 4;
		}else if (num >= 0){
			a[i++] = 'I';
			num--;
//			putchar('I');
		}
	}
	
	a[i] = '\0';
	return a;
}
