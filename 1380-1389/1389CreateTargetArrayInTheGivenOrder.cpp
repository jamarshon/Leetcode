/*
1389. Create Target Array in the Given Order
Given two arrays of integers nums and index. Your task is to create target array
under the following rules:

  Initially target array is empty.
  From left to right read nums[i] and index[i], insert at index index[i] the
value nums[i] in target array.
  Repeat the previous step until there are no elements to read in nums and
index.

Return the target array.

It is guaranteed that the insertion operations will be valid.

Example 1:

Input: nums = [0,1,2,3,4], index = [0,1,2,2,1]
Output: [0,4,1,3,2]
Explanation:
nums       index     target
0            0        [0]
1            1        [0,1]
2            2        [0,1,2]
3            2        [0,1,3,2]
4            1        [0,4,1,3,2]

Example 2:

Input: nums = [1,2,3,4,0], index = [0,1,2,3,0]
Output: [0,1,2,3,4]
Explanation:
nums       index     target
1            0        [1]
2            1        [1,2]
3            2        [1,2,3]
4            3        [1,2,3,4]
0            0        [0,1,2,3,4]

Example 3:

Input: nums = [1], index = [0]
Output: [1]

Constraints:

  1 <= nums.length, index.length <= 100
  nums.length == index.length
  0 <= nums[i] <= 100
  0 <= index[i] <= i
/*
  Submission Date: 2020-04-19
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

class CountOfSmallerNumbersAfterSelf {
 public:
  void mergeSort(vector<pii>& v, vector<pii>& sp, int start, int end) {
    /* for a subarray of v for indices [start, end], there
    is a left subarray [start, mid] and a right subarray
    [mid + 1, end].

    At any given time, j represents the minimum number of elements
    smaller than left[i] to the right of it (could be more).
    for smaller numbers to the right of left[i], they are moved to
    the front of left[i] meaning the actual value is at least
    left[i] + j. the first right[j] that is strictly greater than
    left[i] + j will go behind left[i] so left[i] + j is the next
    element in the sorted sequence

    */
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(v, sp, start, mid);
    mergeSort(v, sp, mid + 1, end);

    int idx = 0;
    int s1 = start, s2 = mid + 1;
    const int e1 = mid + 1, e2 = end + 1;
    while (s1 < e1 || s2 < e2) {
      // right is empty (s2 >= e2) or right is bigger than left
      // so place left
      if (s2 >= e2 ||
          (s1 < e1 && v[s1].first + (s2 - (mid + 1)) < v[s2].first)) {
        v[s1].first += (s2 - (mid + 1));
        sp[idx++] = v[s1];
        s1++;
      } else {
        sp[idx++] = v[s2];
        s2++;
      }
    }

    for (int i = 0; i < idx; i++) v[i + start] = sp[i];
  }

  vector<pii> countSmaller(vector<int>& nums) {
    int N = nums.size();

    vector<pii> v, sp(N);

    for (int i = 0; i < N; i++) {
      v.emplace_back(nums[i], i);
    }

    mergeSort(v, sp, 0, N - 1);
    return v;
  }
};

class Solution {
 public:
  vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
    CountOfSmallerNumbersAfterSelf helper;
    const vector<pii>& arr = helper.countSmaller(index);
    vector<int> res(nums.size());
    for (const auto& p : arr) {
      res[p.first] = nums[p.second];
    }
    return res;
  }
};

class Solution2 {
 public:
  vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
    int N = index.size();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        if (index[i] <= index[j]) {
          // we put index[i] in front of index[j] so increment index[j]
          // to accomodate the element in front of it
          index[j]++;
        }
      }
    }
    vector<int> res(N);
    for (int i = 0; i < N; i++) {
      res[index[i]] = nums[i];
    }
    return res;
  }
};

int main() { return 0; }
