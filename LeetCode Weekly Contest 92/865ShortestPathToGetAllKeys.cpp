/*
865. Shortest Path to Get All Keys
We are given a 2-dimensional grid. "." is an empty cell, "#" is a wall, "@" is 

We start at the starting point, and one move consists of walking one space in 
one of the 4 cardinal directions.  We cannot walk outside the grid, or walk into 
a wall.  If we walk over a key, we pick it up.  We can't walk over a lock unless 

For some 1 <= K <= 6, there is exactly one lowercase and one uppercase letter of 
the first K letters of the English alphabet in the grid.  This means that there 
is exactly one key for each lock, and one lock for each key; and also that the 
letters used to represent the keys and locks were chosen in the same order as 

Return the lowest number of moves to acquire all keys.  If it's impossible, 

 


Example 1:

Input: ["@.a.#","###.#","b.A.B"]
Output: 8



Example 2:

Input: ["@..aA","..B#.","....b"]
Output: 6



 

Note:


    1 <= grid.length <= 30
    1 <= grid[0].length <= 30
    grid[i][j] contains only '.', '#', '@', 'a'-'f' and 'A'-'F'
    The number of keys is in [1, 6].  Each key has a different letter and opens 
/*
    Submission Date: 2018-07-08
    Runtime: 164 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Item {
    int x;
    int y;
    int dist;
    int key;
    Item(int _x, int _y, int _dist, int _key): x(_x), y(_y), dist(_dist), key(_key) {}
};

class Solution {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
public:
    string GetVisitKey(const int& x, const int& y, const int& key) {
        return to_string(x) + "," + to_string(y) + "," + to_string(key);
    }
    
    /*
    do a bfs by marking visited as x,y,key where key represents the keys that we have
    look in the 4 directions, 
        if it is '.' or '@'
            go(new_x, new_y, key) if not visited
        if 'a' - 'z'
            go(new_x, new_y, key | (1 << (grid[new_y][new_x] - 'a'))) if not visited (ie add key)
        if 'A' - 'Z'
            go(new_x, new_y, key) if not visited and has required key (key & 1 << (grid[new_y][new_x] - 'A') 
    terminate once reach x,y,key where key == (2^K-1) meaning has all keys
    */
    int shortestPathAllKeys(vector<string>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        
        int K = 0;
        int start_x = 0;
        int start_y = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if('a' <= grid[i][j] && grid[i][j] <= 'f') K++;
                if(grid[i][j] == '@') {
                    start_y = i;
                    start_x = j;
                }
            }
        }
        
        unordered_set<string> visited;
        int all_key = (1 << K) - 1;
        queue<Item> q;
        q.emplace(start_x, start_y, 0, 0);
        visited.insert(GetVisitKey(start_x, start_y, 0));
        while(!q.empty()) {
            Item item = q.front();
            q.pop();
            if(item.key == all_key) return item.dist;
            for(int i = 0; i < 4; i++) {
                int new_x = item.x + dx[i];
                int new_y = item.y + dy[i];
                if(new_x < 0 || new_x >= M) continue;
                if(new_y < 0 || new_y >= N) continue;
                if(grid[new_y][new_x] == '#') continue;
                if(grid[new_y][new_x] == '.' || grid[new_y][new_x] == '@') {
                    string v_key = GetVisitKey(new_x, new_y, item.key);
                    if(!visited.count(v_key)) { // can visit if not visited
                        q.emplace(new_x, new_y, item.dist + 1, item.key);
                        visited.insert(v_key);
                    }
                } else if('a' <= grid[new_y][new_x] && grid[new_y][new_x] <= 'f') { // key
                    int new_key = item.key | (1 << (grid[new_y][new_x] - 'a'));
                    string v_key = GetVisitKey(new_x, new_y, new_key);
                    if(!visited.count(v_key)) { // see if picking up key is already visited
                        q.emplace(new_x, new_y, item.dist + 1, new_key);
                        visited.insert(v_key);
                    }
                } else { // lock
                    int req_key = 1 << (grid[new_y][new_x] - 'A');
                    string v_key = GetVisitKey(new_x, new_y, item.key);
                    if((req_key & item.key) && !visited.count(v_key)){ // have required key and not visited
                        q.emplace(new_x, new_y, item.dist + 1, item.key);
                        visited.insert(v_key);
                    }
                }
            }
        }
        return -1;
    }
};

struct Node {
    vector<Node*> adj;
    int dist = 0;
};

class Solution2 {
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
public:
    bool IsKey(const char& c) { return 'a' <= c && c <= 'f'; }
    bool IsLock(const char& c) { return 'A' <= c && c <= 'F'; }
    
    /*
    dp[i][j][k] is a node representing grid[i][j] where k is the current status of keys
    there are up to 2^k status of keys
    
    create adj for dp[i][j][k] by looking at 4 neighbors 
    do bfs starting from dp[start_y][start_x][0], if a node dp[i][j][k] is already visited
    ie. dist != 0, then visiting it again with the same state will have a larger distance
    so don't visit it again
    
    now for all dp[i][j][(2^k) - 1] ie when all the keys are collected, find the minimum
    distance it took
    */
    int shortestPathAllKeys(vector<string>& grid) {
        int N = grid.size();
        int M = grid[0].size();
        
        int K = 0;
        int start_x = 0;
        int start_y = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(IsKey(grid[i][j])) K++;
                if(grid[i][j] == '@') {
                    start_y = i;
                    start_x = j;
                }
            }
        }
        
        int k_limit = 1 << K;
        vector<vector<vector<Node*>>> dp(N, vector<vector<Node*>>(M, vector<Node*>(k_limit)));
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                for(int k = 0; k < k_limit; k++) {
                    dp[i][j][k] = new Node();
                }
            }
        }
        
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                for(int k = 0; k < k_limit; k++) {
                    for(int l = 0; l < 4; l++) {
                        int new_y = i + dy[l];
                        int new_x = j + dx[l];
                        
                        if(!(0 <= new_y && new_y < N)) continue;
                        if(!(0 <= new_x && new_x < M)) continue;
                        
                        if(IsKey(grid[new_y][new_x])) {
                            // add key
                            int new_key = k | (1 << (grid[new_y][new_x] - 'a'));
                            dp[i][j][k]->adj.push_back(dp[new_y][new_x][new_key]);
                        } else if(IsLock(grid[new_y][new_x])) {
                            // check if we have key
                            int needed_key = 1 << (grid[new_y][new_x] - 'A');
                            if(k & needed_key) {
                                dp[i][j][k]->adj.push_back(dp[new_y][new_x][k]);
                            }
                        } else if(grid[new_y][new_x] != '#') { // '@' or '.'
                            dp[i][j][k]->adj.push_back(dp[new_y][new_x][k]);
                        }
                    }
                }
            }
        }
        
        queue<Node*> q;
        q.push(dp[start_y][start_x][0]);
        while(!q.empty()) {
            Node* curr = q.front();
            q.pop();
            for(auto* neighbor: curr->adj) {
                if(neighbor->dist != 0) continue; // visited already
                neighbor->dist = curr->dist + 1;
                q.push(neighbor);
            }
        }
        
        int all_keys = k_limit - 1;
        int res = -1;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                if(dp[i][j][all_keys]->dist == 0) continue; // this node isnt visitable
                if(res == -1) res = dp[i][j][all_keys]->dist;
                res = min(res, dp[i][j][all_keys]->dist);
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}