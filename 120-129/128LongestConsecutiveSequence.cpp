/*
128. Longest Consecutive Sequence
Given an unsorted array of integers, find the length of the longest consecutive
elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

/*
    Submission Date: 2017-06-29
    Runtime: 12 ms
    Difficulty: HARD
*/

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int res = 0;
    for (auto item : s) {
      int range = 1;
      int temp = item - 1;
      while (s.count(temp)) {
        s.erase(temp);
        temp--;
        range++;
      }

      temp = item + 1;
      while (s.count(temp)) {
        s.erase(temp);
        temp++;
        range++;
      }

      res = max(res, range);
    }
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}