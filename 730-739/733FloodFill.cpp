/*
733. Flood Fill
An image is represented by a 2-D array of integers, each integer representing
the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of
the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels
connected 4-directionally to the starting pixel of the same color as the
starting pixel, plus any pixels connected 4-directionally to those pixels (also
with the same color as the starting pixel), and so on. Replace the color of all
of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:
Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels
connected by a path of the same color as the starting pixel are colored with the
new color. Note the bottom corner is not colored 2, because it is not
4-directionally connected to the starting pixel. Note:

The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc <
image[0].length. The value of each color in image[i][j] and newColor will be an
integer in [0, 65535].
/*
    Submission Date: 2018-06-08
    Runtime: 57 ms
    Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};

 public:
  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                int newColor) {
    if (image.empty()) return {};
    queue<pair<int, int>> q;
    unordered_set<string> visited;

    int N = image.size();
    int M = image[0].size();
    int original_color = image[sr][sc];

    q.emplace(sr, sc);
    visited.insert(to_string(sr) + "," + to_string(sc));
    while (!q.empty()) {
      pair<int, int> p = q.front();
      q.pop();
      image[p.first][p.second] = newColor;

      for (int k = 0; k < 4; k++) {
        int new_row = p.first + dy[k];
        int new_col = p.second + dx[k];
        if (0 <= new_row && new_row < N && 0 <= new_col && new_col < M &&
            image[new_row][new_col] == original_color) {
          string key = to_string(new_row) + "," + to_string(new_col);
          if (!visited.count(key)) {
            q.emplace(new_row, new_col);
            visited.insert(key);
          }
        }
      }
    }

    return image;
  }
};

int main() { return 0; }