/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode ListNode;

ListNode* removeElements(ListNode* head, int val){    
    while (head && head->val == val){
       head = head->next;
    }
    if (!head){
       return head;
    }
    ListNode* temphead = head;
    ListNode* previous = head;
    head = head->next;
    while (head){
       while (head && head->val == val){
           head = head->next;
       }
       previous->next = head;
       previous = head;
       if (head){
          head = head->next;
       }
    }
    return temphead;
}
