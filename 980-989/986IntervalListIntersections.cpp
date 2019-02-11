/*
986. Interval List Intersections
Given two lists of closed intervals, each list of intervals is pairwise disjoint
and in sorted order.

Return the intersection of these two interval lists.

(Formally, a closed interval [a, b] (with a <= b) denotes the set of real
numbers x with a <= x <= b.  The intersection of two closed intervals is a set
of real numbers that is either empty, or can be represented as a closed
interval.  For example, the intersection of [1, 3] and [2, 4] is [2, 3].)

Example 1:

Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
Reminder: The inputs and the desired output are lists of Interval objects, and
not arrays or lists.

Note:

  0 <= A.length < 1000
  0 <= B.length < 1000
  0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
/*
  Submission Date: 2019-02-10
  Runtime: 44 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
 public:
  vector<Interval> intervalIntersection(vector<Interval>& A,
                                        vector<Interval>& B) {
    int i = 0, j = 0;
    int N = A.size(), M = B.size();
    vector<Interval> res;
    res.reserve(N + M);

    while (i < N && j < M) {
      if (A[i].end < B[j].start) {
        i++;
      } else if (B[j].end < A[i].start) {
        j++;
      } else {
        // intersect
        res.emplace_back(max(A[i].start, B[j].start), min(A[i].end, B[j].end));
        if (A[i].end > B[j].end) {
          j++;
        } else if (A[i].end < B[j].end) {
          i++;
        } else {
          i++;
          j++;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }
