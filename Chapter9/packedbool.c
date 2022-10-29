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

typedef struct boolarr{
   char* pack;
   int length;
}boolarr;


boolarr* boolarr_init(void);
bool boolarr_print(const boolarr* ba);
boolarr* boolarr_initstr(const char* str);
boolarr* boolarr_clone(const boolarr* ba);
int boolarr_size(const boolarr* ba);

int main(void){

   
   //init function
   boolarr* x = boolarr_init();
   //print 
   boolarr_print(x);
   
   //initstr
   boolarr* y = boolarr_initstr("0111111110000011111"); //1100 0011 1011 1001
   boolarr_print(y);
   
   //clone
   boolarr* z = boolarr_clone(y);
   boolarr_print(z);
   
   //bit size
   int bitsizey = boolarr_size(y);
   printf("%d", bitsizey);
   
   
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
   
// for (int i = 0; i < ITERTIMES; i++){
//    *(x->pack) |= leastbit;
//    leastbit = leastbit << 1;
// }
// 
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
//
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
   int allcnt = 0;
   int onecnt = 0;
   char* temp = ba->pack;
   for (int i = 0; i < ba->length; i++){
      int bitcmp = MOSTBIT;
      for (int j = 0; j < ITERTIMES; j++){
         allcnt++;
         int bitvalue = *temp & bitcmp;
         int bit = bitvalue >> (ITERTIMES - j - 1);
         if (bit == 1){
            onecnt = allcnt;
         }
         bit = bit >> 1;
      }
      temp++;
   }
   printf("allcnt: %d\n", allcnt);
   return onecnt + 1;
}

///* Return number of bits that are set true */
//  int boolarr_count1s(const boolarr* ba){
////   int cnt = 0;
//// while(ba->pack){
////    if (*(ba->pack) & 
//// }
// return 1;
//}
//
///* Set nth bit on/off */
//bool boolarr_set(boolarr* ba, const int n, const bool b){
// return true;
//}
///* Get nth bit */
//bool boolarr_get(const boolarr* ba, const   int n, bool* b){
// return true;
//}
//
///* Return if two arrays are the same (bitwise) */
////simply use the memcmp
//bool boolarr_issame(const boolarr* b1, const boolarr* b2){
// return true;
//}
//
///* Store to string - rightmost bit is LSB */
//bool boolarr_tostring(const boolarr* ba, char* str);
//
///* Print out array & meta info */
//
//       
///* Flip all bits */
//bool boolarr_negate(boolarr* ba);
//
///* Functions dealing with 2 bitwise-arrays */
///* Must be the same length */
//boolarr* boolarr_bitwise(const boolarr* ba1, const boolarr* ba2, const logicalop l);

/* Clears all space */
//bool boolarr_free(boolarr* p){
// free(p);
// return true;
//}
