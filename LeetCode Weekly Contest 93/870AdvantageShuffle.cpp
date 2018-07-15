/*
870. Advantage Shuffle
Given two arrays A and B of equal size, the advantage of A with respect to B is 
the number of indices i for which A[i] > B[i]. 

Return any permutation of A that maximizes its advantage with respect to B.

 


Example 1:

Input: A = [2,7,11,15], B = [1,10,4,11]
Output: [2,11,7,15]



Example 2:

Input: A = [12,24,8,32], B = [13,25,32,11]
Output: [24,32,8,12]


 

Note:


    1 <= A.length = B.length <= 10000
    0 <= A[i] <= 10^9
    0 <= B[i] <= 10^9
/*
    Submission Date: 2018-07-15
    Runtime: 124 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cassert>

using namespace std;

class Solution {
public:
    /*
    sort A and B, then do two pointers to find the smallest element in A greater than B[i]
    if there is no element then just assign the remaining elemnets in A to B.
    */
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        typedef pair<int,int> pii;
        int N = A.size();
        vector<int> res(N, -1);
        sort(A.begin(), A.end());

        vector<pii> B2;
        for(int i = 0; i < N; i++) B2.emplace_back(B[i], i);
        sort(B2.begin(), B2.end());

        int i = 0, j = 0;
        unordered_set<int> not_used;
        for(int k = 0; k < N; k++) not_used.insert(k);

        while(i < N) {
            while(i < N && A[i] <= B2[j].first) i++;
            if(i < N) {
                res[B2[j].second] = A[i];
                not_used.erase(i);
                i++;
                j++;
            }
        }

        for(const auto& e: not_used) {
            assert(j < N);
            res[B2[j].second] = A[e];
            j++;
        }
        return res;
    }
};

int main() {
    return 0;
}
