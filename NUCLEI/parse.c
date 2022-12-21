#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROW 1000
#define COL 100

typedef struct code{
   char word[ROW][COL];
   int currentrow; //current word
}code;

code* this;

void parse();

int main(void) {
   this = (code*)calloc(1, sizeof(code));
   assert(this);
   parse();
}

void literalparse(char** pstr);
void stringparse(char** pstr);
void letterparse(char** pstr);

void parse(){
   FILE* fp = fopen("parse.txt", "r");
   char* str = (char*)calloc(ROW, sizeof(char));
   char* temp = (char*)calloc(ROW, sizeof(char));
   assert(str);
   assert(temp);

   while (fgets(temp, ROW, fp)){
      temp[((int)strlen(temp) - 1)] = '\0';
      strcat(str, temp);
   }
//   puts(str);

   while (*str != '\0'){
      switch (*str){
         case '(': this->word[this->currentrow++][0] = '('; str++; break;
         case ')': this->word[this->currentrow++][0] = ')'; str++; break;
         case '\'': literalparse(&str); break;
         case '"': stringparse(&str); break;
         case ' ':str++; break;
         default: letterparse(&str); break;
      }
   }
   	
   int i = 0;
   while (this->word[i][0] != '\0'){
      puts(this->word[i++]);
   }

}

void literalparse(char** pstr){
   char* str = *pstr;
   int i = 0;
   assert(str[i++] == '\'');
   while (str[i] != '\''){
      i++;
   }
   i++;
   strncpy(this->word[this->currentrow++], str, i);
   *pstr += i;
}

void stringparse(char** pstr){
   char* str = *pstr;
   int i = 0;
   assert(str[i++] == '"');
   while (str[i] != '"'){
      i++;
   }
   strcpy(this->word[this->currentrow], "\\");
   strncat(this->word[this->currentrow], str, i);
   this->word[this->currentrow][i + 1] = '\\';
   this->word[this->currentrow++][i + 2] = '\"';
   *pstr += i + 2;
}

void letterparse(char** pstr){
   char* str = *pstr;
   int i = 0;
   assert(isupper(str[i++]));
   while (isupper(str[i])){
      i++;
   }
   strncpy(this->word[this->currentrow++], str, i);
   *pstr += i;
}
