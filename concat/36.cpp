
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
844. Backspace String Compare
Given two strings S and T, return if they are equal when both are typed into
empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  string eval(string s) {
    string res = "";
    for (const auto& c : s) {
      if (c == '#') {
        if (!res.empty()) res.pop_back();
      } else {
        res.push_back(c);
      }
    }
    return res;
  }
  bool backspaceCompare(string S, string T) { return eval(S) == eval(T); }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
845. Longest Mountain in Array
Let's call any (contiguous) subarray B (of A) a mountain if the following
properties hold:

  B.length >= 3
  There exists some 0 < i < B.length - 1 such that B[0] < B[1] < ... B[i-1] <
B[i] > B[i+1] > ... > B[B.length - 1]

(Note that B could be any subarray of A, including the entire array A.)

Given an array A of integers, return the length of the longest mountain. 

Return 0 if there is no mountain.

Example 1:

Input: [2,1,4,7,3,2,5]
Output: 5
Explanation: The largest mountain is [1,4,7,3,2] which has length 5.

Example 2:

Input: [2,2,2]
Output: 0
Explanation: There is no mountain.

Note:

  0 <= A.length <= 10000
  0 <= A[i] <= 10000

Follow up:

  Can you solve it using only one pass?
  Can you solve it in O(1) space?
/*
  Submission Date: 2019-01-26
  Runtime: 24 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestMountain(vector<int>& A) {
    int res = 0;
    int up = 0;
    int down = 0;
    for (int i = 1; i < A.size(); i++) {
      if ((down > 0 && A[i - 1] < A[i]) || A[i - 1] == A[i]) {
        // end going down or end equal.
        down = 0;
        up = 0;
      }

      up += A[i - 1] < A[i];
      down += A[i - 1] > A[i];

      if (up > 0 && down > 0) res = max(res, up + down + 1);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
846. Hand of Straights
Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W,
and consists of W consecutive cards.

Return true if and only if she can.

 




Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].

Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.

 

Note:


    1 <= hand.length <= 10000
    0 <= hand[i] <= 10^9
    1 <= W <= hand.length

/*
    Submission Date: 2018-07-11
    Runtime: 44 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <map>
#include <queue>

using namespace std;

class Solution {
 public:
  /*
  create a frequency map. have a sorted queue of ends and loop through freq map
  if the ends isn't empty (meaning it is a part of some interval) and previous
  value in freq map doesn't equal current value - 1, it means a jump occured
  without interval ending so return false
  
  if the frequency is less than the number of intervals (ends.size()), return
  false as more of this number is needed
  
  if the frequency is greater than the number of intervals, then add this number
  + W - 1 as the end interval and do this freq - number of intervals times.
  
  remove all the ends that equal the current value
  
  finally return if ends is empty meaning all the intervals have been completed.
  */
  bool isNStraightHand(vector<int>& hand, int W) {
    map<int, int> freq;
    for (const auto& h : hand) freq[h]++;
    queue<int> ends;

    pair<int, int> prev = {-1, -1};
    for (const auto& kv : freq) {
      if (prev.first != -1 && kv.first != prev.first + 1 && !ends.empty())
        return false;
      prev = kv;
      int diff = kv.second - ends.size();
      if (diff < 0) return false;  // too many numbers needed
      if (diff > 0) {
        // new ends
        for (int i = 0; i < diff; i++) ends.push(kv.first + W - 1);
      }

      while (!ends.empty() && kv.first == ends.front()) ends.pop();
    }

    return ends.empty();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
849. Maximize Distance to Closest Person
In a row of seats, 1 represents a person sitting in that seat, and 0 represents
that the seat is empty.

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest
person to him is maximized.

Return that maximum distance to closest person.

Example 1:

Input: [1,0,0,0,1,0,1]
Output: 2
Explanation:
If Alex sits in the second open seat (seats[2]), then the closest person has
distance 2. If Alex sits in any other open seat, the closest person has
distance 1. Thus, the maximum distance to the closest person is 2. Example 2:

Input: [1,0,0,0]
Output: 3
Explanation:
If Alex sits in the last seat, the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
Note:

1 <= seats.length <= 20000
seats contains only 0s or 1s, at least one 0, and at least one 1.
/*
    Submission Date: 2018-06-24
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxDistToClosest(vector<int>& seats) {
    if (seats.empty()) return INT_MAX;

    int N = seats.size();
    // left[i] indicates the distance to the closest 1 to the left
    vector<int> left(N, INT_MAX);
    for (int i = 0; i < N; i++) {
      if (seats[i] == 1)
        left[i] = 0;
      else if (i > 0 && left[i - 1] < INT_MAX) {
        left[i] = left[i - 1] + 1;
      }
    }

    int right = INT_MAX;
    int res = INT_MIN;
    /*
    if there is at least one 1 and 0
    left[i] will be INT_MAX until the first 1 then some number after it
    
    hence if starting from the back, the number will not be INT_MAX so right
    will be correctly minimized.
    */
    for (int i = N - 1; i >= 0; i--) {
      if (seats[i] == 1)
        right = 0;
      else if (right < INT_MAX)
        right++;

      res = max(res, min(left[i], right));
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
852. Peak Index in a Mountain Array
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i]
> A[i+1] > ... > A[A.length - 1] Given an array that is definitely a mountain,
return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... >
A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
/*
    Submission Date: 2018-06-24
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& A) {
    int low = 0;
    int high = A.size() - 1;
    while (low <= high - 2) {  // at least 3 elements
      int mid = low + (high - low) / 2;
      if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1]) {
        return mid;

        /*
        a number and the next number has only two conditions < and >
        if < then it is before the peak, so go right
        if > then it is after the peak, so go left
        
        need to include mid in the search as it can be either the left
        or right boundary to the peak
        */
      }
      if (A[mid - 1] < A[mid]) {
        low = mid;
      } else {  // A[mid-1] > A[mid]
        high = mid;
      }
    }

    return -1;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
856. Score of Parentheses
Given a balanced parentheses string S, compute the score of the string based on
the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
 

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
/*
    Submission Date: 2018-06-29
    Runtime: 4 ms
    Difficulty:MEDIUM
*/
#include <iostream>
#include <stack>

using namespace std;

class Solution {
 public:
  int scoreOfParentheses(string S) {
    // first is the value or -1 if it is a character '('
    stack<pair<int, char>> stk;
    for (const auto& e : S) {
      if (e == '(') {
        stk.emplace(-1, '(');
      } else {  // e == ')'
        // S is balanced so keep going back until '(' (ie not value)
        // add all the numbers in between and multiply by 2
        int in_between = 0;
        while (stk.top().first != -1) {
          in_between += stk.top().first;
          stk.pop();
        }

        stk.pop();
        stk.emplace(max(1, 2 * in_between), 'r');
      }
    }

    int res = 0;
    // since S is balanced then stk must only contain values so add
    // up and return value
    while (!stk.empty()) {
      res += stk.top().first;
      stk.pop();
    }

    return res;
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