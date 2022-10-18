#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 10
#define COL 20

void makeway(char arr[][COL], int kth);
void insert(char arr[][COL], char temp[]);
void show(char arr[][COL]);

int main(){
   FILE* fp = fopen("word.txt", "r");
   if(fp == NULL){
      fprintf(stderr, "Cannot read %s", "word.txt");
      exit(EXIT_FAILURE);
   }

   char arr[ROW][COL];
   int i;
   i = 0;
   char c;
   char temp[COL];
   while ((c = fgetc(fp)) != EOF){
      if (c == '\n'){
         temp[i] = '\0';
//       puts(temp);
         insert(arr, temp);
         i = 0;
         strcpy(temp, "");
      }else{
         temp[i++] = c;
      }
   }
   printf("------------");
   show(arr);

   fclose(fp);
   return EXIT_SUCCESS;
}

void insert(char arr[][COL], char temp[]){
   int j = 0;
   while (j++ < ROW-1){
      if (strcmp(arr[j], temp) < 0 && strcmp(arr[j+1], temp) > 0){
         makeway(arr, j+1);
         strcpy(arr[j], temp);
         puts(arr[j]);
         return;
      }
   }
}

void makeway(char arr[][COL], int kth){
   for (int j = ROW - 2; j >= kth; j--){
      strcpy(arr[j+1], arr[j]);
   }
}

void show(char arr[][COL]){
   for (int j = 0; j < ROW; j++){
      // if (arr[j][0] == '\0'){
      //    return;
      // }
      printf("%s\n", arr[j]);

   }
}
