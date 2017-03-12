using namespace std;
#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <bitset>

class Solution {
public:
    string reverseStr(string s, int k) {
        string finalStr = "";
        bool reverse = true;
        int i = 0, len = s.size();
        while(i < len) {
            string currentStr = string(1, s[i++]);
            while(i%k != 0 && i < len) {
                currentStr = reverse ? s[i] + currentStr : currentStr + s[i];
                i++;
            }
            finalStr += currentStr;
            reverse ^= reverse;
        }
        
        return finalStr;
    }
};

int main() {
    Solution s;
    cout << s.reverseStr("abcdefg", 2);
    
    return 0;
}