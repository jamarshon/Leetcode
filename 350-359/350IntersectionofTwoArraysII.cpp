/*
350. Intersection of Two Arrays II
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in
both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your
algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm
is better?
What if elements of nums2 are stored on disk, and the memory is limited
such that you cannot load all elements into the memory at once?
/*
    Submission Date: 2017-09-10
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int>*smaller = &nums1, *greater = &nums2;
    if (smaller->size() > greater->size()) swap(smaller, greater);

    unordered_map<int, int> smaller_freq;
    for (auto n : *smaller) smaller_freq[n]++;

    vector<int> res;
    for (auto n : *greater) {
      if (smaller_freq.count(n) && smaller_freq[n] > 0) {
        smaller_freq[n]--;
        res.push_back(n);
      }
    }

    return res;
  }
};

int main() { return 0; }