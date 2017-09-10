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

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <queue>

struct TreeNode {
    int val;
    vector<TreeNode*> children;
    TreeNode(int x) : val(x) {}
};

void preorder(TreeNode* root) {
    if(root == NULL) {
        cout << "null" << endl;
        return;
    }
    cout << (root -> val) << endl;
    for(auto c: root -> children) preorder(c);
}

int longestChain(TreeNode* root, int x) {
    if(root == NULL) return 0;
    if(root -> val == x) {
        int child_chain = 0;
        for(auto c: root -> children) child_chain = max(child_chain, longestChain(c, x));
        return 1 + child_chain;
    }
    
    return 0;
}

/*
longest path of root with val of x is either the longest path in each of its
sub trees or the two longest chain of its subtrees that connect with root and 
have the value of x
*/
typedef priority_queue<int> MaxHeap;
int longestPath(TreeNode* root) {
    if(root == NULL) return 0;
    int res = 1;
    for(auto c: root -> children) res = max(res, longestPath(c));
    
    int x = root -> val;
    MaxHeap max_heap;
    for(auto c: root -> children) max_heap.push(longestChain(c, x));
    
    int M = max_heap.size();
    for(int i = 0; i < min(2, M); i++) {
        res += max_heap.top();
        max_heap.pop();
    }
    
    return res;
}

int solution(vector<int> &A, vector<int> &E) {
    // write your code in C++14 (g++ 6.2.0)
    vector<TreeNode*> nodes;
    for(auto e: A) nodes.push_back(new TreeNode(e));
    
    for(int i = 0; i < E.size(); i += 2) {
        int from = E[i] - 1;
        int to = E[i + 1] - 1;
        nodes[from] -> children.push_back(nodes[to]);
    }
    
    TreeNode* root = nodes[0];
    // preorder(root);
    int longest_path_nodes = longestPath(root);
    return longest_path_nodes - 1;
}

int main() {
    vector<int> a,b;
    a = {1,1,1,2,2};
    b = {1,2,1,3,2,4,2,5};
    cout << solution(a,b) << endl;
    return 0;
}