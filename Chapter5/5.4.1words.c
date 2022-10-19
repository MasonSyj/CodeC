#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 3000
#define COL 10


int binarysearch_it(char arr[][COL], char* str, int l, int r);
int binarysearch_recur(char arr[][COL], char* str, int l, int r);
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

   int x0 = binarysearch_it(arr, "tofu", 0, cnt);
   int x1 = binarysearch_it(arr, "like", 0, cnt);
   int x2 = binarysearch_it(arr, "labs", 0, cnt);
   printf("x0 = %d, x1 = %d, x2 = %d\n", x0, x1, x2);

   int y0 = binarysearch_recur(arr, "tofu", 0, cnt);
   int y1 = binarysearch_recur(arr, "like", 0, cnt);
   int y2 = binarysearch_recur(arr, "labs", 0, cnt);
   printf("y0 = %d, y1 = %d, y2 = %d", y0, y1, y2);

   fclose(fp);
   return EXIT_SUCCESS;
}

int binarysearch_recur(char arr[][COL], char* str, int l, int r){
  int middle = (l + r) / 2;
  if (strcmp(str, arr[middle]) == 0){
    return middle;
  }else if (strcmp(str, arr[middle]) < 0){
    return binarysearch_recur(arr, str, l, middle - 1);
  }else if (strcmp(str, arr[middle]) > 0){
    return binarysearch_recur(arr, str, middle + 1, r);
  }
  return -1;
}

int binarysearch_it(char arr[][COL], char* str, int l, int r){
  int middle;
  while (l <= r){
    middle = (l + r) / 2;
    if (strcmp(str, arr[middle]) == 0){
      return middle;
    }
    else if (strcmp(str, arr[middle]) < 0){
      r = middle - 1;
    }else if (strcmp(str, arr[middle]) > 0){
      l = middle + 1;
    }
  }
  return -1;
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
