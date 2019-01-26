/*
354. Russian Doll Envelopes
You have a number of envelopes with widths and heights given as a pair of
integers (w, h). One envelope can fit into another if and only if both the width
and height of one envelope is greater than the width and height of the other
envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside
other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you
can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
/*
    Submission Date: 2018-05-24
    Runtime: 30 ms
    Difficulty: HARD
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    NlogN sort by width and break ties on height
    For all elements with the same width, apply the changes all at once
    Similar to LIS where dp[i] is the smallest element of sequence of length i
*/
class Solution {
 public:
  int maxEnvelopes(vector<pair<int, int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end());
    vector<int> heights;

    for (int i = 0; i < envelopes.size();) {
      int start = i;
      unordered_map<int, int> index_to_new_val;
      while (i < envelopes.size() &&
             envelopes[i].first == envelopes[start].first) {
        auto it =
            lower_bound(heights.begin(), heights.end(), envelopes[i].second);
        int dist = it - heights.begin();
        if (!index_to_new_val.count(dist))
          index_to_new_val[dist] = envelopes[i].second;
        i++;
      }

      for (const auto& kv : index_to_new_val) {
        if (kv.first < heights.size()) {
          heights[kv.first] = kv.second;
        } else {
          heights.push_back(kv.second);
        }
      }
    }
    return heights.size();
  }
};

/*
    N^2 similar to LIS where dp[i] means the longest sequence ending at element
   i Requires a sort first as all elements of smaller width should appear first.
*/
class Solution2 {
 public:
  int maxEnvelopes(vector<pair<int, int>>& envelopes) {
    sort(envelopes.begin(), envelopes.end());
    vector<int> dp(envelopes.size(), 1);

    for (int i = 0; i < envelopes.size(); i++) {
      for (int j = 0; j < i; j++) {
        if (envelopes[i].first > envelopes[j].first &&
            envelopes[i].second > envelopes[j].second) {
          dp[i] = max(dp[i], 1 + dp[j]);
        }
      }
    }
    return dp.empty() ? 0 : *max_element(dp.begin(), dp.end());
  }
};

int main() { return 0; }