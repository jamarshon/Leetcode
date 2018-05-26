/*
301. Remove Invalid Parentheses
Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]
/*
    Submission Date: 2018-05-26
    Runtime: 2 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
        last_i means checking for negative (more ')' than '(') from string from [last_i, s.size())
        last_j indicates the last removed ')'
        
        suppose the open < 0, that means ')' must be removed. If there are multiple ')' like ")))"
        then the first one should be removed. Loop from the last removed ')' ie. last_j to i and
        look for these ')' to remove.
        
        s from [0, last_i) is guaranteed to have a open of 0
        suppose s = "()())r)"
        ( ) ( ) ) r )
        0 1 2 3 4 5 6
        
        last_i = 0, last_j = 0 : open is -1 at 4
            remove ')' at 1 last_i = 4, last_j = 1
                ( ( ) ) r )
                0 1 2 3 4 5 
                
                open is -1 at 5
                    remove ')' at 2 last_i = 5, last_j = 2
                        ( ( ) r )
                        0 1 2 3 4
                        
                        final res remove (1, 3)
                    remove ')' at 5 last_i = 5, last_j = 5
                        ( ( ) ) r 
                        0 1 2 3 4 
                        
                        final res remove (1, 6)
            remove ')' at 3 last_i = 4, last_j = 3
                ( ) ( ) r )
                0 1 2 3 4 5 
                
                open is -1 at 5
                    remove ')' at 3 last_i = 5, last_j = 3
                        ( ) ( r )
                        0 1 2 3 4 
                        
                        final res remove (3, 4)
                    remove ')' at 5 last_i = 5, last_j = 5
                        ( ) ( ) r 
                        0 1 2 3 4 
                        
                        final res move (3, 6)
        
        last_j keeps track of where we can take ')' from
        
        to consider the case where there is too many '(', just reverse the string
        and change all '(' to ')' and '(' to ')'

    */
    void solve(string s, const int& last_i, const int& last_j, vector<string>& res, const vector<char>& p) {
        int open = 0;
        for(int i = last_i; i < s.size(); i++) {
            open += s[i] == p[0];
            open -= s[i] == p[1];
            if(open >= 0) continue;
            for(int j = last_j; j <= i; j++) {
                if(s[j] == p[1] && (j == last_j || s[j-1] != p[1])) {
                    solve(s.substr(0, j) + s.substr(j+1), i, j, res, p);
                }
                
            }
            return;
        }
        
        reverse(s.begin(), s.end());
        if(p[0] == '(') {
            solve(s, 0, 0, res, {')', '('});
        } else {
            res.push_back(s);
        }
    }
    
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        solve(s, 0, 0, res, {'(', ')'});
        return res;
    }
};

int main() {
    return 0;
}