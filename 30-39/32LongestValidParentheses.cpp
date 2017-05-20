/*
32. Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

/*
    Submission Date: 2017-05-20
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <stack>

class Solution {
public:
    // Run time 12 ms
    int longestValidParentheses(string s) {
        int len = s.length();

        if(len == 0) return 0;

        int dp[len];
        int max_len = -1;
        for(int i = 0; i < len; i++) {
            // longest valid ends here so dp[i] is 0
            if(s[i] == '(') {
                dp[i] = 0;
            } else {
                if(i == 0) { 
                    // ')...' first char is ) so 0
                    dp[i] = 0;
                } else if(s[i-1] == '(') {
                    // '...()' it is two plus the longest valid at i - 2
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else {
                    // '...))' check if it is '...((...))' then it is just the inner length 
                    // dp[i - 1] plus the two brackets completed on the outer plus whatever
                    // was before the first (
                    int ind_prev = i - dp[i - 1] - 1;
                    if(s[ind_prev] == '(') {
                        dp[i] = dp[i - 1] + (ind_prev == 0 ? 0: dp[i - dp[i - 1] - 2]) + 2;
                    } else {
                        dp[i] = 0;
                    }
                }
            }
            max_len = max(dp[i], max_len);
        }
        return max_len;
    }

    // Run time 12 ms
    int longestValidParentheses2(string s) {
        int len = s.size();

        int left, right;
        int max_len = 0;

        // traverse right
        left = right = 0;
        for(int i = 0; i < len; i++) {
            if(s[i] == '(') left++;
            else right++;
            if(left == right) {
                max_len = max(2*left, max_len);
            } 
            if(right > left) {
                left = right = 0;
            }
        }

        // traverse right
        left = right = 0;
        for(int i = len - 1; i >= 0; i--) {
            if(s[i] == '(') left++;
            else right++;
            if(left == right) {
                max_len = max(2*left, max_len);
            } 
            if(left > right) {
                left = right = 0;
            }
        }
        return max_len;
    }

    // Run time 6 ms
    int longestValidParentheses3(string s) {
        int len = s.size();

        int max_len = 0;

        stack<int> st;

        st.push(-1);

        for(int i = 0; i < len; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else {
                // ')'
                st.pop();
                if(st.empty()) {
                    st.push(i);
                } else {
                    int prev = st.top();
                    max_len = max(i - prev, max_len);
                }
            }
        }

        return max_len;
    }
};

int main() {
    Solution s;
    cout << s.longestValidParentheses("(()") << endl;
    cout << s.longestValidParentheses(")()())") << endl;
    return 0;
}