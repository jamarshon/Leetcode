/*
496. Next Greater Element I
You are given two arrays (without duplicates) nums1 and nums2 where nums1’s
elements are subset of nums2. Find all the next greater numbers for nums1's
elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to
its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for
it in the second array, so output -1. For number 1 in the first array, the next
greater number for it in the second array is 3. For number 2 in the first array,
there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the
second array is 3. For number 4 in the first array, there is no next greater
number for it in the second array, so output -1. Note: All elements in nums1 and
nums2 are unique. The length of both nums1 and nums2 would not exceed 1000.
/*
    Submission Date: 2018-06-02
    Runtime: 11 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
      For a stack of decreasing number, if there is a number x encountered.
      All the numbers in the stack that x is greater than will have their return
     value to be x and x is placed in the stack. This means there is no number
     in the stack that is less than x eg [1,3,4,2,3]
       []     1 => [1]
       [1]    3 => [3]    update greater(1) = 3
       [3]    4 => [4]    update greater(3) = 4
       [4]    2 => [4,2]
       [4,2]  3 => [4,3]  update greater(2) = 3
  */
  vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
    if (nums.empty()) return {};

    int N = findNums.size();
    // decreasing numbers
    stack<int> stk;

    unordered_map<int, int> val_to_greater_val;
    for (const auto& x : nums) {
      while (!stk.empty() && stk.top() < x) {
        val_to_greater_val[stk.top()] = x;
        stk.pop();
      }

      stk.push(x);
    }

    vector<int> res;
    for (const auto& x : findNums) {
      res.push_back(val_to_greater_val.count(x) ? val_to_greater_val[x] : -1);
    }
    return res;
  }
};

int main() { return 0; }