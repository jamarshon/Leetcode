#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>
 
using namespace std;

#define pii pair<int,int>
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

struct Compare {
    bool operator()(const int& left, const int& right) const { return left < right; }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void preorder(TreeNode* root) {
    if(root == NULL) {
        cout << "NULL ";
        return;
    }
    cout << root -> val << ' ';
    preorder(root -> left);
    preorder(root -> right);
}

// level order
string serialize(TreeNode* node){
    queue<TreeNode*> q;
    q.push(node);
    string res = "";
    while(!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        if(!res.empty()) res += ",";
        res += curr == NULL ? "null" : to_string(curr->val);
        if(curr) {
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return res;
}

TreeNode* deserialize(string s) {
    if(s.front() == '[' && s.back() == ']') s = s.substr(1, s.size() - 2);
    stringstream ss(s);
    string temp;

    vector<TreeNode*> nodes;
    while(getline(ss, temp, ',')) {
        if(temp == "null") nodes.push_back(NULL);
        else nodes.push_back(new TreeNode(stoi(temp)));
    }

    TreeNode* root = nodes[0];
    int N = nodes.size();
    int curr = 0;
    for(int i = 1;  i < N; i += 2) {
        while(curr < N && nodes[curr] == NULL) curr++;
        nodes[curr]->left = nodes[i];
        if(i + 1 < N) nodes[curr]->right = nodes[i+1];
        curr++;
    }
    return root;
}

void fix(string arr) {
    replace(arr.begin(), arr.end(), '[', '{');
    replace(arr.begin(), arr.end(), ']', '}');
    cout << arr << endl;
}

template <typename T>
void print(vector<T> v) { for(auto e: v) cout << e << ' '; cout << endl; }

template <typename T> 
void print2(vector<vector<T>> v) { for(auto v2: v) print(v2); }

/*
void preorder(TreeNode* root)
string serialize(TreeNode* node)
TreeNode* deserialize(string s)
void fix(string arr)
void print(vector<T> v)
void print2(vector<vector<T>> v)
*/

int main() {
    return 0;
}


