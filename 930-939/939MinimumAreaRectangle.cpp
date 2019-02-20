/*
939. Minimum Area Rectangle
Given a set of points in the xy-plane, determine the minimum area of a rectangle
formed from these points, with sides parallel to the x and y axes.

If there isn't any rectangle, return 0.

Example 1:

Input: [[1,1],[1,3],[3,1],[3,3],[2,2]]
Output: 4

Example 2:

Input: [[1,1],[1,3],[3,1],[3,3],[4,1],[4,3]]
Output: 2

Note:

  1 <= points.length <= 500
  0 <= points[i][0] <= 40000
  0 <= points[i][1] <= 40000
  All points are distinct.
/*
  Submission Date: 2019-02-19
  Runtime: 84 ms
  Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution3 {
 public:
  /*
  consider each point as diagonals of the rectangle (a,b) (c,d) seach
  for (a,d) and (c,b). use hashmap for lookup.
  if same x coord a==c (a,b) (a,d) look for (a,d) (a,b) not valid
  so exclude if same x coord and same y coord.
  */
  int minAreaRect(vector<vector<int>>& points) {
    int res = -1;
    unordered_set<int> s;
    for (const auto& p : points) s.insert(p[0] * 40001 + p[1]);
    for (int i = 0; i < points.size(); i++) {
      for (int j = i + 1; j < points.size(); j++) {
        if (points[i][0] == points[j][0] || points[i][1] == points[j][1])
          continue;
        if (s.count(points[i][0] * 40001 + points[j][1]) &&
            s.count(points[j][0] * 40001 + points[i][1])) {
          int area =
              (points[i][0] - points[j][0]) * (points[i][1] - points[j][1]);
          res = (res == -1) ? abs(area) : min(abs(area), res);
        }
      }
    }
    return max(res, 0);
  }
};

class Solution {
 public:
  /*
  group by x coordinates. sort each column and do pairwise comparison of
  each column by finding intersecting elements. The smallest distance between
  intersecting elements multiplied by the distance between columns is smallest
  rectangle that is bordered by these two columns.
  */
  int ShortestCommon(const vector<int>& A, const vector<int>& B) {
    int res = -1;
    int N = A.size(), M = B.size();
    int i = 0, j = 0;
    int last_y = -1;

    while (i < N && j < M) {
      if (A[i] == B[j]) {
        if (last_y != -1)
          res = (res == -1) ? A[i] - last_y : min(res, A[i] - last_y);
        last_y = A[i];
        i++;
        j++;
      } else if (A[i] > B[j]) {
        j++;
      } else {
        i++;
      }
    }
    return res;
  }

  int minAreaRect(vector<vector<int>>& points) {
    int res = -1;
    unordered_map<int, vector<int>> m;
    for (const auto& p : points) {
      m[p[0]].push_back(p[1]);
    }

    for (auto& kv : m) sort(kv.second.begin(), kv.second.end());
    for (auto it = m.begin(); it != m.end(); it++) {
      for (auto next_it = next(it); next_it != m.end(); next_it++) {
        int height = ShortestCommon(it->second, next_it->second);
        if (height == -1) continue;
        int pos_res = height * abs(it->first - next_it->first);
        res = (res == -1) ? pos_res : min(pos_res, res);
      }
    }

    return max(res, 0);
  }
};

class Solution2 {
 public:
  /*
  group points by x coordinates (into columns)
  traverse these columns starting from the left and for each column
  loop the pair of y1, y2 to see if any previous column had it. since
  we start from the left, it is guaranteed that it will be the shortest
  x distance. this is can be done by having a unordered_map<int,int>
  where key is y1*40001 + y2 where y1 <= y2 and value is the
  most recent x coordinate
  */
  int minAreaRect(vector<vector<int>>& points) {
    int res = -1;
    map<int, vector<int>> m;
    for (const auto& p : points) {
      m[p[0]].push_back(p[1]);
    }

    unordered_map<int, int> x_coord;
    for (const auto& kv : m) {
      const auto& column = kv.second;
      for (int i = 0; i < column.size(); i++) {
        for (int j = i + 1; j < column.size(); j++) {
          int y1 = column[i];
          int y2 = column[j];
          if (y1 > y2) swap(y1, y2);
          auto it = x_coord.find(y1 * 40001 + y2);
          if (it != x_coord.end()) {
            int area = (kv.first - it->second) * (y2 - y1);
            res = (res == -1) ? area : min(area, res);
          }
          x_coord[y1 * 40001 + y2] = kv.first;
        }
      }
    }

    return max(res, 0);
  }
};

int main() { return 0; }
