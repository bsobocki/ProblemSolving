#include <iostream>

/**
 * Definition for singly-linked list.
 * */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1->val == 0 && !l1->next) return l2;
    if (l2->val == 0 && !l2->next) return l1;

    int moved = 0;
    ListNode* lsum = new ListNode();
    ListNode* lsumNode = lsum;
    do {
        int l1val = l1 ? l1->val : 0;
        int l2val = l2 ? l2->val : 0;
        int sum = l1val + l2val + moved;
        if (sum >= 10) {
            sum -= 10;
            moved = 1;
        }
        else {
            moved = 0;
        }
        lsumNode->val = sum;

        l1 = l1 ? l1->next : l1;
        l2 = l2 ? l2->next : l2;

        if (moved || l1 || l2) {
            lsumNode->next = new ListNode();
            lsumNode = lsumNode->next;
        }
        else break;
    } while (true);

    return lsum;
}

void runSolution() {
    std::cout << "TODO: ADD SOME TESTS" << std::endl;
}