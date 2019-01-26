/*
684. Redundant Connection
In this problem, a tree is an undirected graph that is connected and has no
cycles.

The given input is a graph that started as a tree with N nodes (with distinct
values 1, 2, ..., N), with one additional edge added.  The added edge has two
different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges.  Each element of edges is a
pair [u, v] with u < v, that represents an undirected edge connecting nodes u
and v.

Return an edge that can be removed so that the resulting graph is a tree of N
nodes.  If there are multiple answers, return the answer that occurs last in the
given 2D-array.  The answer edge [u, v] should be in the same format, with u <
v.
Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3


Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3


Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is
the size of the input array.





Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly
the graph is an undirected graph. For the directed graph follow up please see
Redundant Connection II). We apologize for any inconvenience caused.

/*
    Submission Date: 2018-07-11
    Runtime: 4 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template <typename T>
class UnionFind {
  // key is element, value is rank
  unordered_map<T, int> rank_;
  // key is element, value is parent
  unordered_map<T, T> parent_;

 public:
  bool IsWithinSet(T e) { return parent_.count(e); }

  void CreateSet(T e) {
    assert(!IsWithinSet(e));
    parent_[e] = e;
    rank_[e] = 0;
  }

  // finds the root of e
  T Find(T e) {
    if (parent_[e] != e) {
      // this is not a root (root has parent to be equal itself)
      // so find root and apply path compression along path
      parent_[e] = Find(parent_[e]);
    }
    return parent_[e];
  }

  // unions the sets of e1 and e2 if necessary
  // return whether an union took place
  bool Union(T e1, T e2) {
    T e1_root = Find(e1);
    T e2_root = Find(e2);

    if (e1_root == e2_root) return false;  // same root

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (rank_[e1_root] < rank_[e2_root]) {
      parent_[e1_root] = e2_root;
    } else {
      parent_[e2_root] = e1_root;
      if (rank_[e1_root] == rank_[e2_root]) {
        rank_[e1_root]++;
      }
    }

    return true;
  }
};

class Solution {
 public:
  /*
  union find
  for each node uv, find if u and v are seperate sets. if they are, union the
  sets else they are in the same set and already connected so return uv
  */
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    UnionFind<int> uf;
    for (const auto& uv : edges) {
      if (!uf.IsWithinSet(uv[0])) uf.CreateSet(uv[0]);
      if (!uf.IsWithinSet(uv[1])) uf.CreateSet(uv[1]);
      if (!uf.Union(uv[0], uv[1])) {  // no union occured as same set already
        return uv;
      }
    }

    return {};
  }
};

class Solution2 {
  vector<int> path;
  int u = -1;

 public:
  bool dfs(int from, unordered_map<int, vector<int>>& adj,
           unordered_set<int>& visited, int parent) {
    for (const auto& to : adj[from]) {
      if (to == parent) continue;
      if (visited.count(to)) {
        u = to;
        return true;
      }

      visited.insert(to);

      path.push_back(to);
      if (dfs(to, adj, visited, from)) {
        return true;
      }
      path.pop_back();
    }

    return false;
  }

  /*
  do dfs and keep track of path. for nodes that are not in cycle the popback
  will remove them the result is path is vector of nodes that go into a cycle
  and u marks where the cycle begins now traverse the cycle (ie path) and find
  the edge that has highest index
  */
  vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    unordered_map<int, vector<int>> adj;

    unordered_map<int, unordered_map<int, int>> priority;
    int i = 0;
    for (const auto& uv : edges) {
      adj[uv[1]].push_back(uv[0]);
      adj[uv[0]].push_back(uv[1]);
      priority[uv[0]][uv[1]] = i++;
    }

    unordered_set<int> visited;

    // no disjoint so can just start at one node and will traverse everything
    visited.insert(1);
    path.push_back(1);

    bool cycle = dfs(1, adj, visited, -1);
    assert(cycle);
    i = 0;
    while (path[i] != u) i++;

    int start = i;
    int pos_u = -1;
    int pos_v = -1;
    int N = path.size();
    for (int j = i; j < N; j++) cout << path[j] << ' ';
    cout << endl;
    for (; i < N; i++) {
      auto p = minmax(path[i], i + 1 < N ? path[i + 1] : path[start]);
      if (pos_u == -1 || priority[p.first][p.second] > priority[pos_u][pos_v]) {
        pos_u = p.first;
        pos_v = p.second;
      }
    }

    return {pos_u, pos_v};
  }
};

int main() { return 0; }
