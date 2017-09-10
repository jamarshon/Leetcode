/*
297. Serialize and Deserialize Binary Tree
Serialization is the process of converting a data structure or object into 
a sequence of bits so that it can be stored in a file or memory buffer, or 
transmitted across a network connection link to be reconstructed later in 
the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is 
no restriction on how your serialization/deserialization algorithm should 
work. You just need to ensure that a binary tree can be serialized to a 
string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

    1
   / \
  2   3
     / \
    4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a 
binary tree. You do not necessarily need to follow this format, so please 
be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. 
Your serialize and deserialize algorithms should be stateless.
/*
    Submission Date: 2017-09-10
    Runtime: 46 ms
    Difficulty: HARD
*/
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL) {
            return "#,";
        } else {
            string curr = to_string(root -> val) + ",";
            string left = serialize(root -> left);
            string right = serialize(root -> right);
            return curr + left + right;
        }
    }
    
    TreeNode* deserializeHelper(const string& data, int& index) {
        size_t comma_ind = data.find(",", index);
        assert(comma_ind != string::npos);
        
        string curr = data.substr(index, comma_ind - index);
        index = comma_ind + 1;
        
        if(curr == "#") return NULL;
        
        TreeNode* root = new TreeNode(stoi(curr));
        root -> left = deserializeHelper(data, index);
        root -> right = deserializeHelper(data, index);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        return deserializeHelper(data, index);
    }
};

class Codec2 {
public:

    // Encodes a tree to a single string.
    string structure(TreeNode* root) {
        if(root == NULL) return "0";
        return "1" + structure(root -> left) + structure(root -> right);
    }
    
    string values(TreeNode* root) {
        if(root == NULL) return "";
        string curr = to_string(root -> val) + ",";
        string left = values(root -> left);
        string right = values(root -> right);
        return curr + left + right;
        
    }
    string serialize(TreeNode* root) {
        string st = structure(root);
        string val = values(root);
        return st + "," + val;
    }
    
    TreeNode* deserializeHelper(const string& st, stringstream& ss, int& index) {
        if(st[index] == '0') return NULL;
        string temp;
        getline(ss, temp, ',');
        assert(!temp.empty());
        
        TreeNode* curr = new TreeNode(stoi(temp));
        index++;
        curr -> left = deserializeHelper(st, ss, index);
        index++;
        curr -> right = deserializeHelper(st, ss, index);
        
        return curr;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int index = 0;
        
        size_t comma_ind = data.find(",");
        string st = data.substr(0, comma_ind);
        string val = data.substr(comma_ind + 1);
        stringstream ss(val);
        return deserializeHelper(st, ss, index);
    }
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main() {
    return 0;
}