/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
   struct ListNode* start = head;
   int length = 0;
   while(head){
       length++;
       head = head->next;
   }
   if (length == 1 && n == 1){
      return NULL;
   }else if (length == n){
       return start->next;
   }
    
   head = start;
   int kth = length - n;
   int i = 1;
   while(i++ < kth){
       head = head->next;
   }
    
   head->next = head->next->next;
   return start;
}