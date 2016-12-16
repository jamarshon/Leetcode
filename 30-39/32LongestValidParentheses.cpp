/*
32. Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

/*
    Submission Date: 2016-12-15
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <stack>
class Solution {
public:
    int longestValidParentheses(string s) {
    	int i = 0,
    			len = s.length(),
    			lastBalancedIndex = -1,
    			currentValidParenthesisCount = 0,
    			longestValidParenthesisCount = 0;
        
        stack<char> charStack;
    	while(i < len) {
    		// find next open bracket
    		int intialI = i;
    		while(s[i] == ')') i++;
    		charStack.push(s[i]);
    		
    		if(lastBalancedIndex != i) {
    			currentValidParenthesisCount = 0;
    		}
    		
    		currentValidParenthesisCount++;
    		
    		while(++i < len && !charStack.empty()) {
    			if(s[i] == ')') {
    				charStack.pop();
    			} else if(s[i] == '(') {
    				charStack.push(s[i]);
    			}
    			currentValidParenthesisCount++;
    		}
    
    		if(charStack.empty()) {
    			lastBalancedIndex = i;
    			longestValidParenthesisCount = max(currentValidParenthesisCount, longestValidParenthesisCount);
    		} else {
    			i = intialI + 1;
                stack<char>().swap(charStack);
    		}
    	}
    	return longestValidParenthesisCount;
    }
};

int main() {
    Solution s;
    cout << s.longestValidParentheses("(()") << endl;
    cout << s.longestValidParentheses(")()())") << endl;
    return 0;
}