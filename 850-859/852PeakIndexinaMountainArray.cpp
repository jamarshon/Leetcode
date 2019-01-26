/*
852. Peak Index in a Mountain Array
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i]
> A[i+1] > ... > A[A.length - 1] Given an array that is definitely a mountain,
return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... >
A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
/*
    Submission Date: 2018-06-24
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& A) {
    int low = 0;
    int high = A.size() - 1;
    while (low <= high - 2) {  // at least 3 elements
      int mid = low + (high - low) / 2;
      if (A[mid - 1] < A[mid] && A[mid] > A[mid + 1]) {
        return mid;

        /*
        a number and the next number has only two conditions < and >
        if < then it is before the peak, so go right
        if > then it is after the peak, so go left
        
        need to include mid in the search as it can be either the left
        or right boundary to the peak
        */
      }
      if (A[mid - 1] < A[mid]) {
        low = mid;
      } else {  // A[mid-1] > A[mid]
        high = mid;
      }
    }

    return -1;
  }
};

int main() { return 0; }