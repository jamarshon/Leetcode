/*
15. 3Sum
Given an array S of n integers, are there elements a, b, c in S such that a + b
+ c = 0? Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
/*
    Submission Date: 2017-05-26
    Runtime: 99 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <map>
#include <vector>
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    map<int, int> freq;

    // Get the frequency of each number
    int N = nums.size();
    for (int i = 0; i < N; i++) {
      if (freq.find(nums[i]) == freq.end())
        freq[nums[i]] = 1;
      else
        freq[nums[i]]++;
    }

    // Store the unique numbers in a sorted order
    int count = freq.size();
    vector<int> uniq(count);

    int index = 0;
    for (map<int, int>::iterator it = freq.begin(); it != freq.end();
         ++it, ++index) {
      uniq[index] = it->first;
    }

    for (int i = 0; i < count; i++) {
      int nums_i = uniq[i];
      int target = -nums_i;

      int j = i + 1;
      int k = count - 1;

      // No positive integer besides zero can sum to zero so check if 3 zeros
      // exist then break
      if (nums_i >= 0) {
        if (nums_i == 0 && freq[nums_i] >= 3)
          res.push_back(vector<int>{0, 0, 0});
        break;
      }

      // nums_i + nums_i + (-2*nums_i) = 0
      if (freq[nums_i] >= 2) {
        int two_nums_i = 2 * target;
        if (freq.find(two_nums_i) != freq.end()) {
          res.push_back(vector<int>{nums_i, nums_i, two_nums_i});
        }
      }

      // (-0.5*nums_i) + (-0.5*nums_i) + nums_i = 0
      if (nums_i % 2 == 0) {
        int half_nums_i = target / 2;
        if (freq.find(half_nums_i) != freq.end() && freq[half_nums_i] >= 2) {
          res.push_back(vector<int>{half_nums_i, half_nums_i, nums_i});
        }
      }

      // Generic O(n) sweep of two sum for unique elements
      while (j < k) {
        int sum = uniq[j] + uniq[k];
        if (sum == target) {
          res.push_back(vector<int>{uniq[i], uniq[j], uniq[k]});
          j++;
          k--;
        } else if (sum < target) {
          j++;
        } else {
          k--;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }