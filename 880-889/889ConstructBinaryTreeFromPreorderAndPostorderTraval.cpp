/*
889. Construct Binary Tree from Preorder and Postorder Traversal
Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

Note:

  1 <= pre.length == post.length <= 30
  pre[] and post[] are both permutations of 1, 2, ..., pre.length.
  It is guaranteed an answer exists. If there exists multiple answers, you can
return any of them.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
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
  /* traverse pre and create nodes from there. the stk represents
  the current path of the tree (ie. from root to node). when the
  stk last value is equal to post[j], it means the tree is done
  so pop stk and increment j until it is no longer so. add the
  pre[i] is either the left or right of the stack depending on
  which is available.
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    vector<TreeNode*> stk;
    stk.emplace_back(new TreeNode(pre[0]));
    for (int i = 1, j = 0; i < pre.size(); i++) {
      while (stk.back()->val == post[j]) {
        j++;
        stk.pop_back();
      }

      TreeNode* curr = new TreeNode(pre[i]);
      if (stk.back()->left == NULL)
        stk.back()->left = curr;
      else
        stk.back()->right = curr;
      stk.emplace_back(curr);
    }

    return stk.front();
  }
};

class Solution2 {
 public:
  TreeNode* f(vector<int>& pre, int a, int b, vector<int>& post, int c, int d,
              unordered_map<int, int>& val_to_post_ind) {
    if (a > b || c > d) return NULL;
    assert(b - a == d - c);

    TreeNode* root = new TreeNode(pre[a]);

    int furthest = -1;
    for (int i = a + 1; i <= b; i++) {
      int ind = val_to_post_ind[pre[i]];
      furthest = max(furthest, ind);
      if (furthest - c == i - (a + 1)) {
        root->left = f(pre, a + 1, i, post, c, furthest, val_to_post_ind);
        root->right =
            f(pre, i + 1, b, post, furthest + 1, d - 1, val_to_post_ind);
        break;
      }
    }

    return root;
  }

  /*
  we traverse from pre i = 1 to N looking for where pre[i] is in post, say it is
  at j. it means every element from 0 to j must be in the tree so keep going
  until the furthest j contains as many elements as i-1. These range must be the
  left sub tree so partition both the pre and post from [1,i] [i+1, N] and [0,
  furthest_j] [furthest_j + 1, N-1]
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    unordered_map<int, int> val_to_post_ind;
    for (int i = 0; i < post.size(); i++) val_to_post_ind[post[i]] = i;
    return f(pre, 0, pre.size() - 1, post, 0, pre.size() - 1, val_to_post_ind);
  }
};

int main() { return 0; }
