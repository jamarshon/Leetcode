/*
474. Ones and Zeroes
In the computer world, use restricted resource you have to generate maximum
benefit is what we always want to pursue.
For now, suppose you are a dominator of m 0s and n 1s respectively. On the other
hand, there is an array with strings consisting of only 0s and 1s.


Now your task is to find the maximum number of strings that you can form with
given m 0s and n 1s. Each 0 and 1 can be used at most once.



Note:

The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.



Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3
1s, which are “10,”0001”,”1”,”0”



Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form
"0" and "1".

/*
    Submission Date: 2018-07-12
    Runtime: 32 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  dp[i][j] is the maximum elements to find i 0's and j 1's
  need to do this for every element in v
  need to go from bottom right to top left as shouldn't visit
  a value that is updated already
  */
  int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    dp[0][0] = 0;

    int res = 0;
    for (const auto& s : strs) {
      int num_zero = 0, num_one = 0;
      for (const auto& c : s) {
        num_zero += c == '0';
        num_one += c == '1';
      }

      // i + num_zero <= m => i <= m - num_zero
      for (int i = m - num_zero; i >= 0; i--) {
        for (int j = n - num_one; j >= 0; j--) {
          // if dp[i][j] can be found
          if (dp[i][j] != -1) {
            dp[i + num_zero][j + num_one] =
                max(dp[i + num_zero][j + num_one], 1 + dp[i][j]);

            res = max(res, dp[i + num_zero][j + num_one]);
          }
        }
      }
    }

    return res;
  }
};

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct Hash {
  template <typename T, typename U>
  size_t operator()(const pair<T, U>& p) const {
    size_t seed = 0;
    hash_combine(seed, p.first);
    hash_combine(seed, p.second);
    return seed;
  }
};

class Solution3 {
 public:
  /*
  curr has key i, j where i is number of 0 and j is number of 1
  the value is the maximum amount of elements to get there
  
  start curr with m,n and 0
  
  for every number, loop over every i,j and see if we can use the number
  meaning i-number_0, j-number_1 is >= 0, 0. we reached this new state with
  1 + kv.second so max this on every time we hit this new state from using
  a different i,j state as well as max this with not using number.
  */
  int findMaxForm(vector<string>& strs, int m, int n) {
    int N = strs.size();
    vector<pair<int, int>> v(N, {0, 0});
    for (int i = 0; i < N; i++) {
      for (const auto& c : strs[i]) {
        v[i].first += c == '0';
        v[i].second += c == '1';
      }
    }

    unordered_map<pair<int, int>, int, Hash> curr;
    curr[make_pair(m, n)] = 0;

    int res = 0;
    for (int i = N - 1; i >= 0; i--) {
      unordered_map<pair<int, int>, int, Hash> new_curr;
      for (const auto& kv : curr) {
        const auto& p = kv.first;
        if (p.first >= v[i].first && p.second >= v[i].second) {
          const auto& new_p =
              make_pair(p.first - v[i].first, p.second - v[i].second);
          new_curr[new_p] = max(new_curr[new_p], 1 + kv.second);
          if (curr.count(new_p))
            new_curr[new_p] = max(curr[new_p], new_curr[new_p]);
          res = max(res, new_curr[new_p]);
        }
      }

      for (const auto& kv : new_curr) {
        curr[kv.first] = kv.second;
      }
    }
    return res;
  }
};

class Solution2 {
 public:
  /*
  take or not take v[index] this solution times out
  */
  int f(int index, const vector<pair<int, int>>& v, int N, int m, int n) {
    if (index == N) return 0;

    int res = f(index + 1, v, N, m, n);
    if (v[index].first <= m && v[index].second <= n) {
      res = max(
          res, 1 + f(index + 1, v, N, m - v[index].first, n - v[index].second));
    }
    return res;
  }
  int findMaxForm(vector<string>& strs, int m, int n) {
    int N = strs.size();
    vector<pair<int, int>> v(N, {0, 0});
    for (int i = 0; i < N; i++) {
      for (const auto& c : strs[i]) {
        v[i].first += c == '0';
        v[i].second += c == '1';
      }
    }

    return f(0, v, N, m, n);
  }
};

int main() { return 0; }
