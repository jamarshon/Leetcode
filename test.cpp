/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
using namespace std;
#include <iostream>
#include <vector>
#include <string>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    void incrementalReverse(ListNode*& A, ListNode*& B, ListNode*& C) {
        B -> next = A;
        A = B;
        B = C;
        if(C != NULL) {
            C = C -> next;
        }
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k < 0 || head == NULL) return NULL;
        if(k == 1) return head;

        ListNode* newHead = NULL;
        ListNode* A = NULL;
        ListNode* B = head;
        ListNode* C = head -> next;
        ListNode* lastInterval = head;
        ListNode* nextInterval = head;

        int i = k;

        while(i--) {
            if(nextInterval == NULL) {
                return head;
            }
            nextInterval = nextInterval -> next;
        }

        while(true) {
            while(B != nextInterval) incrementalReverse(A, B, C);
            if(newHead == NULL) newHead = A;

            A = nextInterval;
            B = (A == NULL) ? NULL : A -> next;
            C = (B == NULL) ? NULL : B -> next;

            i = k;
            while(i--) {
                if(nextInterval == NULL) {
                    lastInterval -> next = A;
                    return newHead;
                } else {
                     if(i == 0) lastInterval -> next = nextInterval;
                    nextInterval = nextInterval -> next;
                }
            }

            lastInterval = A;
            lastInterval -> next = NULL;
        }
    }
};

int main() {
    Solution s;
    ListNode* head = new ListNode(1);
    ListNode* current = head;

    vector<int> v{2,3,4, 5, 6};
    for(int e : v) {
        ListNode* newNode = new ListNode(e);
        current -> next = newNode;
        current = newNode;
    }
   
    ListNode* b = s.reverseKGroup(head, 3);
    ListNode* current2 = b;
    while(current2 != NULL) {
        cout << current2 -> val << "->";
        current2 = current2 -> next;
    }
    cout << endl;
    return 0;
}