/*
207. Course Schedule
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to
first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it
possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have
finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have
finished course 0, and to take course 0 you should also have finished course 1.
So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency
matrices. Read more about how a graph is represented. You may assume that there
are no duplicate edges in the input prerequisites.

/*
    Submission Date: 2017-08-03
    Runtime: 23 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  bool checkForCycle(int vertex, const vector<vector<int>>& graph,
                     unordered_set<int>& visited,
                     unordered_set<int>& expanding) {
    if (expanding.count(vertex)) return false;

    expanding.insert(vertex);
    for (auto neighbor : graph[vertex]) {
      if (visited.count(neighbor)) continue;
      if (!checkForCycle(neighbor, graph, visited, expanding)) {
        return false;
      }
    }

    visited.insert(vertex);
    expanding.erase(vertex);

    return true;
  }
  bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto prereq : prerequisites) {
      graph[prereq.second].push_back(prereq.first);
    }

    unordered_set<int> visited, expanding;
    for (int i = 0; i < numCourses; i++) {
      if (visited.count(i)) continue;
      if (!checkForCycle(i, graph, visited, expanding)) {
        return false;
      }
    }
    return true;
  }
};

int main() { return 0; }