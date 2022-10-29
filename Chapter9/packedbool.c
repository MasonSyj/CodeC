#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define N 8
#define SCALEFACTOR 2
#define SIZE 1
#define NONE 0b00000000
#define LEASTBIT 0b00000001
#define MOSTBIT 0b10000000
#define ITERTIMES 8
#define ALLONE 0b11111111

typedef struct boolarr{
   char* pack;
   int length;
}boolarr;

typedef enum logicalop {or, and, xor} logicalop;


boolarr* boolarr_init(void);
bool boolarr_print(const boolarr* ba);
boolarr* boolarr_initstr(const char* str);
boolarr* boolarr_clone(const boolarr* ba);
int boolarr_size(const boolarr* ba);
int boolarr_count1s(const boolarr* ba);
bool boolarr_issame(const boolarr* b1, const boolarr* b2);
char* boolarr_tostring(const boolarr* ba);
bool boolarr_free(boolarr* p);
boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l);
void boolarr_set(boolarr* ba, const int n, const bool b);
bool boolarr_get(const boolarr* ba, const int n);
void boolarr_negate(boolarr* ba);

int main(void){

   
   //init function
   boolarr* x = boolarr_init();
   //print 
   boolarr_print(x);
   
   //initstr
   boolarr* y = boolarr_initstr("0111111110000011111"); //1100 0011 1011 1001
   boolarr_print(y);
   //get
   int get = boolarr_get(y, 4);
   printf("getbefore: %d\n", get);
   boolarr_set(y, 4, 0);
   printf("getafter: %d\n", boolarr_get(y, 4));
   
   //clone
   boolarr* z = boolarr_clone(y);
   boolarr_print(z);
   
   //bit size
   int bitsizey = boolarr_size(y);
   printf("bitsize: %d\n", bitsizey);
   
   //count one
   int onecnt = boolarr_count1s(y);
   printf("count1s:%d\n", onecnt);
   
   //issame
   int bool1 = boolarr_issame(y, z);
   printf("bool1: %d\n", bool1);
   int bool2 = boolarr_issame(x, z);
   printf("bool2: %d\n", bool2);
   
   //tostring
   char* str = boolarr_tostring(y);
   puts(str);
   
   //free
   int isfree = boolarr_free(z);
   printf("isfree: %d\n", isfree);
   
   //bitwise
   boolarr* ba1 = boolarr_initstr("1000000000000000000");
   boolarr* ba2 = boolarr_initstr("1100111111111111110");
   char* str1 = boolarr_tostring(ba1);
   char* str2 = boolarr_tostring(ba2);
   puts(str1);
   puts(str2);
   boolarr* result = boolarr_bitwise(ba1, ba2, and);
   boolarr_print(ba1);
   boolarr_print(ba2);
   boolarr_print(result);
   puts(boolarr_tostring(result));
   
   printf("***********************\n");
   //flip
// boolarr* flip1 = boolarr_initstr("1000000000000000000");
   boolarr* flip2 = boolarr_initstr("0000110000");
   boolarr_negate(flip2);
   printf("\n");
   boolarr_print(flip2);
   
   return 0;
}

/* All elements initialised to "0" */
boolarr* boolarr_init(void){
   boolarr* x = (boolarr*)malloc(sizeof(boolarr));
   int size = SIZE;
   x->pack = (char*)calloc(size, sizeof(char));
   x->length = sizeof(x->pack) / N;
   
   int leastbit = LEASTBIT;
   *(x->pack) &= NONE;
   
   return x;
}

bool boolarr_print(const boolarr* ba){
   if (!ba){
      return false;
   }
   int i = 0;
   char* temp = ba->pack;
   
   while(i < ba->length){
      int mostbit = MOSTBIT;
      for (int i = 0; i < ITERTIMES; i++){
         int bitvalue = *temp & mostbit;
         int bit = bitvalue >> (ITERTIMES - i - 1);
         printf("%d", bit);
         mostbit = mostbit >> 1;
      }
      
      temp++;
      i++;
      printf("\n");
   }
   printf("----------------------\n");
   
   return true;
}


/* Create boolarr based on string e.g. "1100 0011 1011 1001" */
boolarr* boolarr_initstr(const char* str){
   int len;
   len = (((double)strlen(str) / N)) + 0.9;

   boolarr* x = (boolarr*)malloc(sizeof(boolarr));
   x->pack = (char*)calloc(len, sizeof(char));
   x->length = len;
   char* temp = x->pack;
   
   int strcnt = 0;
   int l = strlen(str);
   int i = 0;
   while (i < x->length){
      char c;
      for (int j = 0; j < ITERTIMES; j++){
         
         if(strcnt <  l){
            c = *str;
            str++;
            strcnt++;
         }else{
            c = '0';
         }
         
         int bit = c & LEASTBIT;
         int bitvalue = bit << (ITERTIMES - j - 1);
         *(x->pack) |= bitvalue;
         
         
      }
      x->pack++;
      i++;
   }
   x->pack = temp;
   
   return x;
}

/* Return a deep copy */
// or use the memcpy
boolarr* boolarr_clone(const boolarr* ba){
   boolarr* x = (boolarr*)malloc(sizeof(boolarr));
   x->length = ba->length;
   x->pack = (char*)malloc(x->length * sizeof(char));
   memcpy(x->pack, ba->pack, x->length);
   return x;
}
//}
//
/* Get number of bits in array */
int boolarr_size(const boolarr* ba){
// int allcnt = 0;
// int onecnt = 0;
// char* temp = ba->pack;
// for (int i = 0; i < ba->length; i++){
//    int bitcmp = MOSTBIT;
//    for (int j = 0; j < ITERTIMES; j++){
//       allcnt++;
//       int bitvalue = *temp & bitcmp;
//       int bit = bitvalue >> (ITERTIMES - j - 1);
//       if (bit == 1){
//          onecnt = allcnt;
//       }
//       bit = bit >> 1;
//    }
//    temp++;
// }
// return onecnt + 1;
   return (ba->length + 1) * N;
}

/* Return number of bits that are set true */
int boolarr_count1s(const boolarr* ba){
   char* temp = ba->pack;
   int onecnt = 0;
   for (int i = 0; i < ba->length; i++){
      int mostbit = MOSTBIT;
      for (int j = 0; j < ITERTIMES; j++){
         if ((mostbit & (*temp)) > 0){
            onecnt++;
         }
         mostbit = mostbit >> 1;
      }
      temp++;
   }   
   return onecnt;
}

/* Set nth bit on/off */
void boolarr_set(boolarr* ba, const int n, const bool b){
   if (!ba || (ba->length) * N < n - 1){
      return;
   }
   int divisor = (n - 1) / N;
   int mod = (n - 1) % N;
   char* temp = ba->pack;
   temp+=divisor;
   int mostbit = MOSTBIT;
   mostbit = mostbit >> mod;
   *temp = *temp | mostbit;
   *temp = *temp & (mostbit * b);
   return;
   
}
/* Get nth bit */
bool boolarr_get(const boolarr* ba, const int n){
   if (!ba || (ba->length) * N < n - 1){
      return false;
   }
   int divisor = (n - 1) / N;
   int mod = (n - 1) % N;
   char* temp = ba->pack;
   temp+=divisor;
   int mostbit = MOSTBIT;
   mostbit = mostbit >> mod;
   int bit = *temp & mostbit;
   if (bit == 0){
      return false;
   }else{
      return true;
   }
}

/* Return if two arrays are the same (bitwise) */
bool boolarr_issame(const boolarr* b1, const boolarr* b2){
   if (boolarr_size(b1) != boolarr_size(b2)){
      return false;
   }else if (memcmp(b1->pack, b2->pack, b1->length) != 0){
      return false;
   }
   return true;
}
//
/* Store to string - rightmost bit is LSB */
char* boolarr_tostring(const boolarr* ba){
   if (!ba){
      return "";
   }
   int len = boolarr_size(ba);
   int lencnt = 0;
   char* temp = ba->pack;
   
   char* str = (char*)calloc(sizeof(char), len + 2);
   char* strtemp = str;
   for (int i = 0; i < ba->length; i++){
      int mostbit = MOSTBIT;
      for (int j = 0; j < ITERTIMES; j++){
         
         int bitvalue = *temp & mostbit;
         int bit = bitvalue >> (ITERTIMES - j - 1);
         *strtemp = bit + '0';
         strtemp++;
         mostbit = mostbit >> 1;
         lencnt++;
      }
      temp++;
   }
   *strtemp = '\0';
// puts(str);
   return str;
}

/* Flip all bits  */
void boolarr_negate(boolarr* ba){
   char* temp = ba->pack;
   for (int i = 0; i < ba->length; i++){
      int mostbit = MOSTBIT;
      int allone = ALLONE;
      for (int j = 0; j < ITERTIMES; j++){
         int bit = *temp & mostbit;
         if (bit == 0){
            *temp = *temp | mostbit;
            mostbit = mostbit >> 1;
            allone = allone >> 1;
            printf("1");
         }else{
            allone = allone >> 1;
            *temp &= allone;
            mostbit = mostbit >> 1;
            printf("0");
         }
         
      }
      temp++;
   }
}

/* Functions dealing with 2 bitwise-arrays */
/* Must be the same length */
boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l){
   if (boolarr_size(ba1) != boolarr_size(ba2)){
      fprintf(stderr, "2 bitwise-arrays is not same in length");
      exit(EXIT_FAILURE);
   }
   boolarr* x = (boolarr*)malloc(sizeof(boolarr));
   x->pack = (char*)calloc(ba1->length, sizeof(char));
   x->length = ba1->length;
   char* temp = x->pack;
   char* tempba1 = ba1->pack;
   char* tempba2 = ba2->pack;
   if (l == and){
      for (int i = 0; i < ba1->length; i++){
         *temp++ = *tempba1++ & *tempba2++;
      }
   }else if (l == or){
      for (int i = 0; i < ba1->length; i++){
         *temp++ = *tempba1++ | *tempba2++;
      }
   }else if (l == xor){
      for (int i = 0; i < ba1->length; i++){
         *temp++ = *tempba1++ ^ *tempba2++;
      }
   }
   return x;
}

//Clears all space 
bool boolarr_free(boolarr* p){
   if(!p){
      return false;
   }
   free(p->pack);
   free(p);
   return true;
}
