/*

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
/*
    Submission Date: 2017-05-20
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // O(KN) where K is the number of lists and N is the maximum number of elements in a list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;
        
        while(true) {
            int min_node_ind = -1;
            for(int i = 0, K = lists.size(); i < K; i++) {
                if(lists[i] == NULL) continue;
                if(min_node_ind == -1) {
                    min_node_ind = i;
                } else if(lists[min_node_ind] -> val > lists[i] -> val) {
                    min_node_ind = i;
                }
            }
            
            if(min_node_ind == -1) 
                break;

            current -> next = lists[min_node_ind];
            lists[min_node_ind] = lists[min_node_ind] -> next;

            if(lists[min_node_ind] == NULL) 
                lists.erase(lists.begin() + min_node_ind);

            current = current -> next;
            current -> next = NULL;
        }
        
        ListNode* head = dummy -> next;
        delete dummy;
        return head;
    }
};

int main() {
    Solution s;
    return 0;
}