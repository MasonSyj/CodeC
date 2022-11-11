#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define CAPACITY 20

typedef struct park{
   char a[CAPACITY][CAPACITY+1];
   struct park* next;
   struct park* previous;
}park;

typedef struct list{
   park* p;
   int parksize;
}list;

char* carlist(park* p);
void movectrl(park* p);
void movecar(park* p, char car);
void cardirctrl(park* p, char car);
void moveVertical(int y1, int y2, int x, park* p);
void moveHorizont(int x1, int x2, int y, park* p);
void add2list(park* p, park* new);
bool samepark(park* p1, park* p2);
park* newpark(park* p);
int parksize(park* p);
void panel(park* p);
void show(park* p);
void test();



int main(void){
   //assert exist
   list* l = (list*)calloc(1, sizeof(struct list));
   assert(l);
   assert(parksize(l->p) == 0);
   //assert exist
   l->p = (park*)calloc(1, sizeof(park));
	l->p->next = NULL;
	l->p->previous = NULL;
   assert(l->p);
   char cmp[CAPACITY][CAPACITY+1];
   for (int i = 0; i < CAPACITY; i++){
      strcpy(cmp[i], "");
   }
// assert(memcmp(l->p->a, cmp, CAPACITY * (CAPACITY + 1)) == 0);
   
   l->parksize = 7;
   strcpy(l->p->a[0], "#.#####");
   strcpy(l->p->a[1], ".BBB..#");
   strcpy(l->p->a[2], "#A....#");
   strcpy(l->p->a[3], "#A....#");
   strcpy(l->p->a[4], "#A....#");
   strcpy(l->p->a[5], "#.....#");
	strcpy(l->p->a[6], "#.....#");
// printf("%d", carnum(l->p, parksize(l)));
// park* p2 = newpark(l->p);
	
	assert(parksize(l->p) == 7);
	
//	park* this = l->p;
//	moveHorizont(1, 3, 1, this);
//	while(this){
//		show(this);
//		this = this->next;
//	}
	

//	panel(l->p);
//	
	int cnt = 10;
	park* this = l->p;
	for (int i = 0; i < cnt; i++){
		show(this);
		movectrl(this);
		this = this->next;
		if (!this){
			return 0;
		}
	}
}


void panel(park* p){
	while(p){
		movectrl(p);
		p = p->next;
	}
}

void movectrl(park* p){
   char* list = carlist(p);
   unsigned int i = 0;
	while (i < strlen(list)){
		cardirctrl(p, list[i]);
		i++;
	}
	free(list);
}

void cardirctrl(park* p, char car){
   int y1 = 0, x1 = 0;
   int y2 = 0, x2 = 0;
	int size = parksize(p) - 1;
   for (int j = 1; j < size; j++){
      for (int i = 1; i < size; i++){
         if (p->a[j][i] == car){
            if (y1 == 0){
               y1 = j;
               x1 = i;
            }else{
               y2 = j;
               x2 = i;
            }
         }
      }
   }
   
   if (y1 == y2){
      moveHorizont(x1, x2, y1, p);
   }else{
		moveVertical(y1, y2, x1, p);
   }
   
}

void moveVertical(int y1, int y2, int x, park* p){
   //move up 
   if (p->a[y1 - 1][x] == '.'){
      if (y1 - 1 == 0){
         park* new = newpark(p);
         for (int j = y1; j <= y2; j++){
            new->a[j][x] = '.';
         }
			add2list(p, new);
      }else{
         park* new = newpark(p);
         for (int j = y1 - 1; j < y2; j++){
            new->a[j][x] = new->a[j+1][x];
         }
         new->a[y2][x] = '.';
			add2list(p, new);
         
      }
   }
   //move down
   if (p->a[y2 + 1][x] == '.'){
      if (y2 + 1 == parksize(p) - 1){
         park* new = newpark(p);         
         for (int j = y1; j <= y2; j++){
            new->a[j][x] = '.';
         }
			add2list(p, new);
      }else{
         park* new = newpark(p);
         for (int j = y2 + 1; j > y1; j--){
            new->a[j][x] = new->a[j-1][x];
         }
         new->a[y1][x] = '.';
			add2list(p, new);
      }
   }
}

void moveHorizont(int x1, int x2, int y, park* p){
	//move left
	if (p->a[y][x1 - 1] == '.'){
		if (x1 - 1 == 0){
			park* new = newpark(p);
			for (int i = x1; i <= x2; i++){
				new->a[y][i] = '.';
			}
			add2list(p, new);
		}else{
			park* new = newpark(p);		
			for (int i = x1 - 1; i < x2; i++){
				new->a[y][i] = new->a[y][i+1];
			}
			new->a[y][x2] = '.';
			add2list(p, new);	
		}
	}
	//move right
	if (p->a[y][x2 + 1] == '.'){
		if (x2 + 1 == parksize(p) - 1){
			park* new = newpark(p);
			for (int i = x2; i >= x1; i--){
				new->a[y][i] = '.';
			}
			add2list(p, new);
		}else{
			park* new = newpark(p);
			for (int i = x2 + 1; i > x1; i--){
				new->a[y][i] = new->a[y][i-1];
			}
			new->a[y][x1] = '.';
			add2list(p, new);
		}
	}
}



void add2list(park* p, park* new){
//	show(new);
	park* parent = p;
	while (parent->previous){
		printf("211 parent = p->previous:%p\n", parent->previous);
		parent = p->previous;
		printf("211 newparent = p->previous:%p\n", parent->previous);
	}
	
	if (!parent){
		parent = p;
	}
	
   while(parent->next){
      if (samepark(p, new) == 0){
			free(new);
         return;
      }
		parent = parent->next;
   }
   parent->next = new;
}

park* newpark(park* p){
   park* new = (park*)malloc(sizeof(park));
   assert(new);
   memcpy(new, p, sizeof(park));
   new->previous = p;
	new->next = NULL;
   return new;
}

bool samepark(park* p1, park* p2){
   int len = strlen(p1->a[0]);
   return memcmp(p1->a, p2->a, len * (len + 1));
}

int parksize(park* p){
	if (!p){
		return 0;
	}
	return strlen(p->a[0]);
}

char* carlist(park* p){
	int cnt = 0;
	bool temp[26] = {0};
	char car[100];
	for (int j = 1; j < parksize(p) - 1; j++){
		for (int i = 1; i < parksize(p) - 1; i++){
			if (isalpha(p->a[j][i]) && temp[p->a[j][i] - 'A'] == 0){
		      temp[p->a[j][i] - 'A'] = 1;
				car[cnt++] = p->a[j][i];
			}
		}
	}
	char* list = (char*)calloc(cnt + 1, sizeof(char));
	
	strncpy(list, car, cnt);
	
	return list;
}

void show(park* p){
	for (int j = 0; j < parksize(p); j++){
		puts(p->a[j]);
	}
	printf("---------------\n");
}

void test(){
	
}