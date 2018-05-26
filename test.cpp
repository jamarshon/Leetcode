#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <list>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <algorithm>
#include <functional>
 
using namespace std;

#define pii pair<int,int>
#define vt vector
#define uos unordered_set
#define uom unordered_map

typedef long long ll;

struct Compare {
    bool operator()(const int& left, const int& right) const { return left < right; }
};


class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int N = s.size();
        
        int open = 0;
        int i = 0;
        int last_zero = -1;
        
        vector<int> close_brackets;
        for(; i < N; i++) {
            open += s[i] == '(';
            open -= s[i] == ')';
            if(s[i] == ')' && (close_brackets.empty() || close_brackets.back() != i - 1)) close_brackets.push_back(i);
            if(open < 0) {
                break;
            }
            if(open == 0) last_zero = i;
        }
        
        if(open < 0) {
            // remove closing brackets and recurse
            // cout << s << endl;
            const vector<string>& rem = removeInvalidParentheses(s.substr(i+1));
            vector<string> res;
            for(const auto& j: close_brackets) {
                string new_pre = s.substr(0, j) + s.substr(j+1, (i+1)-(j+1));
                for(const auto& r: rem) {
                    res.push_back(new_pre + r);
                }
            }       
            return res;
        } else { // went through whole string
            if(open == 0) {
                return {s};
            } else {
                // open > 0 remove open brackets
                string rem = s.substr(last_zero+1);
                reverse(rem.begin(), rem.end());
                for(int i = 0; i < rem.size(); i++) rem[i] = rem[i] == ')' ? rem[i] = '(' : rem[i] == '(' ? rem[i] = ')' : rem[i];
                string pre = s.substr(0, last_zero+1);
                vector<string> res;
                vector<string> rem_rev = removeInvalidParentheses(rem);
                for(auto& rr: rem_rev) {
                    reverse(rr.begin(), rr.end());
                    for(int i = 0; i < rr.size(); i++) rr[i] = rr[i] == ')' ? rr[i] = '(' : rr[i] == '(' ? rr[i] = ')' : rr[i];
                    res.push_back(pre + rr);
                }
                return res;
            }
        }
    }
};
int main() {
    Solution s;
    vector<string> m = s.removeInvalidParentheses("(((k()((");
    for(auto e: m) cout << e << ' '; cout << endl;
    return 0;
}


