
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
865. Shortest Path to Get All Keys
We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is

We start at the starting point, and one move consists of walking one space in
one of the 4 cardinal directions.  We cannot walk outside the grid, or walk into
a wall.  If we walk over a key, we pick it up.  We can't walk over a lock unless

For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of
the first K letters of the English alphabet in the grid.  This means that there
is exactly one key for each lock, and one lock for each key; and also that the
letters used to represent the keys and locks were chosen in the same order as

Return the lowest number of moves to acquire all keys.  If it's impossible,

 


Example 1:

Input: ["@.a.#","###.#","b.A.B"]
Output: 8



Example 2:

Input: ["@..aA","..B#.","....b"]
Output: 6



 

Note:


    1 <= grid.length <= 30
    1 <= grid[0].length <= 30
    grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
    The number of keys is in [1, 6].  Each key has a different letter and opens
/*
    Submission Date: 2018-07-08
    Runtime: 164 ms
    Difficulty: HARD
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

struct Item {
  int x;
  int y;
  int dist;
  int key;
  Item(int _x, int _y, int _dist, int _key)
      : x(_x), y(_y), dist(_dist), key(_key) {}
};

class Solution {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};

 public:
  string GetVisitKey(const int& x, const int& y, const int& key) {
    return to_string(x) + "," + to_string(y) + "," + to_string(key);
  }

  /*
  do a bfs by marking visited as x,y,key where key represents the keys that we
  have look in the 4 directions, if it is '.' or '@' go(new_x, new_y, key) if
  not visited if 'a' - 'z' go(new_x, new_y, key | (1 << (grid[new_y][new_x] -
  'a'))) if not visited (ie add key) if 'A' - 'Z' go(new_x, new_y, key) if not
  visited and has required key (key & 1 << (grid[new_y][new_x] - 'A') terminate
  once reach x,y,key where key == (2^K-1) meaning has all keys
  */
  int shortestPathAllKeys(vector<string>& grid) {
    int N = grid.size();
    int M = grid[0].size();

    int K = 0;
    int start_x = 0;
    int start_y = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if ('a' <= grid[i][j] && grid[i][j] <= 'f') K++;
        if (grid[i][j] == '@') {
          start_y = i;
          start_x = j;
        }
      }
    }

    unordered_set<string> visited;
    int all_key = (1 << K) - 1;
    queue<Item> q;
    q.emplace(start_x, start_y, 0, 0);
    visited.insert(GetVisitKey(start_x, start_y, 0));
    while (!q.empty()) {
      Item item = q.front();
      q.pop();
      if (item.key == all_key) return item.dist;
      for (int i = 0; i < 4; i++) {
        int new_x = item.x + dx[i];
        int new_y = item.y + dy[i];
        if (new_x < 0 || new_x >= M) continue;
        if (new_y < 0 || new_y >= N) continue;
        if (grid[new_y][new_x] == '#') continue;
        if (grid[new_y][new_x] == '.' || grid[new_y][new_x] == '@') {
          string v_key = GetVisitKey(new_x, new_y, item.key);
          if (!visited.count(v_key)) {  // can visit if not visited
            q.emplace(new_x, new_y, item.dist + 1, item.key);
            visited.insert(v_key);
          }
        } else if ('a' <= grid[new_y][new_x] &&
                   grid[new_y][new_x] <= 'f') {  // key
          int new_key = item.key | (1 << (grid[new_y][new_x] - 'a'));
          string v_key = GetVisitKey(new_x, new_y, new_key);
          if (!visited.count(
                  v_key)) {  // see if picking up key is already visited
            q.emplace(new_x, new_y, item.dist + 1, new_key);
            visited.insert(v_key);
          }
        } else {  // lock
          int req_key = 1 << (grid[new_y][new_x] - 'A');
          string v_key = GetVisitKey(new_x, new_y, item.key);
          if ((req_key & item.key) &&
              !visited.count(v_key)) {  // have required key and not visited
            q.emplace(new_x, new_y, item.dist + 1, item.key);
            visited.insert(v_key);
          }
        }
      }
    }
    return -1;
  }
};

struct Node {
  vector<Node*> adj;
  int dist = 0;
};

class Solution2 {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};

 public:
  bool IsKey(const char& c) { return 'a' <= c && c <= 'f'; }
  bool IsLock(const char& c) { return 'A' <= c && c <= 'F'; }

  /*
  dp[i][j][k] is a node representing grid[i][j] where k is the current status of
  keys there are up to 2^k status of keys
  
  create adj for dp[i][j][k] by looking at 4 neighbors
  do bfs starting from dp[start_y][start_x][0], if a node dp[i][j][k] is already
  visited ie. dist != 0, then visiting it again with the same state will have a
  larger distance so don't visit it again
  
  now for all dp[i][j][(2^k) - 1] ie when all the keys are collected, find the
  minimum distance it took
  */
  int shortestPathAllKeys(vector<string>& grid) {
    int N = grid.size();
    int M = grid[0].size();

    int K = 0;
    int start_x = 0;
    int start_y = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (IsKey(grid[i][j])) K++;
        if (grid[i][j] == '@') {
          start_y = i;
          start_x = j;
        }
      }
    }

    int k_limit = 1 << K;
    vector<vector<vector<Node*>>> dp(
        N, vector<vector<Node*>>(M, vector<Node*>(k_limit)));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k < k_limit; k++) {
          dp[i][j][k] = new Node();
        }
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k < k_limit; k++) {
          for (int l = 0; l < 4; l++) {
            int new_y = i + dy[l];
            int new_x = j + dx[l];

            if (!(0 <= new_y && new_y < N)) continue;
            if (!(0 <= new_x && new_x < M)) continue;

            if (IsKey(grid[new_y][new_x])) {
              // add key
              int new_key = k | (1 << (grid[new_y][new_x] - 'a'));
              dp[i][j][k]->adj.push_back(dp[new_y][new_x][new_key]);
            } else if (IsLock(grid[new_y][new_x])) {
              // check if we have key
              int needed_key = 1 << (grid[new_y][new_x] - 'A');
              if (k & needed_key) {
                dp[i][j][k]->adj.push_back(dp[new_y][new_x][k]);
              }
            } else if (grid[new_y][new_x] != '#') {  // '@' or '.'
              dp[i][j][k]->adj.push_back(dp[new_y][new_x][k]);
            }
          }
        }
      }
    }

    queue<Node*> q;
    q.push(dp[start_y][start_x][0]);
    while (!q.empty()) {
      Node* curr = q.front();
      q.pop();
      for (auto* neighbor : curr->adj) {
        if (neighbor->dist != 0) continue;  // visited already
        neighbor->dist = curr->dist + 1;
        q.push(neighbor);
      }
    }

    int all_keys = k_limit - 1;
    int res = -1;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (dp[i][j][all_keys]->dist == 0)
          continue;  // this node isnt visitable
        if (res == -1) res = dp[i][j][all_keys]->dist;
        res = min(res, dp[i][j][all_keys]->dist);
      }
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
866. Smallest Subtree with all the Deepest Nodes
Given a binary tree rooted at root, the depth of each node is the shortest

A node is deepest if it has the largest depth possible among any node in the

The subtree of a node is that node, plus the set of all descendants of that

Return the node with the largest depth such that it contains all the deepest

 

Example 1:

Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:



We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with
Both the input and output have TreeNode type.


 

Note:


    The number of nodes in the tree will be between 1 and 500.
    The values of each node are unique.
/*
    Submission Date: 2018-07-08
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  TreeNode* lca(TreeNode* root, TreeNode* A, TreeNode* B) {
    if (root == NULL) return NULL;
    if (root == A || root == B) return root;
    TreeNode* l = lca(root->left, A, B);
    TreeNode* r = lca(root->right, A, B);
    if (l && r) return root;
    return l ? l : r;
  }

  /*
  do level order search and keep track of the deepest nodes
  then for all the deepest nodes do lca and return that result.
  by folding lca, curr goes higher and higher such that further
  calls to lca are faster (does not reprocess same nodes)
  */
  TreeNode* subtreeWithAllDeepest(TreeNode* root) {
    if (root == NULL) return root;
    queue<TreeNode*> q;
    q.push(root);

    vector<TreeNode*> last;

    while (!q.empty()) {
      last.clear();
      int q_size = q.size();
      for (int i = 0; i < q_size; i++) {
        TreeNode* temp = q.front();
        last.push_back(temp);
        q.pop();
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
      }
    }

    TreeNode* curr = last[0];
    for (int i = 1; i < last.size(); i++) {
      curr = lca(root, curr, last[i]);
    }

    return curr;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
867. Prime Palindrome
Find the smallest prime palindrome greater than or equal to N.

Recall that a number is prime if it's only divisors are 1 and itself, and it is

For example, 2,3,5,7,11 and 13 are primes.

Recall that a number is a palindrome if it reads the same from left to right as

For example, 12321 is a palindrome.

 


Example 1:

Input: 6
Output: 7



Example 2:

Input: 8
Output: 11



Example 3:

Input: 13
Output: 101




 

Note:


    1 <= N <= 10^8
    The answer is guaranteed to exist and be less than 2 * 10^8.
/*
    Submission Date: 2018-07-08
    Runtime: 172 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isprime(int x) {
    if (x < 2) return false;
    for (int i = 2; i <= sqrt(x); i++) {
      if (x % i == 0) return false;
    }
    return true;
  }

  typedef long long ll;
  /*
  generate increasing palindrome as odd or even by taking a number, reversing it
  and appending to self. find the first palindrome that is >= N and prime then
  break compare the even and odd result to see which is smaller and return that.
  */
  int primePalindrome(int N) {
    int res = INT_MAX;
    // odd
    for (int i = 0; i < INT_MAX; i++) {
      string s = to_string(i);
      string rev = s;
      reverse(rev.begin(), rev.end());
      string pal = s + rev.substr(1);

      ll pal_long = stoll(pal);
      if (pal_long >= INT_MAX) break;

      int pal_int = pal_long;
      if (pal_int >= N && isprime(pal_int)) {
        res = pal_int;
        break;
      }
    }
    // even
    for (int i = 0; i < INT_MAX; i++) {
      string s = to_string(i);
      string rev = s;
      reverse(rev.begin(), rev.end());
      string pal = s + rev;

      ll pal_long = stoll(pal);

      if (pal_long >= INT_MAX) break;
      int pal_int = pal_long;

      if (pal_int >= N && isprime(pal_int)) {
        res = min(pal_int, res);
        break;
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
868. Transpose Matrix
Given a matrix A, return the transpose of A.

The transpose of a matrix is the matrix flipped over it's main diagonal,

 


Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]



Example 2:

Input: [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]


 

Note:


    1 <= A.length <= 1000
    1 <= A[0].length <= 1000
/*
    Submission Date: 2018-07-08
    Runtime: 20 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> transpose(vector<vector<int>>& A) {
    int N = A.size();
    int M = A[0].size();
    vector<vector<int>> res(M, vector<int>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        res[j][i] = A[i][j];
      }
    }

    return res;
  }
};

int main() { return 0; }