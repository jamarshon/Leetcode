/*
/*
1007. Minimum Domino Rotations For Equal Row
In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the
i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each
half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.

Return the minimum number of rotations so that all the values in A are the same,
or all the values in B are the same.

If it cannot be done, return -1.

Example 1:

Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any
rotations.
If we rotate the second and fourth dominoes, we can make every value in the top
row equal to 2, as indicated by the second figure.

Example 2:

Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of
values equal.

Note:

  1 <= A[i], B[i] <= 6
  2 <= A.length == B.length <= 20000
/*
  Submission Date: 2019-09-22
  Runtime: 192 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int f(const vector<int>& A, const vector<int>& B) {
    int N = A.size();
    int target = A[0];
    int A_cnt = 0;
    int B_cnt = 0;
    for (int i = 0; i < N; i++) {
      if (A[i] != target && B[i] != target) return -1;
      A_cnt += A[i] == target;
      B_cnt += B[i] == target;
    }
    return min(min(B_cnt, N - B_cnt), min(A_cnt, N - A_cnt));
  }
  int minDominoRotations(vector<int>& A, vector<int>& B) {
    /*
    check that every element has either A[0] or B[0]
    count the number of occurences in A or B
    if it is A_cnt it means swap all the occurences in A where (A[i] == target)
    if it is N-A_cnt it means swap all the occurrences in B where
      (B[i] for i where A[i] != target)
    if it is B_cnt it means swap all the occurences in B where (B[i] == target)
    if it is N-B_cnt it means swap all the occurrences in A where
      (A[i] for i where B[i] != target)
    */
    int f1 = f(A, B);
    int f2 = f(B, A);
    if (f1 == -1)
      return f2;
    else if (f2 == -1)
      return f1;
    else
      return min(f1, f2);
  }
};

class Solution2 {
 public:
  int minDominoRotations(vector<int>& A, vector<int>& B) {
    /*
    get the most frequent character in A and B, assume A's most
    frequent character > B's most frequent character
    A_freq[A_max_key] should at least be N/2 as to cover the whole
    array, the minimum size of a half is N/2
    A_freq[A_max_key] + B_freq[B_max_key] >= N as there should be
    enough characters in B to make N
    just swap all non A_max_key in B which is N - A_freq[A_max_key]
    need to check that for i in A[i] B[i] must have at least one
    A_max_key
    */
    unordered_map<int, int> A_freq, B_freq;
    int A_max_key = -1;
    for (const auto& e : A) {
      A_freq[e]++;
      if (A_max_key == -1 || A_freq[A_max_key] < A_freq[e]) A_max_key = e;
    }
    int B_max_key = -1;
    for (const auto& e : B) {
      B_freq[e]++;
      if (B_max_key == -1 || B_freq[B_max_key] < B_freq[e]) B_max_key = e;
    }

    if (A_freq[A_max_key] < B_freq[B_max_key]) {
      A_freq.swap(B_freq);
      A.swap(B);
      swap(A_max_key, B_max_key);
    }

    // A has the majority frequency
    int N = A.size();
    if (A_freq[A_max_key] < N / 2 || A_freq[A_max_key] + B_freq[B_max_key] < N)
      return -1;
    for (int i = 0; i < N; i++) {
      if (A[i] != A_max_key && B[i] != A_max_key) return -1;
    }
    return N - A_freq[A_max_key];
  }
};

int main() { return 0; }
