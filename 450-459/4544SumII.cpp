/*
454. 4Sum II
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, 
l) there are such that A[i] + B[j] + C[k] + D[l] is zero. 

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 
500. All integers are in the range of -228 to 228 - 1 and the result is 
guaranteed to be at most 231 - 1. 

Example:
Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

/*
    Submission Date: 2018-07-08
    Runtime: 104 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /*
    O(n^2) generate all n^2 sums of A and B and put in hashmap of sum to frequency
    generate all n^2 sums of C and D and see if the sum exists in hashmap, if it does
    then res increases by the frequency as the frequency represents how many ways to 
    get that sum
    */
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> sum_A_B;
        for(const auto& a: A) {
            for(const auto& b: B) {
                sum_A_B[a + b]++;
            }
        }
        
        int res = 0;
        for(const auto& c: C) {
            for(const auto& d: D) {
                if(sum_A_B.count(-c-d)) {
                    res += sum_A_B[-c-d];
                }
            }
        }
        return res;
    }
};

int main() {
    return 0;
}
