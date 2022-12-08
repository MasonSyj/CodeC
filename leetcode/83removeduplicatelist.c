#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

struct ListNode {
   int val;
   struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head);

int main(void) {
	
}

struct ListNode* deleteDuplicates(struct ListNode* head){
   bool value[201] = {0};
   struct ListNode* temp;
   struct ListNode* temphead = head;
   while (head){
       if (value[head->val + 100] == false){
           value[head->val + 100] = true;
           temp = head;
           head = head->next;
       }else{
           do{
               head = head->next;
           }while (head && value[head->val + 100] == true);
           temp->next = head;
           temp = head;
       }
   }
   return temphead;
}
