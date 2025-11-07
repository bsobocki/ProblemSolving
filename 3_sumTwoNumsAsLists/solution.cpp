#include <iostream>
#include <vector>
#include <utils/utils.hpp>

using namespace std;

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

// Helper functions
ListNode* createList(const vector<int>& nums) {
    if (nums.empty()) return new ListNode(0);
    ListNode* head = new ListNode(nums[0]);
    ListNode* curr = head;
    for (int i = 1; i < nums.size(); i++) {
        curr->next = new ListNode(nums[i]);
        curr = curr->next;
    }
    return head;
}

vector<int> listToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

struct Test {
    vector<int> l1;
    vector<int> l2;
    vector<int> expectedResult;
    
    string getInfo() const {
        return to_string(l1) + " + " + to_string(l2);
    }
};

void runSolution() {
    const vector<Test> tests = {
        {{2,4,3}, {5,6,4}, {7,0,8}},        // 342 + 465 = 807
        {{0}, {0}, {0}},                     // 0 + 0 = 0
        {{9,9,9,9,9,9,9}, {9,9,9,9}, {8,9,9,9,0,0,0,1}}, // 9999999 + 9999 = 10009998
        {{1}, {9,9}, {0,0,1}},              // 1 + 99 = 100
        {{5}, {5}, {0,1}},                  // 5 + 5 = 10
    };

    cout << getResultInfoHeader() << endl;
    for (auto& test : tests) {
        ListNode* l1 = createList(test.l1);
        ListNode* l2 = createList(test.l2);
        ListNode* result = addTwoNumbers(l1, l2);
        vector<int> resultVec = listToVector(result);
        
        cout << getTestResultInfo(test.getInfo(), test.expectedResult, resultVec) << endl;
        
        if (l1 != result && l2 != result)
            deleteList(result);
        deleteList(l1);
        deleteList(l2);
    }
}
