/*
334. Increasing Triplet Subsequence
Given an unsorted array return whether an increasing subsequence of
length 3 exists or not in the array.

Formally the function should:
Return true if there exists i, j, k
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else
return false.
Your algorithm should run in O(n) time complexity and O(1) space
complexity.

Examples:
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.
/*
    Submission Date: 2017-08-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      we have a vector of size 3 where smallest[i] indicates
      the smallest last element of a sequence of size i

      similar to LIS

      for example if smallest is {1, _, _} and a 2 is found
      it becomes {1, 2, _} but if a 0 is found it becomes
      {0, 2, _}. Notice how it stops replacing as soon as finds
      a smallest[i] <= num. this is to prevent replacing multiple
      values.
  */
  bool increasingTriplet(vector<int>& nums) {
    vector<int> smallest(3, 0);
    int size = 0;

    for (auto num : nums) {
      bool found_replace = false;
      for (int i = 0; i < size; i++) {
        if (num <= smallest[i]) {
          smallest[i] = num;
          found_replace = true;
          break;
        }
      }

      if (found_replace) continue;

      if (size == 0 || smallest[size - 1] < num) {
        smallest[size++] = num;
      }

      if (size == 3) return true;
    }

    return false;
  }
};

int main() {
  Solution s;
  return 0;
}