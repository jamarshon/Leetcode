
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
858. Mirror Reflection
There is a special square room with mirrors on each of the four walls.  Except
for the southwest corner, there are receptors on each of the remaining corners,
numbered 0, 1, and 2.

The square room has walls of length p, and a laser ray from the southwest
corner first meets the east wall at a distance q from the 0th receptor.

Return the number of the receptor that the ray meets first.  (It is guaranteed
that the ray will meet a receptor eventually.)

Example 1:

Input: p = 2, q = 1
Output: 2
Explanation: The ray meets receptor 2 the first time it gets reflected back to
the left wall.

Note:

  1 <= p <= 1000
  0 <= q <= p
/*
  Submission Date: 2019-02-17
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  /*
  expand these pxp blocks so that they form a grid in cartesian
  the line q/p*x must intersect with a point that is (aq, bq)
  where a is the number of qblocks horizontally and b is for vertically

  q/p*(aq) = bq
  aq^2/p = bq
  aq/p = b
  aq = bp

  so find lcm of p and q and this would equal aq and bp
  lcm(c,d) = c*d/gcd(c,d)


  for the qblocks if a is even it means the receptors are in the same place
  else it is flipped horizontally
  if b is odd it is flipped vertically

  a = p/gcd(p,q)
  b = q/gcd(p,q)

  the grid for the qblocks would be (bottom row is a,b = 0,0)
  ...
  [2,1,2,1,2]...
  [0,x,0,x,0]...
  [2,1,2,1,2]...
  [x,0,x,0,x]...

  the guarantee is that the cell will not end on x
  */
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  int mirrorReflection(int p, int q) {
    int g = gcd(p, q);
    int a = p / g;
    int b = q / g;
    if (b % 2 == 0) {
      // not going to be x
      return 0;
    } else {
      return a % 2 == 0 ? 2 : 1;
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
859. Buddy Strings
Given two strings A and B of lowercase letters, return true if and only if we
can swap two letters in A so that the result equals B.

 

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool buddyStrings(string A, string B) {
    if (A.size() != B.size()) return false;

    vector<int> diff;
    for (int i = 0; i < A.size(); i++) {
      if (A[i] != B[i]) {
        diff.push_back(i);
        if (diff.size() > 2) return false;
      }
    }

    if (diff.size() == 1) return false;
    if (diff.size() == 0)
      return unordered_set<char>(A.begin(), A.end()).size() < A.size();
    return A[diff[0]] == B[diff[1]] && A[diff[1]] == B[diff[0]];
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
860. Lemonade Change
At a lemonade stand, each lemonade costs $5.

Customers are standing in a queue to buy from you, and order one at a time
(in the order specified by bills).

Each customer will only buy one lemonade and pay with either a $5, $10, or $20
bill. You must provide the correct change to each customer, so that the net
transaction is that the customer pays $5.

Note that you don't have any change in hand at first.

Return true if and only if you can provide every customer with correct change.

 

Example 1:

Input: [5,5,5,10,20]
Output: true
Explanation:
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.
Example 2:

Input: [5,5,10]
Output: true
Example 3:

Input: [10,10]
Output: false
Example 4:

Input: [5,5,10,10,20]
Output: false
Explanation:
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5
bill. For the last customer, we can't give change of $15 back because we only
have two $10 bills. Since not every customer received correct change, the answer
is false.
 

Note:

0 <= bills.length <= 10000
bills[i] will be either 5, 10, or 20.
/*
    Submission Date: 2018-07-01
    Runtime: 30 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool lemonadeChange(vector<int>& bills) {
    // change[0] is number of 5's and change[1] is number of 10's.
    // 20's will never be given back so no need to count them.
    vector<int> change(2, 0);
    for (const auto& e : bills) {
      if (e == 5) {
        change[0]++;
      } else if (e == 10) {  // can only give a 5 back
        if (change[0] == 0) return false;
        change[0]--;
        change[1]++;
      } else {  // e == 20 can give back either 5 and 10 or 3 fives
        if (change[1] > 0 &&
            change[0] >
                0) {  // try to give back the 10 first as it is less useful
          change[1]--;
          change[0]--;
        } else if (change[0] >= 3) {
          change[0] -= 3;
        } else {
          return false;
        }
      }
    }

    return true;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
861. Score After Flipping Matrix
We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that
row or column: changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a
binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.
/*
    Submission Date: 2018-07-01
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void FlipRow(vector<vector<int>>& A, int row, int M) {
    for (int j = 0; j < M; j++) A[row][j] ^= 1;
  }

  void FlipCol(vector<vector<int>>& A, int col, int N) {
    for (int i = 0; i < N; i++) A[i][col] ^= 1;
  }

  /*
  First get all the the elements in A[i][0] to be 1 by toggling rows
  this is because having a 1 in the left most column gives the greatest value
  1000 > 0111 Then for each column, flip the column if it gives a greater amount
  of 1's in that column
  */
  int matrixScore(vector<vector<int>>& A) {
    if (A.empty()) return 0;
    int N = A.size(), M = A[0].size();
    for (int i = 0; i < N; i++) {
      if (A[i][0] == 0) {
        FlipRow(A, i, M);
      }
    }

    for (int j = 0; j < M; j++) {
      int one_count = 0;
      for (int i = 0; i < N; i++) one_count += A[i][j] == 1;
      if (one_count < N - one_count) {
        FlipCol(A, j, N);
      }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
      int temp = 0;
      for (int j = 0; j < M; j++) {
        temp |= A[i][j];
        temp <<= 1;
      }
      res += temp >> 1;
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
864. Shortest Path to Get All Keys
We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is 
the starting point, ("a", "b", ...) are keys, and ("A", "B", ...) are locks. 

We start at the starting point, and one move consists of walking one space in 
one of the 4 cardinal directions.  We cannot walk outside the grid, or walk into 
a wall.  If we walk over a key, we pick it up.  We can't walk over a lock unless 
we have the corresponding key. 

For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of 
the first K letters of the English alphabet in the grid.  This means that there 
is exactly one key for each lock, and one lock for each key; and also that the 
letters used to represent the keys and locks were chosen in the same order as 
the English alphabet. 

Return the lowest number of moves to acquire all keys.  If it's impossible, 
return -1. 

 


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
exactly one lock. 

/*
    Submission Date: 2018-07-08
    Runtime: 164 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Item {
    int x;
    int y;
    int dist;
    int key;
    Item(int _x, int _y, int _dist, int _key): x(_x), y(_y), dist(_dist), key(_key) {}
};

class Solution {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
public:
    string GetVisitKey(const int& x, const int& y, const int& key) {
        return to_string(x) + "," + to_string(y) + "," + to_string(key);
    }
    
    /*
    do a bfs by marking visited as x,y,key where key represents the keys that we have
    look in the 4 directions, 
        if it is '.' or '@'
            go(new_x, new_y, key) if not visited
        if 'a' - 'z'
            go(new_x, new_y, key | (1 << (grid[new_y][new_x] - 'a'))) if not visited (ie add key)
        if 'A' - 'Z'
            go(new_x, new_y, key) if not visited and has required key (key & 1 << (grid[new_y][new_x] - 'A') 
    terminate once reach x,y,key where key == (2^K-1) meaning has all keys
    */
    int shortestPathAllKeys(vector<string>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        
        int K = 0;
        int start_x = 0;
        int start_y = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if('a' <= grid[i][j] && grid[i][j] <= 'f') K++;
                if(grid[i][j] == '@') {
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
        while(!q.empty()) {
            Item item = q.front();
            q.pop();
            if(item.key == all_key) return item.dist;
            for(int i = 0; i < 4; i++) {
                int new_x = item.x + dx[i];
                int new_y = item.y + dy[i];
                if(new_x < 0 || new_x >= M) continue;
                if(new_y < 0 || new_y >= N) continue;
                if(grid[new_y][new_x] == '#') continue;
                if(grid[new_y][new_x] == '.' || grid[new_y][new_x] == '@') {
                    string v_key = GetVisitKey(new_x, new_y, item.key);
                    if(!visited.count(v_key)) { // can visit if not visited
                        q.emplace(new_x, new_y, item.dist + 1, item.key);
                        visited.insert(v_key);
                    }
                } else if('a' <= grid[new_y][new_x] && grid[new_y][new_x] <= 'f') { // key
                    int new_key = item.key | (1 << (grid[new_y][new_x] - 'a'));
                    string v_key = GetVisitKey(new_x, new_y, new_key);
                    if(!visited.count(v_key)) { // see if picking up key is already visited
                        q.emplace(new_x, new_y, item.dist + 1, new_key);
                        visited.insert(v_key);
                    }
                } else { // lock
                    int req_key = 1 << (grid[new_y][new_x] - 'A');
                    string v_key = GetVisitKey(new_x, new_y, item.key);
                    if((req_key & item.key) && !visited.count(v_key)){ // have required key and not visited
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
    dp[i][j][k] is a node representing grid[i][j] where k is the current status of keys
    there are up to 2^k status of keys
    
    create adj for dp[i][j][k] by looking at 4 neighbors 
    do bfs starting from dp[start_y][start_x][0], if a node dp[i][j][k] is already visited
    ie. dist != 0, then visiting it again with the same state will have a larger distance
    so don't visit it again
    
    now for all dp[i][j][(2^k) - 1] ie when all the keys are collected, find the minimum
    distance it took
    */
    int shortestPathAllKeys(vector<string>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        
        int K = 0;
        int start_x = 0;
        int start_y = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(IsKey(grid[i][j])) K++;
                if(grid[i][j] == '@') {
                    start_y = i;
                    start_x = j;
                }
            }
        }
        
        int k_limit = 1 << K;
        vector<vector<vector<Node*>>> dp(N, vector<vector<Node*>>(M, vector<Node*>(k_limit)));
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                for(int k = 0; k < k_limit; k++) {
                    dp[i][j][k] = new Node();
                }
            }
        }
        
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                for(int k = 0; k < k_limit; k++) {
                    for(int l = 0; l < 4; l++) {
                        int new_y = i + dy[l];
                        int new_x = j + dx[l];
                        
                        if(!(0 <= new_y && new_y < N)) continue;
                        if(!(0 <= new_x && new_x < M)) continue;
                        
                        if(IsKey(grid[new_y][new_x])) {
                            // add key
                            int new_key = k | (1 << (grid[new_y][new_x] - 'a'));
                            dp[i][j][k]->adj.push_back(dp[new_y][new_x][new_key]);
                        } else if(IsLock(grid[new_y][new_x])) {
                            // check if we have key
                            int needed_key = 1 << (grid[new_y][new_x] - 'A');
                            if(k & needed_key) {
                                dp[i][j][k]->adj.push_back(dp[new_y][new_x][k]);
                            }
                        } else if(grid[new_y][new_x] != '#') { // '@' or '.'
                            dp[i][j][k]->adj.push_back(dp[new_y][new_x][k]);
                        }
                    }
                }
            }
        }
        
        queue<Node*> q;
        q.push(dp[start_y][start_x][0]);
        while(!q.empty()) {
            Node* curr = q.front();
            q.pop();
            for(auto* neighbor: curr->adj) {
                if(neighbor->dist != 0) continue; // visited already
                neighbor->dist = curr->dist + 1;
                q.push(neighbor);
            }
        }
        
        int all_keys = k_limit - 1;
        int res = -1;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(dp[i][j][all_keys]->dist == 0) continue; // this node isnt visitable
                if(res == -1) res = dp[i][j][all_keys]->dist;
                res = min(res, dp[i][j][all_keys]->dist);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
865. Smallest Subtree with all the Deepest Nodes
Given a binary tree rooted at root, the depth of each node is the shortest 
distance to the root. 

A node is deepest if it has the largest depth possible among any node in the 
entire tree. 

The subtree of a node is that node, plus the set of all descendants of that 
node. 

Return the node with the largest depth such that it contains all the deepest 
nodes in its subtree. 

 

Example 1:

Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:



We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the 
given tree. 
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with 
value 2. 
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
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lca(TreeNode* root, TreeNode* A, TreeNode* B) {
        if(root == NULL) return NULL;
        if(root == A || root == B) return root;
        TreeNode* l = lca(root->left, A, B);
        TreeNode* r = lca(root->right, A, B);
        if(l && r) return root;
        return l ? l: r;
    }
    
    /*
    do level order search and keep track of the deepest nodes
    then for all the deepest nodes do lca and return that result.
    by folding lca, curr goes higher and higher such that further
    calls to lca are faster (does not reprocess same nodes)
    */
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if(root == NULL) return root;
        queue<TreeNode*> q;
        q.push(root);
        
        vector<TreeNode*> last;
        
        while(!q.empty()) {
            last.clear();
            int q_size = q.size();
            for(int i = 0; i < q_size; i++) {
                TreeNode* temp = q.front();
                last.push_back(temp);
                q.pop();
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
        }
        
        TreeNode* curr = last[0];
        for(int i = 1; i < last.size(); i++) {
            curr = lca(root, curr, last[i]);
        }
        
        return curr;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
866. Prime Palindrome
Find the smallest prime palindrome greater than or equal to N.

Recall that a number is prime if it's only divisors are 1 and itself, and it is 
greater than 1.  

For example, 2,3,5,7,11 and 13 are primes.

Recall that a number is a palindrome if it reads the same from left to right as 
it does from right to left.  

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
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isprime(int x) {
        if(x < 2) return false;
        for(int i = 2; i <= sqrt(x); i++) {
            if(x % i == 0) return false;
        }
        return true;
    }
    
    typedef long long ll;
    /*
    generate increasing palindrome as odd or even by taking a number, reversing it and appending
    to self. find the first palindrome that is >= N and prime then break compare the even and odd
    result to see which is smaller and return that.
    */
    int primePalindrome(int N) {
        int res = INT_MAX;
       // odd
        for(int i = 0; i < INT_MAX; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string pal = s + rev.substr(1);
            
            ll pal_long = stoll(pal);
            if(pal_long >= INT_MAX) break;
            
            int pal_int = pal_long;
            if(pal_int >= N && isprime(pal_int)) {
                res = pal_int;
                break;
            }
        }
        // even
        for(int i = 0; i < INT_MAX; i++) {
            string s = to_string(i);
            string rev = s;
            reverse(rev.begin(), rev.end());
            string pal = s + rev;
            
            ll pal_long = stoll(pal);
            
            if(pal_long >= INT_MAX) break;
            int pal_int = pal_long;

            if(pal_int >= N && isprime(pal_int)) {
                res = min(pal_int, res);
                break;
            }
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
867. Transpose Matrix
Given a matrix A, return the transpose of A.

The transpose of a matrix is the matrix flipped over it's main diagonal, 
switching the row and column indices of the matrix. 

 


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
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                res[j][i] = A[i][j];
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
868. Binary Gap
Given a positive integer N, find and return the longest distance between two 
consecutive 1's in the binary representation of N. 

If there aren't two consecutive 1's, return 0.

 











Example 1:

Input: 22
Output: 2
Explanation: 
22 in binary is 0b10110.
In the binary representation of 22, there are three ones, and two consecutive 
pairs of 1's. 
The first consecutive pair of 1's have distance 2.
The second consecutive pair of 1's have distance 1.
The answer is the largest of these two distances, which is 2.



Example 2:

Input: 5
Output: 2
Explanation: 
5 in binary is 0b101.



Example 3:

Input: 6
Output: 1
Explanation: 
6 in binary is 0b110.



Example 4:

Input: 8
Output: 0
Explanation: 
8 in binary is 0b1000.
There aren't any consecutive pairs of 1's in the binary representation of 8, so 
we return 0. 


 




Note:


    1 <= N <= 10^9
/*
    Submission Date: 2018-07-15
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <iostream>
#include <bitset>

using namespace std;

class Solution {
public:
    int binaryGap(int N) {
        string s = bitset<31>(N).to_string();
        int last_one = -1;
        int res = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') continue;
            if(last_one == -1) {
                last_one = i;
            } else {
                res = max(res, i - last_one);
                last_one = i;
            }
        }
        return res;
    }
};
int main() {
    return 0;
}
