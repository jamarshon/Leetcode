/*
453. Minimum Moves to Equal Array Elements
Given a non-empty integer array of size n, find the minimum number of moves
required to make all array elements equal, where a move is incrementing n - 1
elements by 1.

Example:

Input:
[1,2,3]

Output:
3

Explanation:
Only three moves are needed (remember each move increments two elements):

[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
/*
    Submission Date: 2018-06-07
    Runtime: 51 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  increasing everything besides a number is equivalent to decreasing the number
  by 1 so if all the numbers have to be decreased to equal the same value, then
  they should all be decreased until it reaches the smallest element in the
  array
  
  e.g 1 4 7
  the 4 needs to be decreased 3 times and the 7 decreased 6 times to get
  (4-1) + (7-1) = 9
  
  or
  
  let an array be A = {A[0], A[1], A[2], ... A[N]} and Z = {Z[0], Z[1], Z[2],
  Z[N]} where Z[i] means the number of rows where the element at i is zero then
  if x is the final value which all the elements equal to then
  
  A[0] + Z[1] + Z[2] + ... + Z[N] = x
  Z[0] + A[1] + Z[2] + ... + Z[N] = x
  Z[0] + Z[1] + A[2] + ... + Z[N] = x
  ...
  
  subtracting one row from another gets
  Z[0] - Z[1] + A[1] - A[0] = 0
  Z[1] - Z[0] = A[1] - A[0]
  
  let Z[0] = 0,
  Z[i] = A[i] - A[i-1] + Z[i-1]
      = A[i] - A[i-1] + (A[i-1] - A[i-2] + Z[i-2])
      = A[i] - A[i-1] + (A[i-1] - A[i-2] + (A[i-2] - A[i-3] + Z[i-3]))
      = A[i] - A[i-1] + (A[i-1] - A[i-2] + (A[i-2] - A[i-3] + .... -A[1] + (A[1]
  - A[0] + Z[0])))
      ...
      = A[i] + (A[i-1] - A[i-1]) + (A[i-2] - A[i-2]) + .... (A[1] - A[1]) - A[0]
      = A[i] - A[0]
  
  The result is number of rows or sum Z[i] from i = [0, N]
  Z[i] must be >= 0 as number of rows can't be negative. to minimize then
  A[i] - A[0] should have A[0] as large as possible with having A[i] become < 0
  so A[0] should be the smallest in the array as A[min_ind] - A[min_ind] >= 0
  */
  int minMoves(vector<int>& nums) {
    if (nums.empty()) return 0;
    int min_el = *min_element(nums.begin(), nums.end());
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
      res += nums[i] - min_el;
    }

    return res;
  }
};

int main() { return 0; }