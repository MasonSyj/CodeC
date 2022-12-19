#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

int myAtoi(char * s);

int main(void){
//  char s1[] = "-91283472332";
//  int x1 = myAtoi(s1);
//  printf("%d\n",x1);
//  
//  char s2[] = "    -42";
//  int x2 = myAtoi(s2);
//  printf("%d\n",x2);
//  
//  
//  char s3[] = "words and 987";
//  int x3 = myAtoi(s3);
//  printf("%d\n",x3);
    
    char s4[] = "+";
    int x4 = myAtoi(s4);
    printf("%d\n",x4);
}

int myAtoi(char * s){
    long sum = 0;
    bool spaceflag = 0;
    bool minusflag = 1;
    bool minusapper = 0;
    bool digitapper = 0;
    while (*s){
        while (s[0] == ' '){
            spaceflag = 1;
            s++;
        }
        
        if (*s == '-'){
            minusflag = 0;
            minusapper = 1;
            s++;
        }else if (*s == '+'){
            minusflag = 1;
            minusapper = 1;
            s++;
        }
        
        if ((*s == '-' || *s == '+') && minusapper == 1){
            return 0;
        }
        
        
        if(isalpha(*s) || *s == ' ' || *s == '.'){
            break;
        }
        
        while (*s >= '0' && *s <= '9'){
            sum = sum * 10 + (*s - '0');
            if (sum > pow(2, 31) - 1){
                break;
            }
            s++;
            digitapper = 1;
        }
        
        if (digitapper){
            break;
        }
        
    }
    if (minusflag == 0){
        sum = -sum;
    }
    
    if (sum < -1 * pow(2,31)){
        return -1 * pow(2,31);
    }else if (sum > pow(2, 31) - 1){
        return pow(2, 31) - 1;
    }
    
    return sum;
}


