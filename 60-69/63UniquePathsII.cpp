/*
63. Unique Paths II
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.

/*
    Submission Date: 2017-06-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <vector>
#include <unordered_map>

struct PairHash {
    size_t operator()(pair<int, int> const& p) const {
        return ((hash<int>()(p.first) ^ (hash<int>()(p.second) << 1)) >> 1);
    }
};

class Solution {
    unordered_map<pair<int, int>, int, PairHash> m;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid, int i, int j, int M, int N) {
        pair<int, int> p = {i, j};

        auto it = m.find(p);
        if(it != m.end()) return it -> second;

        if(i >= M || j >= N) return 0;
        if(grid[i][j]) return 0;
        if(i == M - 1 && j == N - 1) return 1;

        int res = uniquePathsWithObstacles(grid, i + 1, j, M, N) + uniquePathsWithObstacles(grid, i, j + 1, M, N);
        return m[p] = res;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()) return 0;
        int M = obstacleGrid.size();
        int N = obstacleGrid.front().size();
        return uniquePathsWithObstacles(obstacleGrid, 0, 0, M, N);
    }
};

int main() {
    return 0;
}