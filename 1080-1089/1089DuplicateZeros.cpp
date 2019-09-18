/*
1089. Duplicate Zeros
Given a fixed length array arr of integers, duplicate each occurrence of zero,
shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.

Do the above modifications to the input array in place, do not return anything
from your function.

Example 1:

Input: [1,0,2,3,0,4,5,0]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,0,0,2,3,0,0,4]

Example 2:

Input: [1,2,3]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,2,3]

Note:

  1 <= arr.length <= 10000
  0 <= arr[i] <= 9
/*
  Submission Date: 2019-09-17
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void duplicateZeros(vector<int>& arr) {
    /*
    two passes where i is the original arr index
    and j is the new arr index. stop when j >= N
    then go backwards and fill
    */
    int N = arr.size();
    int i = 0, j = 0;
    for (; i < N && j < N; i++) {
      j += (arr[i] == 0) ? 2 : 1;
    }

    while (i >= 0 && j >= 0) {
      i--;
      if (i >= 0) {
        if (arr[i] == 0) {
          if (j - 1 < N) arr[j - 1] = 0;
          if (j - 2 < N) arr[j - 2] = 0;
          j -= 2;
        } else {
          arr[j - 1] = arr[i];
          j--;
        }
      }
    }
  }
};

int main() { return 0; }
