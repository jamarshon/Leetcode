
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
766. Toeplitz Matrix
A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same element.

Now given an M x N matrix, return True if and only if the matrix is Toeplitz.
 

Example 1:

Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
Output: True
Explanation:
1234
5123
9512

In the above grid, the diagonals are "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]", and in each 
diagonal all elements are the same, so the answer is True.
Example 2:

Input: matrix = [[1,2],[2,2]]
Output: False
Explanation:
The diagonal "[1, 2]" has different elements.
Note:

matrix will be a 2D array of integers.
matrix will have a number of rows and columns in range [1, 20].
matrix[i][j] will be integers in range [0, 99].
/*
    Submission Date: 2018-05-31
    Runtime: 22 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty()) return true;
        int N = matrix.size();
        int M = matrix[0].size();
        
        for(int i = 1; i < N; i++) {
            for(int j = 1; j < M; j++) {
                if(matrix[i][j] != matrix[i-1][j-1]) return false;
            }
        }
        
        return true;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
771. Jewels and Stones
You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  
Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.

The letters in J are guaranteed distinct, and all characters in J and S are letters. Letters are case sensitive, so "a" 
is considered a different type of stone from "A".

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
Note:

S and J will consist of letters and have length at most 50.
The characters in J are distinct.
/*
    Submission Date: 2018-05-31
    Runtime: 10 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        unordered_set<char> jewels(J.begin(), J.end());
        int res = 0;
        for(const auto& stone: S) res += jewels.count(stone);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
784. Letter Case Permutation
Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  
Return a list of all possible strings we could create.

Examples:
Input: S = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Input: S = "3z4"
Output: ["3z4", "3Z4"]

Input: S = "12345"
Output: ["12345"]
Note:

S will be a string with length at most 12.
S will consist only of letters or digits.
/*
    Submission Date: 2018-06-03
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    unordered_map<string, vector<string>> dp_;
public:
    /*
     find the first alphabetical letter. get the vector for the remaining string
     add prefix with the letter lower case and upper case to each element from the vector
    */
    vector<string> letterCasePermutation(string S) {
        if(dp_.count(S)) return dp_[S];
        
        int N = S.size();
        int i = 0;
        for(; i < N; i++) {
            if(isalpha(S[i])) break;
        }
        
        if(i >= N) return { S };
        vector<string> rem = letterCasePermutation(S.substr(i + 1));
        int M = rem.size();
        rem.reserve(2*M);
        
        string s1 = S.substr(0, i) + string(1, toupper(S[i]));
        string s2 = S.substr(0, i) + string(1, tolower(S[i]));
        for(int j = 0; j < M; j++) {
            rem.push_back(s2 + rem[j]);
            rem[j] = s1 + rem[j];
        }
        return rem;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
804. Unique Morse Code Words
International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as 
follows: "a" maps to ".-", "b" maps to "-...", "c" maps to "-.-.", and so on.

For convenience, the full table for the 26 letters of the English alphabet is given below:

[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
Now, given a list of words, each word can be written as a concatenation of the Morse code of each letter. 
For example, "cab" can be written as "-.-.-....-", (which is the concatenation "-.-." + "-..." + ".-"). We'll call 
such a concatenation, the transformation of a word.

Return the number of different transformations among all words we have.

Example:
Input: words = ["gin", "zen", "gig", "msg"]
Output: 2
Explanation: 
The transformation of each word is:
"gin" -> "--...-."
"zen" -> "--...-."
"gig" -> "--...--."
"msg" -> "--...--."

There are 2 different transformations, "--...-." and "--...--.".
 

Note:

The length of words will be at most 100.
Each words[i] will have length in range [1, 12].
words[i] will only consist of lowercase letters.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
    vector<string> morse_{".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        unordered_set<string> comb;
        for(const auto& s: words) {
            string curr = "";
            for(const auto& c: s) {
                curr += morse_[c - 'a'];
            }
            comb.insert(curr);
        }
        return comb.size();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
806. Number of Lines To Write String
We are to write the letters of a given string S, from left to right into lines. Each line has maximum width 100 units, 
and if writing a letter would cause the width of the line to exceed 100 units, it is written on the next line. We are given 
an array widths, an array where widths[0] is the width of 'a', widths[1] is the width of 'b', ..., and widths[25] is the width of 'z'.

Now answer two questions: how many lines have at least one character from S, and what is the width used by the last such line? 
Return your answer as an integer list of length 2.

Example :
Input: 
widths = [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "abcdefghijklmnopqrstuvwxyz"
Output: [3, 60]
Explanation: 
All letters have the same length of 10. To write all 26 letters,
we need two full lines and one line with 60 units.
Example :
Input: 
widths = [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10]
S = "bbbcccdddaaa"
Output: [2, 4]
Explanation: 
All letters except 'a' have the same length of 10, and 
"bbbcccdddaa" will cover 9 * 10 + 2 * 4 = 98 units.
For the last 'a', it is written on the second line because
there is only 2 units left in the first line.
So the answer is 2 lines, plus 4 units in the second line.
 
Note:

The length of S will be in the range [1, 1000].
S will only contain lowercase letters.
widths is an array of length 26.
widths[i] will be in the range of [2, 10].
/*
    Submission Date: 2018-05-31
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string S) {
        int current_len = 0;
        int num_lines = 0;
        for(const auto& c: S) {
            if(current_len + widths[c - 'a'] > 100) {
                num_lines++;
                current_len = 0;
            }
            current_len += widths[c - 'a'];
        }
        return {num_lines+1, current_len};
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
811. Subdomain Visit Count
A website domain like "discuss.leetcode.com" consists of various subdomains. At the top level, we have "com", 
at the next level, we have "leetcode.com", and at the lowest level, "discuss.leetcode.com". When we visit a domain like 
"discuss.leetcode.com", we will also visit the parent domains "leetcode.com" and "com" implicitly.

Now, call a "count-paired domain" to be a count (representing the number of visits this domain received), followed by a space, 
followed by the address. An example of a count-paired domain might be "9001 discuss.leetcode.com".

We are given a list cpdomains of count-paired domains. We would like a list of count-paired domains, (in the same format as the 
input, and in any order), that explicitly counts the number of visits to each subdomain.

Example 1:
Input: 
["9001 discuss.leetcode.com"]
Output: 
["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
Explanation: 
We only have one website domain: "discuss.leetcode.com". As discussed above, the subdomain "leetcode.com" and "com" will also be visited. 
So they will all be visited 9001 times.

Example 2:
Input: 
["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output: 
["901 mail.com","50 yahoo.com","900 google.mail.com","5 wiki.org","5 org","1 intel.mail.com","951 com"]
Explanation: 
We will visit "google.mail.com" 900 times, "yahoo.com" 50 times, "intel.mail.com" once and "wiki.org" 5 times. For the subdomains, 
we will visit "mail.com" 900 + 1 = 901 times, "com" 900 + 50 + 1 = 951 times, and "org" 5 times.

Notes:

The length of cpdomains will not exceed 100. 
The length of each domain name will not exceed 100.
Each address will have either 1 or 2 "." characters.
The input count in any count-paired domain will not exceed 10000.
The answer output can be returned in any order.
/*
    Submission Date: 2018-05-31
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> domain_to_count;
        for(const auto& s: cpdomains) {
            int num = 0;
            int i = 0;
            while(i < s.size()) {
                if(isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                } else {
                    break;
                }
                i++;
            }
            
            string domain = s.substr(i + 1);
            while(domain.find('.') != string::npos) {
                domain_to_count[domain] += num;
                domain = domain.substr(domain.find('.') + 1);
            }
            
            domain_to_count[domain] += num;
        }
        
        vector<string> res;
        for(const auto& kv: domain_to_count) {
            res.push_back(to_string(kv.second) + " " + kv.first);
        }
        
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
812. Largest Triangle Area
You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.

Example:
Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
Output: 2
Explanation: 
The five points are show in the figure below. The red triangle is the largest.

Notes:

3 <= points.length <= 50.
No points will be duplicated.
 -50 <= points[i][j] <= 50.
Answers within 10^-6 of the true value will be accepted as correct.
/*
    Submission Date: 2018-06-03
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double largestTriangleArea(vector<vector<int>>& points) {
        int res = 0;
        int N = points.size();
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
                for(int k = j + 1; k < N; k++) {
                    /*
                    given points (a,b), (c,d), (e,f)
                    vector A = (c-a, d-b, 0) and B = (e-a, f-b, 0)
                    cross product of A and B is 
                    ((d-b)*0 - (f-b)*0, -((c-a)*0 - (e-a)*0), (c-a)*(f-b) - (e-a)*(d-b))
                    (0, 0, (c-a)*(f-b) - (e-a)*(d-b))
                    magnitude of A cross B is area of parallelogram so divide by half
                    */
                    int c_minus_a = points[j][0] - points[i][0];
                    int d_minus_b = points[j][1] - points[i][1];
                    int e_minus_a = points[k][0] - points[i][0];
                    int f_minus_b = points[k][1] - points[i][1];
                    
                    res = max(res, abs(c_minus_a*f_minus_b - e_minus_a*d_minus_b));
                }
            }
        }
        return res/2.0;
    }
};

int main() {
    return 0;
}
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