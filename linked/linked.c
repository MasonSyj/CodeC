#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct person{
   int age;
   char name[20];
   char sex;
   double salary;
   short height;
   struct person* next;
} person;

person* create(int nage, char* nname, char nsex, double nsalary, short nheight);
void printAll(person* p);
void searchbyname(person* p, char* nname);

int main(void){
   person* p1 = create(21, "Mason", 'M', 20000, 180);
   person* p2 = create(25, "Adam", 'M', 22000, 165);
   person* p3 = create(27, "Bob", 'M', 18000, 185);
   person* p4 = create(33, "Charlie", 'F', 25000, 188);
   person* p5 = create(45, "Mary", 'F', 15000, 170);
   p1->next = p2;
   p2->next = p3;
   p3->next = p4;
   p4->next = p5;
   printAll(p1);
   searchbyname(p1, "Bob");
   
}

person* create(int nage, char* nname, char nsex, double nsalary, short nheight){
   person* p = (person*)malloc(sizeof(struct person));
   p->age = nage;
   strcpy(p->name, nname);
   p->sex = nsex;
   p->salary = nsalary;
   p->height = nheight;
   p->next = NULL;
   return p;
}

void printAll(person* p){
   while(p){
      printf("name: %s, age: %d, sex: %c, salary: %f, height: %u\n", p->name, p->age, p->sex, p->salary, p->height);
      p = p->next;
   }
}

void searchbyname(person* p, char* nname){
   while(p){
      if (strcmp(p->name,nname) == 0 ){
         printf("name: %s, age: %d, sex: %c, salary: %f, height: %u\n", p->name, p->age, p->sex, p->salary, p->height);
         return;
      }
      p = p->next;
   }
   return;
}
