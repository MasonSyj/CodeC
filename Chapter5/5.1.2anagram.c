#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

void swap(char* a, char* b);
void permuatecnt(char a[], int n, FILE* fp);

int main(void){
   FILE* fp = fopen("34words.txt", "r");
   FILE* fp2 = fopen("34words.txt", "r");
   if (!fp){
      fprintf(stderr, "txt failed to access");
      exit(EXIT_FAILURE);
   }
   char str[SIZE];
   while (fgets(str, SIZE, fp) != NULL){
/**      
      if (fgets(str, SIZE, fp) == NULL){
         fprintf(stderr, "cannot access line.");
         exit(EXIT_FAILURE);
      }
*/      
      fp2 = fp;
      int len = strlen(str);
      str[len - 1] = '\0';
      permuatecnt(str, len - 2, fp2);
      printf("next one::\n");
   }
   
   
   fclose(fp);
}

void permuatecnt(char a[], int n, FILE* fp){
   if (n == 0){
      puts(a);
		char str[SIZE];
		while (fgets(str, SIZE, fp) != NULL){
         int len = strlen(str);
         str[len - 1] = '\0';
         if (strcmp(a, str) == 0){
            printf("%s   ", a);
         }
		}
		printf("\n");
		return;
	}
	
	for (int i = n; i >= 0; i--){
		swap(&a[i], &a[n]);
		permuatecnt(a, n - 1, fp);
		swap(&a[i], &a[n]);
	}
}

void swap(char* a, char* b){
	char temp = *a;
	*a = *b;
	*b = temp;
}
