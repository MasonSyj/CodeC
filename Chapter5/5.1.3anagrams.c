#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#define ROW 371000
#define COL 10

bool isana(char* a, char* b, char* c);
int counting(char* str);
// insert a word into a list
void insert(char arr[][COL], char temp[], int last);
// print all words from an array
void show(char arr[][COL], int cnt);
// insert element into an array and have to shift each elment one position back
void makeway(char arr[][COL], int kth, int last);
// control function for a word to split up two words.
void pairsctrl(char* word, char arr[][COL]);
// split the word into two words
void pair(int left, int right, char* word, char arr[][COL]);

int main(void){
   FILE* fp = fopen("words_alpha.txt", "r");
   if(fp == NULL){
     fprintf(stderr, "Cannnot read %s", "words_alpha.txt");
     exit(EXIT_FAILURE);
   }

   char arr[ROW][COL];
   char temp[COL];

   int cnt = 0;
   while (fgets(temp, COL, fp) != NULL){
      int length = strlen(temp);
      temp[length - 1] = '\0';
      insert(arr, temp, cnt++);
   }
   show(arr, cnt);
   char word[] = "compiler";
   pairsctrl(word, arr);
}

void pairsctrl(char* word, char arr[][COL]){

   int length = strlen(word);

   if (length <= 3){
      return;
   }else{
      int l = 2;
      int r = length - l;
      while (l <= r){
         pair(l++, r--, word, arr);
      }
   }
}

void pair(int left, int right, char* word, char arr[][COL]){
   for (int l = 0; l < ROW; l++){
     for (int r = ROW - 1; r >= l; r--){
        if (arr[l] && arr[r]){
          if (counting(arr[l]) + counting(arr[r]) == counting(word)){
             if (strlen(arr[l]) + strlen(arr[r]) == strlen(word)
             && (int)strlen(arr[l]) == left && (int)strlen(arr[r]) == right
             && isana(arr[l], arr[r], word)){
                printf("%s%s\n", arr[l], arr[r]);
             }
           }
        }
     }
   }
}


void insert(char arr[][COL], char temp[], int last){
   int j = 0;
   while (j < ROW - 1){
      if (strcmp(arr[0], "") == 0){
        strcpy(arr[0], temp);
        return;
      }
      else if (counting(temp) <= counting(arr[0])){
         makeway(arr, 0, last);
         strcpy(arr[0], temp);
         return;
      }
      else if (counting(temp) > counting(arr[j]) && counting(temp) <= counting(arr[j+1])){
         makeway(arr, j+1, last);
         strcpy(arr[j+1], temp);
         return;
      }else if (counting(temp) > counting(arr[j]) && arr[j+1][0] == '\0'){
         strcpy(arr[j+1], temp);
         return;
      }
      j++;
   }
}

int counting(char* str){
   int i = 0;
   int n = strlen(str);
   int count = 0;
   while(i < n){
     count += str[i++] - 'a' + 1;
   }
   return count;
}

void makeway(char arr[][COL], int kth, int last){
   int j = last;
   while (j >= kth){
     strcpy(arr[j+1], arr[j]);
     j--;
   }
}

bool isana(char* a, char* b, char* c){
   int lengtha = strlen(a);
   int lengthb = strlen(b);
   int lengthc = strlen(c);
   int indexleft[26] = {0};
   int indexright[26] = {0};
   for (int i = 0; i < lengtha; i++){
      indexleft[a[i] - 'a']++;
   }

   for (int i = 0; i < lengthb; i++){
      indexleft[b[i] - 'a']++;
   }

   for (int i = 0; i < lengthc; i++){
      indexright[c[i] - 'a']++;
   }

   for (int i = 0; i < 26; i++){
      if (indexleft[i] == indexright[i]){
         continue;
      }
      else{
         return false;
      }
   }
   return true;
}

void show(char arr[][COL], int cnt){
   for (int j = 0; j < cnt; j++){
      printf("%s %d\n", arr[j], counting(arr[j]));

   }
}
