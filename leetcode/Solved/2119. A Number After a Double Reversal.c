#include <stdbool.h>
#include <assert.h>

bool isSameAfterReversals(int num);

int main(void){
    assert(isSameAfterReversals(121));
    assert(isSameAfterReversals(526));
    assert(!isSameAfterReversals(1800));
    assert(isSameAfterReversals(0));
}

bool isSameAfterReversals(int num){
    int reversed1 = 0;
    int reversed2 = 0;
    int temp = num;
    while (temp > 0){
        reversed1 = reversed1 * 10 + temp % 10;
        temp /= 10;
    }
    
    while (reversed1 > 0){
        reversed2 = reversed2 * 10 + reversed1 % 10;
        reversed1 /= 10;
    }
    
    return num == reversed2;
}
