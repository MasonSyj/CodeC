#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode head = {.next = NULL}, *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    head.next = node;
    while(l1 && l2){
        node->val = l1->val + l2->val;
        printf("%d  ", node->val);
        node->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        node = node->next;
        node->next = NULL;
        l1 = l1->next;
        l2 = l2->next;
        
    }
    printf("\n");
    if (l1){
        node->val = l1->val;
        node->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        node = node->next;
    }else if (l2){
        node->val = l2->val;
        node->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        node = node->next;
    }
    
    node = head.next;
    while (node){
        printf("%d  ", node->val);
        if (node->val >= 10){
            node->val -= 10;
  //          printf("%d  ", node->val);
            node->next->val++;
        }
        node = node->next;
    }
    return head.next;
}

struct ListNode *makeListFromChars(const char *array, int size) {
    struct ListNode anchor  = { .next = NULL }, *curr = &anchor;

    for(int i = 0; i < size; i++) {
        curr = curr->next = malloc(sizeof(struct ListNode));
        //Creating lists and adding data is a separate function.
        curr->val = array[i];
        curr->next = NULL;
    }
    return anchor.next;
}

void printList(struct ListNode *p) {
    for(; p; p = p->next)
        printf("%d ", p->val);
    printf("\n");
}

int main(void){
    char lista1[9] = {4,5,2,2,9,3,8,9,2};
    char lista2[9] = {0,7,6,1,6,5,0,6,7};
    struct ListNode *l1 = makeListFromChars(lista1, 9);
    struct ListNode *l2 = makeListFromChars(lista2, 9);

    printList(l1);
    printList(l2);

    struct ListNode *answer = addTwoNumbers(l1, l2);
    printList(answer);
    //freeList(l1);freeList(l2);freeList(answer);
    return 0;
} 

