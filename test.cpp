/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
using namespace std;
#include <iostream>
class Solution {
public:
    int lengthOfLastWord(string s) {
        if(s == "") return 0;
        
        int nonSpaceCharIndex = s.size() - 1;
        while(s[nonSpaceCharIndex] == ' ') {
            if(nonSpaceCharIndex == 0) return 0;
            nonSpaceCharIndex--;
        }
        
        int lastWordEndIndex = nonSpaceCharIndex;
        int lastWordStartIndex = nonSpaceCharIndex;
        while(lastWordStartIndex >= 0 && s[lastWordStartIndex] != ' ') {
            lastWordStartIndex--;

        }
        
        return lastWordEndIndex - lastWordStartIndex;
    }
};
int main() {
    Solution s;
    int c = s.lengthOfLastWord(" ");
    cout << c << endl;
    return 0;
}