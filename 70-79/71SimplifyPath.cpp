/*
71. Simplify Path
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

Corner Cases:
Did you consider the case where path = "/../"?
In this case, you should return "/".
Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
In this case, you should ignore redundant slashes and return "/home/foo".

/*
    Submission Date: 2017-06-22
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        path += "/";

        stack<string> s;

        stringstream ss(path);
        string token;
        while(getline(ss, token, '/')) {
            // cout << "SS" << token << endl;
            if(token.empty() || token == ".") continue;
            else if(token == "..") {
                if(!s.empty()) s.pop();
            } else s.push(token);
        }

        string res;
        while(!s.empty()) {
            res = s.top() + (res.empty() ? "" : "/" + res);
            s.pop();
        }

        return "/" + res;
    }
};

int main() {
    return 0;
}