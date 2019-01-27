/*
754. Reach a Number
You are standing at position 0 on an infinite number line.  There is a goal at
position target.

On each move, you can either go left or right.  During the n-th move (starting
from 1), you take n steps.

Return the minimum number of steps required to reach the destination.

Example 1:
Input: target = 3
Output: 2
Explanation:
On the first move we step from 0 to 1.
On the second step we step from 1 to 3.

Example 2:
Input: target = 2
Output: 3
Explanation:
On the first move we step from 0 to 1.
On the second move we step  from 1 to -1.
On the third move we step from -1 to 2.

Note:
target will be a non-zero integer in the range [-10^9, 10^9].
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  int reachNumber(int target) {
    target = abs(target);  // due to symmetry.

    // n*(n+1)/2 <= target
    int n = (-1LL + sqrt(1LL + 8LL * target)) / 2LL;

    if (n * (n + 1) / 2 < target) n++;

    int sum = n * (n + 1) / 2;
    // if the difference between sum and target is even,
    // then we can reach target by changing a right to left
    // which will cause a loss of 2 times the value.
    // we can do this for any amount of numbers that equal to
    // half the difference. The difference will be at most n (the
    // last step) and it is guaranteed to have some combination
    // that adds up to at least n/2 because it is consecutive
    // no gaps hence able to create numbers from [0, n*(n+1)/2]
    while ((sum - target) % 2 != 0) {
      n++;
      sum += n;
    }

    return n;
  }
};

int main() { return 0; }
