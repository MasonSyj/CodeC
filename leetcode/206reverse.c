#include <stdio.h>
#include <stdlib.h>

struct ListNode {
   int val;
   struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* reverseList(ListNode* head);

int main(void){
   ListNode* l1 = (ListNode*)calloc(1, sizeof(ListNode));
   l1->val = 1;
   l1->next = (ListNode*)calloc(1, sizeof(ListNode));
   l1->next->val = 2;

   l1->next->next = (ListNode*)calloc(1, sizeof(ListNode));
   l1->next->next->val = 3;
   printf("1th: %p, 2th: %p, 3th: %p\n", l1, l1->next, l1->next->next);

   ListNode* rl1 = reverseList(l1);

   printf("1th: %d, 2th: %d, 3th: %d\n", rl1->val, rl1->next->val, rl1->next->next->val);

}

//temp -> 1 

//temp -> 2 -> 1

//temp -> 3 -> 2 -> 1

ListNode* reverseList(ListNode* head){
   if (head == NULL){
       return head;
   }

   ListNode* temp = (ListNode*)calloc(1, sizeof(ListNode));

   while (head){
      ListNode* oldnext = temp->next;
      temp->next = head;
      ListNode* newnext = temp->next->next;
      temp->next->next = oldnext;
      head = newnext;
//      printf("temp->next address: %p\n", temp->next);
//      printf("head next address: %p\n", head);     
   }

   return temp->next;

}
