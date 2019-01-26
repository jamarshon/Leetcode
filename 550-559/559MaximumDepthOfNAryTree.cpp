/*
559. Maximum Depth of N-ary Tree
Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root
node down to the farthest leaf node.

For example, given a 3-ary tree:
 


 

We should return its max depth, which is 3.

Note:


    The depth of the tree is at most 1000.
    The total number of nodes is at most 5000.

/*
    Submission Date: 2018-07-13
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
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
  int maxDepth(Node* root) {
    if (!root) return 0;

    int res = 0;
    for (const auto& c : root->children) res = max(res, maxDepth(c));

    return res + 1;
  }
};

int main() { return 0; }
