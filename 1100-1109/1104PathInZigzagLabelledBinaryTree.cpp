/*
1104. Path In Zigzag Labelled Binary Tree
In an infinite binary tree where every node has two children, the nodes are
labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is
left to right, while in the even numbered rows (second, fourth, sixth,...), the
labelling is right to left.

Given the label of a node in this tree, return the labels in the path from the
root of the tree to the node with that label.

Example 1:

Input: label = 14
Output: [1,3,4,14]

Example 2:

Input: label = 26
Output: [1,2,6,10,26]

Constraints:

  1 <= label <= 10^6
/*
  Submission Date: 2019-09-22
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> pathInZigZagTree(int label) {
    /*
    get the current level, reverse the level and
    divide by two to get the parent
    to reverse a number y around x do 2x-y
    now for level i in a tree [2^i, 2^(i+1)-1] the
    center is (2^i + 2^(i+1)-1)/2 so to reverse a level
    just reverse around the center
    */
    int level = log2(label);
    vector<int> res;
    while (level >= 0) {
      res.push_back(label);
      int flipped = (1 << level) + (1 << (level + 1)) - 1 - label;
      level--;
      label = flipped / 2;
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

int main() { return 0; }
