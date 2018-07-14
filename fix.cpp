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
    else if(s.front() == '{' && s.back() == '}') s = s.substr(1, s.size() - 2);
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* tolist(const vector<int>& v) {
    ListNode* head = NULL, *curr = NULL;
    for(const auto& n: v) {
        if(curr == NULL) {
            curr = new ListNode(n);
            head = curr;
        } else {
            curr->next = new ListNode(n);
            curr = curr->next;
        }
    }

    return head;
}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

struct Hash {
    template <typename T, typename U>
    size_t operator()(const pair<T, U>& p) const {
        size_t seed = 0;
        hash_combine(seed, p.first);
        hash_combine(seed, p.second);
        return seed;
    }
};

template <typename T>
void print(vector<T> v) { for(auto e: v) cout << e << ' '; cout << endl; }

template <typename T> 
void print2(vector<vector<T>> v) { for(auto v2: v) print(v2); }

/*
void preorder(TreeNode* root)
string serialize(TreeNode* node)
TreeNode* deserialize(string s)
void fix(string arr)
ListNode* tolist(const vector<int>& v)
void print(vector<T> v)
void print2(vector<vector<T>> v)
*/

int main() {
    fix("[[-6,9],[1,6],[8,10],[-1,4],[-6,-2],[-9,8],[-5,3],[0,3]]");
    TreeNode* root = deserialize("[1,2,3,4,null,2,4,null,null,4]");
    serialize(root);

    ListNode* temp = tolist(vector<int>{1,2,3,4});
    while(temp) {
        cout << (temp->val) << endl;
        temp = temp->next;
    }
    return 0;
}

