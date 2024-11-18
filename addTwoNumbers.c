#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* listNodeInit(int val, struct ListNode* next) {
    struct ListNode* self = malloc(sizeof(struct ListNode));
    self->val = val;
    self->next = next;
    return self;
}

struct ListNode* addTwoNumbersRecursively(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL) {
        return l2;
    } else if (l2 == NULL) {
        return l1;
    } else {
        return listNodeInit(
            l1->val + l2->val,
            addTwoNumbersRecursively(l1->next, l2->next)
        );
    }
}

struct ListNode* carryRecursively(struct ListNode* l) {
    if (l == NULL) {
        return NULL;
    }
    if (l->val >= 10) {
        l->val -= 10;
        if (l->next == NULL) {
            l->next = listNodeInit(0, NULL);
        }
        l->next->val += 1;
    }
    l->next = carryRecursively(l->next);
    return l;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    return carryRecursively(addTwoNumbersRecursively(l1, l2));
}
