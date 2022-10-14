#include<stdio.h>

int prime(int a[]);
int search(int key,int a[], int len);

int main()
{
    const int NUM=15,N=96;//2-52 have 15 primes; N is the ASCII value of a-1
    int a[NUM];
    int count=1;
    int vowel[5]={'a','e','i','o','u'};

    prime(a);
    for(int i='a';i<='z';i++){
        if((search(i, vowel, sizeof(vowel)/sizeof(vowel[0])))==1){
            for(int n='a';n<='z';n++){
                if((search(n, vowel, sizeof(vowel)/sizeof(vowel[0])))==0){
                    if(search(i*2+n-N*3, a, (sizeof(a)/sizeof(a[0])))==1){
                        printf("%d %c%c%c\n",count,i,n,i);
                        count++;
                    }
                }
            }
        }else{
            for(int n='a';n<='z';n++){
                if((search(n, vowel, sizeof(vowel)/sizeof(vowel[0])))==1){
                    if(search(i*2+n-N*3, a, (sizeof(a)/sizeof(a[0])))==1){
                        printf("%d %c%c%c\n",count,i,n,i);
                        count++;
                    }
                }
            }
        }
    }

    return 0;
}


int prime(int a[])
{
    const int TLT=52;
    int i=0;
    int jug=1;
    for(int n=2;n<=TLT;n++){
        for(int m=2;m<n;m++){
            if(n%m==0){
                jug=0;
            }
        }
        if(jug==1){
            a[i]=n;
            i++;
        }
        jug=1;
    }
    return *a;
}


int search(int key, int a[], int len)
{
    int ret=0;
    for(int i=0;i<len;i++){
        if(key==a[i]){
            ret=1;
            return ret;
        }
    }

    return ret;
}