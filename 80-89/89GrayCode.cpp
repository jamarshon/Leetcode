/*
89. Gray Code

The gray code is a binary numeral system where two successive values differ in
only one bit.

Given a non-negative integer n representing the total number of bits in the
code, print the sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above
definition.

For now, the judge is able to judge based on one instance of gray code sequence.
Sorry about that.

/*
    Submission Date: 2017-06-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> grayCode(int n) {
    if (n == 0) return {0};

    vector<int> prev = grayCode(n - 1);

    for (int i = prev.size() - 1; i >= 0; i--) {
      prev.push_back(prev[i] + (1 << (n - 1)));
    }

    return prev;
  }
};

int main() {
  Solution s;
  vector<int> t = s.grayCode(2);
  for (auto e : t) cout << bitset<3>(e).to_string() << endl;
  return 0;
}