/*
109. Convert Sorted List to Binary Search Tree
Given a singly linked list where elements are sorted in ascending order, 
convert it to a height balanced BST.

/*
    Submission Date: 2017-06-11
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode* convertToBST(ListNode* list_node, int n) {
        if(n <= 0) return NULL;
        int mid = n/2;
        ListNode* temp = list_node;
        for(int i = 0; i < mid; i++) {
            temp = temp -> next;
        }
        TreeNode* new_val = new TreeNode(temp -> val);
        TreeNode* right_child = convertToBST(temp -> next, n - mid - 1);
        TreeNode* left_child = convertToBST(list_node, mid);
        new_val -> left = left_child;
        new_val -> right = right_child;
        return new_val;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        ListNode* temp = head;
        int n = 0;
        while(temp) {
            n++;
            temp = temp -> next;
        }
        return convertToBST(head, n);
    }
};

int main() {
    Solution s;
    return 0;
}