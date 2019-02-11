
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

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
877. Stone Game
Alex and Lee play a game with piles of stones.  There are an even number
of piles arranged in a row, and each pile has a positive integer number of
stones piles[i].

The objective of the game is to end with the most stones.  The total number of
stones is odd, so there are no ties.

Alex and Lee take turns, with Alex starting first.  Each turn, a player takes
the entire pile of stones from either the beginning or the end of the row.  This
continues until there are no more piles left, at which point the person with the
most stones wins.

Assuming Alex and Lee play optimally, return True if and only if Alex wins the
game.

Example 1:

Input: [5,3,4,5]
Output: true
Explanation:
Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10
points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with
9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we
return true.

Note:

  2 <= piles.length <= 500
  piles.length is even.
  1 <= piles[i] <= 500
  sum(piles) is odd.
/*
  Submission Date: 2019-01-26
  Runtime: 16 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int N;

 public:
  int get(const vector<vector<int>>& dp, int i, int j) {
    if (i <= j && i >= 0 && i < N && j >= 0 && j < N) {
      return dp[i][j];
    }
    return 0;
  }
  bool stoneGame(vector<int>& piles) {
    N = piles.size();
    vector<vector<int>> dp(N, vector<int>(N, 0));

    for (int gap = 0; gap < N; gap++) {
      for (int i = 0; i + gap < N; i++) {
        int j = gap;
        dp[i][j] =
            max(piles[i] + min(get(dp, i + 1, j - 1), get(dp, i + 2, j)),
                piles[j] + min(get(dp, i, j - 2), get(dp, i + 1, j - 1)));
      }
    }

    return get(dp, 0, N - 1) > get(dp, 1, N - 1) ||
           get(dp, 0, N - 1) > get(dp, 0, N - 2);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
883. Projection Area of 3D Shapes
On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x,
y, and z axes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid
cell (i, j).

Now we view the projection of these cubes onto the xy, yz, and zx planes.

A projection is like a shadow, that maps our 3 dimensional figure to a 2
dimensional plane. 

Here, we are viewing the "shadow" when looking at the cubes from the top, the
front, and the side.

Return the total area of all three projections.

Example 1:

Input: [[2]]
Output: 5

Example 2:

Input: [[1,2],[3,4]]
Output: 17
Explanation:
Here are the three projections ("shadows") of the shape made with each
axis-aligned plane.

Example 3:

Input: [[1,0],[0,2]]
Output: 8

Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 14

Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 21

Note:

  1 <= grid.length = grid[0].length <= 50
  0 <= grid[i][j] <= 50
/*
  Submission Date: 2019-01-26
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int projectionArea(vector<vector<int>>& grid) {
    int res = 0;
    int N = grid.size();

    vector<int> row(N, 0), col(N, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (grid[i][j] > 0) res++;
        row[i] = max(row[i], grid[i][j]);
        col[j] = max(col[j], grid[i][j]);
      }
    }

    for (int i = 0; i < N; i++) {
      res += row[i] + col[i];
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
884. Uncommon Words from Two Sentences
We are given two sentences A and B.  (A sentence is a string of space separated
words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does
not appear in the other sentence.

Return a list of all uncommon words. 

You may return the list in any order.

Example 1:

Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]

Example 2:

Input: A = "apple apple", B = "banana"
Output: ["banana"]

Note:

  0 <= A.length <= 200
  0 <= B.length <= 200
  A and B both contain only spaces and lowercase letters.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> uncommonFromSentences(string A, string B) {
    unordered_map<string, int> freq;
    stringstream ssA(A), ssB(B);
    string temp;

    while (ssA >> temp) freq[temp]++;
    while (ssB >> temp) freq[temp]++;

    vector<string> res;
    for (const auto& kv : freq)
      if (kv.second == 1) res.push_back(kv.first);

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
885. Spiral Matrix III
On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing
east.

Here, the north-west corner of the grid is at the first row and column, and the
south-east corner of the grid is at the last row and column.

Now, we walk in a clockwise spiral shape to visit every position in this grid. 

Whenever we would move outside the boundary of the grid, we continue our walk
outside the grid (but may return to the grid boundary later.) 

Eventually, we reach all R * C spaces of the grid.

Return a list of coordinates representing the positions of the grid in the order
they were visited.

Example 1:

Input: R = 1, C = 4, r0 = 0, c0 = 0
Output: [[0,0],[0,1],[0,2],[0,3]]

Example 2:

Input: R = 5, C = 6, r0 = 1, c0 = 4
Output:
[[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]

Note:

  1 <= R <= 100
  1 <= C <= 100
  0 <= r0 < R
  0 <= c0 < C
/*
  Submission Date: 2019-01-26
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int key(int i, int j, int R, int C) { return i * C + j; }
  vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
    unordered_set<int> visited;

    vector<vector<int>> res;
    res.push_back({r0, c0});
    visited.insert(key(r0, c0, R, C));

    int i = r0, j = c0;
    int dx = 1;
    int dy = 0;
    while (visited.size() != R * C) {
      if (!(0 <= i + dy && i + dy < R) || !(0 <= j + dx && j + dx < C)) {
        // will go out of bounds so change direction
        swap(dx, dy);
        dx *= -1;
      } else {
        i += dy;
        j += dx;
        if (visited.count(key(i, j, R, C))) {
          continue;
        } else {
          // an unvisited cell so push it to result
          res.push_back({i, j});
          visited.insert(key(i, j, R, C));

          // if node to the right isn't visited or if it is out of bounds change
          // directions
          int rot_dx = -dy;
          int rot_dy = dx;

          if (!(0 <= i + rot_dy && i + rot_dy < R) ||
              !(0 <= j + rot_dx && j + rot_dx < C) ||
              !visited.count(key(i + rot_dy, j + rot_dx, R, C))) {
            swap(dx, dy);
            dx *= -1;
          }
        }
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
888. Fair Candy Swap
Alice and Bob have candy bars of different sizes: A[i] is the size of the i-th
bar of candy that Alice has, and B[j] is the size of the j-th bar of candy that
Bob has.

Since they are friends, they would like to exchange one candy bar each so that
after the exchange, they both have the same total amount of candy.  (The total
amount of candy a person has is the sum of the sizes of candy bars they have.)

Return an integer array ans where ans[0] is the size of the candy bar that Alice
must exchange, and ans[1] is the size of the candy bar that Bob must exchange.

If there are multiple answers, you may return any one of them.  It is guaranteed
an answer exists.

Example 1:

Input: A = [1,1], B = [2,2]
Output: [1,2]

Example 2:

Input: A = [1,2], B = [2,3]
Output: [1,2]

Example 3:

Input: A = [2], B = [1,3]
Output: [2,3]

Example 4:

Input: A = [1,2,5], B = [2,4]
Output: [5,4]

Note:

  1 <= A.length <= 10000
  1 <= B.length <= 10000
  1 <= A[i] <= 100000
  1 <= B[i] <= 100000
  It is guaranteed that Alice and Bob have different total amounts of candy.
  It is guaranteed there exists an answer.
/*
  Submission Date: 2019-01-26
  Runtime: 64 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  /*sum_A + (B[j] - A[i]) == sum_B == (A[i] - B[j])
  sum_A = sum_B + 2*A[i] - 2*B[j]
  */
  vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
    int sum_A = 0;
    int sum_B = 0;
    for (auto& e : A) sum_A += e;
    for (auto& e : B) sum_B += e;

    unordered_set<int> B_set(B.begin(), B.end());
    for (auto& e : A) {
      int B_j = (sum_A - sum_B - 2 * e) / -2;
      if (B_set.count(B_j)) return {e, B_j};
    }

    return {};
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
889. Construct Binary Tree from Preorder and Postorder Traversal
Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

Note:

  1 <= pre.length == post.length <= 30
  pre[] and post[] are both permutations of 1, 2, ..., pre.length.
  It is guaranteed an answer exists. If there exists multiple answers, you can
return any of them.
/*
  Submission Date: 2019-01-26
  Runtime: 8 ms
  Difficulty: MEDIUM
*/
#include <cassert>
#include <iostream>
#include <unordered_map>
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
  /* traverse pre and create nodes from there. the stk represents
  the current path of the tree (ie. from root to node). when the
  stk last value is equal to post[j], it means the tree is done
  so pop stk and increment j until it is no longer so. add the
  pre[i] is either the left or right of the stack depending on
  which is available.
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    vector<TreeNode*> stk;
    stk.emplace_back(new TreeNode(pre[0]));
    for (int i = 1, j = 0; i < pre.size(); i++) {
      while (stk.back()->val == post[j]) {
        j++;
        stk.pop_back();
      }

      TreeNode* curr = new TreeNode(pre[i]);
      if (stk.back()->left == NULL)
        stk.back()->left = curr;
      else
        stk.back()->right = curr;
      stk.emplace_back(curr);
    }

    return stk.front();
  }
};

class Solution2 {
 public:
  TreeNode* f(vector<int>& pre, int a, int b, vector<int>& post, int c, int d,
              unordered_map<int, int>& val_to_post_ind) {
    if (a > b || c > d) return NULL;
    assert(b - a == d - c);

    TreeNode* root = new TreeNode(pre[a]);

    int furthest = -1;
    for (int i = a + 1; i <= b; i++) {
      int ind = val_to_post_ind[pre[i]];
      furthest = max(furthest, ind);
      if (furthest - c == i - (a + 1)) {
        root->left = f(pre, a + 1, i, post, c, furthest, val_to_post_ind);
        root->right =
            f(pre, i + 1, b, post, furthest + 1, d - 1, val_to_post_ind);
        break;
      }
    }

    return root;
  }

  /*
  we traverse from pre i = 1 to N looking for where pre[i] is in post, say it is
  at j. it means every element from 0 to j must be in the tree so keep going
  until the furthest j contains as many elements as i-1. These range must be the
  left sub tree so partition both the pre and post from [1,i] [i+1, N] and [0,
  furthest_j] [furthest_j + 1, N-1]
  */
  TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    unordered_map<int, int> val_to_post_ind;
    for (int i = 0; i < post.size(); i++) val_to_post_ind[post[i]] = i;
    return f(pre, 0, pre.size() - 1, post, 0, pre.size() - 1, val_to_post_ind);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
890. Find and Replace Pattern
You have a list of words and a pattern, and you want to know which words in
words matches the pattern.

A word matches the pattern if there exists a permutation of letters p so that
after replacing every letter x in the pattern with p(x), we get the desired
word.

(Recall that a permutation of letters is a bijection from letters to letters:
every letter maps to another letter, and no two letters map to the same letter.)

Return a list of the words in words that match the given pattern. 

You may return the answer in any order.

 


Example 1:

Input: words = ["abc","deq","mee","aqq","dkd","ccc"], pattern = "abb"
Output: ["mee","aqq"]
Explanation: "mee" matches the pattern because there is a permutation {a -> m, b
-> e, ...}.
"ccc" does not match the pattern because {a -> c, b -> c, ...} is not a
permutation,
since a and b map to the same letter.

 

Note:


  1 <= words.length <= 50
  1 <= pattern.length = words[i].length <= 20
/*
  Submission Date: 2019-01-25
  Runtime: 4 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
    vector<string> res;
    for (const auto& w : words) {
      if (w.size() != pattern.size()) continue;
      unordered_map<char, char> p;

      unordered_set<char> used;
      bool can_insert = true;
      for (int i = 0; i < w.size(); i++) {
        if (p.count(w[i])) {
          if (p[w[i]] != pattern[i]) {
            can_insert = false;
            break;
          }
        } else {
          if (used.count(pattern[i])) {
            can_insert = false;
            break;
          } else {
            p[w[i]] = pattern[i];
            used.insert(pattern[i]);
          }
        }
      }

      if (can_insert) res.push_back(w);
    }

    return res;
  }
};

int main() { return 0; }
