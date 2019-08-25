/*
1051. Height Checker
Students are asked to stand in non-decreasing order of heights for an annual
photo.

Return the minimum number of students not standing in the right positions. 
(This is the number of students that must move in order for all students to be
standing in non-decreasing order of height.)

Example 1:

Input: [1,1,4,2,1,3]
Output: 3
Explanation:
Students with heights 4, 3 and the last 1 are not standing in the right
positions.

Note:

  1 <= heights.length <= 100
  1 <= heights[i] <= 100
/*
  Submission Date: 2019-08-25
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // sort the list and see compare elmentwise between
  // the two lists to see how many elements are out of place
  int heightChecker(vector<int>& heights) {
    int res = 0;
    vector<int> v = heights;
    sort(v.begin(), v.end());
    for (int i = 0; i < heights.size(); i++) res += v[i] != heights[i];
    return res;
  }
};

int main() { return 0; }
