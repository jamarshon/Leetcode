/*
142. Linked List Cycle II
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?

/*
    Submission Date: 2017-08-02
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle2(ListNode *head) {
        ListNode* slow, *fast;
        slow = fast = head;

        while(fast && fast -> next) {
            fast = fast -> next -> next;
            slow = slow -> next;
            if(fast == slow) {
                break;
            }
        }

        if(!(fast && fast -> next)) return NULL;
        ListNode* temp = slow;
        int cycle_len = 0;
        do {
            temp = temp -> next;
            cycle_len++;
        } while(temp != slow);

        // if a cycle has a length n, then the start is the mth last node when
        // list is unravelled without including duplicates
        ListNode* backward, *forward;
        backward = forward = head;
        for(int i = 0; i < cycle_len; i++) {
            forward = forward -> next;
        }

        while(backward != forward) {
            backward = backward -> next;
            forward = forward -> next;
        }

        return forward;
    }

    ListNode* detectCycle(ListNode* head) {
        ListNode* slow, *fast;
        slow = fast = head;
        while(fast && fast -> next) {
            slow = slow -> next;
            fast = fast -> next -> next;

            // m - distance from start to cycle start
            // n - cycle len
            // k - distance from cycle start to where slow meets fast
            // if d is distance, then fast moved twice as much distance as slow
            // for some positive integers (p and q) slow moved d = m + k + p*n
            // fast moved 2*d = m + k + q*n where p*n and q*n represents number of times
            // it looped the cycle. 2*(m + k + p*n) = m + k + q*n -> m + k = (q - 2*p)*n
            // this means if you pick any node in the cycle and iterate m + k steps, you 
            // will reach the same place and looped the cycle q - 2*p times.
            // if you have fast at where slow met fast (m + k) and have slow at start and 
            // move both one at a time, they will meet at the cycle start because slow will have
            // traveled m while fast will have traveled (q-2*p)*n - k from k which means it is k
            // away from where fast started which is the cycle start 
            if(slow == fast) {
                slow = head;
                while(slow != fast) {
                    slow = slow -> next;
                    fast = fast -> next;
                }

                return slow;
            }
        }

        return NULL;
    }
};

int main() {
    return 0;
}