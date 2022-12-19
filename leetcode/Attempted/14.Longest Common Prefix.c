#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int length(char ** strs, int strsSize){
    int length = 1;
    while (1){
        int i = 0;
        for (i = 0; i < strsSize - 1; i++){
            if (strncmp(strs[i], strs[i + 1], length) == 0){
                continue;
            }else{
                break;
            }
        }
        if (i == strsSize - 1){
            length++;
        }else {
            break;
        }
    }
    
    return length - 1;
}

char* longestCommonPrefix(char ** strs, int strsSize){
    int length = 1;
    while (1){
        int i = 0;
        for (i = 0; i < strsSize - 1; i++){
            if (strncmp(strs[i], strs[i + 1], length) == 0){
                continue;
            }else{
                break;
            }
        }
        if (i == strsSize - 1){
            length++;
        }else {
            break;
        }
    }
    
    char* result = (char*)malloc(length * sizeof(char));
    strncpy(result, strs[0], length-1);
    return result;
}

int main(void){
    char* str[] = {"flower", "flour", "flight"};
    int x = length(str, 3);
    char* result = (char*)malloc((x+1) * sizeof(char));
    result = longestCommonPrefix(str, 3);
    printf("%d\n", x);
    puts(result);
}

