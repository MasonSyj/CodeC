#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * addBinary(char * a, char * b){
    int len = strlen(a)>=strlen(b)?strlen(a):strlen(b);
    char* s = (char*)malloc((len + 2) * sizeof(char));
    strcpy(s, "");
    s[len+1] = '\0';
    int la = strlen(a) - 1;
    int lb = strlen(b) - 1;
    while (la >= 0 && lb >= 0){
        s[len--] = a[la--] + b[lb--] - '0';
    }
    while (la >= 0){
        s[len--] = a[la--];
    }
    while (lb >= 0){
        s[len--] = b[lb--];
    }
    
    s[0] = '0';
    
    len = strlen(a)>=strlen(b)?strlen(a):strlen(b);
    while (len > 0){
        if (s[len] == '2'){
            s[len] = '0';
            s[len-1]++;
        }else if (s[len] == '3'){
            s[len] = '1';
            s[len-1]++;
        }
        len--;
    }
    
    if (s[0] == '0'){
        return s+1;
    }
    else{
        return s;
    } 
}

int main(void){
    char* s = addBinary("01", "10");
//  puts(s);
}
