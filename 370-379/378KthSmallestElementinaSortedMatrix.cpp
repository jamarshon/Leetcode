/*
378. Kth Smallest Element in a Sorted Matrix
Given a n x n matrix where each of the rows and columns are sorted in ascending
order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth
distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note:
You may assume k is always valid, 1 ≤ k ≤ n2.
/*
    Submission Date: 2018-05-30
    Runtime: 38 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution2 {
 public:
  bool Get(const vector<vector<int>>& matrix, int num, int N, int M, int k) {
    int i = 0;
    int j = M - 1;
    int curr = 0;

    int occurences = 0;

    while (i < N && j >= 0) {
      if (matrix[i][j] > num) {
        j--;
      } else {
        int temp = j;
        while (temp >= 0 && matrix[i][temp] == num) temp--;
        i++;
        curr += temp + 1;
        occurences += j - temp;
      }
    }

    return curr < k && k <= curr + occurences;
  }

  // for each element in the array, count the number of elements smaller than it
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    int N = matrix.size();
    int M = matrix[0].size();

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (Get(matrix, matrix[i][j], N, M, k)) {
          return matrix[i][j];
        }
      }
    }

    return -1;
  }
};

struct Item {
  int i, j, val;
  Item(const int& _i, const int& _j, const int& _val)
      : i(_i), j(_j), val(_val) {}
  bool operator>(const Item& rhs) const { return val > rhs.val; }
};

class Solution3 {
 public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    int N = matrix.size();
    int M = matrix[0].size();

    priority_queue<Item, vector<Item>, greater<Item>> min_heap;
    for (int j = 0; j < M; j++) {
      min_heap.emplace(0, j, matrix[0][j]);
    }

    for (int i = 0; i < k - 1;
         i++) {  // remove k- 1 elements to get the kth element
      Item smallest = min_heap.top();
      min_heap.pop();
      if (smallest.i + 1 < N) {
        smallest.i++;
        smallest.val = matrix[smallest.i][smallest.j];
        min_heap.push(smallest);
      }
    }

    return min_heap.top().val;
  }
};

class Solution {
 public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
    int N = matrix.size();
    int M = matrix[0].size();

    // matrix[i][j] >= matrix[k][l] for all k > i && l > j
    int low = matrix[0][0];
    int high = matrix[M - 1][M - 1];

    while (low <= high) {
      int mid = low + (high - low) / 2;
      int num_smaller_than_mid = 0;
      // get the number of elements that are <= mid.
      // suppose the two elements in the array are 10 x 1, 10 x 2 and 10 x 3
      // if k == 15, mid = 2 and num_smaller_than_mid are 10, 20, 30 return low
      // gets the number larger than k
      for (int j = M - 1, i = 0; i < N; i++) {
        while (j >= 0 && matrix[i][j] > mid) j--;
        num_smaller_than_mid += j + 1;
      }

      if (num_smaller_than_mid >= k)
        high = mid - 1;  // too many elements
      else
        low = mid + 1;  // too little elements
    }

    return low;
  }
};

int main() { return 0; }