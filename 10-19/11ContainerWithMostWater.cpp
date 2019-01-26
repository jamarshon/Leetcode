/*
11. Container With Most Water
Given n non-negative integers a1, a2, ..., an, where each represents a point at
coordinate (i, ai). n vertical lines are drawn such that the two endpoints of
line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis
forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

/*
    Submission Date: 2017-01-20
    Runtime: 32 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>
#include <vector>

class Solution {
 public:
  int maxArea(vector<int>& height) {
    int currentArea;
    int low = 0;
    int high = height.size() - 1;
    int maximumArea = -1;

    while (low < high) {
      currentArea = (high - low) * min(height[low], height[high]);
      maximumArea = max(currentArea, maximumArea);

      if (height[low] > height[high]) {
        high--;
      } else {
        low++;
      }
    }

    return maximumArea;
  }
};

int main() { return 0; }