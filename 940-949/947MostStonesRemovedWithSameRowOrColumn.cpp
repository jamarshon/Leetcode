/*
947. Most Stones Removed with Same Row or Column
On a 2D plane, we place stones at some integer coordinate points.  Each
coordinate point may have at most one stone.

Now, a move consists of removing a stone that shares a column or row with
another stone on the grid.

What is the largest possible number of moves we can make?

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5

Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3

Example 3:

Input: stones = [[0,0]]
Output: 0

Note:

  1 <= stones.length <= 1000
  0 <= stones[i][j] < 10000
/*
  Submission Date: 2019-02-16
  Runtime: 60 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct UnionFind {
  unordered_map<int, int> parent_, rank_;

  int FindHelper(int k) {
    if (parent_[k] != k) {
      parent_[k] = FindHelper(parent_[k]);
    }

    return parent_[k];
  }

  int Find(int k) {
    if (!parent_.count(k)) {
      parent_[k] = k;
      rank_[k] = 1;
    }

    return FindHelper(k);
  }

  void Union(int a, int b) {
    int a_root = Find(a);
    int b_root = Find(b);
    if (a_root == b_root) return;
    if (rank_[a_root] > rank_[b_root]) {
      parent_[b_root] = a_root;
    } else {
      parent_[a_root] = b_root;
      if (rank_[a_root] == rank_[b_root]) rank_[b_root]++;
    }
  }

  int NumberOfComponents() {
    int res = 0;
    for (const auto& kv : parent_) res += kv.first == kv.second;
    return res;
  }
};

class Solution {
 public:
  /*
  if a stone shares the same x or y coordinates then
  connect them in a graph. instead of connecting stones
  or indices, say that if two stones have the same x coordinates (same column)
  connect their y coordinates (the rows).
  connecting columns to rows can be done by having the key of columns
  be negative (x = -x-1 = ~x use -1 for zero to prevent collision) and the
  key for rows to be positive in union find.

  the result is the number of stones minus the number of islands
  this is because for each island we can remove all stones except one.
  this is done by doing a dfs and then removing those nodes in reverse
  similar to removing leaves from a tree.
  */
  int removeStones(vector<vector<int>>& stones) {
    UnionFind uf;
    int N = stones.size();
    for (const auto& s : stones) uf.Union(s[0], ~s[1]);
    return N - uf.NumberOfComponents();
  }
};

int main() { return 0; }
