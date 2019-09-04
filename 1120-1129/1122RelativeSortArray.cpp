/*
1122. Relative Sort Array
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all
elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are
the same as in arr2.  Elements that don't appear in arr2 should be placed at the
end of arr1 in ascending order.

Example 1:
Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]

Constraints:

  arr1.length, arr2.length <= 1000
  0 <= arr1[i], arr2[i] <= 1000
  Each arr2[i] is distinct.
  Each arr2[i] is in arr1.
/*
  Submission Date: 2019-09-03
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    unordered_map<int, int> arr2_to_ind;
    for (int i = 0; i < arr2.size(); i++) {
      arr2_to_ind[arr2[i]] = i;
    }

    auto end_it = arr2_to_ind.end();

    sort(arr1.begin(), arr1.end(),
         [&arr2_to_ind, &end_it](const int& left, const int& right) {
           auto left_it = arr2_to_ind.find(left);
           auto right_it = arr2_to_ind.find(right);
           if (left_it == end_it && right_it == end_it) {
             // ascending order
             return left < right;
           } else if (left_it == end_it) {
             // put the right in front as the left is not defined
             return false;
           } else if (right_it == end_it) {
             // put the left in front as the right is not defined
             return true;
           } else {
             // return the relative order of left, right
             return left_it->second < right_it->second;
           }
         });

    return arr1;
  }
};

int main() { return 0; }
