/*
306. Additive Number
Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers.
Except for the first two numbers, each subsequent number in the
sequence must be the sum of the preceding two.

For example:
"112358" is an additive number because the digits can form an
additive sequence: 1, 1, 2, 3, 5, 8.

1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
"199100199" is also an additive number, the additive sequence is:
1, 99, 100, 199.
1 + 99 = 100, 99 + 100 = 199
Note: Numbers in the additive sequence cannot have leading zeros,
so sequence 1, 2, 03 or 1, 02, 3 is invalid.

Given a string containing only digits '0'-'9', write a function
to determine if it's an additive number.

Follow up:
How would you handle overflow for very large input integers?
/*
    Submission Date: 2017-08-21
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  bool isAdditiveNumber(string num) {
    int N = num.size();

    long long o1 = 0;
    long long o2 = 0;

    // given a string, we extract o1 and o2 from it leaving (o3)xxxx and calling
    // the recursive function
    for (int i = 0; i < N; i++) {
      o1 = o1 * 10 + (num[i] - '0');
      o2 = 0;
      for (int j = i + 1; j < N; j++) {
        o2 = o2 * 10 + (num[j] - '0');
        if (isAdditiveNumber(num.substr(j + 1), o2, o1 + o2)) {
          return true;
        }
        if (o2 == 0) break;  // o2 begins with 0
      }

      if (o1 == 0) break;  // o1 begins with 0
    }

    return false;
  }

  // num should be (o3)xxxx if it is o3 then return true
  // else if it is (o3)xxxx then call the function on xxxx looking for o2 + o3
  // at the front and o3 becomes o2 f(num, o2, o3) -> f(num.substr(i), o3, o2 +
  // o3) where i the first index of x
  bool isAdditiveNumber(string num, long long o2, long long o3) {
    int N = num.size();
    if (N == 0) return false;
    if (num.front() == '0') return N == 1 && o3 == 0;  // o3 begins with zero

    long long curr = 0;
    for (int i = 0; i < N; i++) {
      curr = curr * 10 + (num[i] - '0');
      if (curr > o3) return false;
      if (curr == o3) {
        return i == N - 1 || isAdditiveNumber(num.substr(i + 1), o3, o2 + o3);
      }
    }

    return false;
  }
};

int main() {
  Solution s;
  return 0;
}