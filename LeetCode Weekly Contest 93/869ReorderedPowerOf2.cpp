/*
869. Reordered Power of 2
Starting with a positive integer N, we reorder the digits in any order 
(including the original order) such that the leading digit is not zero. 

Return true if and only if we can do this in a way such that the resulting 
number is a power of 2. 

 





Example 1:

Input: 1
Output: true



Example 2:

Input: 10
Output: false



Example 3:

Input: 16
Output: true



Example 4:

Input: 24
Output: false



Example 5:

Input: 46
Output: true


 

Note:


    1 <= N <= 10^9
/*
    Submission Date: 2018-07-15
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    /*
    generate all powers of 2 which has the same length as the number
    compare the sorted number and the sorted power to see if they
    are anagrams of each other, return true if so.
    */
    bool reorderedPowerOf2(int N) {
        string s = to_string(N);
        sort(s.begin(), s.end());
        unordered_set<string> seen;

        for(int i = 0; i < 50; i++) {
            string a = to_string(1LL << i);
            if(a.size() > s.size()) break;
            if(a.size() < s.size()) continue;
            // a.size() == s.size();
            sort(a.begin(), a.end());
            if(a == s) {
                // cout << a << ' '  << s << endl;
                return true;
            }
        }

        return false;
    }
};

int main() {
    return 0;
}
