/*
210. Course Schedule II
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to
first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the
ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it
is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have
finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have
finished both courses 1 and 2. Both courses 1 and 2 should be taken after you
finished course 0. So one correct course order is [0,1,2,3]. Another correct
ordering is [0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency
matrices. Read more about how a graph is represented. You may assume that there
are no duplicate edges in the input prerequisites.

/*
    Submission Date: 2017-07-26
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool TopologicalSortUtil(const int vertex,
                           const vector<vector<int>>& vertex_to_edges,
                           unordered_set<int>& visited,
                           unordered_set<int>& expanding, stack<int>& st) {
    if (expanding.count(vertex)) {
      return true;
    }

    expanding.insert(vertex);

    for (auto neighbor : vertex_to_edges[vertex]) {
      if (visited.count(neighbor)) continue;
      bool has_cycle = TopologicalSortUtil(neighbor, vertex_to_edges, visited,
                                           expanding, st);
      if (has_cycle) return true;
    }

    visited.insert(vertex);
    expanding.erase(vertex);

    st.push(vertex);
    return false;
  }

  vector<int> TopologicalSort(const int numCourses,
                              const vector<vector<int>>& vertex_to_edges) {
    unordered_set<int> visited;
    unordered_set<int> expanding;
    stack<int> st;

    bool has_cycle = false;
    for (int vertex = 0; vertex < numCourses; vertex++) {
      if (visited.count(vertex)) continue;
      has_cycle =
          TopologicalSortUtil(vertex, vertex_to_edges, visited, expanding, st);
      if (has_cycle) break;
    }

    vector<int> res;
    if (!has_cycle) {
      while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
      }
    }

    return res;
  }
  vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> vertex_to_edges(numCourses, vector<int>{});

    for (auto prereq : prerequisites) {
      vertex_to_edges[prereq.second].push_back(prereq.first);
    }

    return TopologicalSort(numCourses, vertex_to_edges);
  }
};

int main() { return 0; }