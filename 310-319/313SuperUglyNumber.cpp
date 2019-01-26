/*
313. Super Ugly Number
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given
prime list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26,
28, 32] is the sequence of the first 12 super ugly numbers given primes = [2, 7,
13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 10^6, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

/*
    Submission Date: 2017-08-12
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution2 {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int K = primes.size();
    if (n <= 0 || K <= 0) return 0;

    set<int> res{1};
    vector<int> last_prime(K, 1);

    while (res.size() < n) {
      int min_j = 0;
      for (int j = 1; j < K; j++) {
        if (last_prime[j] * primes[j] < last_prime[min_j] * primes[min_j]) {
          min_j = j;
        }
      }

      res.insert(last_prime[min_j] * primes[min_j]);
      last_prime[min_j] = *res.upper_bound(last_prime[min_j]);
    }

    return *res.rbegin();
  }
};

class Solution3 {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int K = primes.size();
    if (n <= 0 || K <= 0) return 0;

    // idx[j] corresponds to the first element in dp which
    // primes[j]*dp[idx[j]] >= dp[i]
    vector<int> dp(n), idx(K, 0);
    dp[0] = 1;

    for (int i = 1; i < n; i++) {
      int best_j = 0;
      for (int j = 0; j < K; j++) {
        // avoid duplicates e.g 4*3 and 6*2
        if (dp[idx[j]] * primes[j] == dp[i - 1]) idx[j]++;
        if (dp[idx[j]] * primes[j] < dp[idx[best_j]] * primes[best_j]) {
          best_j = j;
        }
      }
      dp[i] = dp[idx[best_j]] * primes[best_j];
      idx[best_j]++;
    }

    return dp[n - 1];
  }
};

class Solution {
 public:
  int nthSuperUglyNumber(int n, vector<int>& primes) {
    int K = primes.size();
    if (n <= 0 || K <= 0) return 0;

    vector<int> dp(n);
    dp[0] = 1;
    // pair<prime, index in dp>
    auto func = [&dp](const pair<int, int> lhs, const pair<int, int> rhs) {
      return lhs.first * dp[lhs.second] > rhs.first * dp[rhs.second];
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(func)> pq(
        func);

    for (int i = 0; i < K; i++) pq.push({primes[i], 0});

    for (int i = 1; i < n; i++) {
      pair<int, int> p;
      do {
        p = pq.top();
        pq.pop();
        dp[i] = p.first * dp[p.second];
        pq.emplace(p.first, p.second + 1);
      } while (p.first * dp[p.second] == dp[i - 1]);
    }

    return dp[n - 1];
  }
};

int main() { return 0; }