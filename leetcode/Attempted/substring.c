#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ALPHANUM 250

int lengthOfLongestSubstring(char * s){
    int result = 0;
    
    
    bool comp[ALPHANUM] = {false};
    
    int length = strlen(s);
    for (int i = 0; i < length; i++){
        if (comp[s[i]] == true){
            int first = 0;
            if (s[first] != s[i]){
                first++;
            }
            int sub = lengthOfLongestSubstring(s + first + 1);
            return (result>sub?result:sub);
        }else{
            comp[s[i]] = true;
            result++;
        }
    }
    return result;
}



int main(void){
    char s[] = "dvcdf";
    int x = lengthOfLongestSubstring(s);
    printf("%d", x);
}