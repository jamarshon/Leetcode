#include <bits/stdc++.h>

int solve(const vector<int>& v, int N) {
  vector<int> dp(N);
  int res = 0;
  for (int i = N - 1; i >= 0; i--) {
    dp[i] = i;
    if (i + 1 < N && v[i] < v[dp[dp[i + 1]]]) {
      dp[i] = dp[dp[i + 1]];
    }

    res = max(res, dp[i] - i);
  }

  return res;
}

int main() {
  int T, N;
  cin >> T;
  for (int i = 0; i < T; i++) {
    cin >> N;
    vector<int> v(N);
    for (int j = 0; j < N; j++) {
      cin >> v[j];
    }
    cout << solve(v, N) << endl;
  }

  return 0;
}