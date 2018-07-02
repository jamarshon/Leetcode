
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
859. Buddy Strings
Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.

 

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool buddyStrings(string A, string B) {
        if(A.size() != B.size()) return false;
        
        vector<int> diff;
        for(int i = 0; i < A.size(); i++) {
            if(A[i] != B[i]) {
                diff.push_back(i);
                if(diff.size() > 2) return false;
            }
        }
        
        if(diff.size() == 1) return false;
        if(diff.size() == 0) return unordered_set<char>(A.begin(), A.end()).size() < A.size();
        return A[diff[0]] == B[diff[1]] && A[diff[1]] == B[diff[0]];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
860. Lemonade Change
At a lemonade stand, each lemonade costs $5. 

Customers are standing in a queue to buy from you, and order one at a time 
(in the order specified by bills).

Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.  
You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

Note that you don't have any change in hand at first.

Return true if and only if you can provide every customer with correct change.

 

Example 1:

Input: [5,5,5,10,20]
Output: true
Explanation: 
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.
Example 2:

Input: [5,5,10]
Output: true
Example 3:

Input: [10,10]
Output: false
Example 4:

Input: [5,5,10,10,20]
Output: false
Explanation: 
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can't give change of $15 back because we only have two $10 bills.
Since not every customer received correct change, the answer is false.
 

Note:

0 <= bills.length <= 10000
bills[i] will be either 5, 10, or 20.
/*
    Submission Date: 2018-07-01
    Runtime: 30 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        // change[0] is number of 5's and change[1] is number of 10's.
        // 20's will never be given back so no need to count them.
        vector<int> change(2, 0);
        for(const auto& e: bills) {
            if(e == 5) {
                change[0]++;
            } else if(e == 10) { // can only give a 5 back
                if(change[0] == 0) return false;
                change[0]--;
                change[1]++;
            } else { // e == 20 can give back either 5 and 10 or 3 fives
                if(change[1] > 0 && change[0] > 0) { // try to give back the 10 first as it is less useful
                    change[1]--;
                    change[0]--;
                } else if(change[0] >= 3) {
                    change[0] -= 3;
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
861. Score After Flipping Matrix
We have a two dimensional matrix A where each value is 0 or 1.

A move consists of choosing any row or column, and toggling each value in that row or column: 
changing all 0s to 1s, and all 1s to 0s.

After making any number of moves, every row of this matrix is interpreted as a binary number, 
and the score of the matrix is the sum of these numbers.

Return the highest possible score.

 

Example 1:

Input: [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation:
Toggled to [[1,1,1,1],[1,0,0,1],[1,1,1,1]].
0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 

Note:

1 <= A.length <= 20
1 <= A[0].length <= 20
A[i][j] is 0 or 1.
/*
    Submission Date: 2018-07-01
    Runtime: 5 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void FlipRow(vector<vector<int>>& A, int row, int M) {
        for(int j = 0; j < M; j++) A[row][j] ^= 1;
    }
    
    void FlipCol(vector<vector<int>>& A, int col, int N) {
        for(int i = 0; i < N; i++) A[i][col] ^= 1;
    }
    
    /*
    First get all the the elements in A[i][0] to be 1 by toggling rows
    this is because having a 1 in the left most column gives the greatest value 1000 > 0111
    Then for each column, flip the column if it gives a greater amount of 1's in that column
    */
    int matrixScore(vector<vector<int>>& A) {
        if(A.empty()) return 0;
        int N = A.size(), M = A[0].size();
        for(int i = 0; i < N; i++) {
            if(A[i][0] == 0) {
                FlipRow(A, i, M);
            }
        }
        
        for(int j = 0; j < M; j++) {
            int one_count = 0;
            for(int i = 0; i < N; i++) one_count += A[i][j] == 1;
            if(one_count < N - one_count) {
                FlipCol(A, j, N);
            }
        }
        
        int res = 0;
        for(int i = 0; i < N; i++) {
            int temp = 0;
            for(int j = 0; j < M; j++) {
                temp |= A[i][j];
                temp <<= 1;
            }
            res += temp >> 1;
        }
        return res;
    }
};

int main() {
    return 0;
}