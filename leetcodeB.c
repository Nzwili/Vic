#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Function to get the length of a linked list.
int getListLength(struct ListNode *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

// Function to find the intersection node of two linked lists.
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    // Get the lengths of both lists and their last nodes.
    int lengthA = getListLength(headA);
    int lengthB = getListLength(headB);

    struct ListNode *endA = headA;
    struct ListNode *endB = headB;

    while (endA != NULL && endA->next != NULL) {
        endA = endA->next;
    }
    while (endB != NULL && endB->next != NULL) {
        endB = endB->next;
    }

    // If the last nodes are different, the lists do not intersect.
    if (endA != endB) {
        return NULL;
    }

    // Traverse the longer list by the absolute difference in lengths.
    int diff = abs(lengthA - lengthB);
    struct ListNode *longer = lengthA > lengthB ? headA : headB;
    struct ListNode *shorter = lengthA > lengthB ? headB : headA;
    while (diff > 0) {
        longer = longer->next;
        diff--;
    }

    // Traverse both lists in parallel to find the intersection node.
    while (longer != shorter) {
        longer = longer->next;
        shorter = shorter->next;
    }

    return longer;
}

// Example usage:
int main() {
    // Constructing two intersecting linked lists
    struct ListNode *headA = malloc(sizeof(struct ListNode));
    struct ListNode *node1 = malloc(sizeof(struct ListNode));
    struct ListNode *node2 = malloc(sizeof(struct ListNode));
    struct ListNode *headB = malloc(sizeof(struct ListNode));
    struct ListNode *node3 = malloc(sizeof(struct ListNode));

    headA->val = 1; headA->next = node1;
    node1->val = 2; node1->next = node2;
    node2->val = 3; node2->next = node3;
    node3->val = 6; node3->next = NULL;

    headB->val = 4; headB->next = node3;

    struct ListNode *intersectionNode = getIntersectionNode(headA, headB);

    if (intersectionNode != NULL) {
        printf("Intersection at node with value %d\n", intersectionNode->val);
    } else {
        printf("No intersection found\n");
    }

    // Free memory
    free(headA);
    free(node1);
    free(node2);
    free(headB);
    free(node3);

    return 0;
}
