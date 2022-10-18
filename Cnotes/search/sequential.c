#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NOTFOUND -1
#define NUMPEOPLE 6
typedef struct person{
   char* name;
   int age;
}person;

int findAge(const char* name, const person *p, int n);

int main(void){
   person p[NUMPEOPLE] = {{"Ackerby", 21}, {"Bloggs", 25}, {"Chumley", 26}, 
   {"Dalton, 25",}, {"Eggson", 22}, {"Fulton", 41}};
   assert(findAge("Ackerby", p, NUMPEOPLE) == 21);
   assert(findAge("Chumley", p, NUMPEOPLE) == 26);
}

int findAge(const char* name, const person *p, int n){
   for (int i = 0; i < n; i++){
      if (strcmp(name, p[i].name) == 0){
         return p[i].age;
      }
   }
   
   return NOTFOUND;
}
