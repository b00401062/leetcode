struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode dummy = {0, head};
    struct ListNode* prevGroupEnd = &dummy;
    struct ListNode* groupStart = head;
    while (TRUE) {
        struct ListNode* groupEnd = prevGroupEnd;
        for (int i = 0; i < k && groupEnd != NULL; i++) {
            groupEnd = groupEnd->next;
        }
        if (groupEnd == NULL) {
            break;
        }
        struct ListNode* nextGroupStart = groupEnd->next;
        struct ListNode* prev = nextGroupStart;
        struct ListNode* curr = groupStart;
        while (curr != nextGroupStart) {
            struct ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        prevGroupEnd->next = groupEnd;
        prevGroupEnd = groupStart;
        groupStart = nextGroupStart;
    }
    return dummy.next;
}
