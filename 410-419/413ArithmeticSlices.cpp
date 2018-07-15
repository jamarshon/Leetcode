/*
413. Arithmetic Slices
A sequence of number is called arithmetic if it consists of at least three 
elements and if the difference between any two consecutive elements is the same. 

For example, these are arithmetic sequence:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9

The following sequence is not arithmetic. 1, 1, 2, 5, 7 


A zero-indexed array A consisting of N numbers is given. A slice of that array 
is any pair of integers (P, Q) such that 0 <= P < Q < N. 

A slice (P, Q) of array A is called arithmetic if the sequence:
    A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means 
that P + 1 < Q. 

The function should return the number of arithmetic slices in the array A. 


Example:
A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] 
itself. 

/*
    Submission Date: 2018-06-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    find the length of sequence where A[i+1] - A[i] is the same for all numbers in the sequence
    let this length be called len, then there are len - 2 subarrays of size 3, len - 3 subarrays
    of size 4 and so on. so the sum of 0 to len - 2 is just n*(n+1)/2 or (len - 2)*(len - 1)/2
    */
    int numberOfArithmeticSlices(vector<int>& A) {
        int res = 0;
        int N = A.size();
        for(int i = 0; i + 1 < N;) {
            int diff = A[i+1] - A[i];
            int start = i;
            while(i + 1 < N && A[i+1] - A[i] == diff) i++;
            int len = i - start + 1;
            if(len >= 3) {
                res += (len - 2)*(len - 1)/2;
            }
        }
        
        return res;
    }
};

int main() {
    return 0;
}