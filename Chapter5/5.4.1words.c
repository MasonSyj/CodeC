#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 3000
#define COL 10

void makeway(char arr[][COL], int kth, int last);
void insert(char arr[][COL], char temp[], int last);
void show(char arr[][COL], int cnt);

int main(){
   FILE* fp = fopen("34words.txt", "r");
   if(fp == NULL){
      fprintf(stderr, "Cannot read %s", "word.txt");
      exit(EXIT_FAILURE);
   }

   char arr[ROW][COL];
   int i = 0;
   char c;
   char temp[COL];
   int cnt = 0;
   while ((c = fgetc(fp)) != EOF){
      if (c == '\n'){
         strcpy(arr[cnt], "");
         temp[i] = '\0';
         i = 0;
         cnt++;
         puts(temp);
         insert(arr, temp, cnt);
         strcpy(temp, "");
      }else{
         temp[i++] = c;
      }
   }
   printf("------------\n");
   show(arr, cnt);

   fclose(fp);
   return EXIT_SUCCESS;
}

void insert(char arr[][COL], char temp[], int last){
   int j = 0;
   while (j < ROW - 1){
      if (strcmp(arr[0], "") == 0){
        strcpy(arr[0], temp);
      }
      else if (strcmp(temp, arr[0]) < 0){
         makeway(arr, 0, last);
         strcpy(arr[0], temp);
         return;
      }
      else if (strcmp(temp, arr[j]) > 0 && strcmp(temp, arr[j+1]) < 0){
         makeway(arr, j+1, last);
         strcpy(arr[j+1], temp);
         return;
      }else if (strcmp(temp, arr[j]) > 0 && arr[j+1][0] == '\0'){
         strcpy(arr[j+1], temp);
         return;
      }
      j++;
   }
}

void makeway(char arr[][COL], int kth, int last){
   int j = last;
   while (j >= kth){
     strcpy(arr[j+1], arr[j]);
     j--;
   }
}

void show(char arr[][COL], int cnt){
   for (int j = 0; j < cnt; j++){
      // if (arr[j][0] == '\0'){
      //    return;
      // }
      printf("%s\n", arr[j]);

   }
}
