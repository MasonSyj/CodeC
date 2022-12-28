#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct ListNode {
   int val;
   struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode* init(int val){
   struct ListNode* head = (struct ListNode*)calloc(1, sizeof(struct ListNode));
   head->val = val;
   return head;
}

struct ListNode* insert(struct ListNode *head, int val){
   while (head->next){
      head = head->next;
   }
   head->next = (struct ListNode*)calloc(1, sizeof(struct ListNode));
   head->next->val = val;
   return head;
}

void print(struct ListNode* head){
   while (head){
      printf("%d  ", head->val);
      head = head->next;
   }
   printf("\n-------separate line-------\n");
}

struct ListNode* removeElements(struct ListNode* head, int val){
    ListNode* new = (ListNode*)calloc(1, sizeof(ListNode));
    ListNode* newhead = new;
    while (head){
        if (head->val != val){
            if (new == NULL){
               new = (ListNode*)calloc(1, sizeof(ListNode));
            }
            new->val = val;
            new = new->next;
        }
        head = head->next;
    }

    return newhead;
}

int main(void) {
   ListNode* l = init(1);
   insert(l, 2);
   insert(l, 6);
   insert(l, 3);
   insert(l, 4);
   insert(l, 5);
   insert(l, 6);
   print(l);
   ListNode* newl = removeElements(l, 6);
   print(newl);
}
