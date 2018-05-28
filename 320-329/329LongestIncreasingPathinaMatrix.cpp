/*
329. Longest Increasing Path in a Matrix
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally 
or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums = 
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
] 
Output: 4 
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: nums = 
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
] 
Output: 4 
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
/*
    Submission Date: 2018-05-26
    Runtime: 112 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    vector<int> dx_{1,-1,0,0};
    vector<int> dy_{0,0,1,-1};
    
    unordered_map<int, int> dp_;
public:
    int id(const int& i, const int& j, const int& M) {
        return i*M + j;
    }
    
    /*
         graph has vertex being a cell and the edges to cells strictly greater than it (directed graph)
         do a dfs on all the neighbors and take the max of this to return
         use memoization as the longest path for a cell is the same once computed.
    */
    int dfs(int curr, const unordered_map<int, vector<int>>& graph) {
        if(dp_.count(curr)) return dp_[curr];
        
        const auto& it = graph.find(curr);
        if(it == graph.cend()) return dp_[curr] = 1;
        
        int res = 0;
        
        for(const auto& n: it->second) {
            res = max(res, dfs(n, graph));
        }
        
        return dp_[curr] = res + 1;
    }
    
    int longestIncreasingPath(vector<vector<int>>& A) {
        if(A.empty()) return 0;
        
        int N = A.size();
        int M = A[0].size();
        unordered_map<int, vector<int>> graph;
        
        
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                for(int k = 0; k < 4; k++) {
                    if((0 <= dy_[k] + i && dy_[k] + i < N) && 
                       (0 <= dx_[k] + j && dx_[k] + j < M) && 
                        A[i][j] < A[i + dy_[k]][j + dx_[k]]) 
                        graph[id(i, j, M)].push_back(id(i + dy_[k], j + dx_[k], M));
                }
            }
        }
        
        int res = 1;
        for(const auto& kv: graph) {
            res = max(res, dfs(kv.first, graph));
        }
        
        return res;
    }
};

int main() {
    return 0;
}