

int strStr(char * haystack, char * needle){
    char c = *needle;
    int length = strlen(needle);
    int i = 0;
    while (haystack[i]){
        if (haystack[i] == c){
            if (strncmp(haystack + i, needle, length) == 0){
                return i;
            }
        }
        i++;
    }
    return -1;
}