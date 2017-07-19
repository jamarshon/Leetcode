/*
150. Evaluate Reverse Polish Notation
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

/*
    Submission Date: 2017-07-18
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <functional>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    unordered_map<string, function<int(int, int)>> binop{
        {"*", [](const int& a, const int& b){ return a*b; }},
        {"+", [](const int& a, const int& b){ return a+b; }},
        {"-", [](const int& a, const int& b){ return a-b; }},
        {"/", [](const int& a, const int& b){ return a/b; }},
    };
    bool isNumber(string s) {
        return any_of(s.begin(), s.end(), [](const char& c) -> bool { return isdigit(c); });
    }
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty()) return 0;

        stack<int> st;
        int a, b;
        for(auto token: tokens) {
            if(isNumber(token)) {
                st.push(stoi(token));
            } else {
                b = st.top();
                st.pop();
                a = st.top();
                st.pop();
                st.push(binop[token](a,b));
            }
        }
        return st.top();
    }
};

int main() {
    Solution s;
    return 0;
}