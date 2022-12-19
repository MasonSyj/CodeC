#include <stdio.h>
#include <stdlib.h>
// * Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode head = {.next = NULL}, *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    head.next = node;
    while(l1&& l2){
        node->val = l1->val + l2->val;
        if (l1->next || l2->next){
            node->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        }
        node = node->next;
//        node->next = NULL;
        l1 = l1->next;
        l2 = l2->next;
        
    }
    if (l1){
        node->val = l1->val;
        node->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        node = node->next;
        node->next = NULL;
    }else if (l2){
        node->val = l2->val;
        node->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        node = node->next;
        node->next = NULL;
    }
    
    node = head.next;
    while (node->next){
        if (node->val >= 10){
            node->val -= 10;
            node->next->val++;
        }
        node = node->next;
    }
    return head.next;
}

