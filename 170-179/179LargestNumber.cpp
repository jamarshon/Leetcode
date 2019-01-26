/*
179. Largest Number
Given a list of non negative integers, arrange them such that they form the
largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an
integer.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string concat(const vector<string>& nums_str) {
    return accumulate(
        nums_str.begin(), nums_str.end(), string(),
        [](const string& memo, const string& el) { return memo + el; });
  }

  string largestNumber(vector<int>& nums) {
    if (nums.empty()) return "0";
    int N = nums.size();
    vector<string> nums_str(N);
    transform(nums.begin(), nums.end(), nums_str.begin(),
              [](const int& num) { return to_string(num); });
    sort(nums_str.begin(), nums_str.end(),
         [](const string& lhs, const string& rhs) {
           return lhs + rhs > rhs + lhs;
         });

    if (nums_str.front()[0] == '0') return "0";
    return concat(nums_str);
  }
};

int main() {
  Solution s;
  return 0;
}