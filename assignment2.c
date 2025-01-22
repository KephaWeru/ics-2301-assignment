/*
ICS 2301: Design and Analysis of Algorithms Assignment 2

Kepha Weru          SCT221-0218/2022
Keith Kihara        SCT221-0217/2022
Stephen Githua      SCT221-0668/2022

Design an algorithm to merge two sorted lists that are passed as parameters, and return one merged
sorted list. Derive a recurrence relation for this algorithm. Estimate time and space complexities for
the same algorithm.
*/


#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*) malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next;
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct ListNode* l1 = createNode(1);
    l1->next = createNode(3);
    l1->next->next = createNode(5);

    struct ListNode* l2 = createNode(2);
    l2->next = createNode(4);
    l2->next->next = createNode(6);

    struct ListNode* mergedList = mergeTwoLists(l1, l2);

    printList(mergedList);

    return 0;
}
/*
The recurrence relation for merging two lists can be described as follows:

Let T(n) be the time complexity for merging two lists, where n is the total number of elements in both lists.
At each step, we compare and append an element from one of the lists to the merged list. Since we do this for each element, we have:

T(n)= n

The time complexity of this algorithm is O(n), where n is the total number of elements in the merged list.
This is because each element from both lists is processed exactly once.

The space complexity of this algorithm is O(1) for the merging process itself, as it only uses a constant amount of extra space.
However, if we consider the input and output lists, the total space complexity is O(n), where n is the total number of elements in the merged list.
*/
