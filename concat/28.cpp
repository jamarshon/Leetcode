
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
821. Shortest Distance to a Character
Given a string S and a character C, return an array of integers representing the shortest distance from the character C in the string.

Example 1:

Input: S = "loveleetcode", C = 'e'
Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 

Note:

S string length is in [1, 10000].
C is a single character, and guaranteed to be in string S.
All letters in S and C are lowercase.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    /*
    keep track of last seen C and use that as the distance
    then do it from the back and take the min of this value with the previous value
    */
    vector<int> shortestToChar(string S, char C) {
        int N = S.size();
        vector<int> res(N, INT_MAX);
        
        int last_C_forward = -1;
        int last_C_backward = -1;
        for(int i = 0; i < N; i++) {
            if(S[i] == C) last_C_forward = i;
            if(S[N-i-1] == C) last_C_backward = N-i-1;
            
            if(last_C_forward >= 0) {
                res[i] = min(res[i], i - last_C_forward);
            }
            
            if(last_C_backward >= 0) {
                res[N-i-1] = min(res[N-i-1], last_C_backward - (N-i-1));
            }
            
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
824. Goat Latin
A sentence S is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
For example, the word 'apple' becomes 'applema'.
 
If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".
 
Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
Return the final sentence representing the conversion from S to Goat Latin. 

Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
 

Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each word.
1 <= S.length <= 150.
/*
    Submission Date: 2018-05-31
    Runtime: 4 ms
    Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_set>

using namespace std;

class Solution {
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
public:
    string toGoatLatin(string S) {
        stringstream ss(S);
        string token;
        string res = "";
        int i = 1;
        while(getline(ss, token, ' ')) {
            if(!res.empty()) res += ' ';
            if(vowels.count(tolower(token[0]))) {
                res += token;
            } else {
                res += token.substr(1) + string(1, token[0]); 
            }
            
            res += "ma" + string(i, 'a');
            i++;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
830. Positions of Large Groups
In a string S of lowercase letters, these letters form consecutive groups of the same character.

For example, a string like S = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z" and "yy".

Call a group large if it has 3 or more characters.  We would like the starting and ending positions of every large group.

The final answer should be in lexicographic order.

 

Example 1:

Input: "abbxxxxzzy"
Output: [[3,6]]
Explanation: "xxxx" is the single large group with starting  3 and ending positions 6.
Example 2:

Input: "abc"
Output: []
Explanation: We have "a","b" and "c" but no large group.
Example 3:

Input: "abcdddeeeeaabbbcd"
Output: [[3,5],[6,9],[12,14]]
 

Note:  1 <= S.length <= 1000
/*
    Submission Date: 2018-06-08
    Runtime: 12 ms
    Difficulty: EASY 
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        vector<vector<int>> res;
        for(int i = 0; i < S.size();) {
            int j = i;
            while(j < S.size() && S[i] == S[j]) j++;
            if(j - i >= 3) {
                res.push_back({i, j-1});
            }
            i = j;
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
832. Flipping an Image
Given a binary matrix A, we want to flip the image horizontally, then invert it, and return the resulting image.

To flip an image horizontally means that each row of the image is reversed.  For example, flipping [1, 1, 0] horizontally results in [0, 1, 1].

To invert an image means that each 0 is replaced by 1, and each 1 is replaced by 0. For example, inverting [0, 1, 1] results in [1, 0, 0].

Example 1:

Input: [[1,1,0],[1,0,1],[0,0,0]]
Output: [[1,0,0],[0,1,0],[1,1,1]]
Explanation: First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]
Example 2:

Input: [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Explanation: First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
Notes:

1 <= A.length = A[0].length <= 20
0 <= A[i][j] <= 1
/*
    Submission Date: 2018-05-31
    Runtime: 15 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        for(auto& row: A) {
            reverse(row.begin(), row.end());
            for(auto& el: row) el ^= 1;
        }
        
        return A;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
836. Rectangle Overlap
A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are the coordinates of its bottom-left corner, and (x2, y2) are 
the coordinates of its top-right corner.

Two rectangles overlap if the area of their intersection is positive.  To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two rectangles, return whether they overlap.

Example 1:

Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
Example 2:

Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
Notes:

Both rectangles rec1 and rec2 are lists of 4 integers.
All coordinates in rectangles will be between -10^9 and 10^9.
/*
    Submission Date: 2018-05-24
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool intersects(int a1, int a2, int b1, int b2) {
        return !(b1 >= a2 || a1 >= b2);
    }
    
    // Check if x intervals intersect and y intervals intersect
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return intersects(rec1[0], rec1[2], rec2[0], rec2[2]) && intersects(rec1[1], rec1[3], rec2[1], rec2[3]);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
844. Backspace String Compare
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
public:
    string eval(string s) {
        string res = "";
        for(const auto& c: s) {
            if(c == '#') {
                if(!res.empty()) res.pop_back();
            } else {
                res.push_back(c);
            }
        }
        return res;
    }
    bool backspaceCompare(string S, string T) {
        return eval(S) == eval(T);
    }
};

int main() {
    return 0;
}