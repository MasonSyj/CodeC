#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node{
   int data;
   struct node* next;
   struct node* previous;
}node;

node* add(node* head, int data);
int searchfstart(node* head, int data);
int searchflast(node* head, int data);
int searchkth(node* head, int k);
void removen(node* head, int data);
bool isin(node* head, int data);
int size(node* head);
void mft(node* head, node* n);
void transpose(node* head, node* n);
// void freen(node* n);

int main(void){
   node* head = (node*)malloc(sizeof(node));
   head->data = 0;
   head->next = NULL;
   head->previous = NULL;
   node* lastnode;
   node* nodefour;
   node* nodethree;

   nodethree = add(head, 3);
   nodefour = add(head, 4);
   lastnode = add(head, 5);
   printf("%d\n", searchfstart(head, 3));
   printf("%d\n", searchfstart(head, 4));
   printf("%d\n", searchfstart(head, 5));

   printf("%d\n", searchflast(lastnode, 3));
   printf("%d\n", searchflast(lastnode, 4));
   printf("%d\n", searchflast(lastnode, 5));
   printf("size: %d\n", size(head));
   printf("--------------------------\n");
   printf("%d %d\n", 0, searchkth(head, 0));
   printf("%d %d\n", 1, searchkth(head, 1));
   printf("%d %d\n", 2, searchkth(head, 2));
   printf("--------------------------\n");
   printf("isin test:\n");
   printf("%d\n", isin(head, 3));
   printf("%d\n", isin(head, 4));
   printf("%d\n", isin(head, 6));
   // printf("--------------------------\nmove to front test:\n");
   // mft(head, nodefour);
   // printf("%d %d\n", 0, searchkth(head, 0));
   // printf("%d %d\n", 1, searchkth(head, 1));
   // printf("%d %d\n", 2, searchkth(head, 2));
   printf("--------------------------\ntranspose:\n");
   transpose(head, nodefour);
   printf("%d %d\n", 0, searchkth(head, 0));
   printf("%d %d\n", 1, searchkth(head, 1));
   printf("%d %d\n", 2, searchkth(head, 2));
   printf("--------------------------\nremove test: remove the data 4\n");
   removen(head, 4);
   printf("%d %d\n", 0, searchkth(head, 0));
   printf("%d %d\n", 1, searchkth(head, 1));
   printf("%d %d\n", 2, searchkth(head, 2));

}

// add at the very last of the list, so the last one is the end
node* add(node* head, int data){
   node* n = (node*)malloc(sizeof(node));
   if (!n){
      fprintf(stderr, "node malloc failed");
      exit(EXIT_FAILURE);
   }
   n->data = data;
   n->next = NULL;

   if (head->next == NULL){
      head->next = n;
      n->previous = head;
      return n;
   }

   node* firstnode = head->next;
   while(firstnode->next){
      firstnode = firstnode->next;
   }
   firstnode->next = n;
   n->previous = firstnode;
   return n;
}

int searchfstart(node* head, int data){
   if (!head->next){
      printf("list doesn't contain any node.\n");
      return -1;
   }

   node* probe = head->next;
   int cnt = 0;
   while (probe->next && probe->data != data){
      probe = probe->next;
      cnt++;
   }
   if (probe->data == data){
      return cnt;
   }else{
      printf("list doesn't contain the wanted node.\n");
      return -1;
   }
}

int searchflast(node* tail, int data){
   node* probe = tail;
   int cnt = 0;
   while (probe->previous && probe->data != data){
      probe = probe->previous;
      cnt++;
   }
   if (probe->data == data){
      return cnt;
   }else{
      printf("list doesn't contain the wanted node.\n");
      return -1;
   }
}

int searchkth(node* head, int k){
   if (k < 0 || (k + 1) > size(head)){
      printf("index %dth doesn't exist.\n", k);
      return -1;
   }
   node* probe = head->next;
   for (int i = 0; i < k; i++){
      probe = probe->next;
   }
   return probe->data;
}
void removen(node* head, int data){
  if (!head->next){
     printf("list doesn't contain any node.\n");
     return;
  }
  node* probe = head->next;
  if (probe->data == data){
     head->next = probe->next;
     probe->next->previous = probe->previous;
     free(probe);
     return;
  }
  while (probe->next){
     if (probe->next->data == data){
        if (probe->next->next == NULL){
           free(probe->next);
           probe->next = NULL;
           return;
        }
        probe->next = probe->next->next;
        free(probe->next->previous);
        probe->next->previous = probe;
        return;
     }
     probe = probe->next;
  }
}
bool isin(node* head, int data){
   if (!head->next){
      printf("list doesn't contain any node.\n");
      return 0;
   }
   node* probe = head->next;
   while (probe->next){
      if (probe->data == data){
         return true;
      }
      probe = probe->next;
   }
   return false;
}

int size(node* head){
   if (!head->next){
      printf("list doesn't contain any node.\n");
      return 0;
   }
   int cnt = 0;
   node* probe = head->next;
   while (probe->next){
      cnt++;
      probe = probe->next;
   }
   return cnt + 1;
}

void mft(node* head, node* n){
   if (n->next == NULL){
      n->previous->next = NULL;
      head->next->previous = n;
      n->next = head->next;
      head->next = n;
      return;
   }
   n->next->previous = n->previous;
   n->previous->next = n->next;
   n->next = head->next;
   head->next = n;
}

void transpose(node* head, node* n){

   if (head->next == n){
      return;
   }else{
      node* first = n->previous->previous;
      node* second = n->previous;
      node* third = n;
      node* fourth = n->next;
      n->previous->previous->next = third;
      n->previous->previous = third;
      n->previous->next = fourth;
      n->previous = first;
      n->next = second;
      if (n->next){
         n->next->previous = second;
      }
   }
}
