/*
433. Minimum Genetic Mutation
A gene string can be represented by an 8-character long string, with choices
from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to
"end"), where ONE mutation is defined as ONE single character changed in the
gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations.
A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the
minimum number of mutations needed to mutate from "start" to "end". If there is
no such a mutation, return -1.

Note:

Starting point is assumed to be valid, so it might not be included in the bank.
If multiple mutations are needed, all mutations during in the sequence must be
valid. You may assume start and end string is not the same. Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1
Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  bool isConnect(string s1, string s2) {
    int diff_count = 0;
    for (int i = 0, len = s1.size(); i < len; i++) {
      diff_count += s1[i] != s2[i];
    }
    return diff_count == 1;
  }

 public:
  int minMutation(string start, string end, vector<string>& bank) {
    unordered_map<string, vector<string>> graph;

    bank.push_back(start);
    int N = bank.size();
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if (isConnect(bank[i], bank[j])) {
          graph[bank[i]].push_back(bank[j]);
          graph[bank[j]].push_back(bank[i]);
        }
      }
    }

    unordered_set<string> visited;
    queue<pair<string, int>> q;
    q.emplace(start, 0);
    visited.insert(start);

    string curr;
    int dist;
    while (!q.empty()) {
      tie(curr, dist) = q.front();
      // cout << curr << ' ' << dist << endl;
      q.pop();
      if (curr == end) return dist;
      for (auto neighbor : graph[curr]) {
        if (visited.count(neighbor)) continue;
        q.emplace(neighbor, dist + 1);
        visited.insert(neighbor);
      }
    }
    return -1;
  }
};

int main() { return 0; }