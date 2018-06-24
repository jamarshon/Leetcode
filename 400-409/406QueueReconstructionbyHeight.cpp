/*
406. Queue Reconstruction by Height
Suppose you have a random list of people standing in a queue. Each person is described by a pair 
of integers (h, k), where h is the height of the person and k is the number of people in front of this 
person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.


Example

Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
/*
    Submission Date: 2018-06-24
    Runtime: 42 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    sort by height (h) and break tie on number greater than or equal to before (called k)

    start from the lowest and for each of the same height, find the kth not used spot and 
    place the pair there. keep track of the number of same height elements already placed.
    */
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        vector<pair<int,int>> res(people.size(), {-1, -1});
        sort(people.begin(), people.end());
        
        int N = people.size();
        for(int i = 0; i < N;) {
            int start = i;
            while(people[i].first == people[start].first) {
                auto p = people[i];
                int to_go = p.second - (i - start);
                for(int j = 0; j < N; j++) {
                    if(res[j].second != -1) continue;
                    if(to_go == 0) {
                        res[j] = p;
                        break;
                    }
                    to_go--;
                }
                i++;
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}