/*
589. N-ary Tree Preorder Traversal
Given an n-ary tree, return the preorder traversal of its nodes' values.
 

For example, given a 3-ary tree:


 

Return its preorder traversal as: [1,3,5,6,2,4].
 

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2018-07-14
    Runtime: 52 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> preorder(Node* root) {
        if(root == NULL) return {};
        stack<Node*> stk;
        stk.emplace(root);
        vector<int> res;
        
        while(!stk.empty()) {
            Node* curr = stk.top();
            stk.pop();
            res.push_back(curr->val);
            for(int i = curr->children.size() - 1; i >= 0; i--) {
                if(curr->children[i]) stk.push(curr->children[i]);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
