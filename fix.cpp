#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// $('#question-app tr .text-success').closest('tr').remove()
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

TreeNode* wr(string s) {
    s = s.substr(1, s.size() - 2);
    stringstream ss(s);
    string temp;
   
    vector<TreeNode*> v;   
    while(getline(ss, temp, ',')) {
        if(temp == "null") {
            v.push_back(NULL);
        } else {
            v.push_back(new TreeNode(stoi(temp)));
        }
    }
 
    int index = 0;
    queue<TreeNode*> q{{v.front()}};
    int N = v.size();
    while(!q.empty() && index + 1 < N) {
        int level_size = q.size();
        for(int i = 0; i < level_size; i++) {
            TreeNode* top = q.front();
            top -> left = index + 1 < N ? v[++index] : NULL;
            top -> right = index + 1 < N ? v[++index] : NULL;
            if(top -> left != NULL) q.push(top -> left);
            if(top -> right != NULL) q.push(top -> right);
            q.pop();
        }
    }
    preorder(v.front()); cout << endl;
    return v.front();
}

void fix(string arr) {
    replace(arr.begin(), arr.end(), '[', '{');
    replace(arr.begin(), arr.end(), ']', '}');
    cout << arr << endl;
}

template <typename T>
void print(vector<T> v) {
    for(auto e: v) cout << e << ' ';
    cout << endl;
}

template <typename T> 
void print2(vector<vector<T>> v) {
    for(auto v2: v) print(v2);
}

int main() {
    fix("[[-6,9],[1,6],[8,10],[-1,4],[-6,-2],[-9,8],[-5,3],[0,3]]");
    TreeNode* root = wr("[1,2,3,4,null,2,4,null,null,4]");
    return 0;
}

