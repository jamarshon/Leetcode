#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// #define pii pair<int,int>
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

struct Compare {
  bool operator()(const int& left, const int& right) const {
    return left < right;
  }
};

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void preorder(TreeNode* root) {
  if (root == NULL) {
    cout << "NULL ";
    return;
  }
  cout << root->val << ' ';
  preorder(root->left);
  preorder(root->right);
}

// level order
string serialize(TreeNode* node) {
  queue<TreeNode*> q;
  q.push(node);
  string res = "";
  while (!q.empty()) {
    TreeNode* curr = q.front();
    q.pop();
    if (!res.empty()) res += ",";
    res += curr == NULL ? "null" : to_string(curr->val);
    if (curr) {
      q.push(curr->left);
      q.push(curr->right);
    }
  }
  return res;
}

TreeNode* deserialize(string s) {
  if (s.front() == '[' && s.back() == ']')
    s = s.substr(1, s.size() - 2);
  else if (s.front() == '{' && s.back() == '}')
    s = s.substr(1, s.size() - 2);
  stringstream ss(s);
  string temp;

  vector<TreeNode*> nodes;
  while (getline(ss, temp, ',')) {
    if (temp == "null")
      nodes.push_back(NULL);
    else
      nodes.push_back(new TreeNode(stoi(temp)));
  }

  TreeNode* root = nodes[0];
  int N = nodes.size();
  int curr = 0;
  for (int i = 1; i < N; i += 2) {
    while (curr < N && nodes[curr] == NULL) curr++;
    nodes[curr]->left = nodes[i];
    if (i + 1 < N) nodes[curr]->right = nodes[i + 1];
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
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* tolist(const vector<int>& v) {
  ListNode *head = NULL, *curr = NULL;
  for (const auto& n : v) {
    if (curr == NULL) {
      curr = new ListNode(n);
      head = curr;
    } else {
      curr->next = new ListNode(n);
      curr = curr->next;
    }
  }

  return head;
}

template <typename T>
void print(vector<T> v) {
  for (auto e : v) cout << e << ' ';
  cout << endl;
}

template <typename T>
void print2(vector<vector<T>> v) {
  for (auto v2 : v) print(v2);
}

/*
void preorder(TreeNode* root)
string serialize(TreeNode* node)
TreeNode* deserialize(string s)
void fix(string arr)
ListNode* tolist(const vector<int>& v)
void print(vector<T> v)
void print2(vector<vector<T>> v)
*/

void f(const vector<string>& s) {
  double s1 = 0;
  double s2 = 0;

  for (const auto& e : s) {
    string f = e.substr(e.find(' ') + 1);
    int ind = f.find('/');

    double x = stod(f.substr(0, ind));
    double y = stod(f.substr(ind + 1));
    cout << x << ' ' << y << endl;
    s1 += x;
    s2 += y;
  }

  cout << "s1= " << s1 << ' ' << s2 << endl;
}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
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

bool IsPrime(int n) {
  if (n < 2) return false;
  for (int i = 2; i <= n / i; i++)
    if (n % i == 0) return false;
  return true;
}

class Solution {
 public:
  vector<int> advantageCount(vector<int>& A, vector<int>& B) {
    typedef pair<int, int> pii;
    int N = A.size();
    vector<int> res(N, -1);
    sort(A.begin(), A.end());

    vector<pii> B2;
    for (int i = 0; i < N; i++) B2.emplace_back(B[i], i);
    sort(B2.begin(), B2.end());

    int i = 0, j = 0;
    unordered_set<int> not_used;
    for (int k = 0; k < N; k++) not_used.insert(k);

    while (i < N) {
      while (i < N && A[i] <= B2[j].first) i++;
      if (i < N) {
        res[B2[j].second] = A[i];
        not_used.erase(i);
        i++;
        j++;
      }
    }

    for (const auto& e : not_used) {
      assert(j < N);
      res[B2[j].second] = A[e];
      j++;
    }
    return res;
  }
};
int main() {
  vector<int> A = {2, 7, 11, 15}, B = {1, 10, 4, 11};

  // {2,11,7,15}
  // vector<int> A = {12,24,8,32}, B = {13,25,32,11};
  // {24,32,8,12}
  Solution s;
  vector<int> v = s.advantageCount(A, B);
  print(v);
  return 0;
}
