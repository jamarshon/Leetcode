
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
849. Maximize Distance to Closest Person
In a row of seats, 1 represents a person sitting in that seat, and 0 represents that the seat is empty. 

There is at least one empty seat, and at least one person sitting.

Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized. 

Return that maximum distance to closest person.

Example 1:

Input: [1,0,0,0,1,0,1]
Output: 2
Explanation: 
If Alex sits in the second open seat (seats[2]), then the closest person has distance 2.
If Alex sits in any other open seat, the closest person has distance 1.
Thus, the maximum distance to the closest person is 2.
Example 2:

Input: [1,0,0,0]
Output: 3
Explanation: 
If Alex sits in the last seat, the closest person is 3 seats away.
This is the maximum distance possible, so the answer is 3.
Note:

1 <= seats.length <= 20000
seats contains only 0s or 1s, at least one 0, and at least one 1.
/*
    Submission Date: 2018-06-24
    Runtime: 16 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        if(seats.empty()) return INT_MAX;
        
        int N = seats.size();
        // left[i] indicates the distance to the closest 1 to the left 
        vector<int> left(N, INT_MAX);
        for(int i = 0; i < N; i++) {
            if(seats[i] == 1) left[i] = 0;
            else if(i > 0 && left[i-1] < INT_MAX) {
                left[i] = left[i-1] + 1;
            }
        }
        
        int right = INT_MAX;
        int res = INT_MIN;
        /*
        if there is at least one 1 and 0
        left[i] will be INT_MAX until the first 1 then some number after it 
        
        hence if starting from the back, the number will not be INT_MAX so right
        will be correctly minimized.
        */
        for(int i = N-1; i >= 0; i--) {
            if(seats[i] == 1) right = 0;
            else if(right < INT_MAX) right++;
            
            res = max(res, min(left[i], right));
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
852. Peak Index in a Mountain Array
Let's call an array A a mountain if the following properties hold:

A.length >= 3
There exists some 0 < i < A.length - 1 such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1]
Given an array that is definitely a mountain, return any i such that A[0] < A[1] < ... A[i-1] < A[i] > A[i+1] > ... > A[A.length - 1].

Example 1:

Input: [0,1,0]
Output: 1
Example 2:

Input: [0,2,1,0]
Output: 1
Note:

3 <= A.length <= 10000
0 <= A[i] <= 10^6
A is a mountain, as defined above.
/*
    Submission Date: 2018-06-24
    Runtime: 17 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int low = 0;
        int high = A.size() - 1;
        while(low <= high-2) { // at least 3 elements
            int mid = low + (high-low)/2;
            if(A[mid-1] < A[mid] && A[mid] > A[mid+1]) {
                return mid;
                
            /* 
            a number and the next number has only two conditions < and >
            if < then it is before the peak, so go right
            if > then it is after the peak, so go left
            
            need to include mid in the search as it can be either the left
            or right boundary to the peak
            */
            } if(A[mid-1] < A[mid]) {
                low = mid; 
            } else { // A[mid-1] > A[mid]
                high = mid;
            }
        }
        
        return -1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
856. Score of Parentheses
Given a balanced parentheses string S, compute the score of the string based on the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
 

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50
/*
    Submission Date: 2018-06-29
    Runtime: 4 ms
    Difficulty:MEDIUM 
*/
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string S) {
        // first is the value or -1 if it is a character '(' 
        stack<pair<int, char>> stk;
        for(const auto& e: S) {
            if(e == '(') {
                stk.emplace(-1, '(');
            } else { // e == ')'
                // S is balanced so keep going back until '(' (ie not value)
                // add all the numbers in between and multiply by 2
                int in_between = 0;
                while(stk.top().first != -1) {
                    in_between += stk.top().first;
                    stk.pop();
                }
                
                stk.pop();
                stk.emplace(max(1, 2*in_between), 'r');
            }
        }
        
        int res = 0;
        // since S is balanced then stk must only contain values so add 
        // up and return value
        while(!stk.empty()) {
            res += stk.top().first;
            stk.pop();
        }
        
        return res;
    }
};

int main() {
    return 0;
}
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