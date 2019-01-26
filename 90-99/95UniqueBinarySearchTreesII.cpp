/*
95. Unique Binary Search Trees II
Given an integer n, generate all structurally unique BST's (binary search trees)
that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

/*
    Submission Date: 2017-07-18
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  void labelInorder(TreeNode* curr, int& count) {
    if (curr == NULL) return;

    labelInorder(curr->left, count);
    curr->val = count++;
    labelInorder(curr->right, count);
  }

  void getPreorderSequence(string s, vector<string>& res, int zeros, int ones,
                           int len) {
    if (ones > len / 2) return;

    if (s.size() == len) {
      res.push_back(s);
      return;
    }

    getPreorderSequence(s + '1', res, zeros, ones + 1, len);
    if (ones > zeros) {
      getPreorderSequence(s + '0', res, zeros + 1, ones, len);
    }
  }

  TreeNode* buildFromPreOrder(string seq, int& index) {
    if (seq[index] == '0') {
      index++;
      return NULL;
    }

    TreeNode* curr = new TreeNode(-1);
    index++;
    curr->left = buildFromPreOrder(seq, index);
    curr->right = buildFromPreOrder(seq, index);
    return curr;
  }

  vector<TreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    vector<string> pre_seq;
    getPreorderSequence("", pre_seq, 0, 0, n * 2);

    vector<TreeNode*> res(pre_seq.size());
    transform(pre_seq.begin(), pre_seq.end(), res.begin(),
              [this](const string s) {
                int temp = 0;
                TreeNode* root = buildFromPreOrder(s + "0", temp);
                temp = 1;
                labelInorder(root, temp);
                return root;
              });
    return res;
  }
};

int main() { return 0; }