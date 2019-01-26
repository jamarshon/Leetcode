/*
332. Reconstruct Itinerary
Given a list of airline tickets represented by pairs of departure and arrival
airports [from, to], reconstruct the itinerary in order. All of the tickets
belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
If there are multiple valid itineraries, you should return the itinerary that
has the smallest lexical order when read as a single string. For example, the
itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"]. All
airports are represented by three capital letters (IATA code). You may assume
all tickets form at least one valid itinerary. Example 1: tickets = [["MUC",
"LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]] Return ["JFK", "MUC",
"LHR", "SFO", "SJC"]. Example 2: tickets =
[["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]] Return
["JFK","ATL","JFK","SFO","ATL","SFO"]. Another possible reconstruction is
["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
/*
    Submission Date: 2018-05-02
    Runtime: 20 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  // m is unordered key of 'from' with value of ordered key of 'to' with value
  // frequency
  void recurse(unordered_map<string, map<string, int>>& m, string from,
               const int& tickets_to_use, vector<string>& curr,
               vector<string>& res) {
    if (tickets_to_use == 0) {
      assert(res.empty());
      res = curr;
    } else {
      if (!m.count(from)) return;

      for (auto& kv : m[from]) {
        if (kv.second > 0) {
          // there is a to for from so try to use it
          kv.second--;
          curr.push_back(kv.first);
          recurse(m, kv.first, tickets_to_use - 1, curr, res);
          // if res isn't empty, then a path was found and return it
          curr.pop_back();
          if (!res.empty()) return;
          kv.second++;
        }
      }
    }
  }

  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    unordered_map<string, map<string, int>> m;
    for (auto p : tickets) m[p.first][p.second]++;
    vector<string> res, curr;
    curr.push_back("JFK");
    recurse(m, curr.front(), tickets.size(), curr, res);
    return res;
  }
};

class Solution2 {
 public:
  /*
  Eulerian path using Hierholzer's algorithm
  Starting from a vertex, do a dfs. put the vertex in the stack and then loop
  back outward.
  */
  void recurse(unordered_map<string, multiset<string>>& m, string from,
               vector<string>& stk) {
    while (!m[from].empty()) {
      const string& to = *(m[from].begin());
      m[from].erase(m[from].begin());
      recurse(m, to, stk);
    }

    stk.push_back(from);
  }

  vector<string> findItinerary(vector<pair<string, string>> tickets) {
    unordered_map<string, multiset<string>> m;
    for (auto p : tickets) m[p.first].insert(p.second);
    vector<string> stk;
    recurse(m, "JFK", stk);
    reverse(stk.begin(), stk.end());
    return stk;
  }
};

int main() { return 0; }