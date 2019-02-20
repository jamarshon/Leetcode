/*
449. Serialize and Deserialize BST
Serialization is the process of converting a data structure or object into a
sequence of bits so that it can be stored in a file or memory buffer, or
transmitted across a network connection link to be reconstructed later in the
same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is
no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary search tree can be serialized to a string
and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your
serialize and deserialize algorithms should be stateless.
/*
  Submission Date: 2019-02-20
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
  /*
  normally store preorder with null but since its bst, a preorder
  without null is enough as the bst property determines whether
  a node is a left child or right child.
  */
  TreeNode* deserializeHelper(const string& data, int& i, const int& l,
                              const int& r) {
    size_t comma_ind = data.find(",", i);
    if (comma_ind == string::npos) return nullptr;
    int val = stoi(data.substr(i, comma_ind - i));
    // if outside bound, this node shouldn't be here
    if (val < l || val > r) return nullptr;
    i = comma_ind + 1;
    TreeNode* node = new TreeNode(val);
    node->left = deserializeHelper(data, i, l, val);
    node->right = deserializeHelper(data, i, val, r);
    return node;
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    if (!root) return "";
    return to_string(root->val) + "," + serialize(root->left) +
           serialize(root->right);
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int i = 0;
    return deserializeHelper(data, i, INT_MIN, INT_MAX);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() { return 0; }
