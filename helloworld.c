#include <stdio.h>
#include <assert.h>

int main(void) {
	printf("Hello World.!");
   int x;
   printf("Input a value for x: ");
   assert(scanf("%d", &x) == 1);
   int y = 4;
   x = x + y;
   y = y + 2 * x;
   printf("x: %d, y: %d", x, y);
}
