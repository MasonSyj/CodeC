/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fizzBuzz(int n, int* returnSize){
   char** table = (char**)calloc(n, sizeof(char*));
   *returnSize = n;
   for (int i = 1; i <= n; i++){
      if (i % 3 == 0 && i % 5 == 0){
          table[i - 1] = (char*)calloc(9, sizeof(char));
          strcpy(table[i - 1], "FizzBuzz");
      }else if (i % 3 == 0){
          table[i - 1] = (char*)calloc(5, sizeof(char));
          strcpy(table[i - 1], "Fizz");
      }else if (i % 5 == 0){
          table[i - 1] = (char*)calloc(5, sizeof(char));
          strcpy(table[i - 1], "Buzz");
      }else{
          char str[50];
          sprintf(str, "%d", i);
          int len = strlen(str);
          table[i - 1] = (char*)calloc(len + 1, sizeof(char));
          strcpy(table[i - 1], str);
      }
   }
   return table;
}
