#include<stdio.h>
#include<stdlib.h>

int f(int n);

int main(void){
    printf("Hello world");
    int cnt = 0;
    int MAX = 0;
    for(int i = 1; i < 10; i++){
        int r = f(i);
        if(r > MAX)
            {cnt = i;
            MAX = r;}
    }

    printf("The result is %d have the longest sequence.\n", cnt);
    return 0;

}

int f(int n){
    int i = 0;
    do{
        (i++);
        if(n%2 == 0)
            { n = n/2; }
        else if(n%2 != 0)
            { n = 3*n+1;}
    } while( n != 1 );
    return i;
}