/*
429. N-ary Tree Level Order Traversal
Given an n-ary tree, return the level order traversal of its nodes' values. (ie, 

For example, given a 3-ary tree:
 


 

We should return its level order traversal:

 

 

[
     [1],
     [3,2,4],
     [5,6]
]


 

Note:


    The depth of the tree is at most 1000.
    The total number of nodes is at most 5000.
/*
    Submission Date: 2018-07-13
    Runtime: 44 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if(root == NULL) return {};
        vector<vector<int>> res;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            int q_size = q.size();
            res.push_back({});
            for(int i = 0; i < q_size; i++) {
                Node* curr = q.front();
                q.pop();
                res.back().push_back(curr->val);
                for(const auto& c: curr->children) {
                    if(c) q.push(c);
                }
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
