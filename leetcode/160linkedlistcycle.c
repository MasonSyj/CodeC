/**
 * Definition for singly-linked list.
 *struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdlib.h>
struct ListNode {
   int val;
   struct ListNode *next;
};
typedef struct ListNode ListNode;
#define SIZE 1000
#define SCALEFACTOR 3

typedef struct set{
   ListNode* list;
   int size;
   int usage;
}set;

set* nodeset = (set*)calloc(1, sizeof(set));
nodeset->list = (ListNode*)calloc(SIZE, sizeof(ListNode));
nodeset->size = SIZE;

ListNode* insert(ListNode* this){
    for (int i = 0; i < nodeset->usage; i++){
       this == nodeset->list[i];
       return this; 
    }
    ListNode* temp = NULL;
    nodeset->list[nodeset->usage++] = this;
    if (nodeset->usage == nodeset->size){
        nodeset->list = (ListNode*)realloc(nodeset->list, sizeof(ListNode) * nodeset->size * SCALEFACTOR);
        nodeset->size *= SCALEFACTOR;
    }
    return temp;
}


ListNode* detectCycle(ListNode* head) {
    while (head){
        ListNode* ret = insert(head);
        if (ret == head){
            return head;
        }
        head = head->next;
    }
    return head;
}

int main(void){

}
