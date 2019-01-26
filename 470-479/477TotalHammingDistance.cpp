/*
477. Total Hamming Distance
The Hamming distance between two integers is the number of positions at which
the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the
given numbers.


Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010
(just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2
+ 2 = 6.



Note:

Elements of the given array are in the range of 0  to 10^9
Length of the array will not exceed 10^4.

/*
    Submission Date: 2018-07-08
    Runtime: 40 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  o(n) for the ith bit count how many 0 and how many 1 there are
  suppose there are x 0's and y 1's, then there are total x*y pairs
  because for every value in x, it can pair y values in y.
  */
  int totalHammingDistance(vector<int>& nums) {
    int N = nums.size();
    int res = 0;
    for (int i = 0; i < 31; i++) {
      int one_cnt = 0;
      for (const auto& n : nums) {
        bool one = n & (1 << i);
        one_cnt += one;
      }

      res += one_cnt * (N - one_cnt);
    }
    return res;
  }
};

int main() { return 0; }
