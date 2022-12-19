#include <stdio.h>

int sizecalu(int i, int j, int* a);
int maxArea(int* a, int heightSize);

int main(void){
    int height[9] = {1,8,6,2,5,4,8,3,7};

    int x = maxArea(height, 9);
    printf("%d\n", x);

}

int maxArea(int* height, int heightSize){
    
    int i = 0, j = heightSize - 1;
    int h = height[i]>height[j]?height[j]:height[i];
    int max = (j - 1) * h;
    while (i < j){
        if (height[i] > height[j]){
            j--;
        }else {
            i++;
        }
        int this = sizecalu(i, j, height);
        max = max>this?max:this;
    }
    
    return max;
}

int sizecalu(int i, int j, int* a){
    int height;
    if (a[i] > a[j]){
        height = a[j];
    }else{
        height = a[i];
    }
    int value = (j - i) * height;
    return value;
}
