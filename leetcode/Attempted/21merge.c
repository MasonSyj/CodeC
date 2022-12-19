#include <stdio.h>
#include <stdbool.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 struct ListNode {
   int val;
   struct ListNode *next;
 };

 struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    bool beginning = 0;
    bool end = 0;
    struct ListNode* list1begin = list1;
    struct ListNode* temp;
    while (list2){
      if (!(list1+1)){
        list1->next = list2;
          return list1begin;
      }

      if (list2->val <= list1begin->val){
        temp = list2->next;
        list2->next = list1begin;
      }

      if (list2->val <= list1->next->val && list2->val > list1->val){
        temp = list2->next;
        list2->next = list1->next;
        list1->next = list2;
      }

      list2 = temp;

    }

    return list1begin;
 }

int main(void){
   struct ListNode* list1a;
   struct ListNode* list1b;
   struct ListNode* list1c;
   list1a->val = 1;
   list1b->val = 2;
   list1c->val = 3;
   list1a->next = 1b;
   1b->next = 1c;
   struct ListNode* list2a;
   struct ListNode* list2b;
   struct ListNode* list2c;
   list2a->next = 2b;
   2b->next = 2c;
   list1a->val = 1;
   list1b->val = 2;
   list1c->val = 3;
}
