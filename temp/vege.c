#include <stdio.h>

enum vege {carrot, apple, croc, pea, beet};
typedef enum vege vege;

int main(void){
	vege v1 = carrot;
	vege v2 = pea;
	printf("%d %d", v1, v2);
}
