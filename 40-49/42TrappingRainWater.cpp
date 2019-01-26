/*
42. Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of
each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int trap(vector<int>& height) {
    int len = height.size();

    int temp = 0;
    int res = 0;
    int curr_max = 0;
    for (int i = 1; i < len; i++) {
      if (height[i] >= height[curr_max]) {
        res += (i - curr_max - 1) * height[curr_max] - temp;
        curr_max = i;
        temp = 0;
      } else {
        temp += height[i];
      }
    }
    temp = 0;
    curr_max = len - 1;
    for (int i = len - 2; i >= 0; i--) {
      if (height[i] > height[curr_max]) {
        res += (curr_max - i - 1) * height[curr_max] - temp;
        curr_max = i;
        temp = 0;
      } else {
        temp += height[i];
      }
    }

    return res;
  }
};

int main() {
  Solution s;
  vector<int> v{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  // vector<int> v{2,0,2};
  cout << s.trap(v);
  return 0;
}