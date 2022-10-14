#include <stdio.h>

#define N 96;

int isprime(int n);
int isvowel(char c);

int main(void)
{
    char first, second, third;
    int i, j, k, sum, cnt = 0;
    
    for(i=1; i<27; i++){
        for(j=1; j<27; j++){
            for(k=1; k<27; k++){
                
                sum = i + j + k;
                
                if(isprime(sum) == 1){
                    first = i + N;
                    second = j + N;
                    third = k + N;
                    
                    if(first == third && ((isvowel(first) == 1 && isvowel(second) == 0 && isvowel(third) == 1) || \
                    (isvowel(first) == 0 && isvowel(second) == 1 && isvowel(third) == 0))){
                        cnt++;
                        printf("%i  %c%c%c\n", cnt, first, second, third);
                    }
                }
            }
        }
    }
    
    return 0;
}


int isprime(int n)
{
    int i, bool = 1;
    for(i=2; i<=n; i++){
       if(n%i == 0 && i!=n){
            bool = 0;
            return bool;
        }
    }
    return bool;
}

int isvowel(char c)
{
    int bool = 0;
    if(c=='a' || c=='e' ||  c=='i' || c=='o' || c=='u'){
        bool = 1;
    }
    return bool;
}