/*
743. Network Delay Time
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w),
where u is the source node, v is the target node, and w is the time it takes for
a signal to travel from source to target.

Now, we send a signal from a certain node K.  How long will it take for all
nodes to receive the signal?  If it is impossible, return -1.

Note:

N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
/*
  Submission Date: 2019-01-26
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
 public:
  typedef pair<int, int> pii;
  int networkDelayTime(vector<vector<int>>& times, int N, int K) {
    vector<vector<pii>> edges(N);
    K--;
    for (auto& v : times) {
      edges[v[0] - 1].emplace_back(v[2], v[1] - 1);
    }

    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, K);
    vector<int> dist(N, INT_MAX);
    dist[K] = 0;
    int cnt = 0;
    while (cnt < N && !q.empty()) {
      int weight, node;

      tie(weight, node) = q.top();
      q.pop();

      if (dist[node] == INT_MAX) break;
      if (dist[node] < weight) continue;
      cnt++;

      for (pii& n : edges[node]) {
        if (dist[n.second] == INT_MAX ||
            dist[node] + n.first < dist[n.second]) {
          dist[n.second] = dist[node] + n.first;
          q.emplace(dist[n.second], n.second);
        }
      }
    }
    int res = *max_element(dist.begin(), dist.end());
    return res == INT_MAX ? -1 : res;
  }
};

int main() { return 0; }
