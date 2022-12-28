#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
   int val;
   struct ListNode *next;
};

bool hasCycle(struct ListNode *head) {
   struct ListNode* defaultt = (struct ListNode*)calloc(1, sizeof(struct ListNode));
   struct ListNode* temp;
   while (head){
       if (head == defaultt){
           return true;
       }
       temp = head;
       head = head->next;
       temp = defaultt;
       
       printf("%d\n", head->val);
   }
   return false;
}

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

int main(void) {
   struct ListNode* l1 = init(3);

   struct ListNode* temp1;
   struct ListNode* temp2;
   temp1 = insert(l1, 2);
   insert(l1, 0);
   temp2 = insert(l1, -4);
   insert(l1, 5);
   temp2->next = temp1;

   printf("cycle or not: %d\n", hasCycle(l1));
}
