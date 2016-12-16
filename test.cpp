using namespace std;
#include <iostream>
#include <stack>

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

int main() {
	cout << longestValidParentheses("(()") << endl;
	cout << longestValidParentheses(")()())") << endl;
	return 0;
}


