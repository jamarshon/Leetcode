/*
590. N-ary Tree Postorder Traversal
Given an n-ary tree, return the postorder traversal of its nodes' values.
 

For example, given a 3-ary tree:


 

Return its postorder traversal as: [5,6,3,2,4,1].
 

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2018-07-13
    Runtime: 44 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>
#include <tuple>
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
  vector<int> postorder(Node* root) {
    if (root == NULL) return {};
    stack<pair<int, Node*>> stk;
    stk.emplace(0, root);
    vector<int> res;

    int ind;
    Node* curr;
    while (!stk.empty()) {
      tie(ind, curr) = stk.top();
      stk.pop();
      if (ind == curr->children.size()) {
        res.push_back(curr->val);
      } else {
        stk.emplace(ind + 1, curr);
        if (curr->children[ind]) stk.emplace(0, curr->children[ind]);
      }
    }

    return res;
  }
};

int main() { return 0; }
