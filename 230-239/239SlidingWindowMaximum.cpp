/*
239. Sliding Window Maximum
Given an array nums, there is a sliding window of size k which is
moving from the very left of the array to the very right. You can
only see the k numbers in the window. Each time the sliding window
moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ≤ k ≤ input array's
size for non-empty array.

Follow up:
Could you solve it in linear time?
/*
    Submission Date: 2017-08-21
    Runtime: 69 ms
    Difficulty: HARD
*/
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    typedef pair<int, int> pii;
    list<pii> ls;

    int N = nums.size();
    vector<int> res;
    for (int i = 0; i < N; i++) {
      while (!ls.empty() && ls.front().second <= i - k) {
        ls.pop_front();
      }

      while (!ls.empty() && ls.back().first < nums[i]) {
        ls.pop_back();
      }

      ls.emplace_back(nums[i], i);
      if (i >= k - 1) res.push_back(ls.front().first);
    }

    return res;
  }
};

int main() { return 0; }