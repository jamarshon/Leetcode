/*
5. Longest Palindromic Substring
Given a string S, find the longest palindromic substring in S. You may assume 
that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
*/

/*
	Submission Date: 2016-11-29
	Runtime: 106 ms
	Difficulty: MEDIUM
*/

using namespace std;
#include <algorithm>
#include "../UtilityHelper.hpp"
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cstring>
class Solution {
public:
    string convertToFormat(string s) {
        string retStr;
        for(int i = 0, len = s.length(); i < len; i++) {
            retStr += s[i] + string("#");
        }
        return "$#" + retStr + "@";
    }
    string longestPalindrome(string s) {
        string str = convertToFormat(s);
        int len = str.length();
        int P[len];
        
        memset(P, 0, sizeof(int)*len);
        int R = 1, C = 1;

        int maxLen = 0;
        string maxStr;
        for(int i = 2; i < len; i++) {
            int mirror = 2 * C - i;
            if(i < R) {
                P[i] = min(R - i, P[mirror]);
            }
            
            while(str[i + (1 + P[i])] == str[i - (1 + P[i])]) {
                P[i]++;
            }
            cout << P[i] << endl;
            if(P[i] > maxLen) {
                maxLen = P[i];
                maxStr = str.substr(i - maxLen, 2 * maxLen + 1);
            }
            
            if(i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }

        maxStr.erase(remove(maxStr.begin(), maxStr.end(), '#'), maxStr.end());
        return maxStr;
    }
};
///////////////////TestCases////////////////////////////////////////
int main() {
	Solution s;
    UtilityHelper<string, string> util;
    double output, result;

    vector<string> inputs = {
        "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth",
        "cbbc"
    };
    vector<string> outputs = {
        "test",
    };
    cout << s.longestPalindrome(inputs[1]) << endl;
    // function<string(string)> func = bind(&Solution::longestPalindrome, &s, placeholders::_1);
    // util.run(inputs, outputs, func);
    return 0;
}