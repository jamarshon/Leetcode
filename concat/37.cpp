
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
869. Reordered Power of 2
Starting with a positive integer N, we reorder the digits in any order 
(including the original order) such that the leading digit is not zero. 

Return true if and only if we can do this in a way such that the resulting 
number is a power of 2. 

 





Example 1:

Input: 1
Output: true



Example 2:

Input: 10
Output: false



Example 3:

Input: 16
Output: true



Example 4:

Input: 24
Output: false



Example 5:

Input: 46
Output: true


 

Note:


    1 <= N <= 10^9
/*
    Submission Date: 2018-07-15
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    /*
    generate all powers of 2 which has the same length as the number
    compare the sorted number and the sorted power to see if they
    are anagrams of each other, return true if so.
    */
    bool reorderedPowerOf2(int N) {
        string s = to_string(N);
        sort(s.begin(), s.end());
        unordered_set<string> seen;

        for(int i = 0; i < 50; i++) {
            string a = to_string(1LL << i);
            if(a.size() > s.size()) break;
            if(a.size() < s.size()) continue;
            // a.size() == s.size();
            sort(a.begin(), a.end());
            if(a == s) {
                // cout << a << ' '  << s << endl;
                return true;
            }
        }

        return false;
    }
};

int main() {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
870. Advantage Shuffle
Given two arrays A and B of equal size, the advantage of A with respect to B is 
the number of indices i for which A[i] > B[i]. 

Return any permutation of A that maximizes its advantage with respect to B.

 


Example 1:

Input: A = [2,7,11,15], B = [1,10,4,11]
Output: [2,11,7,15]



Example 2:

Input: A = [12,24,8,32], B = [13,25,32,11]
Output: [24,32,8,12]


 

Note:


    1 <= A.length = B.length <= 10000
    0 <= A[i] <= 10^9
    0 <= B[i] <= 10^9
/*
    Submission Date: 2018-07-15
    Runtime: 124 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cassert>

using namespace std;

class Solution {
public:
    /*
    sort A and B, then do two pointers to find the smallest element in A greater than B[i]
    if there is no element then just assign the remaining elemnets in A to B.
    */
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        typedef pair<int,int> pii;
        int N = A.size();
        vector<int> res(N, -1);
        sort(A.begin(), A.end());

        vector<pii> B2;
        for(int i = 0; i < N; i++) B2.emplace_back(B[i], i);
        sort(B2.begin(), B2.end());

        int i = 0, j = 0;
        unordered_set<int> not_used;
        for(int k = 0; k < N; k++) not_used.insert(k);

        while(i < N) {
            while(i < N && A[i] <= B2[j].first) i++;
            if(i < N) {
                res[B2[j].second] = A[i];
                not_used.erase(i);
                i++;
                j++;
            }
        }

        for(const auto& e: not_used) {
            assert(j < N);
            res[B2[j].second] = A[e];
            j++;
        }
        return res;
    }
};

int main() {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
871. Minimum Number of Refueling Stops
A car travels from a starting position to a destination which is target miles 
east of the starting position. 

Along the way, there are gas stations.  Each station[i] represents a gas station 
that is station[i][0] miles east of the starting position, and has station[i][1] 
liters of gas. 

The car starts with an infinite tank of gas, which initially 
has startFuel liters of fuel in it.  It uses 1 liter of gas per 1 mile that it 
drives. 

When the car reaches a gas station, it may stop and refuel, transferring all the 
gas from the station into the car. 

What is the least number of refueling stops the car must make in order to reach 
its destination?  If it cannot reach the destination, return -1. 

Note that if the car reaches a gas station with 0 fuel left, the car can still 
refuel there.  If the car reaches the destination with 0 fuel left, it is still 
considered to have arrived. 

 


Example 1:

Input: target = 1, startFuel = 1, stations = []
Output: 0
Explanation: We can reach the target without refueling.



Example 2:

Input: target = 100, startFuel = 1, stations = [[10,100]]
Output: -1
Explanation: We can't reach the target (or even the first gas station).



Example 3:

Input: target = 100, startFuel = 10, stations = 
[[10,60],[20,30],[30,30],[60,40]] 
Output: 2
Explanation: 
We start with 10 liters of fuel.
We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters 
to 60 liters of gas. 
Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the 
target. 
We made 2 refueling stops along the way, so we return 2.


 

Note:


    1 <= target, startFuel, stations[i][1] <= 10^9
    0 <= stations.length <= 500
    0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] < 
target 

/*
    Submission Date: 2018-07-15
    Runtime: 44 ms
    Difficulty: HARD
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        typedef long long ll;
        int N = stations.size();
        
        // dp[t] is the furthest distance you can go with t number of refuels
        // so for a new stations[i] that is smaller distance than dp[t]
        // we can take a refuel (e.g update dp[t+1]) and have a new larger distance
        // by refueling at stations[i]
        vector<ll> dp(N + 1, 0);
        dp[0] = startFuel;
        for(int i = 0; i < N; i++) {
            for(int t = i; t >= 0; t--) {
                if(dp[t] >= stations[i][0]) {
                    dp[t+1] = max(dp[t+1], dp[t] + stations[i][1]);
                }
            }
        }
        
        for(int t = 0; t <= N; t++) if(dp[t] >= target) return t;
        return -1;
    }
};
        

class Solution3 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& s) {
        typedef long long ll;
        priority_queue<int> pq;
        // keep travelling until can't travel any more than use the largest fuel seen
        int res = 0;
        ll dist = startFuel;
        int ind = 0;
        while(true) {
            while(ind < s.size() && s[ind][0] <= dist) {
                pq.push(s[ind][1]);
                ind++;
            }
            
            if(dist >= target) return res;
            if(pq.empty()) return -1;
            // take largest refuel from pq
            dist += pq.top();
            pq.pop();
            res++;
        }
    }
};

class Solution2 {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& s) {
        vector<vector<int>> stations;
        stations.push_back({0, 0});
        for(const auto& v: s) stations.push_back(v);
        stations.push_back({target, 0});
        
        int N = stations.size();
        // dp[i][j] = x where x is the minimum refuels to reach station i with j battery remaining
        vector<unordered_map<int,int>> dp(N);
        dp[0][startFuel] = 0; 
        
        int res = INT_MAX;
        
        for(int i = 0; i < N; i++) {
            for(auto battery_to_min: dp[i]) {
                int battery = battery_to_min.first;
                
                if(battery >= stations[N-1][0] - stations[i][0]) { // can reach target
                    res = min(res, battery_to_min.second);
                    continue;
                }
                
                // dont use station i
                for(int j = i + 1; j < N; j++) {
                    int rem = battery - (stations[j][0] - stations[i][0]);
                    if(rem < 0) break;
                    if(!dp[j].count(rem) || dp[j][rem] > battery_to_min.second)
                        dp[j][rem] = battery_to_min.second;
                }
                
                // use station i
                for(int j = i + 1; j < N; j++) {
                    int rem = battery - (stations[j][0] - stations[i][0]);
                    if(rem < 0) break;
                    rem += stations[j][1];
                    if(!dp[j].count(rem) || dp[j][rem] > battery_to_min.second + 1)
                        dp[j][rem] = battery_to_min.second + 1;
                }
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};

int main() {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
872. Leaf-Similar Trees
Consider all the leaves of a binary tree.  From left to right order, the values
of those leaves form a leaf value sequence.

For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9,
8).

Two binary trees are considered leaf-similar if their leaf value sequence is the
same.

Return true if and only if the two given trees with head nodes root1 and root2
are leaf-similar.

Note:

  Both of the given trees will have between 1 and 100 nodes.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
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
  void inorder(TreeNode* root, vector<int>& leaf) {
    if (root) {
      if (root->left == NULL && root->right == NULL) {
        leaf.push_back(root->val);
      }

      inorder(root->left, leaf);
      inorder(root->right, leaf);
    }
  }

  bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    vector<int> leaf1, leaf2;
    inorder(root1, leaf1);
    inorder(root2, leaf2);

    if (leaf1.size() != leaf2.size()) return false;
    for (int i = 0; i < leaf1.size(); i++)
      if (leaf1[i] != leaf2[i]) return false;
    return true;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
874. Walking Robot Simulation
A robot on an infinite grid starts at point (0, 0) and faces north.  The robot
can receive one of three possible types of commands:

  -2: turn left 90 degrees
  -1: turn right 90 degrees
  1 <= x <= 9: move forward x units

Some of the grid squares are obstacles. 

The i-th obstacle is at grid point (obstacles[i][0], obstacles[i][1])

If the robot would try to move onto them, the robot stays on the previous grid
square instead (but still continues following the rest of the route.)

Return the square of the maximum Euclidean distance that the robot will be from
the origin.

Example 1:

Input: commands = [4,-1,3], obstacles = []
Output: 25
Explanation: robot will go to (3, 4)

Example 2:

Input: commands = [4,-1,4,-2,4], obstacles = [[2,4]]
Output: 65
Explanation: robot will be stuck at (1, 4) before turning left and going to (1,
8)

Note:

  0 <= commands.length <= 10000
  0 <= obstacles.length <= 10000
  -30000 <= obstacle[i][0] <= 30000
  -30000 <= obstacle[i][1] <= 30000
  The answer is guaranteed to be less than 2 ^ 31.
/*
  Submission Date: 2019-01-26
  Runtime: 120 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int dx = 0;
  int dy = 1;

  /*
  0,1 => 1,0 => 0,-1 => -1,0
  */
  void rotateCW() {
    swap(dx, dy);
    dy = -dy;
  }

  /*
  0,1 => -1,0 => 0,-1 => 1,0
  */
  void rotateCCW() {
    swap(dx, dy);
    dx = -dx;
  }

  int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    int mx = 0;
    int my = 0;
    long long res = pow(mx, 2LL) + pow(my, 2LL);
    unordered_set<string> st;
    for (auto& p : obstacles) {
      st.insert(to_string(p[0]) + "," + to_string(p[1]));
    }

    for (auto& c : commands) {
      if (c == -2) {  // left
        rotateCCW();
      } else if (c == -1) {  // right
        rotateCW();
      } else {  // forward
        for (int i = 1; i <= c; i++) {
          string key = to_string(mx + dx) + "," + to_string(my + dy);
          if (st.count(key)) break;

          mx += dx;
          my += dy;

          long long pos = pow(mx, 2LL) + pow(my, 2LL);
          res = max(res, pos);
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
876. Middle of the Linked List
Given a non-empty, singly linked list with head node head, return a middle node
of linked list.

If there are two middle nodes, return the second middle node.

Example 1:

Input: [1,2,3,4,5]
Output: Node 3 from this list (Serialization: [3,4,5])
The returned node has value 3.  (The judge's serialization of this node is
[3,4,5]).
Note that we returned a ListNode object ans, such that:
ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, and ans.next.next.next =
NULL.

Example 2:

Input: [1,2,3,4,5,6]
Output: Node 4 from this list (Serialization: [4,5,6])
Since the list has two middle nodes with values 3 and 4, we return the second
one.

Note:

  The number of nodes in the given list will be between 1 and 100.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;

    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow;
  }
};

int main() { return 0; }
