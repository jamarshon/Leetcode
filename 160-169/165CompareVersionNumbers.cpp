/*
165. Compare Version Numbers
Compare two version numbers version1 and version2.
If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.

You may assume that the version strings are non-empty and contain only digits and the . character.
The . character does not represent a decimal point and is used to separate number sequences.
For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level 
revision of the second first-level revision.

Here is an example of version numbers ordering:

0.1 < 1.1 < 1.2 < 13.37

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        if(version1 == version2) return 0;

        stringstream stream_version1(version1);
        stringstream stream_version2(version2);

        vector<int> token_version1, token_version2;
        string temp;
        while(getline(stream_version1, temp, '.')) token_version1.push_back(stoi(temp));
        while(getline(stream_version2, temp, '.')) token_version2.push_back(stoi(temp));

        int token1_size = token_version1.size();
        int token2_size = token_version2.size();

        int N = max(token1_size, token2_size);
        for(int i = 0; i < N; i++) {
            int token1 = i < token1_size ? token_version1[i] : 0;
            int token2 = i < token2_size ? token_version2[i] : 0;
            if(token1 > token2) {
                return 1;
            } else if(token1 < token2) {
                return -1;
            }
        }
        return 0;
    }
};

int main() {
    Solution s;
    return 0;
}