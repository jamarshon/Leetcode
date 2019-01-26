/*
769. Max Chunks To Make Sorted
Given an array arr that is a permutation of [0, 1, ..., arr.length - 1], we
split the array into some number of "chunks" (partitions), and individually sort
each chunk.  After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:

Input: arr = [4,3,2,1,0]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2],
which isn't sorted.


Example 2:

Input: arr = [1,0,2,3,4]
Output: 4
Explanation:
We can split into two chunks, such as [1, 0], [2, 3, 4].
However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks
possible.


Note:


    arr will have length in range [1, 10].
    arr[i] will be a permutation of [0, 1, ..., arr.length - 1].

/*
    Submission Date: 2018-07-08
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  nums[i] must be moved to the index nums[i] so keep track of right
  boundary, once i > right boundary it means all the number from the previous
  right boundary this right boundary can be sorted such that nums[i] == i
  so increase res by 1
  
  proof that nums[i] will never get sorted to a number of a previous boundary
  all numbers from [0, i) all smaller than i as i was the previous boundary
  hence nums[i] must be >= i (ie you won't find any smaller number outside
  of the boundary as all of them are already in boundary since there are
  exactly i numbers < i)
  */
  int maxChunksToSorted(vector<int>& arr) {
    int right = 0;
    int N = arr.size();
    int res = 1;
    for (int i = 0; i < N; i++) {
      if (i > right) {
        res++;
      }
      right = max(right, arr[i]);
    }

    return res;
  }
};

int main() { return 0; }
