/*
624. Maximum Distance in Arrays
Given m arrays, and each array is sorted in ascending order. Now you can pick up two 
integers from two different arrays (each array picks one) and calculate the distance. 
We define the distance between two integers a and b to be their absolute difference 
|a-b|. Your task is to find the maximum distance.

Example 1:
Input: 
[[1,2,3],
 [4,5],
 [1,2,3]]
Output: 4
Explanation: 
One way to reach the maximum distance 4 is to pick 1 in the first or third array 
and pick 5 in the second array.
Note:
Each given array will have at least 1 number. There will be at least two non-empty arrays.
The total number of the integers in all the m arrays will be in the range of [2, 10000].
The integers in the m arrays will be in the range of [-10000, 10000].

/*
    Submission Date: 2017-06-18
    Runtime: 32 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Start {
    int index;
    int first_value;
};

struct End {
    int index;
    int last_value;
};

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int N = arrays.size();
        vector<Start> v;
        vector<End> v2;
        for(int i = 0; i < N; i++) {
            Start e = {i, arrays[i][0]};
            End e2 = {i, arrays[i].back()};
            v.push_back(e);
            v2.push_back(e2);
        }

        sort(v.begin(), v.end(), [](Start e, Start b){ return e.first_value < b.first_value; });
        sort(v2.begin(), v2.end(), [](End e, End b){ return e.last_value > b.last_value; });

        int max_dist = -1;
        int max_search = N;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < max_search; j++) {
                if(v[i].index != v2[j].index) {
                    max_dist = max(abs(v2[j].last_value - v[i].first_value), max_dist);
                    max_search = j;
                    break;
                }
            }
        }
        return max_dist;
    }
};

int main() {
    return 0;
}