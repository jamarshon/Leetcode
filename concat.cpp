
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1. Two Sum
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
*/

/*
	Submission Date: 2016-07-09
	Runtime: 20ms
	Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
	private:
		// An unordered map is a hash table with a look up time of O(1)
		// The key is the number that was seen already and the value is the index
		// if the value is -1, then it means it has been used already
		unordered_map <int, int> hashTable; 
	public:
		// Assumes numbers in nums is unqiue
	    vector<int> twoSum(vector<int> nums, int target) {
	    	int complement, currentElement, complementIndex;
	    	vector<int> result;

	        for(int i = 0, len = nums.size(); i < len; i++) {
	        	currentElement = nums[i];
	        	complement = target - currentElement;

	        	// Checks to see if the complement has already been seen
	        	if (hashTable.find(complement) != hashTable.end()) {
	        		// The element has only been seen once
	        		complementIndex = hashTable[complement];
	        		if(complementIndex >= 0) {
	        			result.push_back(complementIndex);
	        			result.push_back(i);
	        			hashTable[complement] = -1;
	        		}
	        	}

	        	hashTable[currentElement] = i;
	        }

	        hashTable.clear();
	        return result;
	    }
};

int main() {
	Solution s;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
2. Add Two Numbers
You are given two linked lists representing two non-negative numbers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/*
	Submission Date: 2016-07-10
	Runtime: 40 ms
	Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:
	    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	    	int l1Val, l2Val, total;
	    	ListNode* head = l1;
	        ListNode* prev = NULL;
	    	int carryover = 0;
	        while(l1 != NULL && l2 != NULL) {
	        	l1Val = l1 -> val;
	        	l2Val = l2 -> val;
	        	total = l1Val + l2Val + carryover;
	        	l1 -> val = total % 10;
	        	carryover = total > 9 ? 1 : 0;
	        	prev = l1;
	        	l1 = l1 -> next;
	        	l2 = l2 -> next;
	        }
	        // The minimum length list has been all added up meaning
	        // if l1 is shorter, then just append the remaining l2
	        // if l2 is shorter, then keep l1
	        if(l1 == NULL && l2 != NULL) {
	            l1 = prev;
	            l1 -> next = l2;
	            l1 = l1 -> next;
	        }

	        // Using the carryover, just distribute it over the remaining elements
	        while(l1 != NULL) {
	        	l1Val = l1 -> val;
	        	total = l1Val + carryover;
	        	l1 -> val = total % 10;
	        	carryover = total > 9 ? 1 : 0;
	        	prev = l1;
	        	l1 = l1 -> next;
	        }

	        // End of both lists, if there is still a carryover than create a new node
	        if(carryover == 1) {
	            ListNode* lastNode = new ListNode(1);
	            prev -> next = lastNode;
	        }
	        return head;
	    }
};

int main() {
	return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
/*
3. Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, 
"pwke" is a subsequence and not a substring.
*/

/*
	Submission Date: 2016-07-10
	Runtime: 116 ms
	Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
	private:
		// key is the letter that has been seen and value is its indexes in the string
		unordered_map <string, vector<int>> hashTable; 
	public:
	    int lengthOfLongestSubstring(string s) {
	    	string startLetter, lastLetter;
	    	vector<int> indices;

	    	int currentLen;

	    	string longestSubstring; // not returned only for debugging purpose
	    	int longestSubstrLen = 0,
	    		longestSubstrStartInd = 0;

	    	int startIndex = 0,
	    		endIndex = 0,
	    		len = s.length();
	    	
	    	while(endIndex != len) {
	    		lastLetter = s[endIndex];
	    		
	    		// if the letter has been seen already then find the new startIndex
	    		// it should be the largest of the already seen indexes of that letter
	    		// which will always be the last element of the vector
	    		if (hashTable.find(lastLetter) != hashTable.end()) {
	    				indices = hashTable[lastLetter];
	        		startIndex = max(indices[indices.size() - 1] + 1, startIndex);
	        	}

	        	currentLen = endIndex - startIndex + 1;
	        	if(currentLen > longestSubstrLen) {
	        		longestSubstrStartInd = startIndex;
	        		longestSubstrLen = currentLen;
	        	}
	        	hashTable[lastLetter].push_back(endIndex);
	        	endIndex++;
	    	}
	    	
	    	longestSubstring = s.substr(longestSubstrStartInd, longestSubstrLen);
	    	hashTable.clear();
        return longestSubstring.length();
	    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
4. Median of Two Sorted Arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

/*
	Submission Date: 2016-07-22
	Runtime: 35 ms
	Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& C, vector<int>& D) {
        int cLen = C.size(),
            dLen = D.size();
        vector<int> A;
        vector<int> B;
        int i, j, M, N;
        if(cLen < dLen) {
            A = C;
            B = D;
            M = cLen;
            N = dLen;
        } else {
            B = C;
            A = D;
            N = cLen;
            M = dLen;
        }

        int imin = 0,
            imax = M,
            halfLen = (M + N + 1)/2; // this is middle index of the combined length of A and B
        int maxLeft, minRight;
        while(imin <= imax) {
            i = (imin + imax) / 2;
            j = halfLen - i;
            if(i > 0 && j < N && A[i-1] > B[j]) {
                imax = i - 1; // i is too large so decrease it
            } else if(j > 0 && i < M && B[j-1] > A[i]) {
                imin = i + 1; // i is too small so increase it
            } else {
                if(i == 0){ maxLeft = B[j-1]; }
                else if(j == 0){ maxLeft = A[i-1]; }
                else{ maxLeft = max(B[j-1], A[i-1]); }
                if((M + N) % 2 == 1) {
                    return maxLeft;
                }

                if(i == M){ minRight = B[j]; }
                else if(j == N){ minRight = A[i]; }
                else{ minRight = min(B[j], A[i]); }
                return (maxLeft + minRight) / 2.0;
            }
        }
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
        
        fill(P, P + len, 0);
        int R = 0, C = 0;

        int maxLen = 0;
        string maxStr;
        for(int i = 1; i < len; i++) {
            int mirror = 2 * C - i;
            if(i < R) {
                P[i] = min(R - i, P[mirror]);
            }
            
            while(str[i + (1 + P[i])] == str[i - (1 + P[i])]) {
                P[i]++;
            }
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

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
6. ZigZag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);

convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

/*
    Submission Date: 2016-11-30
    Runtime: 16 ms
    Difficulty: EASY
*/
using namespace std;

#include <iostream>
#include <string>

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1){ return s; }
        
        string result = "";
        int len = s.length();
        int distBtwnCol = 2 * numRows - 2;
        for(int i = 0; i < numRows; i++) {
            int secondJumpDist = 2*i;
            int firstJumpDist = distBtwnCol - secondJumpDist;
            
            if(firstJumpDist == 0 || secondJumpDist == 0){ 
                firstJumpDist = secondJumpDist = distBtwnCol;
            }
            
            int j = i;
            bool jumpToggle = true;
            while(j < len) {
                result += s[j];
                if(jumpToggle) {
                    j += firstJumpDist;
                } else {
                    j += secondJumpDist;
                }
                jumpToggle = !jumpToggle;
            }
        }
        
        return result;
    }
};

int main(){
    Solution s;
    s.convert("PAYPALISHIRING", 3);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
7. Reverse Integer
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

/*
    Submission Date: 2016-11-30
    Runtime: 16 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <limits.h>

class Solution {
public:
    int reverse(int x) {
        if(x == INT_MIN){ return 0; }
        int sign = x >= 0 ? 1 : -1;
        int absX = abs(x);
        int result = 0;
        int maxSafeResult = INT_MAX / 10;
        while(absX != 0) {
            result = result * 10 + absX % 10;
            absX /= 10;
            cout << result << endl;
            if(result > maxSafeResult && absX != 0){ 
                return 0;
            }
        }

        return result * sign;
    }
};

int main() {
    Solution s;
    // cout << s.reverse(-2147483412) << endl;
    cout << s.reverse(-2147483648) << endl;
    // cout << abs(INT_MIN + 1) << endl;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
8. String to Integer (atoi)
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, 
please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). 
You are responsible to gather all the input requirements up front.

/*
    Submission Date: 2016-11-30
    Runtime: 9 ms
    Difficulty: EASY
*/

using namespace std;

#include <iostream>
#include <limits.h>

class Solution {
public:
    int myAtoi(string str) {
        int len = str.length();
        int result = 0;
        bool seenNumeric = false;
        bool seenNonNumeric = false;
        bool negative = false;
        for(int i = 0; i < len; i++) {
            if(str[i] == ' ') {
                if(seenNumeric) return result;
                if(seenNonNumeric) return 0;
            } else if(str[i] == '+') {
                if(seenNumeric) return result;
                if(seenNonNumeric) return 0;
                seenNonNumeric = true;
                negative = false;
            } else if(str[i] == '-') {
                if(seenNumeric) return result;
                if(seenNonNumeric) return 0;
                seenNonNumeric = true;
                negative = true;
            } else{
                int possibleDigit = str[i] - '0';
                if(possibleDigit < 0 || possibleDigit > 9){ // invalid character
                    return result;
                } else {
                    if(negative) {
                        if(result < INT_MIN / 10) return INT_MIN;
                        result *= 10;
                        if(result < INT_MIN + possibleDigit) return INT_MIN;
                        result -= possibleDigit;
                    } else {
                        if(result > INT_MAX / 10) return INT_MAX;
                        result *= 10;
                        if(result > INT_MAX - possibleDigit) return INT_MAX;
                        result += possibleDigit;
                    }
                    seenNumeric = true;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution s;
    // cout << s.reverse(-2147483412) << endl;
    cout << s.myAtoi("-2147483647") << endl;
    // cout << abs(INT_MIN + 1) << endl;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
9. Palindrome Number
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.

/*
    Submission Date: 2016-12-06
    Runtime: 95 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <cmath>

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0){ return false; }
        int i = floor(log10(x));
        while(i > 0) {
            int leftDigit = floor(x / pow(10, i));
            int rightDigit = x % 10;
            if(leftDigit != rightDigit) {
                return false;
            }
            x %= (int)pow(10, i);
            x /= 10;
            i -= 2;
        }
        return true;
    }
};

int main() {
    Solution s;
    int input = -2147483648;
    cout << s.isPalindrome(input) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
10. Regular Expression Matching
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

/*
    Submission Date: 2017-05-25
    Runtime: 15 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
class Solution {
public:
    bool isMatch(string s, string p) {
        int M = s.size(); 
        int N = p.size();
        bool dp[M + 1][N + 1];
        for(int i = 0; i < M + 1; i++) {
            for(int j = 0; j < N + 1; j++) {
                dp[i][j] = false;
            }
        }
        dp[0][0] = true;
        for(int i = 0; i < M + 1; i++) {
            for(int j = 1; j < N + 1; j++) {
                if(p[j - 1] == '*') {
                    // repeat zero times so take the result of excluding the last two characters of p
                    bool repeat_zero_times = dp[i][j - 2];
                    // or repeat many times which is matching preceding char to '*' and previous characters excluding current character in s
                    dp[i][j] = repeat_zero_times || (i > 0 && dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                    
                } else {
                    // s must not be empty and the current characters of s and j must match and the previous characters excluding
                    // the current must match
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        return dp[M][N];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
11. Container With Most Water
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

/*
    Submission Date: 2017-01-20
    Runtime: 32 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>
#include <vector>

class Solution {
public:
    int maxArea(vector<int>& height) {
        int currentArea;
        int low = 0;
        int high = height.size() - 1;
        int maximumArea = -1;
        
        while(low < high) {
            currentArea = (high - low) * min(height[low], height[high]);
            maximumArea = max(currentArea, maximumArea);
            
            if(height[low] > height[high]) {
                high--;
            } else {
                low++;
            }
        }
        
        return maximumArea;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
12. Integer to Roman

Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

/*
    Submission Date: 2017-01-23
    Runtime: 138 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>

struct Denomination {
    int value;
    string symbol;
};

class Solution {
public:
    vector<Denomination> VEC = {
        Denomination{1000, "M"},
        Denomination{500, "D"},
        Denomination{100, "C"},
        Denomination{50, "L"},
        Denomination{10, "X"},
        Denomination{5, "V"},
        Denomination{1, "I"}
    };

    void checkAndAddDenomination(int i, int offset, int len, Denomination denomination, int& num, string& result) {
        if(i + offset < len) {
            Denomination smallerDenomination = VEC[i + offset];
            int difference = denomination.value - smallerDenomination.value;
            if(num >= difference && difference > smallerDenomination.value) {
              num -= difference;
              result += smallerDenomination.symbol + denomination.symbol;
            }
        }
    }
    string intToRoman(int num) {
        int difference;
        string result = "";
        Denomination denomination, smallerDenomination;
        int i = 0, len = VEC.size();

        while(num) {
            denomination = VEC[i];
            if(num >= denomination.value) {
                num -= denomination.value;
                result += denomination.symbol;
            } else {
                checkAndAddDenomination(i, 1, len, denomination, num, result);
                checkAndAddDenomination(i, 2, len, denomination, num, result);
                i++;
            }
        }

        return result;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
13. Roman to Integer

Given a roman numeral, convert it to an integer.

Input is guaranteed to be within the range from 1 to 3999.

/*
    Submission Date: 2017-01-25
    Runtime: 172 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

struct Denomination {
    int value;
    string symbol;
    int numChar;
};

class Solution {
public:
    unordered_map<char, vector<Denomination>> CHAR_TO_DENOMINATIONS_MAP = {
        {'M', {Denomination{1000, "M", 1}}},
        {'D', {Denomination{500, "D", 1}}},
        {'C', {Denomination{900, "CM", 2}, Denomination{400, "CD", 2}, Denomination{100, "C", 1}}},
        {'L', {Denomination{50, "L", 1}}},
        {'X', {Denomination{90, "XC", 2}, Denomination{40, "XL", 2}, Denomination{10, "X", 1}}},
        {'V', {Denomination{5, "V", 1}}},
        {'I', {Denomination{9, "IX", 2}, Denomination{4, "IV", 2}, Denomination{1, "I", 1}}}
    };

    int romanToInt(string s) {
        int result = 0, 
        		i = 0,
        		len = s.size();

        vector<Denomination> possibleDenominations;
        Denomination denomination;

        while(i < len) {
	        	possibleDenominations = CHAR_TO_DENOMINATIONS_MAP[s[i]];
	        	for(int j = 0, jLen = possibleDenominations.size(); j < jLen; j++) {
		        		denomination = possibleDenominations[j];
		        		if(s.substr(i, denomination.numChar) == denomination.symbol) {
			        			result += denomination.value;
			        			i += denomination.numChar;
			        			break;
		        		}
	        	}
        }

        return result;
    }
};

int main() {
		Solution s;
		cout << s.romanToInt("MCMXCVI") << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
14. Longest Common Prefix
Write a function to find the longest common prefix string amongst an array of strings.

/*
    Submission Date: 2016-11-26
    Runtime: 6 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

class Solution {
public:
    tuple<string, int> longestCommonPrefix(string str1, string str2) {
    	int prefixLen = 0;
    	int len = min(str1.length(), str2.length());
    	for(int i = 0; i < len; i++) {
    		if(str1[i] == str2[i])
    			prefixLen++;
    		else
    			break;
    	}
    	return make_tuple(str1.substr(0, prefixLen), prefixLen);
    }
    string longestCommonPrefix(vector<string>& strs) {
        int currentLen;
    	string current;
    	
    	int minLength = 1000;
    	string lcp = "";
    	
    	int len = strs.size();
    	if(len == 0) return lcp;
    	if(len == 1) return strs[0];
    	
    	for(int i = 1; i < len; i++) {
    		tie(current, currentLen) = longestCommonPrefix(strs[i - 1], strs[i]);
    		if(currentLen < minLength) {
    			minLength = currentLen;
    			lcp = current;
    		}
    	}
    	return lcp;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
15. 3Sum
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
/*
    Submission Date: 2017-05-26
    Runtime: 99 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <map>
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        map<int, int> freq;
 
        // Get the frequency of each number
        int N = nums.size();
        for(int i = 0; i < N; i++) {
            if(freq.find(nums[i]) == freq.end()) freq[nums[i]] = 1;
            else freq[nums[i]]++;
        }
 
        // Store the unique numbers in a sorted order
        int count = freq.size();
        vector<int> uniq(count);
 
        int index = 0;
        for (map<int,int>::iterator it = freq.begin(); it != freq.end(); ++it, ++index) {
            uniq[index] = it -> first;
        }
 
        for(int i = 0; i < count; i++) {
            int nums_i = uniq[i];
            int target = -nums_i;
 
            int j = i + 1;
            int k = count - 1;
 
            // No positive integer besides zero can sum to zero so check if 3 zeros exist then break
            if(nums_i >= 0) {
                if(nums_i == 0 && freq[nums_i] >= 3) res.push_back(vector<int>{0, 0, 0});
                break;
            }
 
            // nums_i + nums_i + (-2*nums_i) = 0
            if(freq[nums_i] >= 2) {
                int two_nums_i = 2*target;
                if(freq.find(two_nums_i) != freq.end()) {
                    res.push_back(vector<int>{nums_i, nums_i, two_nums_i});
                }
            }
 
            // (-0.5*nums_i) + (-0.5*nums_i) + nums_i = 0
            if(nums_i % 2 == 0) {
                int half_nums_i = target/2;
                if(freq.find(half_nums_i) != freq.end() && freq[half_nums_i] >= 2) {
                    res.push_back(vector<int>{half_nums_i, half_nums_i, nums_i});
                }
            }
           
            // Generic O(n) sweep of two sum for unique elements
            while(j < k) {
                int sum = uniq[j] + uniq[k];
                if(sum == target) {
                    res.push_back(vector<int>{uniq[i], uniq[j], uniq[k]});
                    j++;
                    k--;
                } else if(sum < target) {
                    j++;
                } else {
                    k--;
                }
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
16. 3Sum Closest
Given an array S of n integers, find three integers in S such that the sum is closest to 
a given number, target. Return the sum of the three integers. You may assume that each 
input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).


/*
    Submission Date: 2017-06-18
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int len = nums.size();
        sort(nums.begin(), nums.end());
        
        int closest = nums[0] + nums[1] + nums[2];
        for(int i = 0; i < len; i++) {
            int low = i + 1;
            int high = len - 1;
            int curr_target = target - nums[i];
            while(low < high) {
                int curr_closest = nums[i] + nums[low] + nums[high];
                if(abs(target - curr_closest) < abs(target - closest)) {
                    closest = curr_closest;
                }

                if(nums[low] + nums[high] == curr_target) {
                    return target;
                } else if(nums[low] + nums[high] < curr_target) {
                    low++;
                } else {
                    high--;
                }
            }
        }
        return closest;
    }
};
int main() {
    Solution s;
    vector<int> v1{0, 0, 0};
    vector<int> v2{-1,2,1,-4};
    vector<int> v3{1,2,4,8,16,32,64,128};
    vector<int> v4{-55,-24,-18,-11,-7,-3,4,5,6,9,11,23,33};
    vector<int> v5{43,75,-90,47,-49,72,17,-31,-68,-22,-21,-30,65,88,-75,23,97,-61,53,87,-3,33,20,51,-79,43,80,-9,34,-89,-7,93,43,55,-94,29,-32,-49,25,72,-6,35,53,63,6,-62,-96,-83,-73,66,-11,96,-90,-27,78,-51,79,35,-63,85,-82,-15,100,-82,1,-4,-41,-21,11,12,12,72,-82,-22,37,47,-18,61,60,55,22,-6,26,-60,-42,-92,68,45,-1,-26,5,-56,-1,73,92,-55,-20,-43,-56,-15,7,52,35,-90,63,41,-55,-58,46,-84,-92,17,-66,-23,96,-19,-44,77,67,-47,-48,99,51,-25,19,0,-13,-88,-10,-67,14,7,89,-69,-83,86,-70,-66,-38,-50,66,0,-67,-91,-65,83,42,70,-6,52,-21,-86,-87,-44,8,49,-76,86,-3,87,-32,81,-58,37,-55,19,-26,66,-89,-70,-69,37,0,19,-65,38,7,3,1,-96,96,-65,-52,66,5,-3,-87,-16,-96,57,-74,91,46,-79,0,-69,55,49,-96,80,83,73,56,22,58,-44,-40,-45,95,99,-97,-22,-33,-92,-51,62,20,70,90};
    cout << s.threeSumClosest(v1, 1) << endl;
    cout << s.threeSumClosest(v2, 1) << endl;
    cout << s.threeSumClosest(v3, 82) << endl;
    cout << s.threeSumClosest(v4, 0) << endl;
    cout << s.threeSumClosest(v5, 284) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
17. Letter Combinations of a Phone Number
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.

Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

/*
    Submission Date: 2016-11-29
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;

#include <unordered_map>
#include <vector>

class Solution {
private:
    unordered_map<char, vector<char>> LETTER_DIGIT_MAP = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };
public:
    vector<string> letterCombinations(string digits) {
        if(digits == ""){ return {}; }
        vector<string> result = {""};
        for(char digit : digits) {
            vector<char> letters = LETTER_DIGIT_MAP[digit];
            vector<string> temp = {};
            for(char letter : letters) {
                for(string str: result) {
             		temp.push_back(str + letter);
             	}
            }
            result = temp;
        }
        return result;
    }
};

int main(){
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
18. 4Sum
Given an array S of n integers, are there elements a, b, c, and d in S such that 
a + b + c + d = target? Find all unique quadruplets in the array which gives the 
sum of target.

Note: The solution set must not contain duplicate quadruplets.

For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

/*
    Submission Date: 2017-06-19
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int len = nums.size();
        vector<vector<int>> res;

        for(int i = 0; i < len; i++) {
            if(nums[i] > 0 && nums[i] > target) break;
            if(i != 0 && nums[i] == nums[i-1]) continue;
            for(int j = i + 1; j < len; j++) {
                if(j != i + 1 && nums[j] == nums[j-1]) continue;
                int low = j + 1;
                int high = len - 1;
                int curr_target = target - nums[i] - nums[j];
                while(low < high) {
                    if(nums[low] + nums[high] == curr_target) {
                        res.push_back({nums[i], nums[j], nums[low], nums[high]});
                        while(++low < high && nums[low] == nums[low - 1]) {}
                    } else if(nums[low] + nums[high] > curr_target) {
                        high--;
                    } else {
                        low++;
                    }
                }
            }

        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
19. Remove Nth Node From End of List
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.

/*
    Submission Date: 2017-05-20
    Runtime: 6 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* current = head;
        ListNode* forward = head;
        for(int i = 0; i < n + 1; i++) {
            // Delete head
            if(forward == NULL) {
                ListNode* new_head = head -> next;
                delete head;
                return new_head;
            }
            forward = forward -> next;
        }
        
        // We assume deleted node is not the head
        while(forward != NULL) {
            current = current -> next;
            forward = forward -> next;
        }
        
        
        // Delete node at current
        ListNode* next_next_node = current -> next -> next;
        delete current -> next;
        current -> next = next_next_node;
        return head;
    }
};

int main(){
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
20. Valid Parentheses
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.

/*
    Submission Date: 2017-01-20
    Runtime: 3 ms
    Difficulty: EASY
*/

using namespace std;
#include <stack>
#include <unordered_map>

class Solution {
public:
    unordered_map<char, char> MAP = {
      {'(', ')'},
      {'[', ']'},
      {'{', '}'}
    };
    bool isValid(string s) {
        stack<char> st;
        char topChar;
        for(char c: s) {
            if(c == ')' || c == '}' || c == ']') {
                if(st.empty()) return false;
                topChar = st.top();
                st.pop();
                if(MAP[topChar] != c) return false;
            } else {
                st.push(c);
            }
        }
        
        return st.empty();
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
21. Merge Two Sorted Lists
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

/*
    Submission Date: 2017-01-20
    Runtime: 9 ms
    Difficulty: EASY
*/
using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* tail = head;
        while(l1 != NULL && l2 != NULL) {
            if(l1 -> val > l2 -> val) {
                tail -> next = l2;
                l2 = l2 -> next;
            } else {
                tail -> next = l1;
                l1 = l1 -> next;
            }
            tail = tail -> next;
        }
        
        tail -> next = (l1 != NULL) ? l1 : l2;
        
        return head -> next;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
22. Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

/*
    Submission Date: 2017-05-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <vector>
#include <iostream>

class Solution {
private:
    void generateParenthesis(const int& n, const int& left, const int& right, const string& current, vector<string>& result) {
        if(left == n && right == n) {
            result.push_back(current);
            return;
        }
        if(right > left) return;
        if(left > n || right > n) return;
        generateParenthesis(n, left + 1, right, current + "(", result);
        generateParenthesis(n, left, right + 1, current + ")", result);
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        generateParenthesis(n, 0, 0, "", result);
        return result;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
23. Merge k Sorted Lists
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
/*
    Submission Date: 2017-05-20
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // O(KN) where K is the number of lists and N is the maximum number of elements in a list
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;
        
        while(true) {
            int min_node_ind = -1;
            for(int i = 0, K = lists.size(); i < K; i++) {
                if(lists[i] == NULL) continue;
                if(min_node_ind == -1) {
                    min_node_ind = i;
                } else if(lists[min_node_ind] -> val > lists[i] -> val) {
                    min_node_ind = i;
                }
            }
            
            if(min_node_ind == -1) 
                break;

            current -> next = lists[min_node_ind];
            lists[min_node_ind] = lists[min_node_ind] -> next;

            if(lists[min_node_ind] == NULL) 
                lists.erase(lists.begin() + min_node_ind);

            current = current -> next;
            current -> next = NULL;
        }
        
        ListNode* head = dummy -> next;
        delete dummy;
        return head;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
24. Swap Nodes in Pairs
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only 
nodes itself can be changed.

/*
    Submission Date: 2017-07-21
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* a = head;
        ListNode* b;
        ListNode* newHead = new ListNode(-1);
        ListNode* prev = newHead;
        prev -> next = a;
        
        while(a != NULL && a -> next != NULL){
            b = a -> next;
            prev -> next = b;
            prev = a;
            a -> next = b -> next;
            b -> next = a;
            a = a -> next;
        }
        
        return newHead -> next;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
25. Reverse Nodes in k-Group
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

/*
    Submission Date: 2017-01-08
    Runtime: 22 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void incrementalReverse(ListNode*& A, ListNode*& B, ListNode*& C) {
        B -> next = A;
        A = B;
        B = C;
        if(C != NULL) {
            C = C -> next;
        }
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k < 0 || head == NULL) return NULL;
        if(k == 1) return head;

        ListNode* newHead = NULL;
        ListNode* A = NULL;
        ListNode* B = head;
        ListNode* C = head -> next;
        ListNode* lastInterval = head;
        ListNode* nextInterval = head;

        int i = k;

        while(i--) {
            if(nextInterval == NULL) {
                return head;
            }
            nextInterval = nextInterval -> next;
        }

        while(true) {
            while(B != nextInterval) incrementalReverse(A, B, C);
            if(newHead == NULL) newHead = A;

            A = nextInterval;
            B = (A == NULL) ? NULL : A -> next;
            C = (B == NULL) ? NULL : B -> next;

            i = k;
            while(i--) {
                if(nextInterval == NULL) {
                    lastInterval -> next = A;
                    return newHead;
                } else {
                     if(i == 0) lastInterval -> next = nextInterval;
                    nextInterval = nextInterval -> next;
                }
            }

            lastInterval = A;
            lastInterval -> next = NULL;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
26. Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

For example,
Given input array nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It doesn't matter what you leave beyond the new length.

/*
    Submission Date: 2017-01-22
    Runtime: 48 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>
#include <vector>

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i = 0, j = 1, len = nums.size();
        if(len == 0) return 0;
        
        while(true) {
            while(j < len && nums[i] == nums[j]) j++;
            if(j == len) return i + 1;
            swap(nums[++i], nums[j++]);
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
27. Remove Element
Given an array and a value, remove all instances of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with constant memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums being 2.

/*
    Submission Date: 2017-01-25
    Runtime: 6 ms
    Difficulty: EASY
*/

using namespace std;
#include <vector>

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        int low = 0;
        int high = len - 1;
        
        while(low < high) {
            if(nums[low] == val) {
                swap(nums[low], nums[high]);
                high--;
            } else {
                low++;
            }
        }
        
        int i = 0, result = 0;
        while(i < len && nums[i++] != val) result++;
        return result;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
28. Implement strStr()
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int hLen = haystack.size();
        int nLen = needle.size();
        if(nLen == 0) return 0;
        if(nLen == hLen) return haystack == needle ? 0 : -1;
        if(nLen > hLen) return -1;
        
        vector<int> start;
        int i = 0, j = 0;
        
        while(i < hLen) {
            if(haystack[i] == needle[0]) start.push_back(i);
            i++;
        }
        
        for(int index : start) {
            i = index;
            j = 0;
            while(i < hLen && j < nLen) {
                if(haystack[i] != needle[j]) break;
                i++;
                j++;
            }
            if(j == nLen) {
                return index;
            }
        }
        
        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
29. Divide Two Integers
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.

/*
    Submission Date: 2017-06-21
    Runtime: 12 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        if(dividend == 0) return 0;
        if(divisor == 0) return INT_MAX;
        if(dividend == INT_MIN && divisor == -1) return INT_MAX; // INT_MIN/-1 overflow

        int sign = ((divisor < 0) ^ (dividend < 0)) ? -1 : 1;

        // make both negative as range is larger
        if(divisor > 0) divisor = -divisor;
        if(dividend > 0) dividend = -dividend;
        if(divisor < dividend) return 0;

        int count = 0;
        for(int i = 31; i >= 0; i--) {
            // maintain (divisor << i) >= INT_MIN
            if(divisor >= INT_MIN >> i) {
                int divisor_shift = divisor << i;
                // check if (divisor << (i+1)) < dividend < (divisor << i)  then i can be used in the result
                if(divisor_shift >= dividend) {
                    count += 1 << i;
                    dividend -= divisor_shift;
                    if(dividend == 0){
                        break;
                    }
                }
            }
        }

        return sign*count;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
30. Substring with Concatenation of All Words
You are given a string, s, and a list of words, words, that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word in words 
exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int num_words = words.size();
        int K = words.front().size();
        int N = s.size();
        int target_count = words.size();

        unordered_map<string, int> freq;
        map<int, string> m;

        // store frequency of the words
        for(string word: words) {
            freq[word]++;
        }

        // associate substrings with each index
        for(int i = 0; i < N - K + 1; i++) {
            string sub = s.substr(i, K);
            if(freq.count(sub)) {
                m[i] = sub;
            }
        }

        vector<int> res;
        for(int i = 0; i < K; i++) {
            // hop K from i keep track of longest 
            int start = i;
            int curr = i;
            int count = 0;
            unordered_map<string, int> not_seen(freq);

            while(curr < N) {
                // no string from words is at this index
                if(m.find(curr) == m.end()) {
                    not_seen = freq;
                    while(curr < N && m.find(curr) == m.end()) {
                        curr += K;
                    }
                    count = 0;
                    start = curr;
                }
                
                if(curr >= N) break;

                string s = m.find(curr) -> second;

                // the word occured more times than needed so keep removing from start
                while(not_seen[s] == 0 && start < min(N, curr)) {
                    string next = m.find(start) -> second;
                    not_seen[next]++;
                    count--;
                    start += K;
                }

                // increase the longest length if the frequency of the word is greater than zero
                if(not_seen[s] > 0) {
                    not_seen[s]--;
                    count++;
                    if(count == target_count) {
                        res.push_back(start);
                    }
                }

                curr += K;
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
31. Next Permutation
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

/*
    Submission Date: 2017-01-24
    Runtime: 13 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if(len <= 1) return;
        
        // starting from the right find any elements that are after it that are larger than it
        // if there is, swap them and sort in descending order all the elements after it
        int i = len - 2;
        while(i >= 0 && nums[i] >= nums[i + 1]) i--;

        int offset;
        if(i == -1) {
            offset = 0;
        } else {
            int j = len - 1;
            while(nums[i] >= nums[j]) j--;
            swap(nums[i], nums[j]);
            offset = i + 1;
        }

        reverse(nums.begin() + offset, nums.end());   
    }
};

int main() {
    Solution s;
    vector<int> v{1,5,1};
    s.nextPermutation(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
32. Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

/*
    Submission Date: 2017-05-20
    Runtime: 3 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <stack>

class Solution {
public:
    // Run time 12 ms
    int longestValidParentheses(string s) {
        int len = s.length();

        if(len == 0) return 0;

        int dp[len];
        int max_len = -1;
        for(int i = 0; i < len; i++) {
            // longest valid ends here so dp[i] is 0
            if(s[i] == '(') {
                dp[i] = 0;
            } else {
                if(i == 0) { 
                    // ')...' first char is ) so 0
                    dp[i] = 0;
                } else if(s[i-1] == '(') {
                    // '...()' it is two plus the longest valid at i - 2
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else {
                    // '...))' check if it is '...((...))' then it is just the inner length 
                    // dp[i - 1] plus the two brackets completed on the outer plus whatever
                    // was before the first (
                    int ind_prev = i - dp[i - 1] - 1;
                    if(s[ind_prev] == '(') {
                        dp[i] = dp[i - 1] + (ind_prev == 0 ? 0: dp[i - dp[i - 1] - 2]) + 2;
                    } else {
                        dp[i] = 0;
                    }
                }
            }
            max_len = max(dp[i], max_len);
        }
        return max_len;
    }

    // Run time 12 ms
    int longestValidParentheses2(string s) {
        int len = s.size();

        int left, right;
        int max_len = 0;

        // traverse right
        left = right = 0;
        for(int i = 0; i < len; i++) {
            if(s[i] == '(') left++;
            else right++;
            if(left == right) {
                max_len = max(2*left, max_len);
            } 
            if(right > left) {
                left = right = 0;
            }
        }

        // traverse right
        left = right = 0;
        for(int i = len - 1; i >= 0; i--) {
            if(s[i] == '(') left++;
            else right++;
            if(left == right) {
                max_len = max(2*left, max_len);
            } 
            if(left > right) {
                left = right = 0;
            }
        }
        return max_len;
    }

    // Run time 6 ms
    int longestValidParentheses3(string s) {
        int len = s.size();

        int max_len = 0;

        stack<int> st;

        st.push(-1);

        for(int i = 0; i < len; i++) {
            if(s[i] == '(') {
                st.push(i);
            } else {
                // ')'
                st.pop();
                if(st.empty()) {
                    st.push(i);
                } else {
                    int prev = st.top();
                    max_len = max(i - prev, max_len);
                }
            }
        }

        return max_len;
    }
};

int main() {
    Solution s;
    cout << s.longestValidParentheses("(()") << endl;
    cout << s.longestValidParentheses(")()())") << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
33. Search in Rotated Sorted Array
Suppose a sorted array is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

/*
    Submission Date: 2016-12-30
    Runtime: 6 ms
    Difficulty: HARD
*/
using namespace std;
#include <vector>

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high) {
            int mid = low + (high - low)/2;

            if(nums[mid] == target) return mid;
            if(nums[low] <= nums[mid]) {
                if(target >= nums[low] && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else { // nums[mid] < nums[high]
                if(target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
34. Search for a Range
Given an array of integers sorted in ascending order, find the starting and ending 
position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        int low = 0;
        int high = len - 1;

        int start = -1;
        int end = -1;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) {
                if(mid == 0 || nums[mid - 1] != nums[mid]) {
                    start = mid;
                    break;
                } else {
                    high = mid - 1;
                }
            } else if(nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if(start != -1) {
            low = 0;
            high = len - 1;
            while(low <= high) {
                int mid = low + (high - low)/2;
                if(nums[mid] == target) {
                    if(mid == len - 1 || nums[mid] != nums[mid + 1]) {
                        end = mid;
                        break;
                    } else {
                        low = mid + 1;
                    }
                } else if(nums[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        
        return {start, end};
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
35. Search Insert Position
Given a sorted array and a target value, return the index if the target is found. 
If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0

/*
    Submission Date: 2017-06-19
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int len = nums.size();

        int low = 0;
        int high = len - 1;

        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) high = mid - 1;
            else low = mid + 1;
        }

        return low;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
36. Valid Sudoku
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled 
with the character '.'.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. 
Only the filled cells need to be validated.


/*
    Submission Date: 2017-06-18
    Runtime: 25 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<pair<int, int>> getNeighbors(const vector<vector<char>>& board, const int& i, const int& j) {
        vector<pair<int, int>> neighbors;
        // traverse row and col
        for(int temp = 0; temp < 9; temp++) {
            // traverse row
            if(isdigit(board[i][temp])) neighbors.emplace_back(i, temp);
            // traverse col
            if(isdigit(board[temp][j])) neighbors.emplace_back(temp, j);
        }

        // traverse subgrid
        int sb_row_low = (i/3)*3;
        int sb_col_low = (j/3)*3;

        for(int row = 0; row < 3; row++) {
            for(int col = 0; col < 3; col++) {
                char c = board[sb_row_low + row][sb_col_low + col];
                if(isdigit(c)) neighbors.emplace_back(sb_row_low + row, sb_col_low + col);
            }
        }

        return neighbors;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                vector<pair<int, int>> neighbors = getNeighbors(board, i, j);
                for(auto p: neighbors) {
                    if(i == p.first && j == p.second) continue;
                    if(board[i][j] == board[p.first][p.second]) return false;
                }
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
37. Sudoku Solver
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.

/*
    Submission Date: 2017-06-18
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <functional>

using namespace std;
struct ValidNums {
    bool avail[10] = {true, true, true, true, true, 
                        true, true, true, true, true};
    int num_avail = 9;
};

class Solution {
    vector<pair<int, int>> getNeighborsDigits(const vector<vector<char>>& board, const int& i, const int& j) {
        function<bool(char)> is_digit = [](const char& c) -> bool { return isdigit(c); };
        return getNeighbors(board, i, j, is_digit);
    }

    vector<pair<int, int>> getNeighborsEmpty(const vector<vector<char>>& board, const int& i, const int& j) {
        function<bool(char)> is_empty = [](const char& c) -> bool { return c == '.'; };
        return getNeighbors(board, i, j, is_empty);
    }

    vector<pair<int, int>> getNeighbors(const vector<vector<char>>& board, const int& i, const int& j, const function<bool(char)>& f) {
        vector<pair<int, int>> neighbors;
        // traverse row and col
        for(int temp = 0; temp < 9; temp++) {
            // traverse row
            if(f(board[i][temp])) neighbors.emplace_back(i, temp);
            // traverse col
            if(f(board[temp][j])) neighbors.emplace_back(temp, j);
        }

        // traverse subgrid
        int sb_row_low = (i/3)*3;
        int sb_col_low = (j/3)*3;

        for(int row = 0; row < 3; row++) {
            for(int col = 0; col < 3; col++) {
                char c = board[sb_row_low + row][sb_col_low + col];
                if(f(c)) neighbors.emplace_back(sb_row_low + row, sb_col_low + col);
            }
        }

        return neighbors;
    }

    bool canSolveSudoku(vector<vector<char>>& board, vector<vector<ValidNums>>& dof) {
        ValidNums min_vn;
        min_vn.num_avail = -1;
        int row, col;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                ValidNums vn = dof[i][j];
                if(vn.num_avail == 0 && board[i][j] == '.') {
                    return false;
                }
                
                if(vn.num_avail > 0 && (min_vn.num_avail == -1 || vn.num_avail < min_vn.num_avail)) {
                    min_vn = vn;
                    row = i;
                    col = j;
                }
            }
        }

        if(min_vn.num_avail == -1) return true;

        vector<pair<int, int>> neighbors = getNeighborsEmpty(board, row, col);

        int& curr_num_avail = dof[row][col].num_avail;
        int temp = curr_num_avail;
        curr_num_avail = 0;

        for(char c = '1'; c <= '9'; c++) {
            if(!min_vn.avail[c - '0']) continue;

            vector<pair<int, int>> need_to_correct;

            board[row][col] = c;

            for(auto p: neighbors) {
                if(p.first == row && p.second == col) continue;
                ValidNums& neighbor_vn = dof[p.first][p.second];
                if(neighbor_vn.num_avail > 0 && neighbor_vn.avail[c - '0']) {
                    need_to_correct.emplace_back(p.first, p.second);
                    neighbor_vn.avail[c - '0'] = false;
                    neighbor_vn.num_avail--;
                }
            }

            
            if(canSolveSudoku(board, dof)) {
                return true;
            }

            for(auto p: need_to_correct) {
                ValidNums& vn = dof[p.first][p.second];
                vn.avail[c - '0'] = true;
                vn.num_avail++;
            }
        }
        
        board[row][col] = '.';
        curr_num_avail = temp;
        return false;
    }
public:
    void populateDof(const vector<vector<char>>& board, vector<vector<ValidNums>>& dof) {
        for(int i = 0; i < 9; i++) {
            vector<ValidNums> temp;
            for(int j = 0; j < 9; j++) {
                ValidNums vn;

                if(isdigit(board[i][j])) {
                    vn.num_avail = 0;
                } else{
                    vector<pair<int, int>> neighbors = getNeighborsDigits(board, i, j);
                    for(auto p: neighbors) {
                        char c = board[p.first][p.second];
                        if(vn.avail[c - '0']) {
                            vn.avail[c - '0'] = false;
                            vn.num_avail--;
                        }
                    }
                }

                temp.push_back(vn);
            }
            dof.push_back(temp);
        }
    }

    bool canSolveSudoku(vector<vector<char>>& board) {
        vector<vector<ValidNums>> dof;
        populateDof(board, dof);
        return canSolveSudoku(board, dof);
    }

    void solveSudoku(vector<vector<char>>& board) {
        bool solved = canSolveSudoku(board);
        return;
    }
};

int main() {
    Solution s;
    function<vector<char>(string)> to_v = [](string s) -> vector<char> { return vector<char>(s.begin(), s.end()); };

    // vector<vector<char>> board{to_v(".87654321"),to_v("2........"),to_v("3........"),to_v("4........"),to_v("5........"),to_v("6........"),to_v("7........"),to_v("8........"),to_v("9........")};
    vector<vector<char>> board{to_v("..9748..."),to_v("7........"),to_v(".2.1.9..."),to_v("..7...24."),to_v(".64.1.59."),to_v(".98...3.."),to_v("...8.3.2."),to_v("........6"),to_v("...2759..")};
    // vector<vector<char>> board{to_v("..4...63."),to_v("........."),to_v("5......9."),to_v("...56...."),to_v("4.3.....1"),to_v("...7....."),to_v("...5....."),to_v("........."),to_v(".........")};
    
    s.solveSudoku(board);
    for(auto v: board) {
        for(auto c: v) cout << c << ' ';
            cout << endl;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
38. Count and Say
The count-and-say sequence is the sequence of integers with the first five terms as 
following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"

/*
    Submission Date: 2017-06-18
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if(n == 1) return "1";
        string prev = countAndSay(n - 1);
        int len = prev.size();
        string res = "";
        for(int i = 0; i < len; i++) {
            int j = i + 1;
            for(; j < len; j++) {
                if(prev[i] != prev[j]) {
                    break;
                }
            }
            
            int count = j - i;
            res += to_string(count) + prev[i];
            i = j - 1;
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
39. Combination Sum
Given a set of candidate numbers (C) (without duplicates) and a target number (T), 
find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7, 
A solution set is: 
[
  [7],
  [2, 2, 3]
]

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void combinationSum(vector<int>& candidates, int sum, vector<vector<int>>& res, vector<int>& curr, int index) {
        for(int i = index; i < candidates.size(); i++) {
            int c = candidates[i];
            if(c > sum) break;

            curr.push_back(c);
            if(c == sum) {
                res.push_back(curr);
                curr.pop_back();
                break;
            } else {
                combinationSum(candidates, sum - c, res, curr, i);
                curr.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> curr;
        combinationSum(candidates, target, res, curr, 0);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
40. Combination Sum II
Given a collection of candidate numbers (C) and a target number (T), find all 
unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

/*
    Submission Date: 2017-06-20
    Runtime: 38 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    void combinationSum2(vector<int>& candidates, vector<int>& curr, int sum, int target, int index, vector<vector<int>>& res) {
        if(sum > target) return;
        if(sum == target) {
            res.push_back(curr);
            return;
        }

        for(int i = index; i < candidates.size(); i++) {
            if(i != index && candidates[i - 1] == candidates[i]) continue;
            curr.push_back(candidates[i]);
            combinationSum2(candidates, curr, sum + candidates[i], target, i + 1, res);
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        vector<int> curr;
        combinationSum2(candidates, curr, 0, target, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
41. First Missing Positive
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.

/*
    Submission Date: 2017-06-19
    Runtime: 9 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int len = nums.size();
        if(len == 0) return 1;

        for(int i = 0; i < len; i++) {
            while(nums[i] != i && nums[i] >= 0 && nums[i] < len && nums[i] != nums[nums[i]]) {
                swap(nums[i], nums[nums[i]]);
            }
        }

        for(int i = 1; i < len; i++) {
            if(nums[i] != i) {
                return i;
            }
        }

        int first_el = nums.front();
        if(first_el <= 0) {
            return len;
        }

        return len + (first_el == len);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
42. Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();

        int temp = 0;
        int res = 0;
        int curr_max = 0;
        for(int i = 1; i < len; i++) {
            if(height[i] >= height[curr_max]) {
                res += (i - curr_max - 1)*height[curr_max] - temp;
                curr_max = i;
                temp = 0;
            } else {
                temp += height[i];
            }
        }
        temp = 0;
        curr_max = len - 1;
        for(int i = len - 2; i >= 0; i--) {
            if(height[i] > height[curr_max]) {
                res += (curr_max - i - 1)*height[curr_max] - temp;
                curr_max = i;
                temp = 0;
            } else {
                temp += height[i];
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{0,1,0,2,1,0,1,3,2,1,2,1};
    // vector<int> v{2,0,2};
    cout << s.trap(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
43. Multiply Strings
Given two non-negative integers num1 and num2 represented as strings, return the 
product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer 
directly.

/*
    Submission Date: 2017-06-19
    Runtime: 25 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<char, string> m;
public:
    string multiply_d(string num1, char d) {
        if(m.count(d)) return m[d];

        string res;
        int carry = 0;

        int d_n = d - '0';
        for(int i = num1.size() - 1; i >= 0; i--) {
            int c = num1[i] - '0';
            int temp = carry + c*d_n;
            res = to_string(temp % 10) + res;
            carry = temp / 10;
        }

        if(carry > 0) res = to_string(carry) + res;
        return m[d] = res;
    }

    string add(string num1, string num2, int offset) {
        int M = num1.size();
        int N = num2.size();

        string res = num2;

        while(N++ < offset) res = "0" + res;

        N = num2.size();
        int carry = 0;
        int index = N - offset - 1;
        for(int i = M - 1; i >= 0; i--) {
            if(index < 0) {
                int temp = carry + (num1[i] - '0');
                res = to_string(temp % 10) + res;
                carry = temp / 10;
            } else {
                int temp = carry + (num1[i] - '0') + (num2[index] - '0');
                res[index] = (temp % 10) + '0';
                carry = temp / 10;
            }
            index--;
        }

        if(carry > 0) res = to_string(carry) + res;
        return res;
    }

    string multiply(string num1, string num2) {
        if(num1.size() > num2.size()) swap(num1, num2);

        if(num1 == "0") return "0";

        int M = num1.size();
        int N = num2.size();

        string res = "0";
        for(int i = N - 1; i >= 0; i--) {
            if(num2[i] == '0') continue;
            string mul = multiply_d(num1, num2[i]);
            res = add(mul, res, N - 1 - i);
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
44. Wildcard Matching
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

/*
    Submission Date: 2017-06-20
    Runtime: 75 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int M = p.size();
        int N = s.size();

        vector<vector<bool>> dp(M + 1, vector<bool>(N + 1, false));

        dp[0][0] = true;

        for(int j = 1; j <= N; j++) {
            dp[0][j] = false;
        }

        for(int i = 1; i <= M; i++) {
            if(p[i-1] == '?') 
                dp[i][0] = false;
            else if(p[i-1] == '*')
                dp[i][0] = dp[i-1][0];
        }

        for(int i = 1; i <= M; i++) {
            for(int j = 1; j <= N; j++) {
                // same or single character means diagonal
                if(p[i-1] == s[j-1] || p[i-1] == '?') { 
                    dp[i][j] = dp[i-1][j-1];
                } else if(p[i-1] == '*') {
                    // either empty sequence or everything not including s[j]
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
                } else {
                    // different letters
                    dp[i][j] = false;
                }
            }
        }

        return dp[M][N];
    }
};

int main() {
    Solution s;
    cout << s.isMatch("aa","a") << ' ' <<  false << endl;
    cout << s.isMatch("aa","aa") << ' ' <<  true << endl;
    cout << s.isMatch("aaa","aa") << ' ' <<  false << endl;
    cout << s.isMatch("aa", "*") << ' ' <<  true << endl;
    cout << s.isMatch("aa", "a*") << ' ' <<  true << endl;
    cout << s.isMatch("ab", "?*") << ' ' <<  true << endl;
    cout << s.isMatch("aab", "c*a*b") << ' ' <<  false << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
45. Jump Game II
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, 
then 3 steps to the last index.)

Note:
You can assume that you can always reach the last index.

/*
    Submission Date: 2017-06-21
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int len = nums.size();

        int curr_max_dist = 0;
        int next_max_dist = 0;
        int min_jumps = 0;
        for(int i = 0; i < len; i++) {
            if(curr_max_dist >= len - 1) {
                return min_jumps;
            }
            
            next_max_dist = max(i + nums[i], next_max_dist);
            if(next_max_dist >= len - 1) {
                return min_jumps + 1;
            }

            if(i == curr_max_dist) {
                curr_max_dist = next_max_dist;
                min_jumps++;
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
46. Permutations
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

/*
    Submission Date: 2017-06-19
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void permuteHelper(vector<int>& nums, int index, vector<vector<int>>& res) {
        int len = nums.size();

        if(index == len - 1) {
            res.push_back(nums);
            return;
        }

        for(int i = index; i < len; i++) {
            swap(nums[i], nums[index]);
            permuteHelper(nums, index + 1, res);
            swap(nums[i], nums[index]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        permuteHelper(nums, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v{1,2,3};
    vector<vector<int>> p = s.permute(v);
    for(auto v2: p) {
        for(auto e: v2) cout << e << ' ';
        cout << endl;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
47. Permutations II
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

/*
    Submission Date: 2017-06-20
    Runtime: 35 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
    void permuteUnique(vector<int>& nums, int index, vector<vector<int>>& res) {
        int len = nums.size();
        if(index == len - 1) {
            res.push_back(nums);
            return;
        }

        unordered_set<int> s;
        for(int i = index; i < len; i++) {
            // Swap any number from i in [index, len) with nums[index] if moving that number x
            // to nums[index] hasn't been done before. Basically just swapping unique x's to nums[index]
            if(s.find(nums[i]) == s.end()) {
                s.insert(nums[i]);
                swap(nums[i], nums[index]);
                permuteUnique(nums, index + 1, res);
                swap(nums[i], nums[index]);
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        permuteUnique(nums, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v;
    vector<vector<int>> t;

    v = {1,1,2};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }

    cout << t.size() <<endl; // 3

    v = {0,1,0,0,9};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }

    cout << t.size() <<endl; // 20

    v = {2,2,1,1};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }
    cout << t.size() <<endl; // 6


    v = {-1,2,0,-1,1,0,1};
    t = s.permuteUnique(v);

    // for(auto v2: t) {
    //     for(auto e: v2) cout << e << ' ';
    //     cout << endl;
    // }
    cout << t.size() <<endl; // 630
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
48. Rotate Image
You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Follow up:
Could you do this in-place?

/*
    Submission Date: 2016-12-15
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <vector>
class Solution {
public:
    int replace(int value, int i, int j, vector<vector<int>>& matrix) {
    	int prev = matrix[i][j];
    	matrix[i][j] = value;
    	return prev;
    }

    void rotate(vector<vector<int>>& matrix) {
        int n = matrix[0].size();
    	for(int i = 0, numLayers = n / 2; i < numLayers; i++) {
    		for(int j = i, rightBoundary = n - i - 1; j < rightBoundary; j++) {
    			int temp =  matrix[n- j - 1][i];
    			temp = replace(temp, i, j, matrix);
                temp = replace(temp, j, n - i - 1, matrix);
                temp = replace(temp, n - i - 1, n - j - 1, matrix);
                temp = replace(temp, n - j - 1, i, matrix);
    		}
    	}
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
49. Group Anagrams

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 

Return:
    [
      ["ate", "eat","tea"],
      ["nat","tan"],
      ["bat"]
    ]

Note: All inputs will be in lower-case.

/*
    Submission Date: 2017-02-19
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    unordered_map<char, int> m = {{'a',2},{'b',3},{'c',5},{'d',7},{'e',11},{'f',13},{'g',17},{'h',19},{'i',23},{'j',29},{'k',31},{'l',37},{'m',41},{'n',43},{'o',47},{'p',53},{'q',59},{'r',61},{'s',67},{'t',71},{'u',73},{'v',79},{'w',83},{'x',89},{'y',97},{'z',101}};
    
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<int, vector<string>> groups;

        for(string str : strs) {
            int product = 1;
            for(char c: str) product *= m[c];
            unordered_map<int, vector<string>>::iterator i = groups.find(product);

            if(i == groups.end()) {
                groups[product] = {str};
            } else {
                (i -> second).push_back(str);
            }
        }

        vector<vector<string>> result;
        for(auto kv: groups) {
            result.push_back(kv.second);
        }
        
        return result;
    }
};



int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
50. Pow(x, n)
Implement pow(x, n)

/*
    Submission Date: 2017-05-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
class Solution {
public:
    double myPow(double x, int n) {
        if(n == INT_MIN) {
            double res = myPow(x, -1*((n+1)/2 - 1));
            return 1/(res*res);
        }
        if(x == 1) return 1;
        if(n < 0) return 1/myPow(x, -n);
        if(n == 0) return 1;
        if(n == 1) return x;
        double res = myPow(x, n/2);
        res *= res;
        if(n % 2 == 0) {
            return res;
        } else {
            return x*res;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n 
chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' 
both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void solveNQueens(int n, vector<pair<int, int>>& queens, int row, vector<vector<string>>& res) {
        if(queens.size() == n) {
            vector<string> board(n, string(n, '.'));
            for(auto queen: queens) {
                board[queen.first][queen.second] = 'Q';
            }
            res.push_back(board);
            return;
        }
        
        // iterate through the columns
        for(int c = 0; c < n; c++) {

            bool intersect = false;
            for(auto queen: queens) {
                // check diagonal and column
                intersect = (abs(queen.first - row) == abs(queen.second - c)) || queen.second == c;
                if(intersect) break;
            }

            if(intersect) continue;
            queens.emplace_back(row, c);
            solveNQueens(n, queens, row + 1, res);
            queens.pop_back();
        }
        
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<pair<int, int>> queens;
        solveNQueens(n, queens, 0, res);
        return res;
        
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
52. N-Queens II
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

/*
    Submission Date: 2017-07-08
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    int nQueens(int arr[], int n, int index) {
        if(index == n) return 1;

        bool allowed[n];
        fill(allowed, allowed + n, true);

        for(int i = 0; i < index; i++) {
            allowed[arr[i]] = false; // column
            int diff = abs(index - i); // diagonal abs(x1 - x2) == abs(y1 - y2)
            if(0 <= arr[i] + diff && arr[i] + diff < n) allowed[arr[i] + diff] = false;
            if(0 <= arr[i] - diff && arr[i] - diff < n) allowed[arr[i] - diff] = false;
        }

        int count = 0;
        for(int i = 0; i < n; i++) {
            if(allowed[i]) {
                arr[index] = i;
                count += nQueens(arr, n, index + 1);
            }
        }

        return count;
    }
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int arr[n];

        return nQueens(arr, n, 0);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
53. Maximum Subarray
Find the contiguous subarray within an array (containing at least one number) 
which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

If you have figured out the O(n) solution, try coding another solution using the 
divide and conquer approach, which is more subtle.

/*
    Submission Date: 2017-06-22
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();

        if(len == 0) return 0;

        int max_sub_arr = nums.front();
        int current = max_sub_arr;

        for(int i = 1; i < len; i++) {
            current = max(nums[i], current + nums[i]);
            max_sub_arr = max(current, max_sub_arr);
        }
        
        return max_sub_arr;
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
54. Spiral Matrix
Given a matrix of m x n elements (m rows, n columns), return all elements of the 
matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].


/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        
        int num_rows = matrix.size();
        
        if(num_rows == 0) return res;
        int num_cols = matrix[0].size();
        
        int left = 0;
        int right = num_cols - 1;
        int top = 0;
        int bottom = num_rows - 1;
        
        int temp;
        while(left <= right && top <= bottom) {
            temp = left;
            while(temp <= right) {
                res.push_back(matrix[top][temp++]);
            }
            
            top++;
            temp = top;
            
            while(temp <= bottom) {
                res.push_back(matrix[temp++][right]);
            }
            
            if(top > bottom) break;
            
            right--;
            temp = right;
            while(temp >= left) {
                res.push_back(matrix[bottom][temp--]);
            }
            
            if(left > right) break;

            bottom--;
            temp = bottom;
            while(temp >= top) {
                res.push_back(matrix[temp--][left]);
            }
            
            left++;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> v;
    v = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    v = {{1,2,3,4},{4,5,6,7},{7,8,9,10}};
    vector<int> t = s.spiralOrder(v);
    for(auto e : t) cout << e << ' ';
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
55. Jump Game
Given an array of non-negative integers, you are initially positioned at the first 
index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.

/*
    Submission Date: 2017-06-19
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();

        if(len == 0) return false;

        int curr_len = nums.front();
        for(int i = 1; i <= curr_len && curr_len < len - 1; i++) {
            curr_len = max(curr_len, i + nums[i]);
        }

        return curr_len >= len - 1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
56. Merge Intervals
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

/*
    Submission Date: 2017-01-19
    Runtime: 49 ms
    Difficulty: HARD
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct sortComparison {
    inline bool operator() (const Interval& a, const Interval& b) {
        return a.start < b.start;
    }
};


class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int len = intervals.size();
        if(len == 0) return intervals;

        sort(intervals.begin(), intervals.end(), sortComparison());
        int j = 0;
        vector<Interval> retVec = {intervals[0]};
        for(int i = 1; i < len; i++) {
            if(overlap(intervals[i], retVec[j])) {
                retVec[j].start = min(intervals[i].start, retVec[j].start);
                retVec[j].end = max(intervals[i].end, retVec[j].end);
            } else {
                retVec.push_back(intervals[i]);
                j++;
            }
        }
        
        return retVec;
    }
    bool overlap(Interval a, Interval b) {
        return !(a.end < b.start || a.start > b.end);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
57. Insert Interval
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].

/*
    Submission Date: 2017-06-22
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct Compare {
    bool operator() (const Interval& lhs, const Interval& rhs) {
        return lhs.start < rhs.start;
    }
    bool operator() (const Interval& lhs, int start) {
        return lhs.start < start;
    }
    bool operator() (int start, const Interval& rhs) {
        return start < rhs.start;
    }
};

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto it = upper_bound(intervals.begin(), intervals.end(), newInterval.start, Compare());

        auto prev_it = it - 1;
        auto merge_it = prev_it;
        if(it == intervals.begin() || (prev_it -> end) < newInterval.start) {
            // either insert or merge
            if(it == intervals.end() || (it -> start) > newInterval.end) {
                intervals.insert(it, newInterval);
                return intervals;
            } else {
                merge_it = it;
            }
        }

        merge_it -> start = min(merge_it -> start, newInterval.start);

        // find the next disjoint interval, as everything in between is now overlapping
        auto it_large = upper_bound(merge_it, intervals.end(), newInterval.end, Compare());
        int max_end = (it_large - 1) -> end;

        merge_it -> end = max(max(max_end, merge_it -> end), newInterval.end);

        intervals.erase(merge_it + 1, it_large);
        
        return intervals;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
58. Length of Last Word
Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example, 
Given s = "Hello World",
return 5.

/*
    Submission Date: 2017-01-19
    Runtime: 6 ms
    Difficulty: EASY
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
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
59. Spiral Matrix II

Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> v(n, vector<int>(n, 0));
        function<int(int, int)> mod = [](const int& x, const int& n) -> int {
            int r = x % n;
            return r < 0 ? r + n : r;
        };

        int i = 0;
        int j = 0;
        int di = 0;
        int dj = 1;

        for(int count = 1; count <= n*n; count++) {
            v[i][j] = count;
            if(v[mod(i + di, n)][mod(j + dj, n)]) {
                swap(di, dj);
                dj *= -1;
            }
            i += di;
            j += dj;
        }
        return v;
    }
};

int main() {
    Solution s;
    vector<vector<int>> t = s.generateMatrix(4);
    for(auto v2: t) {
        for(auto e: v2) cout << e << ' ';
            cout << endl;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
60. Permutation Sequence

The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

/*
    Submission Date: 2017-06-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    unordered_map<int, int> combinations{
        {0, 1},
        {1, 1},
        {2, 2},
        {3, 6},
        {4, 24},
        {5, 120},
        {6, 720},
        {7, 5040},
        {8, 40320},
        {9, 362880}
    };
public:
    string getPermutation(vector<char>& available, int n, int k, int comb_index) {

        if(available.empty()) return "";

        int index = (k - 1)/combinations[comb_index];
        char leading_char = available[index];
        available.erase(available.begin() + index);

        k -= index * combinations[comb_index];

        return string(1, leading_char) + getPermutation(available, n, k, comb_index - 1);
    }
    string getPermutation(int n, int k) {
        vector<char> available;

        char target = '0' + n;
        for(char i = '1'; i <= target; i++) {
            available.push_back(i);
        }

        return getPermutation(available, n, k, n - 1);
    }
};

int main() {
    Solution s;
    for(int i = 1; i <= 6; i++) cout << s.getPermutation(3, i) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
61. Rotate List
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

/*
    Submission Date: 2017-01-19
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(k == 0 || head == NULL) return head;
        
        ListNode* current = head;
        ListNode* lastNode;
        int len = 0;
        while(current != NULL) {
            len++;
            lastNode = current;
            current = current -> next;
        }
        
        k %= len;
        if(k == 0) return head;
        
        int target = len - k;
        ListNode* kLast = head;
        while(--target) {
            kLast = kLast -> next;
        }
        
        ListNode* newHead = kLast -> next;
        kLast -> next = NULL;
        lastNode -> next = head;
        
        return newHead;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
62. Unique Paths
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the 
bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

/*
    Submission Date: 2017-06-22
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m == 0 || n == 0) return 0;

        int arr[m][n];

        for(int i = 0; i < m; i++) arr[i][0] = 1;
        for(int i = 0; i < n; i++) arr[0][i] = 1;

        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                arr[i][j] = arr[i-1][j] + arr[i][j-1];
            }
        }

        return arr[m-1][n-1];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
63. Unique Paths II
Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.

/*
    Submission Date: 2017-06-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
using namespace std;
#include <vector>
#include <unordered_map>

struct PairHash {
    size_t operator()(pair<int, int> const& p) const {
        return ((hash<int>()(p.first) ^ (hash<int>()(p.second) << 1)) >> 1);
    }
};

class Solution {
    unordered_map<pair<int, int>, int, PairHash> m;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid, int i, int j, int M, int N) {
        pair<int, int> p = {i, j};

        auto it = m.find(p);
        if(it != m.end()) return it -> second;

        if(i >= M || j >= N) return 0;
        if(grid[i][j]) return 0;
        if(i == M - 1 && j == N - 1) return 1;

        int res = uniquePathsWithObstacles(grid, i + 1, j, M, N) + uniquePathsWithObstacles(grid, i, j + 1, M, N);
        return m[p] = res;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()) return 0;
        int M = obstacleGrid.size();
        int N = obstacleGrid.front().size();
        return uniquePathsWithObstacles(obstacleGrid, 0, 0, M, N);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
64. Minimum Path Sum
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right 
which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

/*
    Submission Date: 2017-06-23
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int M = grid.size();

        if(M == 0) return 0;
        int N = grid[0].size();

        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                int min_path = INT_MAX;
                if(j > 0) {
                    min_path = min(min_path, grid[i][j-1]);
                }
                if(i > 0) {
                    min_path = min(min_path, grid[i-1][j]);
                }

                min_path = (min_path == INT_MAX) ? 0 : min_path;
                grid[i][j] += min_path;
            }
        }

        return grid[M-1][N-1];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
65. Valid Number
Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up 
front before implementing one.

/*
    Submission Date: 2017-06-22
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        int len = s.size();
        bool seen_number = false;
        char last_special = '\0';

        bool seen_non_space = false;

        if(s.front() == 'e' || s.back() == 'e' || s.back() == '-' || s.back() == '+') return false;

        for(int i = 0; i < len; i++) {
            if(isdigit(s[i])) {
                seen_number = true;
            } else {
                if(isspace(s[i])) {
                    if(seen_number || last_special != '\0') {
                        while(++i < len) {
                            if(!isspace(s[i])) return false;
                        }
                    }
                } else if(s[i] == '.' || s[i] == 'e' || s[i] == '-' || s[i] == '+') {
                    // consecutive '.' not allowed
                    if(last_special == s[i]) return false;

                    // first char can't be 'e' and last char can't be '-' or 'e'
                    if(s[i] == '-' || s[i] == '+') {
                        if(last_special != '\0' || seen_number) return false;
                    } else if(s[i] == 'e') {
                        if(s[i-1] == '-' || !seen_number) return false;
                        if(s[i+1] == '-' || s[i+1] == '+') i++;

                        seen_number = false;

                        // keep iterating until we find a number
                        while(++i < len) {
                            if(s[i] == '.' || s[i] == 'e' || s[i] == '-' || s[i+1] == '+') return false;
                            if(isdigit(s[i])) {
                                seen_number = true;
                            } else if(isspace(s[i])) {
                                if(!seen_number) return false;
                                while(++i < len) {
                                    if(!isspace(s[i])) return false;
                                }
                            } else {
                                return false;
                            }
                        }

                        return seen_number;
                    }

                    last_special = s[i];
                } else {
                    return false;
                }
            }

        }
        return seen_number;
    }
};

int main() {
    Solution s;
    cout << s.isNumber("0") << ' ' <<  true << endl;
    cout << s.isNumber(" 0.1 ") << ' ' <<  true << endl;
    cout << s.isNumber("abc") << ' ' <<  false << endl;
    cout << s.isNumber("1 a") << ' ' <<  false << endl;
    cout << s.isNumber("1  ") << ' ' <<  true << endl;
    cout << s.isNumber("2e10") << ' ' <<  true << endl;
    cout << s.isNumber("-2e10") << ' ' <<  true << endl;
    cout << s.isNumber("2ee") << ' ' <<  false << endl;
    cout << s.isNumber(" ") << ' ' <<  false << endl;
    cout << s.isNumber(".1") << ' ' <<  true << endl;
    cout << s.isNumber("0e") << ' ' <<  false << endl;
    cout << s.isNumber(". 1") << ' ' <<  false << endl;
    cout << s.isNumber("1e.") << ' ' <<  false << endl;
    cout << s.isNumber("1e.2") << ' ' <<  false << endl;
    cout << s.isNumber("2e0") << ' ' <<  true << endl;
    cout << s.isNumber("1.e2") << ' ' <<  true << endl;
    cout << s.isNumber(".e1") << ' ' <<  false << endl;
    cout << s.isNumber("1e-.2") << ' ' <<  false << endl;
    cout << s.isNumber("2e0.1") << ' ' <<  false << endl;
    cout << s.isNumber("1e2e3") << ' ' <<  false << endl;
    cout << s.isNumber("0e ") << ' ' <<  false << endl;
    cout << s.isNumber(" e0") << ' ' <<  false << endl;
    cout << s.isNumber("3-2") << ' ' <<  false << endl;
    cout << s.isNumber("+.8") << ' ' <<  true << endl;
    cout << s.isNumber(" 005047e+6") << ' ' <<  true << endl;
    cout << s.isNumber("+") << ' ' <<  false << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
66. Plus One
Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

/*
    Submission Date: 2017-01-19
    Runtime: 3 ms
    Difficulty: EASY
*/

using namespace std;
#include <vector>

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size() - 1;
        int currentSum;
        int carryIn = 1;
        
        while(carryIn > 0 && i >= 0) {
            currentSum = digits[i] + carryIn;
            digits[i] = currentSum % 10;
            carryIn = currentSum / 10;
            i--;
        } 
        
        if(carryIn > 0) digits.emplace(digits.begin(), carryIn);
        return digits;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
67. Add Binary
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".

/*
    Submission Date: 2017-01-20
    Runtime: 9 ms
    Difficulty: EASY
*/

using namespace std;
#include <unordered_map>
#include <string>

class Solution {
public:
    unordered_map<char, int> MAP = {
       { '0', 0},
        {'1', 1}
    };
    string addBinary(string a, string b) {
        string result = "";
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        int aCurrent, bCurrent;
        
        while(i >= 0 && j >= 0) {
            aCurrent = MAP[a[i]];
            bCurrent = MAP[b[j]];
            result = to_string(aCurrent ^ bCurrent ^ carry) + result;
            carry = aCurrent & bCurrent | aCurrent & carry | bCurrent & carry;
            i--;
            j--;
        }

        while(i >= 0) {
            aCurrent = MAP[a[i]];
            result = to_string(aCurrent ^ carry) + result;
            carry &= aCurrent;
            i--;
        }

        while(j >= 0) {
            bCurrent = MAP[b[j]];
            result = to_string(bCurrent ^ carry) + result;
            carry &= bCurrent;
            j--;
        }

        if(carry > 0) result = "1" + result;
        return result;
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
68. Text Justification
Given an array of words and a length L, format the text such that each line has exactly L characters and is 
fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. 
Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a 
line do not divide evenly between words, the empty slots on the left will be assigned more spaces than 
the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

Corner Cases:
A line other than the last line might contain only one word. What should you do in this case?
In this case, that line should be left-justified.

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int len = words.size();
        for(int i = 0; i < len; i++) {
            int temp = i;
            int count = 1;
            int width = words[i].size();
            while(++temp < len) {
                if(width + count - 1 >= maxWidth) break;
                width += words[temp].size();
                count++;
            }

            string line = "";
            // either last line or fits
            if(width + count - 1 <= maxWidth) {
                for(int j = i; j < temp; j++) line += words[j] + ((j == temp - 1) ? "" : " ");
            } else {
                // now below maxWidth and add spacing
                width -= words[--temp].size();
                count--;

                if(count == 1) {
                    line = words[i];
                } else {
                    int num_spaces = (maxWidth - width)/(count - 1);
                    string space = string(num_spaces, ' ');
                    
                    int remainder_space = (maxWidth - width) % (count - 1);
                    
                    for(int j = i; j < temp; j++) {
                        line += words[j];
                        if(j != temp - 1) {
                            line += space + (remainder_space-- > 0 ? " " : "");
                        }
                    }
                }
            }
            
            while(line.size() != maxWidth) line += " ";
            res.push_back(line);
            i = temp - 1;
        }
        return res;
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
69. Sqrt(x)
Implement int sqrt(int x).

Compute and return the square root of x.
/*
    Submission Date: 2017-01-19
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

class Solution {
public:
    int mySqrt(int x) {
        if(x == 0) return 0;
        int low = 1;
        int high = x;
        int mid, midComplement;
        while(true) {
            mid = (low + high) / 2;
            if(midComplement == mid) {
                return mid;
            } else if(mid > x / mid) {
                high = mid - 1;
            } else if(mid + 1 > x / (mid + 1)) {
                return mid;                
            } else {
                low = mid + 1;
            }
        }
    }
};

int main() {
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
70. Climbing Stairs
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb 
to the top?

Note: Given n will be a positive integer.

/*
    Submission Date: 2017-06-18
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if(n == 0) return 0;
        
        int two_behind = 1;
        int one_behind = 2;
        
        while(--n) {
            int new_val = two_behind + one_behind;
            two_behind = one_behind;
            one_behind = new_val;
        }
        
        return two_behind;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
72. Edit Distance
Given two words word1 and word2, find the minimum number of steps required to convert 
word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

/*
    Submission Date: 2017-06-22
    Runtime: 13 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int M = word1.size();
        int N = word2.size();

        int dp[M+1][N+1];
        for(int i = 0; i <= M; i++) dp[i][0] = i;
        for(int i = 0; i <= N; i++) dp[0][i] = i;

        for(int i = 1; i <= M; i++) {
            for(int j = 1; j <= N; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1;
                }
            }
        }

        return dp[M][N];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
73. Set Matrix Zeroes
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?

/*
    Submission Date: 2017-06-23
    Runtime: 65 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int M = matrix.size();
        if(M == 0) return;
        int N = matrix[0].size();

        bool has_zero_first_row = false;
        bool has_zero_first_col = false;

        for(int i = 0; i < M; i++) {
            if(matrix[i][0] == 0) { has_zero_first_col = true; }
        }

        for(int j = 0; j < N; j++) {
            if(matrix[0][j] == 0) { has_zero_first_row = true; }
        }

        for(int i = 1; i < M; i++) {
            for(int j = 1; j < N; j++) {
                if(matrix[i][j] == 0) {
                    // mark row and column
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for(int i = 1; i < M; i++) {
            for(int j = 1; j < N; j++) {
                if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if(has_zero_first_row) {
            for(int j = 0; j < N; j++) {
                matrix[0][j] = 0;
            }
        }

        if(has_zero_first_col) {
            for(int i = 0; i < M; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
74. Search a 2D Matrix
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has 
the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
Given target = 3, return true.

/*
    Submission Date: 2017-06-23
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int M = matrix.size();
        if(M == 0) return false;
        int N = matrix[0].size();

        int j = N - 1;
        for(int i = 0; i < M; i++) {
            for(; j >= 0; j--) {
                if(matrix[i][j] == target) return true;
                else if(matrix[i][j] < target) {
                    // skip row
                    break;
                } else {
                    continue;
                }
            }
        }

        return false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
75. Sort Colors
Given an array with n objects colored red, white or blue, sort them so that objects of the same 
color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

click to show follow up.

Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total 
number of 0's, then 1's and followed by 2's.

Could you come up with an one-pass algorithm using only constant space?

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

enum Color{red, white, blue};

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int len = nums.size();
        int left_bound = 0;
        int right_bound = len - 1;
        while(left_bound < len) {
            if(nums[left_bound] != red) break;
            left_bound++;
        }

        while(right_bound >= 0) {
            if(nums[right_bound] != blue) break;
            right_bound--;
        }

        int i = left_bound;
        while(i <= right_bound) {
            switch(nums[i]) {
                case red:
                    swap(nums[left_bound], nums[i]);
                    left_bound++;
                    i = max(left_bound, i);
                    break;
                case blue:
                    swap(nums[right_bound], nums[i]);
                    right_bound--;
                    break;
                case white:
                    i++;
                    break;
            }
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
76. Minimum Window Substring
Given a string S and a string T, find the minimum window in S which will contain all the 
characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one 
unique minimum window in S.

/*
    Submission Date: 2017-06-23
    Runtime: 86 ms
    Difficulty: HARD
*/

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        list<int> l;
        unordered_map<char, list<list<int>::iterator>> m;
        unordered_map<char, int> dict;

        for(auto c: t) dict[c]++;

        int len = s.size();
        int target = t.size();
        string res = "";

        for(int i = 0; i < len; i++) {
            // check if current character is in t
            if(dict.count(s[i])) {
                auto it = m.find(s[i]);

                // check if there is a list for this letter
                if(it != m.end()) {
                    list<list<int>::iterator>& list_of_list_it = it -> second;
                    // if there is a list and its size is same as the frequency we must remove the first element from the list
                    // and the iterator from the map
                    if(list_of_list_it.size() == dict[s[i]]) {
                        list<int>::iterator to_erase = list_of_list_it.front();
                        l.erase(to_erase);
                        list_of_list_it.pop_front();
                    }
                } 

                // add the index to the list and the iterator to the map
                l.push_back(i);

                list<int>::iterator l_it = l.end();
                m[s[i]].push_back(--l_it);

                // if there is enough letters (indices in the list) compare with result
                if(l.size() == target) {
                    string sub = s.substr(l.front(), i - l.front() + 1);
                    if(res.empty() || sub.size() < res.size()) res = sub;
                }
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
77. Combinations
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

/*
    Submission Date: 2017-07-08
    Runtime: 73 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void combine(vector<int>& curr, vector<vector<int>>& res, int start, int n, int k) {
        if(curr.size() == k) {
            res.push_back(curr);
            return;
        }

        for(int i = start; i <= n; i++) {
            curr.push_back(i);
            combine(curr, res, i + 1, n, k);
            curr.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> curr;
        combine(curr, res, 1, n, k);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
78. Subsets
Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]

/*
    Submission Date: 2017-07-08
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void subsets(vector<int>& curr, vector<int>& nums, vector<vector<int>>& res, int index) {
        res.push_back(curr);

        for(int i = index; i < nums.size(); i++) {
            curr.push_back(nums[i]);
            subsets(curr, nums, res, i + 1);
            curr.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> curr;
        vector<vector<int>> res;
        subsets(curr, nums, res, 0);
        return res;
    }
};
int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
79. Word Search
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where 
"adjacent" cells are those horizontally or vertically neighboring. The same letter 
cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
/*
    Submission Date: 2017-06-23
    Runtime: 119 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool exist(vector<vector<char>>& board, vector<pair<int, int>>& offset, string word, string curr, int row, int col, int M, int N) {
        if(curr == word) return true;
        char c = word[curr.size()];

        for(auto p: offset) {
            int new_row = row + p.first;
            int new_col = col + p.second;
            if(new_row >= 0 && new_row < M && new_col >= 0 && new_col < N) {
                if(board[new_row][new_col] == c) {
                    board[new_row][new_col] = '\0';
                    if(exist(board, offset, word, curr + c, new_row, new_col, M, N)) {
                        board[new_row][new_col] = c;
                        return true;
                    }
                    board[new_row][new_col] = c;
                }
            }
        }
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int M = board.size();

        if(M == 0) return false;
        int N = board[0].size();

        vector<pair<int, int>> offset{{-1, 0}, {0, 0}, {1, 0}, {0, -1}, {0, 1}};
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                if(exist(board, offset, word, "", i, j, M, N)) return true;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
80. Remove Duplicates from Sorted Array II
Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?

For example,
Given sorted array nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. 
It doesn't matter what you leave beyond the new length.

/*
    Submission Date: 2017-07-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int N = nums.size();

        if(N == 0) return 0;

        int write_idx = 0;
        for(int i = 0; i < N;) {
            int start = i;
            int start_el = nums[start];
            while(i < N && nums[start] == nums[i]) {
                i++;
            }

            int occurences = min(i - start, 2);
            while(occurences--) {
                nums[write_idx++] = start_el;
            }
        }

        return write_idx;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
81. Search in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

/*
    Submission Date: 2017-08-01
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(nums[mid] == target) return true;

            if(nums[low] < nums[mid]) { // first half is sorted
                if(nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else if(nums[low] > nums[mid]) { // second half is sorted
                if(nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else { // ambiguous (worst case is O(n))
                low++;
            }
        }
        return false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
82. Remove Duplicates from Sorted List II
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only 
distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

/*
    Submission Date: 2017-06-22
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL) return NULL;

        ListNode* dummy = new ListNode(-1);

        dummy -> next = head;

        ListNode* prev = dummy;

        ListNode* current = head;
        ListNode* write_node = head;
        while(current) {
            while(current && current -> val == write_node -> val) {
                current = current -> next;
            }

            if(write_node -> next == current) {
                prev = write_node;
                write_node = write_node -> next;
            } else {
                ListNode* temp;
                while(write_node != current) {
                    temp = write_node;
                    write_node = write_node -> next;
                    delete temp;
                }

                prev -> next = current;
            }
        }

        ListNode* new_head = dummy -> next;
        delete dummy;
        return new_head;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
83. Remove Duplicates from Sorted List
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.

/*
    Submission Date: 2017-06-22
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL) return NULL;

        ListNode* new_head = head;
        ListNode* current = head;
        ListNode* write_node = head;
        while(current) {
            while(current && current -> val == write_node -> val) {
                current = current -> next;
            }

            if(current == NULL) {
                // delete remaining
                ListNode* to_delete = write_node -> next;
                write_node -> next = NULL;
                ListNode* temp;
                while(to_delete) {
                    temp = to_delete;
                    to_delete = to_delete -> next;
                    delete temp;
                }
            } else {
                write_node = write_node -> next;
                write_node -> val = current -> val;
            }
        }

        return new_head;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
84. Largest Rectangle in Histogram
Given n non-negative integers representing the histogram's bar height where the width of each bar is 
1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

/*
    Submission Date: 2017-08-01
    Runtime: 19 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea2(vector<int>& heights) {
        stack<int> st;
        heights.push_back(0);
        int max_area = 0;
        // maintain increasing height stack
        // if current height (heights[i]) is less than last element in stack,
        // last element st[j] is bounded by heights[i] so the width is 
        // i - 1 (right_boundary) - st[j-1] (left boundary) and area is width*heights[st[j]]
        // keep removing elements of stack until reach smaller height which allows height[i] to be added to stack
        // if stack is empty it means st[j] is not bounded on the left (minimum of heights from 0 to st[j]) 
        // so it is just i - 1 - (-1) which is i
        for(int i = 0, len = heights.size(); i < len; i++) {
            if(st.empty() || heights[i] >= heights[st.top()]) {
                st.push(i);
            } else {
                while(true) {
                    int top_ind = st.top();
                    st.pop();
                    int curr_area = st.empty() ? i*heights[top_ind] : (i - st.top() - 1)*heights[top_ind];
                    max_area = max(max_area, curr_area);
                    if(st.empty() || heights[i] >= heights[st.top()]) {
                        st.push(i);
                        break;
                    }
                }
            }
        }

        heights.pop_back();
        return max_area;
    }

    int largestRectangleArea(vector<int>& heights) {
        // at index i the area would be heights[i]*(the first index smaller than heights[i] on the right - the first index
        // smaller than heights[i] on the left - 1) for example in {2,1,5,6,2,3} the area at index 2 would be 5*(index of 2 - index of 1)
        // 5*(4-1-1) = 10

        // to construct left and right in linear time we can take advantage of the fact of jumps. for example
        // 4, 200, 100, 10, 5 the left of 10 is 4 as it is the first number smaller to it when moving left that is left[3] = 0
        // since 10 is greater than 5, we just need to compare 5 with elements smaller than 10 so skip 100, 200 by using left array
        // to find the first number smaller than 10 which is 4 
        int N = heights.size();
        vector<int> left(N), right(N);
        for(int i = 0; i < N; i++) {
            int index = i - 1;
            while(index >= 0 && heights[index] >= heights[i]) {
                index = left[index];
            }
            left[i] = index;
        }

        for(int i = N-1; i >= 0; i--) {
            int index = i + 1;
            while(index < N && heights[index] >= heights[i]) {
                index = right[index];
            }
            right[i] = index;
        }

        int max_area = 0;
        for(int i = 0; i < N; i++) {
            max_area = max(max_area, heights[i]*(right[i] - left[i] - 1));
        }

        return max_area;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
85. Maximal Rectangle
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's 
and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: HARD
*/
using namespace std;
#include <vector>

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;
        int num_rows = matrix.size();
        int num_cols = matrix[0].size();

        int area = 0;
        int curr;
        vector<int> height(num_cols, 0);
        vector<int> left(num_cols, 0);
        vector<int> right(num_cols, num_cols);
        for(int i = 0; i < num_rows; i++) {
            for(int j = 0; j < num_cols; j++) {
                if(matrix[i][j] == '1') height[j]++;
                else height[j] = 0;
            }

            // curr reprsent 1 + index of most recent zero seen from left
            curr = 0;
            for(int j = 0; j < num_cols; j++) {
                if(matrix[i][j] == '1') left[j] = max(curr, left[j]);
                else {
                    curr = j + 1;
                    left[j] = 0;
                }
            }

            // curr represents index of most recent zero seen from right
            curr = num_cols;
            for(int j = num_cols - 1; j >= 0; j--) {
                if(matrix[i][j] == '1') right[j] = min(curr, right[j]);
                else {
                    curr = j;
                    right[j] = num_cols;
                }
            }

            for(int j = 0; j < num_cols; j++) {
                area = max(area, (right[j] - left[j])*height[j]);
            }
        }
        return area;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
86. Partition List
Given a linked list and a value x, partition it such that all nodes less than x come before nodes 
greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less_head(-1);
        ListNode great_eq_head(-1);
        
        ListNode* less_curr = &less_head;
        ListNode* great_eq_curr = &great_eq_head;
        
        ListNode* curr = head;
        while(curr) {
            if(curr -> val < x) {
                less_curr -> next = curr;
                less_curr = less_curr -> next;
            } else {
                great_eq_curr -> next = curr;
                great_eq_curr = great_eq_curr -> next;
            }
            curr = curr -> next;
        }
        
        great_eq_curr -> next = NULL;
        less_curr -> next = great_eq_head.next;
        return less_head.next;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
87. Scramble String
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings 
recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

struct PairHash{
    size_t operator()(const pair<string, string>& p) const {
        hash<string> string_hash;
        return string_hash(p.first) ^ (string_hash(p.second) >> 1);
    }
};

class Solution {
    unordered_map<pair<string, string>, bool, PairHash> m;
public:
    bool isScramble(string s1, string s2) {
        pair<string, string> p{s1, s2};

        if(m.count(p)) return m[p];

        int N = s1.size();
        int M = s2.size();

        assert(M == N);
        if(N == 0) return true;
        if(N == 1) return s1 == s2;

        int freq[26] = {0};
        for(int i = 0; i < N; i++) {
            freq[s1[i] - 'a']++;
            freq[s2[i] - 'a']--;
        }

        for(int i = 0; i < 26; i++) {
            if(freq[i] != 0) return m[p] = false;
        }
        
        for(int i = 0; i < N-1; i++) {
            if(isScramble(s1.substr(0, i + 1), s2.substr(0, i + 1)) && isScramble(s1.substr(i + 1), s2.substr(i + 1))) {
                return m[p] = true;
            }
            if(isScramble(s1.substr(N - i - 1), s2.substr(0, i + 1)) && isScramble(s1.substr(0, N - i - 1), s2.substr(i + 1))) {
                return m[p] = true;
            }
        }

        return m[p] = false;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
88. Merge Sorted Array
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to 
hold additional elements from nums2. The number of elements initialized in nums1 and nums2 
are m and n respectively.

/*
    Submission Date: 2017-06-21
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int write_idx = m + n - 1;
        
        while(i >= 0 && j >= 0) {
            if(nums1[i] > nums2[j]) {
                nums1[write_idx--] = nums1[i--];
            } else {
                nums1[write_idx--] = nums2[j--];
            }
        }
        
        while(j >= 0) {
            nums1[write_idx--] = nums2[j--];
        }
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
89. Gray Code

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the 
sequence of gray code. A gray code sequence must begin with 0.

For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

00 - 0
01 - 1
11 - 3
10 - 2
Note:
For a given n, a gray code sequence is not uniquely defined.

For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.

For now, the judge is able to judge based on one instance of gray code sequence. Sorry about that.

/*
    Submission Date: 2017-06-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> grayCode(int n) {
        if(n == 0) return {0};

        vector<int> prev = grayCode(n - 1);

        for(int i = prev.size() - 1; i >= 0; i--) {
            prev.push_back(prev[i] + (1 << (n - 1)));
        }

        return prev;
    }
};

int main() {
    Solution s;
    vector<int> t = s.grayCode(2);
    for(auto e: t) cout << bitset<3>(e).to_string() << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
90. Subsets II

Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

/*
    Submission Date: 2017-06-25
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void print(vector<T> v) {
    for(auto e: v) cout << e << ' ';
    cout << endl;
}

template <typename T> 
void print2(vector<vector<T>> v) {
    for(auto v2: v) print(v2);
}

class Solution {
public:
    void subsetsWithDupHelper(vector<int>& nums, vector<int>& curr, int index, vector<vector<int>>& res) {
        res.push_back(curr);

        for(int i = index; i < nums.size(); i++) {
            if(i == index || nums[i] != nums[i-1]) {
                curr.push_back(nums[i]);
                subsetsWithDupHelper(nums, curr, i + 1, res);
                curr.pop_back();
            }
            
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> curr;
        sort(nums.begin(), nums.end());
        subsetsWithDupHelper(nums, curr, 0, res);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> v;
    v = {1,2,2};
    vector<vector<int>> v2 = s.subsetsWithDup(v);
    print2(v2);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
91. Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

/*
    Submission Date: 2017-06-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<string, int> m;
public:
    int numDecodingsHelper(string s) {
        if(m.count(s)) return m[s];
        
        int len = s.size();
        if(len == 0) return 1;
        if(len == 1) return s[0] > '0';
        
        // length is at least 2
        int res = 0;
        if(s[0] > '0') {
            if(s[0] < '2' || (s[0] == '2' && s[1] <= '6')) {
                res += numDecodingsHelper(s.substr(2));
            }
            
            res += numDecodingsHelper(s.substr(1));
        }
        
        
        return m[s] = res;
    }

    int numDecodings(string s) {
        if(s.empty()) return 0;
        return numDecodingsHelper(s);
    }
};

int main() {
    Solution s;
    cout << s.numDecodings("12") << endl; // 2
    cout << s.numDecodings("17") << endl; // 2
    cout << s.numDecodings("1273") << endl; // 2
    cout << s.numDecodings("0") << endl; // 0
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.

/*
    Submission Date: 2017-01-14
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(m == n) return head;
        
        ListNode* begin = head;
        bool reverseIncludeHead = m == 1;
        
        for(int i = 0; i < m - 2; i++){
            begin = begin -> next;
        }
        
        ListNode* end = begin->next;
        ListNode* A = reverseIncludeHead ? head : end;
        ListNode* B = A -> next;
        ListNode* C = B == NULL ? NULL : B -> next;
        
        for(int i = 0; i < n-m; i++){
            B -> next = A;
            A = B;
            B = C;
            if(C != NULL) C = C -> next;
            
        }
        
        if(reverseIncludeHead){
            head -> next = B;
            head = A;
        } else {
            begin -> next = A;
            end -> next = B;
        }
        
        return head;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
93. Restore IP Addresses
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void restoreIpAddressesHelper(string rem, string curr, int periods, vector<string>& res) {
        if(periods == 4) {
            if(rem.empty()) {
                res.push_back(curr);
            }
            return;
        }

        int len = rem.size();

        if(len == 0) return;

        if(!curr.empty()) curr += '.';

        string first_substr = rem.substr(0, 1);
        restoreIpAddressesHelper(rem.substr(1), curr + first_substr, periods + 1, res);

        if(len > 1) {
            string second_substr = rem.substr(0, 2);
            if(stoi(second_substr) >= 10) {
                restoreIpAddressesHelper(rem.substr(2), curr + second_substr, periods + 1, res);
            }
        }

        if(len > 2) {
            string third_substr = rem.substr(0, 3);
            if(stoi(third_substr) >= 100 && stoi(third_substr) <= 255) {
                restoreIpAddressesHelper(rem.substr(3), curr + third_substr, periods + 1, res);
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        restoreIpAddressesHelper(s, "", 0, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
94. Binary Tree Inorder Traversal
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],

   1
    \
     2
    /
   3

return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-01-19
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <stack>
#include <unordered_set>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        unordered_set<TreeNode*> set;
        
        vector<int> result;
        s.push(root);
        
        while(!s.empty()){
            TreeNode* top = s.top();
            s.pop();
            if(top == NULL) { 
                continue;
            } else if(set.find(top) == set.end()) {
                s.push(top -> right);
                s.push(top);
                s.push(top -> left);
                set.insert(top);
            } else {
                result.push_back(top -> val);
            }
        }
        
        return result;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
95. Unique Binary Search Trees II
Given an integer n, generate all structurally unique BST's (binary search trees) 
that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

/*
    Submission Date: 2017-07-18
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void labelInorder(TreeNode* curr, int& count) {
        if(curr == NULL) return;

        labelInorder(curr -> left, count);
        curr -> val = count++;
        labelInorder(curr -> right, count);
    }

    void getPreorderSequence(string s, vector<string>& res, int zeros, int ones, int len) {
        if(ones > len/2) return;

        if(s.size() == len) {
            res.push_back(s);
            return;
        }

        getPreorderSequence(s + '1', res, zeros, ones + 1, len);
        if(ones > zeros) {
            getPreorderSequence(s + '0', res, zeros + 1, ones, len);
        }
    }

    TreeNode* buildFromPreOrder(string seq, int& index) {
        if(seq[index] == '0') {
            index++;
            return NULL;
        }

        TreeNode* curr = new TreeNode(-1);
        index++;
        curr -> left = buildFromPreOrder(seq, index);
        curr -> right = buildFromPreOrder(seq, index);
        return curr;
    }

    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return {};
        vector<string> pre_seq;
        getPreorderSequence("", pre_seq, 0, 0, n*2);

        vector<TreeNode*> res(pre_seq.size());
        transform(pre_seq.begin(), pre_seq.end(), res.begin(), [this](const string s) {
            int temp = 0;
            TreeNode* root = buildFromPreOrder(s + "0", temp);
            temp = 1;
            labelInorder(root, temp);
            return root;
        });
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
96. Unique Binary Search Trees
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

/*
    Submission Date: 2017-06-28
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        long long dp[n + 1];

        dp[0] = dp[1] = 1;

        for(long long i = 1; i < n; i++) {
            dp[(int)i + 1] = dp[i]*(2*i + 2)*(2*i + 1)/(i + 1)/(i + 2);
        }

        return dp[n];
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
97. Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    
    bool isInterleave(string s1, string s2, string s3) {
        int M = s1.size();
        int N = s2.size();
        if(M + N != s3.size()) return false;

        bool dp[M + 1][N + 1];

        for(int i = 0; i <= M; i++) {
            for(int j = 0; j <= N; j++) {
                if(i == 0 && j == 0) dp[i][j] = true;
                else if(i == 0) dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i + j - 1];
                else if(j == 0) dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i + j - 1];
                else dp[i][j] = (dp[i][j-1] && s2[j-1] == s3[i + j - 1]) || (dp[i-1][j] && s1[i-1] == s3[i + j - 1]);
            }
        }

        return dp[M][N];
    }
};


int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

    2
   / \
  1   3

Binary tree [2,1,3], return true.

    1
   / \
  2   3

Binary tree [1,2,3], return false.

/*
    Submission Date: 2017-01-27
    Runtime: 13 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    bool isValidBSTHelper(TreeNode* root, int* min, int* max) {
        if(root == NULL) return true;
        
        int rootVal = root -> val;
        int* rootValPtr = &rootVal;
        
        if((min && rootVal <= *min) ||(max && rootVal >= *max)) return false;
        
        bool validLeftSubTree = isValidBSTHelper(root -> left, min, rootValPtr);
        bool validRightSubTree = isValidBSTHelper(root -> right, rootValPtr, max);
        
        return validLeftSubTree && validRightSubTree;
    }
    
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(root, NULL, NULL);
    }
};

int main() {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
100. Same Tree
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have 
the same value.

/*
    Submission Date: 2017-06-23
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == NULL && q == NULL) return true;
        if(p == NULL || q == NULL) return false;

        if(p -> val != q -> val) return false;
        return isSameTree(p -> left, q -> left) && isSameTree(p -> right, q -> right);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
101. Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* left, TreeNode* right) {
        if(left == NULL && right == NULL) return true;
        if(left == NULL || right == NULL) return false;
        if(left -> val != right -> val) return false;

        return isSymmetric(left -> left, right -> right) && isSymmetric(left -> right, right -> left);
    }
    bool isSymmetric(TreeNode* root) {
        if(root) return isSymmetric(root -> left, root -> right);
        return true;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
102. Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values. 
(ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]

/*
    Submission Date: 2017-06-29
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            int level_size = q.size();
            vector<int> temp;
            for(int i = 0; i < level_size; i++) {
                TreeNode* curr = q.front();
                if(curr) {
                    temp.push_back(curr -> val);
                    q.push(curr -> left);
                    q.push(curr -> right);
                }
                q.pop();
            }
            if(!temp.empty()) res.push_back(temp);
        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
103. Binary Tree Zigzag Level Order Traversal
Given a binary tree, return the zigzag level order traversal of its nodes' values. 
(ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]

/*
    Submission Date: 2017-06-29
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;

        bool forward = true;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int level_size = q.size();
            vector<int> temp;
            for(int i = 0; i < level_size; i++) {
                TreeNode* curr = q.front();
                if(curr) {
                    temp.push_back(curr -> val);
                    q.push(curr -> left);
                    q.push(curr -> right);
                }
                q.pop();
            }

            if(!forward) {
                reverse(temp.begin(), temp.end());
            }

            if(!temp.empty()) res.push_back(temp);
            forward ^= true;
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
104. Maximum Depth of Binary Tree
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the 
farthest leaf node.
/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == NULL) return 0;
        return 1 + max(maxDepth(root -> left), maxDepth(root -> right));
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
105. Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

/*
    Submission Date: 2017-07-21
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    unordered_map<int, int> inorder_val_to_index;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i = 0; i < inorder.size(); i++) {
            inorder_val_to_index[inorder[i]] = i;
        }

        return buildTreeHelper(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }
    TreeNode* buildTreeHelper(const vector<int>& preorder, const vector<int>& inorder, 
        int i, int j, int k, int l) {
        assert(j - i == l - k);

        if(i == j) return NULL;

        TreeNode* root = new TreeNode(preorder[i]);
        int root_idx = inorder_val_to_index[preorder[i]];
        int left_size = root_idx - k;

        root -> left = buildTreeHelper(preorder, inorder, i + 1, i + 1 + left_size, k, root_idx);
        root -> right = buildTreeHelper(preorder, inorder, i + left_size + 1, j, root_idx + 1, l);
        return root;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
106. Construct Binary Tree from Inorder and Postorder Traversal
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

/*
    Submission Date: 2017-07-24
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> inorder_val_to_ind;

        int N = postorder.size();

        for(int i = 0; i < N; i++) {
            inorder_val_to_ind[inorder[i]] = i;
        }
        return buildTree(inorder, postorder, inorder_val_to_ind, 0, N, 0, N);
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder, 
        unordered_map<int, int>& inorder_val_to_ind, 
        int in_start, int in_end, int post_start, int post_end) {

        assert(in_end >= in_start && post_end >= post_start);
        assert(in_end - in_start == post_end - post_start);

        if(in_end == in_start) return NULL;

        int root_val = postorder[post_end - 1];
        int left_size = inorder_val_to_ind[root_val] - in_start;
        int right_size = in_end - inorder_val_to_ind[root_val] - 1;

        TreeNode* root = new TreeNode(root_val);
        root -> left = buildTree(inorder, postorder, inorder_val_to_ind, 
            in_start, inorder_val_to_ind[root_val], post_start, post_start + left_size);
        root -> right = buildTree(inorder, postorder, inorder_val_to_ind, 
            inorder_val_to_ind[root_val] + 1, in_end, post_start + left_size, post_end - 1);
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
107. Binary Tree Level Order Traversal II
Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
(ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]

/*
    Submission Date: 2017-07-20
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> q{{root}};
        deque<vector<int>> dq;
        
        while(!q.empty()) {
            int q_size = q.size();
            vector<int> temp;
            for(int i = 0; i < q_size; i++) {
                TreeNode* curr = q.front();
                if(curr) {
                    q.push(curr -> left);
                    q.push(curr -> right);
                    temp.push_back(curr -> val);
                }
                q.pop();
            }
            if(!temp.empty()) dq.push_front(temp);
        }

        vector<vector<int>> res(dq.begin(), dq.end());
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
108. Convert Sorted Array to Binary Search Tree
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

/*
    Submission Date: 2017-07-18
    Runtime: 12 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
        if(start > end) return NULL;
        int mid = start + (end - start + 1)/2;

        TreeNode* root = new TreeNode(nums[mid]);
        root -> left = sortedArrayToBST(nums, start, mid - 1);
        root -> right = sortedArrayToBST(nums, mid + 1, end);
        return root;
    }
    
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
109. Convert Sorted List to Binary Search Tree
Given a singly linked list where elements are sorted in ascending order, 
convert it to a height balanced BST.

/*
    Submission Date: 2017-06-11
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode* convertToBST(ListNode* list_node, int n) {
        if(n <= 0) return NULL;
        int mid = n/2;
        ListNode* temp = list_node;
        for(int i = 0; i < mid; i++) {
            temp = temp -> next;
        }
        TreeNode* new_val = new TreeNode(temp -> val);
        TreeNode* right_child = convertToBST(temp -> next, n - mid - 1);
        TreeNode* left_child = convertToBST(list_node, mid);
        new_val -> left = left_child;
        new_val -> right = right_child;
        return new_val;
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        ListNode* temp = head;
        int n = 0;
        while(temp) {
            n++;
            temp = temp -> next;
        }
        return convertToBST(head, n);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
110. Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which 
the depth of the two subtrees of every node never differ by more than 1.

/*
    Submission Date: 2017-07-18
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int computeHeight(TreeNode* root) {
        if(root == NULL) return -1;

        int left_height = computeHeight(root -> left);
        if(left_height == INT_MIN) return INT_MIN;
        int right_height = computeHeight(root -> right);
        if(right_height == INT_MIN) return INT_MIN;

        if(abs(left_height - right_height) > 1) return INT_MIN;
        return max(left_height, right_height) + 1;
    }

    bool isBalanced(TreeNode* root) {
        return computeHeight(root) != INT_MIN;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path 
from the root node down to the nearest leaf node.

/*
    Submission Date: 2017-07-16
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(root == NULL) return 0;
        if(root -> left == NULL && root -> right == NULL) {
            return 1;
        }

        // either one child or two child meaning res will be updated at least once
        int res = INT_MAX;
        if(root -> left) {
            res = min(res, minDepth(root -> left));
        }

        if(root -> right) {
            res = min(res, minDepth(root -> right));
        }

        return res + 1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
112. Path Sum
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up 
all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;

        int curr = root -> val;
        if(curr == sum && root -> left == NULL && root -> right == NULL) return true;

        return hasPathSum(root -> left, sum - curr) || hasPathSum(root -> right, sum - curr);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
113. Path Sum II
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]

/*
    Submission Date: 2017-07-24
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void pathSum(TreeNode* root, int curr_sum, int sum, vector<int>& curr, vector<vector<int>>& res) {
        if(root == NULL) return;

        curr.push_back(root -> val);
        curr_sum += root -> val;

        if(root -> left == NULL && root -> right == NULL) {
            if(curr_sum == sum) {
                res.push_back(curr);
            }
        } else {
            pathSum(root -> left, curr_sum, sum, curr, res);
            pathSum(root -> right, curr_sum, sum, curr, res);
        }

        curr.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> curr;
        pathSum(root, 0, sum, curr, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
114. Flatten Binary Tree to Linked List
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6

Hints:
If you notice carefully in the flattened tree, each node's right child points to the next node of a 
pre-order traversal.

/*
    Submission Date: 2017-07-04
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        if(root == NULL) return;
        if(root -> left == NULL && root -> right == NULL) return;
        flatten(root -> left);
        flatten(root -> right);
        if(root -> left) {
            TreeNode* right = root -> right;
            root -> right = root -> left;
            TreeNode* temp = root -> right;
            while(temp -> right) {
                temp = temp -> right;
            }
            temp -> right = right;
            root -> left = NULL;
        }
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
116. Populating Next Right Pointers in Each Node
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }
Populate each next pointer to point to its next right node. If there is no next right node, the 
next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every 
parent has two children).
For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

/*
    Submission Date: 2017-07-18
    Runtime: 22 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode* curr = root;
        TreeLinkNode* next_level_start = NULL;
        while(curr) {
            next_level_start = curr -> left;

            while(curr) {
                if(curr->left) {
                    curr -> left -> next = curr -> right;
                }
                if(curr -> right) {
                    if(curr -> next) {
                        curr -> right -> next = curr -> next -> left;
                    } else {
                        curr -> right -> next = NULL;
                    }
                }
                curr = curr -> next;
            }

            curr = next_level_start;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
118. Pascal's Triangle
Given numRows, generate the first numRows of Pascal's triangle.

For example, given numRows = 5,
Return

[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows, vector<int>{});

        for(int i = 0; i < numRows; i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0 || j == i) res[i].push_back(1);
                else res[i].push_back(res[i-1][j-1] + res[i-1][j]);
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
120. Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to 
adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total 
number of rows in the triangle.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int M = triangle.size();
        for(int i = 0; i < M; i++) {
            int N = triangle[i].size();
            for(int j = 0; j < N; j++) {
                if(i == 0 && j == 0) continue;
                if(j == 0) 
                    triangle[i][j] += triangle[i-1][j];
                else if(j == N - 1)
                    triangle[i][j] += triangle[i-1][j-1];
                else
                    triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]);
            }
        }

        int res = INT_MAX;
        for(auto e: triangle.back()) res = min(res, e);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
121. Best Time to Buy and Sell Stock
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the 
stock), design an algorithm to find the maximum profit.

Example 1:
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
Example 2:
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.

/*
    Submission Date: 2017-07-21
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.empty()) return 0;

        int smallest, profit;
        smallest = prices.front();
        profit = 0;

        for(int i = 0; i < prices.size(); i++) {
            smallest = min(prices[i], smallest);
            profit = max(profit, prices[i] - smallest);
        }
        return profit;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
124. Binary Tree Maximum Path Sum
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any 
node in the tree along the parent-child connections. The path must contain at least one node and 
does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.

/*
    Submission Date: 2017-07-21
    Runtime: 19 ms
    Difficulty: HARD
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        if(root == NULL) return 0;
        int max_curr = root -> val;
        maxPathSum(root, max_curr);
        return max_curr;
    }
    int maxPathSum(TreeNode* root, int& max_curr) {
        if(root == NULL) return 0;

        int curr = root -> val;
        int left = maxPathSum(root -> left, max_curr);
        int right = maxPathSum(root -> right, max_curr);
        max_curr = max(max_curr, curr + left + right);
        curr = max(max(curr, curr + left), curr + right);
        max_curr = max(max_curr, curr);
        return curr;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
125. Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>
#include <cctype>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int len = s.size();
        int i = 0;
        int j = len - 1;

        while(i < j) {
            while(!isalnum(s[i]) && i < j) i++;
            if(i >= j) return true;

            while(!isalnum(s[j]) && i < j) j--;
            if(i >= j) return true;

            if(tolower(s[i]) != tolower(s[j])) return false;
            i++;
            j--;
        }

        return true;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
126. Word Ladder II
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation 
sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). Please 
reload the code definition to get the latest changes.

/*
    Submission Date: 2017-07-21
    Runtime: 712 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

struct QueueItem {
    string vertex;
    vector<int> path;
    QueueItem(string _vertex, vector<int> _path=vector<int>{}): vertex(_vertex), path(_path) {}
};

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, vector<string>> vertex_to_edges;

        wordList.push_back(beginWord);

        int N = wordList.size();
        int word_len = beginWord.size();

        unordered_map<string, int> vertex_to_index;

        for(int i = 0; i < N; i++) {
            vertex_to_index[wordList[i]] = i;

            if(wordList[i] == beginWord && i != N - 1) continue;
            for(int j = i + 1; j < N; j++) {
                if(wordList[j] == beginWord && j != N - 1) continue;

                bool seen_different = false;
                bool can_add = true;
                for(int k = 0; k < word_len; k++) {
                    if(wordList[i][k] != wordList[j][k]) {
                        if(seen_different) {
                            can_add = false;
                            break;
                        }
                        seen_different = true;
                    }
                }

                if(can_add) {
                    vertex_to_edges[wordList[i]].push_back(wordList[j]);
                    vertex_to_edges[wordList[j]].push_back(wordList[i]);
                }
            }
        }

        queue<QueueItem> to_do;
        to_do.emplace(beginWord);

        unordered_set<string> visited;
        vector<vector<string>> res;

        vector<vector<int>> paths;
        int min_path = -1;

        while(!to_do.empty()) {
            QueueItem curr = to_do.front();
            to_do.pop();
            if(min_path != -1 && curr.path.size() > min_path) continue;

            if(curr.vertex == endWord) {
                if(min_path == -1) {
                    min_path = curr.path.size();
                }
                paths.push_back(curr.path);
                continue;
            }

            visited.insert(curr.vertex);

            curr.path.push_back(vertex_to_index[curr.vertex]);
            for(auto neighbor: vertex_to_edges[curr.vertex]) {
                if(visited.count(neighbor)) continue;
                to_do.emplace(neighbor, curr.path);
            }
        }

        for(auto path: paths) {
            vector<string> temp(path.size());
            transform(path.begin(), path.end(), temp.begin(), [wordList](const int index){
                return wordList[index];
            });

            temp.push_back(endWord);
            res.push_back(temp);
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
127. Word Ladder
Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest 
transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). 
Please reload the code definition to get the latest changes.

/*
    Submission Date: 2017-06-28
    Runtime: 1449 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
    bool differByOneLetter(string s1, string s2) {
        int len = s1.size();
        bool seen_different = false;
        for(int i = 0; i < len; i++) {
            if(s1[i] != s2[i]) {
                if(seen_different) return false;
                seen_different = true;
            }
        }
        return true;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, unordered_set<string>> adj;
        unordered_set<string> distinct(wordList.begin(), wordList.end());

        if(!distinct.count(endWord)) return 0;
        distinct.insert(beginWord);

        for(auto word_it = distinct.begin(); word_it != distinct.end(); word_it++) {
            for(auto match_word_it = next(word_it); match_word_it != distinct.end(); match_word_it++) {

                string word = *word_it;
                string match_word = *match_word_it;

                if(differByOneLetter(word, match_word)) {
                    adj[word].insert(match_word);
                    adj[match_word].insert(word);
                }
            }
        }

        queue<pair<string, int>> to_do({{beginWord, 1}});
        unordered_set<string> visited{{beginWord}};
        unordered_map<string, string> parent;

        string curr_word;
        int curr_dist;
        while(!to_do.empty()) {
            pair<string, int> curr = to_do.front();
            tie(curr_word, curr_dist) = curr;

            to_do.pop();
            if(curr_word == endWord) {
                string temp = endWord;
                // while(temp != beginWord) {
                //     cout << temp << endl;
                //     temp = parent[temp];
                // }
                return curr_dist;
            }

            unordered_set<string> neighbors = adj[curr_word];
            for(auto neighbor: neighbors) {
                if(visited.count(neighbor)) continue;
                to_do.emplace(neighbor, curr_dist + 1);
                parent[neighbor] = curr_word;
                visited.insert(neighbor);
            }
            
        }

        return 0;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
128. Longest Consecutive Sequence
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

/*
    Submission Date: 2017-06-29
    Runtime: 12 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int res = 0;
        for(auto item: s) {
            int range = 1;
            int temp = item - 1;
            while(s.count(temp)) {
                s.erase(temp);
                temp--;
                range++;
            }
            
            temp = item + 1;
            while(s.count(temp)) {
                s.erase(temp);
                temp++;
                range++;
            }

            res = max(res, range);
        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
129. Sum Root to Leaf Numbers
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

/*
    Submission Date: 2017-07-14
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumNumbers(TreeNode* root, int current_path) {
        if(root == NULL) {
            return 0;
        } 

        int curr_sum = current_path*10 + root -> val;

        if(root -> left == NULL && root -> right == NULL) {
            return curr_sum;
        }

        int left = sumNumbers(root -> left, curr_sum);
        int right = sumNumbers(root -> right, curr_sum);
        return left + right;
    }

    int sumNumbers(TreeNode* root) {
        return sumNumbers(root, 0);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
130. Surrounded Regions
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X

/*
    Submission Date: 2017-07-14
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    void bfs(vector<vector<char>>& board, int i, int j, int N, int M) {
        queue<pair<int, int>> q;
        q.emplace(i, j);

        int dk[4] = {0, -1, 1, 0};
        int dl[4] = {-1, 0, 0, 1};
        while(!q.empty()) {
            pair<int, int>& p = q.front();

            tie(i, j) = p;
            q.pop();

            if(board[i][j] != 'O') continue;
            board[i][j] = 'L';

            int new_i, new_j;
            for(int k = 0; k < 4; k++) {
                new_i = i + dk[k];
                new_j = j + dl[k];

                if(0 <= new_i && new_i < N && 0 <= new_j && new_j < M) {
                    if(board[new_i][new_j] != 'O') continue;
                    q.emplace(new_i, new_j);
                    // dfs(board, new_i, new_j, N, M);
                }
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        int N = board.size();

        if(N == 0) return;

        int M = board.front().size();
        

        for(int i = 0; i < N; i++) {
            if(board[i][0] == 'O') bfs(board, i, 0, N, M);
            if(board[i][M-1] == 'O') bfs(board, i, M-1, N, M);
        }

        for(int i = 0; i < M; i++) {
            if(board[0][i] == 'O') bfs(board, 0, i, N, M);
            if(board[N-1][i] == 'O') bfs(board, N-1, i, N, M);
        }

        unordered_map<char, char> m{{'X', 'X'}, {'L', 'O'}, {'O', 'X'}};
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                board[i][j] = m[board[i][j]];
            }
        }
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
131. Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

/*
    Submission Date: 2017-07-24
    Runtime: 12 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void generate(vector<int>& dp, string str, vector<string>& temp, int index, vector<vector<string>>& res) {
        if(index == str.size() - 1) {
            const char kNullChar = '\0';
            vector<string> temp_copy(temp.size());
            transform(temp.begin(), temp.end(), temp_copy.begin(), [&kNullChar](string s){
                s.erase(remove_if(s.begin(), s.end(), [&kNullChar](const char& c){ return c == kNullChar; }), s.end());
                return s;
            });
            res.push_back(temp_copy);
            return;
        }
        for(int i = index + 1; i < str.size(); i++) {
            if(dp[i] > 0) {
                if(i - dp[i] <= index) { // the palindrome extends to or past our current word so we can take a substring of it
                    int end = i - index;
                    string sub = str.substr(index, 2*end); // includes null at front but not back
                    temp.push_back(sub);
                    // index + sub.size() is the null behind sub
                    generate(dp, str, temp, index + sub.size(), res); 
                    temp.pop_back();
                }
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;

        const char kNullChar = '\0';

        string str = string(1, kNullChar);
        for(auto c: s) str += string(1,c) + kNullChar;

        int N = str.size();
        vector<int> dp(N, 0);
        int right = 0;
        int center = 0;

        for(int i = 1; i < N; i++) {
            int mirr = 2*center - i;
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            int left = i - (1 + dp[i]);
            int right = i + (1 + dp[i]);

            while(left >= 0 && right < N && str[left] == str[right]) {
                left--;
                right++;
                dp[i]++;
            }

            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }

        vector<string> temp;
        generate(dp, str, temp, 0, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
132. Palindrome Partitioning II
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.

/*
    Submission Date: 2017-06-29
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int minCut(string s) {
        int len = s.size();
        int dp[len + 1];
        for(int i = 0; i <= len; i++) dp[i] = i-1;

        for(int i = 0; i < len; i++) {
            for(int j = 0; j < len; j++) {
                if(i + j > len || i - j < 0) break;
                if(s[i+j] != s[i-j]) break;
                dp[i + j + 1] = min(1 + dp[i-j], dp[i + j + 1]);
            }

            for(int j = 0; j < len; j++) {
                if(i + j + 1 > len || i - j < 0) break;
                if(s[i+j+1] != s[i-j]) break;
                if(i + j + 2 > len) break;
                dp[i + j + 2] = min(1 + dp[i-j], dp[i + j + 2]);
            }
        }

        return dp[len];
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
133. Clone Graph
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/

/*
    Submission Date: 2017-07-18
    Runtime: 33 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
    unordered_set<UndirectedGraphNode*> visited;
public:
    void cloneGraph(UndirectedGraphNode* head, UndirectedGraphNode *node) {
        visited.insert(node);
        for(auto neighbor: node -> neighbors) {
            if(!m.count(neighbor)) {
                m[neighbor] = new UndirectedGraphNode(neighbor -> label);
            }

            head -> neighbors.push_back(m[neighbor]);
            if(!visited.count(neighbor)) {
                cloneGraph(m[neighbor], neighbor);
            }
        }
    }

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;

        UndirectedGraphNode* head = new UndirectedGraphNode(node -> label);
        m[node] = head;
        cloneGraph(head, node);
        return head;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
134. Gas Station
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next 
station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.

/*
    Submission Date: 2017-06-29
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int N = gas.size();
        int start = 0;
        int curr_gas = 0;
        int need_to_overcome = 0;
        for(int i = 0; i < N; i++) {
            curr_gas += gas[i] - cost[i];
            if(curr_gas < 0) {
                need_to_overcome -= curr_gas;
                start = i + 1;
                curr_gas = 0;
            }
        }
        return (curr_gas >= need_to_overcome) ? start : -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
135. Candy
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

/*
    Submission Date: 2017-07-21
    Runtime: 29 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int candy(const vector<int>& ratings) {
        int N = ratings.size();

        vector<int> forward(N, 1);
        vector<int> backward(N, 1);

        for(int i = 1; i < N; i++) {
            if(ratings[i] > ratings[i-1]) {
                forward[i] = forward[i-1] + 1;
            }
        }

        for(int i = N - 2; i >= 0; i--) {
            if(ratings[i] > ratings[i+1]) {
                backward[i] = backward[i+1] + 1;
            }
        }

        int count = 0;
        for(int i = 0; i < N; i++) {
            count += max(forward[i], backward[i]);
        }

        return count;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
136. Single Number
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

/*
    Submission Date: 2017-06-29
    Runtime: 19 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(auto e: nums) res ^= e;
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
138. Copy List with Random Pointer
A linked list is given such that each node contains an additional random pointer 
which could point to any node in the list or null.

Return a deep copy of the list.

/*
    Submission Date: 2017-07-16
    Runtime: 46 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head == NULL) return NULL;

        RandomListNode* curr = head;

        // create duplicate node after the original one
        while(curr) {
            RandomListNode* next = curr -> next;
            curr -> next = new RandomListNode(curr -> label);
            curr -> next -> next = next;
            curr = next;
        }

        // set all the random ones as the original node's random is adjacent
        // to the duplicate random node
        curr = head;
        while(curr) {
            RandomListNode* random = curr -> random;
            curr -> next -> random = (random == NULL) ? NULL : random -> next;
            curr = curr -> next -> next;
        }
    
        // remove originals
        RandomListNode* original_head = new RandomListNode(INT_MIN);
        RandomListNode* original_cur = original_head;
        
        RandomListNode* copy_head = new RandomListNode(INT_MIN);
        RandomListNode* copy_curr = copy_head;
        
        curr = head;
        while(curr) {
            original_cur -> next = curr;
            original_cur = original_cur -> next;
            
            copy_curr -> next = curr -> next;
            copy_curr = copy_curr -> next;
            
            curr = curr -> next -> next;
        }
        
        original_cur -> next = NULL;
        head = original_head -> next;
        delete original_head;
        
        copy_curr -> next = NULL;
        RandomListNode* root = copy_head -> next;
        delete copy_head;
        
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
139. Word Break
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, 
determine if s can be segmented into a space-separated sequence of one or more dictionary words. 
You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

/*
    Submission Date: 2017-07-09
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<string, bool> memo;
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if(s.empty()) return true;
        
        if(memo.count(s)) return memo[s];
        
        for(string word: wordDict) {
            int word_len = word.size();
            string prefix = s.substr(0, word_len);
            if(prefix == word) {
                // we can take this word
                if(wordBreak(s.substr(word_len), wordDict)) {
                    return memo[s] = true;
                }
            }
        }
        
        return memo[s] = false;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
140. Word Break II
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces 
in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary 
does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). 
Please reload the code definition to get the latest changes.

/*
    Submission Date: 2017-07-20
    Runtime: 3 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

class Solution {
public:
    void convertLenToStr(int i, string s, string curr, vector<vector<int>>& dp, vector<string>& res) {
        if(i == s.size()) {
            res.push_back(curr);
            return;
        }

        for(const int word_size: dp[i]) {
            string word = s.substr(i, word_size);
            string new_curr = curr.empty() ? word : curr + " " + word;
            convertLenToStr(i + word_size, s, new_curr, dp, res);
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int N = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        set<int> word_sizes;

        for(const string word: dict) 
            word_sizes.insert(word.size());

        vector<vector<int>> dp(N + 1, vector<int>{});
        dp[N].push_back(INT_MAX);

        for(int j = N; j >= 0; j--) {
            if(dp[j].empty()) continue;
            for(const int word_size: word_sizes) {
                if(j - word_size < 0) break;
                string word = s.substr(j - word_size, word_size);
                // we store at dp[j-word_size] the word_size if it is a valid word and it ends at a valid index 
                // meaning dp[j] isn't empty
                if(dict.count(word)) {
                    dp[j - word_size].push_back(word_size);
                }
            }
        }

        vector<string> res;
        convertLenToStr(0, s, "", dp, res);
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
141. Linked List Cycle
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow, *fast;
        slow = fast = head;
        while(fast && fast -> next) {
            slow = slow -> next;
            fast = fast -> next -> next;
            if(slow == fast) return true;
        }

        return false;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
143. Reorder List
Given a singly linked list L: L0?L1?…?Ln-1?Ln,
reorder it to: L0?Ln?L1?Ln-1?L2?Ln-2?…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.

/*
    Submission Date: 2017-07-18
    Runtime: 59 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        // find midpoint
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* last_slow = slow;
        while(fast && fast -> next) {
            last_slow = slow;
            slow = slow -> next;
            fast = fast -> next -> next;
        }

        if(slow == fast) return;

        last_slow -> next = NULL;

        // reverse the second half
        ListNode* prev = NULL;
        ListNode* curr = slow;
        ListNode* new_curr = curr -> next;
        while(curr) {
            curr -> next = prev;
            prev = curr;
            curr = new_curr;
            if(new_curr) new_curr = new_curr -> next;
        }

        // merge first half and second half
        curr = prev;
        ListNode* new_head = NULL;
        new_curr = NULL;
        while(head) {
            new_head = head -> next;
            new_curr = curr -> next;

            head -> next = curr;
            if(new_head) {
                curr -> next = new_head;
            } else if(new_curr) {
                curr -> next = new_curr;
            }

            head = new_head;
            curr = new_curr;
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
144. Binary Tree Preorder Traversal
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?

/*
    Submission Date: 2017-07-21
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> st{{root}};
        vector<int> res;
        while(!st.empty()) {
            TreeNode* top = st.top();
            st.pop();

            if(top == NULL) continue;
            res.push_back(top -> val);
            st.push(top -> right);
            st.push(top -> left);
        }

        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
146. LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the 
following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, 
otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache 
reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache(2);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4

/*
    Submission Date: 2017-07-14
    Runtime: 95 ms
    Difficulty: HARD
*/

#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

struct LRUElement {
    int key, value;
    LRUElement(int _key, int _value): key(_key), value(_value) {}
};

class LRUCache {
    list<LRUElement> linked_list_; // back is just inserted or used recently
    unordered_map<int, list<LRUElement>::iterator> hash_table_;
    int capacity_;

    void moveToBack(int key) {
        auto it = hash_table_[key];

        LRUElement temp = *it;
        linked_list_.erase(it);
        linked_list_.push_back(temp);

        hash_table_[key] = --linked_list_.end();
    }

public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }
    
    int get(int key) {
        if(!hash_table_.count(key)) return -1;

        // update in the linked_list
        moveToBack(key);

        // for(auto e: linked_list_) cout << e.value << endl;
        return linked_list_.back().value;
    }
    
    void put(int key, int value) {
        if(hash_table_.count(key)) {
            moveToBack(key);
            linked_list_.back().value = value;
        } else {
            if(linked_list_.size() == capacity_) {
                hash_table_.erase(linked_list_.begin() -> key);
                linked_list_.erase(linked_list_.begin());
            }
            linked_list_.emplace_back(key, value);
            hash_table_[key] = --linked_list_.end();
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
147. Insertion Sort List
Sort a linked list using insertion sort.

/*
    Submission Date: 2017-07-14
    Runtime: 59 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* dummy = new ListNode(INT_MIN);

        ListNode* curr = head;
        ListNode* insert = NULL;
        while(curr) {
            insert = dummy;
            while(insert -> next && insert -> next -> val < curr -> val) {
                insert = insert -> next;
            }
            
            ListNode* new_curr = curr -> next;
            ListNode* next = insert -> next;
            insert -> next = curr;
            curr -> next = next;
            curr = new_curr;
        }

        head = dummy -> next;
        dummy -> next = NULL;
        delete dummy;
        return head;

    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
148. Sort List
Sort a linked list in O(n log n) time using constant space complexity.

/*
    Submission Date: 2017-07-21
    Runtime: 52 ms
    Difficulty: MEDIUM
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head == NULL) return NULL;
        if(head -> next == NULL) return head;

        ListNode* slow, *fast, *last;
        slow = fast = head;
        while(fast && fast -> next) {
            last = slow;
            slow = slow -> next;
            fast = fast -> next -> next;
        }

        ListNode* head1 = head;
        ListNode* head2 = last -> next;
        last -> next = NULL;

        ListNode* curr1 = sortList(head1);
        ListNode* curr2 = sortList(head2);

        ListNode* merged = new ListNode(INT_MIN);
        ListNode* merged_head = merged;

        while(curr1 && curr2) {
            if(curr1 -> val < curr2 -> val) {
                merged -> next = curr1;
                merged = merged -> next;
                curr1 = curr1 -> next;
            } else {
                merged -> next = curr2;
                merged = merged -> next;
                curr2 = curr2 -> next;
            }
        }

        while(curr1) {
            merged -> next = curr1;
            merged = merged -> next;
            curr1 = curr1 -> next;
        }

        while(curr2) {
            merged -> next = curr2;
            merged = merged -> next;
            curr2 = curr2 -> next;
        }

        merged -> next = NULL;
        merged = merged_head;
        merged_head = merged_head -> next;
        delete merged;

        return merged_head;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
149. Max Points on a Line
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

/*
    Submission Date: 2017-07-18
    Runtime: 9 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int gcd(int a, int b) {
        if(b == 0) return a;
        return gcd(b, a%b);
    }

    int maxPoints(vector<Point>& points) {
        int N = points.size();

        int max_points = 0;

        for(int i = 0; i < N; i++) {
            int same_count = 0;
            map<tuple<int, int, int>, int> m;

            for(int j = i; j < N; j++) {
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    same_count++;
                    continue;
                }

                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;

                int gcd_dx_dy = gcd(dx, dy);
                int rem = dx*points[i].y - dy*points[i].x;

                tuple<int, int, int> tp {dx/gcd_dx_dy, dy/gcd_dx_dy, rem/gcd_dx_dy};
                m[tp]++;
            }

            for(auto kv: m) max_points = max(kv.second + same_count, max_points);
            max_points = max(max_points, same_count);
        }

        return max_points;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
151. Reverse Words in a String
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.

click to show clarification.

Clarification:
What constitutes a word?
A sequence of non-space characters constitutes a word.
Could the input string contain leading or trailing spaces?
Yes. However, your reversed string should not contain leading or trailing spaces.
How about multiple spaces between two words?
Reduce them to a single space in the reversed string.

/*
    Submission Date: 2017-07-24
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        int write_idx = 0;
        int N = s.size();

        for(int i = 0; i < N;) {
            // finding first non space char
            while(i < N && isspace(s[i])) {
                i++;
            }

            if(i < N) {
                // add space if needed between words
                if(write_idx != 0) {
                    s[write_idx++] = ' ';
                }

                // write all non space char to write_idx 
                while(i < N && !isspace(s[i])) {
                    s[write_idx++] = s[i++];
                }

            }
        }

        s.resize(write_idx);
        N = s.size();

        reverse(s.begin(), s.end());
        for(int i = 0; i < N; i++) {
            int start = i;
            while(i < N && !isspace(s[i])) {
                i++;
            }
            reverse(s.begin() + start, s.begin() + i);
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
152. Maximum Product Subarray
Find the contiguous subarray within an array (containing at least one number) which has 
the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

/*
    Submission Date: 2017-07-09
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int N = nums.size();
        
        if(N == 0) return 0;
        
        int min_dp[N];
        int max_dp[N];
        
        min_dp[0] = max_dp[0] = nums.front();
        
        int res = max_dp[0];
        
        for(int i = 1; i < N; i++) {
            min_dp[i] = min(min(min_dp[i-1]*nums[i], max_dp[i-1]*nums[i]), nums[i]);
            max_dp[i] = max(max(min_dp[i-1]*nums[i], max_dp[i-1]*nums[i]), nums[i]);
            res = max(res, max_dp[i]);
        }
        
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;

        int min_item = INT_MAX;
        while(low <= high) {
            int mid = (low + high) >> 1;
            if(nums[low] <= nums[mid]) { // this region is sorted
                min_item = min(min_item, nums[low]);
                low = mid + 1;
            } else {
                min_item = min(min_item, nums[mid]);
                high = mid - 1;
            }
        }

        return min_item;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

/*
    Submission Date: 2017-07-21
    Runtime: 29 ms
    Difficulty: EASY
*/

#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

struct MinStackNode {
  int val;
  MinStackNode* next; 
  int min_so_far;
};

class MinStack {
  MinStackNode * top_node;
  
public:
    MinStack() {
      top_node = NULL;      
    }
    
    void push(int x) {
        MinStackNode* new_top = new MinStackNode();
        new_top -> val = x;
        new_top -> next = top_node; 
            
        if (top_node == NULL ) {
            new_top -> min_so_far = x;
        } else if(top_node -> min_so_far <= x){
            new_top -> min_so_far = top_node -> min_so_far;
        } else{
            new_top -> min_so_far = x;
        } 
        
        top_node = new_top;
    }
    
    void pop() {
        assert(top_node != NULL);
        MinStackNode* temp =  top_node;
        top_node = top_node -> next;
        delete temp;
    }
    
    int top() {
        assert(top_node != NULL);
        return top_node -> val;
    }
    
    int getMin() {
        return top_node -> min_so_far;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
160. Intersection of Two Linked Lists
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

/*
    Submission Date: 2017-07-26
    Runtime: 39 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int length(ListNode* head) {
        int count = 0;
        while(head) {
            head = head -> next;
            count++;
        }

        return count;
    }
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int length_A = length(headA);
        int length_B = length(headB);

        if(length_A > length_B) swap(headA, headB);

        int diff = abs(length_B - length_A);
        for(int i = 0; i < diff; i++) {
            headB = headB -> next;
        }

        while(headA && headB) {
            if(headA == headB) return headA;
            headA = headA -> next;
            headB = headB -> next;
        }

        return NULL;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
162. Find Peak Element
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int N = nums.size();
        int low = 0;
        int high = N-1;

        while(low <= high) {
            int mid = (low + high) >> 1;

            bool left_is_smaller = mid == 0 || nums[mid-1] < nums[mid];
            bool right_is_smaller = mid == N - 1 || nums[mid] > nums[mid+1];

            if(left_is_smaller && right_is_smaller) { // peak
                return mid;
            } else if(left_is_smaller && !right_is_smaller) { // peak on right
                low = mid + 1;
            } else if(!left_is_smaller && right_is_smaller) { // peak on left
                high = mid - 1;
            } else { // both sides have peak
                low = mid + 1;
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
166. Fraction to Recurring Decimal
Given two integers representing the numerator and denominator of a fraction, 
return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".

/*
    Submission Date: 2017-06-11
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string fractionToDecimal(long long numerator, long long denominator) {
        if(numerator == 0) return "0";
        
        unordered_map<int, int> m;
        string sign = ((numerator < 0) ^ (denominator < 0)) ? "-" : "";
        
        string res = "";
        
        numerator = abs(numerator);
        denominator = abs(denominator);
        int num_of_digits = numerator < denominator ? 1: floor(log10(numerator/denominator)) + 1;
        
        while(numerator) {
            if(m.count(numerator)) {
                res = res.substr(0, m[numerator]) + "(" + res.substr(m[numerator]) + ")";
                break;
            }
            m[numerator] = res.size();
            res += to_string(numerator/denominator);
            numerator %= denominator;
            numerator *= 10;
        }
        
        string rem = res.substr(num_of_digits);
        res = sign + res.substr(0, num_of_digits) + (rem.size() ? "." : "") + rem;
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
167. Two Sum II - Input array is sorted
Given an array of integers that is already sorted in ascending order, find two numbers such that they 
add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where 
index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not 
zero-based.

You may assume that each input would have exactly one solution and you may not use the same element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int N = numbers.size();
        int low = 0;
        int high = N-1;
        while(low < high) {
            int curr_sum = numbers[low] + numbers[high];
            if(curr_sum == target) {
                return {low + 1, high + 1};
            } else if(curr_sum < target) {
                low++;
            } else {
                high--;
            }
        }   
        return {};
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
168. Excel Sheet Column Title
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB 

/*
    Submission Date: 2017-07-26
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        return n == 0 ? "" : convertToTitle((n-1)/26) + string(1, ((n-1) % 26) + 'A');
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
169. Majority Element
Given an array of size n, find the majority element. The majority element is the element that appears more 
than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.
/*
    Submission Date: 2017-07-21
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> value_to_freq;
        int max_freq_value = nums.front();
        for(auto num: nums) {
            value_to_freq[num]++;
            if(value_to_freq[num] > value_to_freq[max_freq_value])
                max_freq_value = num;
        }
        return max_freq_value;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
171. Excel Sheet Column Number
Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int titleToNumber(string s) {
        return s == "" ? 0 : titleToNumber(s.substr(0, s.size() - 1))*26 + (s[s.size()-1] - 'A' + 1);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
172. Factorial Trailing Zeroes
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.

/*
    Submission Date: 2017-07-24
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trailingZeroes(int n) {
        return n == 0 ? 0 : n/5 + trailingZeroes(n/5);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
173. Binary Search Tree Iterator
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.

/*
    Submission Date: 2017-07-26
    Runtime: 22 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
    vector<TreeNode*> path_;
public:
    BSTIterator(TreeNode *root) {
        TreeNode* curr = root;
        while(curr) {
            path_.push_back(curr);
            curr = curr -> left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !path_.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* curr = path_.back();
        path_.pop_back();

        int ret_val = curr -> val;

        curr = curr -> right;
        while(curr) {
            path_.push_back(curr);
            curr = curr -> left;
        }

        return ret_val;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
174. Dungeon Game
The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. 
The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned 
in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point 
drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these 
rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health 
(positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or 
downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows 
the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)  -3  3
-5  -10 1
10  30  -5 (P)

Notes:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room 
where the princess is imprisoned.

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int rows = dungeon.size();
        if(rows == 0) return 0;

        int cols = dungeon.front().size();
        vector<vector<int>> hp(rows + 1, vector<int>(cols + 1, INT_MAX));
        hp[rows][cols - 1] = 1;
        hp[rows - 1][cols] = 1;
        
        for(int i = rows-1; i >= 0; i--) {
            for(int j = cols-1; j >= 0; j--) {
                hp[i][j] = max(1, min(hp[i+1][j], hp[i][j+1]) - dungeon[i][j]);
            }
        }
        
        return hp[0][0];
    }
};


int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
179. Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.

For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.

Note: The result may be very large, so you need to return a string instead of an integer.

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    string concat(const vector<string>& nums_str) {
        return accumulate(nums_str.begin(), nums_str.end(), string(), [](const string& memo, const string& el){ return memo + el; });
    }

    string largestNumber(vector<int>& nums) {
        if(nums.empty()) return "0";
        int N = nums.size();
        vector<string> nums_str(N);
        transform(nums.begin(), nums.end(), nums_str.begin(), [](const int& num){ return to_string(num); });
        sort(nums_str.begin(), nums_str.end(), [](const string& lhs, const string& rhs){
            return lhs + rhs > rhs + lhs;        
        });

        if(nums_str.front()[0] == '0') return "0";
        return concat(nums_str);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
187. Repeated DNA Sequences
All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". 
When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

For example,

Given s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT",

Return:
["AAAAACCCCC", "CCCCCAAAAA"].

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> freq;
        for(int i = 0; i <= (int)s.size() - 10; i++) {
            string seq = s.substr(i, 10);
            freq[seq]++;
        }

        vector<string> res;
        for(auto kv: freq) {
            if(kv.second > 1) {
                res.push_back(kv.first);
            }
        }
        return res;
    }
};


int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
189. Rotate Array
Rotate an array of n elements to the right by k steps.

For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].

Note:
Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.

/*
    Submission Date: 2017-07-26
    Runtime: 19 ms
    Difficulty: EASY
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int start, int end, int k) {
        if(start >= end) return;
        int N = end - start;

        k %= N;
        if(k == 0) return;

        for(int i = 0; i < k; i++) {
            swap(nums[start + i], nums[end - k + i]);
        }

        rotate(nums, start + k, end, k);
    }
    void rotate2(vector<int>& nums, int k) {
        rotate(nums, 0, nums.size(), k);
    }

    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
190. Reverse Bits
Reverse bits of a given 32 bits unsigned integer.

For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 
(represented in binary as 00111001011110000010100101000000).

Follow up:
If this function is called many times, how would you optimize it?

/*
    Submission Date: 2017-07-26
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0; i < 32; i++) {
            res |= n % 2;
            n /= 2;
            if(i != 31) res *= 2;
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
191. Number of 1 Bits
Write a function that takes an unsigned integer and returns the number of ’1' bits it has 
(also known as the Hamming weight).

For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, 
so the function should return 3.

/*
    Submission Date: 2017-07-25
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            n = n & (n-1);
            count++;
        }
        return count;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
198. House Robber
You are a professional robber planning to rob houses along a street. Each house has a certain amount of 
money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have 
security system connected and it will automatically contact the police if two adjacent houses were broken 
into on the same night.

Given a list of non-negative integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.

/*
    Submission Date: 2017-08-01
    Runtime: 0 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int N = nums.size();
        vector<int> dp(N);
        dp[N-1] = nums[N-1];

        for(int i = N - 2; i >= 0; i--) {
            dp[i] = max(dp[i + 1], nums[i] + (i + 2 < N ? dp[i+2] : 0));
        }

        return dp[0];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes 
you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

/*
    Submission Date: 2017-07-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        rightSideView(root, res, 0);
        return res;
    }
    
    void rightSideView(TreeNode* root, vector<int>& res, int depth) {
        if(root == NULL) return;
        if(res.size() <= depth) {
            res.push_back(root -> val);
        }
        
        rightSideView(root -> right, res, depth + 1);
        rightSideView(root -> left, res, depth + 1);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
201. Bitwise AND of Numbers Range
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, 
inclusive.

For example, given the range [5, 7], you should return 4.

/*
    Submission Date: 2017-07-25
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int res = 0;
        for(int i = 30; i >= 0; i--) {
            int shift = 1 << i;
            if((shift & m) == (shift & n)) {
                res |= shift & m;
            } else {
                break;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.rangeBitwiseAnd(5, 7) << endl;
    cout << s.rangeBitwiseAnd(5, 5) << endl;
    cout << s.rangeBitwiseAnd(INT_MAX, INT_MAX-1) << endl;
    cout << s.rangeBitwiseAnd(0, 0) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
202. Happy Number
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the 
number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), 
or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1

/*
    Submission Date: 2017-07-26
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_set>
#include <cmath>

using namespace std;

class Solution {
    unordered_set<int> seen;
public:
    bool isHappy(int n) {
        if(n == 1) return true;
        if(n == 0 || seen.count(n)) return false;
        seen.insert(n);
        int sum = 0;
        while(n) {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        return isHappy(sum);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
203. Remove Linked List Elements
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

/*
    Submission Date: 2017-07-26
    Runtime: 26 ms
    Difficulty: EASY
*/

#include <iostream>
#include <climits>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy_head = new ListNode(INT_MIN);
        dummy_head -> next = head;

        ListNode* curr = dummy_head;
        while(curr) {
            ListNode* next = curr -> next;
            while(next && next -> val == val) {
                ListNode* to_delete = next;
                next = next -> next;
                delete to_delete;
            }

            curr -> next = next;
            curr = next;
        }

        ListNode* to_delete = dummy_head;
        head = dummy_head -> next;
        delete to_delete;
        return head;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
205. Isomorphic Strings
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of 
characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

/*
    Submission Date: 2017-08-01
    Runtime: 13 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int N = s.size();
        unordered_map<char, char> hash_map;
        unordered_set<char> mapped;
        for(int i = 0; i < N; i++) {
            if(hash_map.count(s[i])) {
                if(t[i] != hash_map[s[i]]) {
                    return false;
                }
            } else {
                if(mapped.count(t[i])) return false;
                hash_map[s[i]] = t[i];
                mapped.insert(t[i]);
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
206. Reverse Linked List
Reverse a singly linked list.

/*
    Submission Date: 2017-07-26
    Runtime: 9 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;

        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = head -> next;

        while(curr != NULL) {
            curr -> next = prev;
            prev = curr;
            curr = next;
            if(next != NULL) next = next -> next;
        }

        return prev;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
209. Minimum Size Subarray Sum
Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which 
the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

/*
    Submission Date: 2017-07-26
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;

        int N = nums.size();
        int i = 0;
        int curr_sum = 0;
        int start = 0;
        int min_size = INT_MAX;
        while(i < N) {
            curr_sum += nums[i++];
            while(curr_sum >= s) {
                min_size = min(min_size, i - start);
                curr_sum -= nums[start++];
            }
        }
        return min_size == INT_MAX ? 0: min_size;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
210. Course Schedule II
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a 
pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish 
all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, 
return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is 
[0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 
2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is
[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is 
represented.
You may assume that there are no duplicate edges in the input prerequisites.

/*
    Submission Date: 2017-07-26
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

class Solution {
public:
    bool TopologicalSortUtil(const int vertex, const vector<vector<int>>& vertex_to_edges, unordered_set<int>& visited, 
        unordered_set<int>& expanding, stack<int>& st) {

        if(expanding.count(vertex)) {
            return true;
        }

        expanding.insert(vertex);
        
        for(auto neighbor: vertex_to_edges[vertex]) {
            if(visited.count(neighbor)) continue;
            bool has_cycle = TopologicalSortUtil(neighbor, vertex_to_edges, visited, expanding, st);
            if(has_cycle) return true;
        }

        visited.insert(vertex);
        expanding.erase(vertex);

        st.push(vertex);
        return false;
    }

    vector<int> TopologicalSort(const int numCourses, const vector<vector<int>>& vertex_to_edges) {
        unordered_set<int> visited;
        unordered_set<int> expanding;
        stack<int> st;

        bool has_cycle = false;
        for(int vertex = 0; vertex < numCourses; vertex++) {
            if(visited.count(vertex)) continue;
            has_cycle = TopologicalSortUtil(vertex, vertex_to_edges, visited, expanding, st);
            if(has_cycle) break;
        }

        vector<int> res;
        if(!has_cycle) {
            while(!st.empty()) {
                res.push_back(st.top());
                st.pop();
            }
        }

        return res;
    }
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> vertex_to_edges(numCourses, vector<int>{});

        for(auto prereq: prerequisites) {
            vertex_to_edges[prereq.second].push_back(prereq.first);
        }

        return TopologicalSort(numCourses, vertex_to_edges);
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
212. Word Search II
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those 
horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of 
data structure could answer such query efficiently?

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

struct TrieNode {
    bool is_leaf;
    TrieNode* children[26];
    TrieNode() {
        is_leaf = false;
        for(int i = 0; i < 26; i++) children[i] = NULL;
    }
};

class Trie {
    TrieNode* root_;
public:
    Trie() {
        root_ = new TrieNode();
    }

    TrieNode* insert(const vector<string>& words) {
        for(auto word: words) insert(word);
        return root_;
    }

    void insert(string word) {
        TrieNode* curr = root_;
        for(int i = 0; i < word.size(); i++) {
            int letter_index = word[i] - 'a';
            if(curr -> children[letter_index] == NULL) {
                curr -> children[letter_index] = new TrieNode();
            }
            curr = curr -> children[letter_index];
        }
        curr -> is_leaf = true;
    }
};

class Solution {
    vector<int> dx{-1,1,0,0};
    vector<int> dy{0,0,-1,1};
public:
    void check(const vector<vector<char>>& board, const TrieNode* node, string curr, int row, int col, int rows, int cols, 
        unordered_set<string>& res, set<pair<int,int>>& visited) {

        if(node -> is_leaf) res.insert(curr);

        visited.insert({row, col});

        for(int i = 0; i < 4; i++) {
            int new_row = row + dy[i];        
            int new_col = col + dx[i];
            if(0 <= new_row && new_row < rows && 0 <= new_col && new_col < cols) {
                if(visited.count({new_row, new_col})) continue; // visited already

                char board_char = board[new_row][new_col];
                if(node -> children[board_char - 'a'] == NULL) continue; // no words to match

                check(board, node -> children[board_char - 'a'], curr + string(1, board_char), new_row, new_col, rows, cols, res, visited);
            }      
        }

        visited.erase({row, col});
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if(board.empty()) return {};

        Trie trie;
        TrieNode* root = trie.insert(words);
        int rows = board.size();
        int cols = board.front().size();

        unordered_set<string> res;
        set<pair<int,int>> visited;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                char board_char = board[i][j];
                if(root -> children[board_char - 'a'] != NULL) {
                    check(board, root -> children[board_char - 'a'], string(1, board_char), i, j, rows, cols, res, visited);
                }
            }
        }

        vector<string> ret(res.begin(), res.end());
        return ret;
    }
};
int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
213. House Robber II
After robbing those houses on that street, the thief has found himself a new place for his thievery 
so that he will not get too much attention. This time, all houses at this place are arranged in a circle. 
That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses 
remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the 
maximum amount of money you can rob tonight without alerting the police.

/*
    Submission Date: 2017-08-01
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size();

        if(N == 0) return 0;
        if(N == 1) return nums.front();

        vector<int> dp(N);

        int res = 0;
        rob(nums, N, dp);
        res = max(res, dp[1]);
        rob(nums, N-1, dp);
        res = max(res, dp[0]);
        return res;
    }
    
    int rob(vector<int>& nums, int N, vector<int>& dp) {
        dp[N-1] = nums[N-1];

        for(int i = N - 2; i >= 0; i--) {
            dp[i] = max(dp[i + 1], nums[i] + (i + 2 < N ? dp[i+2] : 0));
        }

        return dp[0];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
214. Shortest Palindrome
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. 
Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".

/*
    Submission Date: 2017-07-23
    Runtime: 56 ms
    Difficulty: HARD
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    string Manacher(string s) {
        const char kNullChar = '\0';
        string str = string(1, kNullChar);

        for(auto c: s) str += string(1, c) + kNullChar;

        string max_str = "";
        int len = str.size();
        int right = 0;
        int center = 0;
        vector<int> dp(len, 0);
        
        int start_right = -1;
        for(int i = 1; i < len; i++) {
            int mirr = 2*center - i;

            // i is within right so can take the minimum of the mirror or distance from right
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            // keep expanding around i while it is the same and increment P[i]
            int left_index = i - (1 + dp[i]);
            int right_index = i + (1 + dp[i]);
            while(left_index != -1 && right_index != len && str[left_index] == str[right_index]) {
                left_index--;
                right_index++;
                dp[i]++;
            }
            
            if(left_index == -1) {
                string item = str.substr(left_index + 1, right_index - left_index - 2);           
                if(item.size() > max_str.size()) {
                    start_right = right_index;
                    max_str = item;
                }
            }

            // i goes beyond current right so it is the new center
            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }
        
        string suffix = "";
        max_str.erase(remove_if(max_str.begin(), max_str.end(), [&kNullChar](char c){ return c == kNullChar; }), max_str.end());
        for(int k = start_right; k < len; k++) {
            if(str[k] != kNullChar) {
                suffix += str[k];
            }
        }
        
        string reversed = suffix;
        reverse(reversed.begin(), reversed.end());
        return reversed + max_str + suffix;
    }

    string shortestPalindrome(string s) {
        return Manacher(s);
    }

    string shortestPalindrome2(string s) {
        int N = s.size();
        for(int i = N - 1; i >= 0; i--) {
            bool decision = true;
            for(int j = 0; j < (i + 1)/2; j++) {
                if(s[j] != s[i - j]) {
                    decision = false;
                    break;
                }
            }
            
            if(decision) {
                string suffix = "";
                for(int j = i + 1; j < N; j++) suffix += s[j];
                string reversed = suffix;
                reverse(reversed.begin(), reversed.end());
                return reversed + s.substr(0, i + 1) + suffix;
            }
        }
        return "";
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
215. Kth Largest Element in an Array
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, 
not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ? k ? array's length.

/*
    Submission Date: 2017-07-26
    Runtime: 9 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        MinHeap heap;
        for(int i = 0; i < nums.size(); i++) {
            heap.push(nums[i]);
            if(heap.size() > k) heap.pop();
        }

        return heap.top();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
226. Invert Binary Tree
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1

/*
    Submission Date: 2017-07-30
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == NULL) return NULL;
        TreeNode* left = invertTree(root -> left);
        TreeNode* right = invertTree(root -> right);
        root -> left = right;
        root -> right = left;
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
231. Power of Two
Given an integer, write a function to determine if it is a power of two.

/*
    Submission Date: 2017-07-30
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 ? (n & (n - 1)) == 0 : false;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
237. Delete Node in a Linked List
Write a function to delete a node (except the tail) in a singly linked list, given only access to 
that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list 
should become 1 -> 2 -> 4 after calling your function.

/*
    Submission Date: 2017-07-21
    Runtime: 16 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        node -> val = node -> next -> val;
        node -> next = node -> next -> next;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
238. Product of Array Except Self
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the 
product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

/*
    Submission Date: 2017-07-30
    Runtime: 68 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int N = nums.size();
        vector<int> dp(N);
        
        // forwards sweep
        int product = 1;
        for(int i = 0; i < N; i++) {
            dp[i] = product;
            product *= nums[i];
        }
        
        // backward sweep
        int back_product = 1;
        for(int i = N-1; i >= 0; i--) {
            dp[i] *= back_product;
            back_product *= nums[i];
        }
        
        return dp;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
525. Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
Note: The length of the given binary array will not exceed 50,000.

/*
    Submission Date: 2017-04-01
    Runtime: 162 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxLen = 0;
        int currentSum = 0;
        
        // unordered_map has key to currentSum and value to earliest index seen with that 
        // currentSum. the idea is that if the cumulative sum is the same then the sum of 
        // elements between those two indices is zero meaning equal number of 0's and 1's
        // so finding the smallest index with the same currentSum results in the largest subarray
        unordered_map<int, int> m = {{0, -1}};
    
        for(int i = 0, len = nums.size(); i < len; i++) {
            if(nums[i] == 0) {
                currentSum--;
            } else {
                currentSum++;
            }
            
            if(m.find(currentSum) == m.end()) {
                m[currentSum] = i;
            } else {
                maxLen = max(maxLen, i - m[currentSum]);
            }
        }
        
        return maxLen;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
536. Construct Binary Tree from String
You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, 
one or two pairs of parenthesis. The integer represents the root's value and a pair 
of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   

Note:
There will only be '(', ')', '-' and '0' ~ '9' in the input string.

/*
    Submission Date: 2017-03-11
    Runtime: 42 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* str2tree(string s) {
        int len = s.size();
        if(len == 0) return NULL;

        int firstBracketIndex = s.find('(');
        if(firstBracketIndex == string::npos) return new TreeNode(stoi(s));

        TreeNode* node = new TreeNode(stoi(s.substr(0, firstBracketIndex)));
        int count = 1;
        int offset = firstBracketIndex + 1;
        int i = offset;

        while(count != 0) {
            if(s[i] == ')') count--;
            else if(s[i] == '(') count++;
            i++;
        }

        string leftExpression = s.substr(offset, i - 1 - offset);
        string rightExpression = (i == len) ? "" : s.substr(i + 1, len - i - 2);

        node -> left = str2tree(leftExpression);
        node -> right = str2tree(rightExpression);

        return node;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
539. Minimum Time Difference
Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum 
minutes difference between any two time points in the list.

Example 1:
Input: ["23:59","00:00"]
Output: 1

Note:
The number of time points in the given list is at least 2 and won't exceed 20000.
The input time is legal and ranges from 00:00 to 23:59.

/*
    Submission Date: 2017-03-11
    Runtime: 43 ms
    Difficulty: MEDIUM
*/

using namespace std;
#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

class Solution {
public:
    // Assume time b is larger than a
    int getDifference(string a, string b) {
        int hours = stoi(b.substr(0,2)) - stoi(a.substr(0,2));
        int minutes = stoi(b.substr(3,2)) - stoi(a.substr(3,2));
        return hours*60 + minutes;
    }

    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int minDiff = INT_MAX;
        int len = timePoints.size();

        for(int i = 1; i < len; i++) {
            int diff = getDifference(timePoints[i-1], timePoints[i]);
            if(diff < minDiff) minDiff = diff;
        }

        string firstTimePoint = timePoints.front();
        int wrappedHour = stoi(firstTimePoint.substr(0,2)) + 24;
        string wrap = to_string(wrappedHour) + firstTimePoint.substr(2);
        int wrapDiff = getDifference(timePoints.back(), wrap);

        if(wrapDiff < minDiff) minDiff = wrapDiff;
        return minDiff;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
541. Reverse String II
Given a string and an integer k, you need to reverse the first k characters for every 2k 
characters counting from the start of the string. If there are less than k characters left, 
reverse all of them. If there are less than 2k but greater than or equal to k characters, 
then reverse the first k characters and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"

Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

/*
    Submission Date: 2017-03-11
    Runtime: 26 ms
    Difficulty: EASY
*/

using namespace std;
#include <iostream>

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
            reverse ^= true;
        }
        
        return finalStr;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
565. Array Nesting
A zero-indexed array A consisting of N different integers is given. The array contains 
all integers in the range [0, N - 1].

Sets S[K] for 0 <= K < N are defined as follows:

S[K] = { A[K], A[A[K]], A[A[A[K]]], ... }.

Sets S[K] are finite for each K and should NOT contain duplicates.

Write a function that given an array A consisting of N integers, return the size of 
the largest set S[K] for this array.

Example 1:
Input: A = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
Note:
N is an integer within the range [1, 20,000].
The elements of A are all distinct.
Each element of array A is an integer within the range [0, N-1].
/*
    Submission Date: 2017-05-29
    Runtime: 36 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int N = nums.size();
        vector<bool> mask(N, true);
        int max_set = 0;
        for(int i = 0; i < N; i++) {
            if(mask[i]) { // hasn't been processed
                int current = i;
                int current_set = 0;
                while(true) {
                    if(current >= N || !mask[current]) break;
                    mask[current] = false;
                    current = nums[current];
                    current_set++;
                }
                max_set = max(current_set, max_set);
            }
        }
        return max_set;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this 
subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array 
sorted in ascending order.

Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.

/*
    Submission Date: 2017-05-13
    Runtime: 52 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
            int N = nums.size();
            vector<int> cpy(N);
            copy(nums.begin(), nums.end(), cpy.begin());
            sort(nums.begin(), nums.end());

            int i;
            for(i = 0; i < N; i++) {
                if(nums[i] != cpy[i]) break;
            }

            int j;
            for(j = N-1; j >= 0; j--) {
                if(nums[j] != cpy[j]) break;
            }

        return max(j - i + 1, 0);
    }
};

int main() {
    Solution s;
    vector<int> v{2, 6, 4, 8, 10, 9, 15};
    cout << s.findUnsortedSubarray(v);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
582. Kill Process
Given n processes, each process has a unique PID (process id) and its PPID (parent process id).

Each process only has one parent process, but may have one or more children processes. This 
is just like a tree structure. Only one process has PPID that is 0, which means this process 
has no parent process. All the PIDs will be distinct positive integers.

We use two list of integers to represent a list of processes, where the first list contains 
PID for each process and the second list contains the corresponding PPID.

Now given the two lists, and a PID representing a process you want to kill, return a list 
of PIDs of processes that will be killed in the end. You should assume that when a process 
is killed, all its children processes will be killed. No order is required for the final answer.

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.

Note:
The given kill id is guaranteed to be one of the given PIDs.
n >= 1.
/*
    Submission Date: 2017-05-13
    Runtime: 166 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        unordered_map<int, vector<int>> m;
        int N = pid.size();
        for(int i = 0; i < N; i++) {
            int _ppid = ppid[i];
            int _pid = pid[i];

            if(m.find(_ppid) == m.end()) {
                m[_ppid] = {_pid};
            } else {
                m[_ppid].push_back(_pid);
            }
        }

        vector<int> result{kill};
        int i = 0;
        while(i < result.size()) {
            int current = result[i];
            if(m.find(current) != m.end()) { // non leaf
                vector<int> children = m[current];
                for(auto c: children) {
                    result.push_back(c);
                }
            }
            i++;
        }
        return result;
    }
};

int main() {
	Solution s;
    vector<int> pid{1, 3, 10, 5, 4, 1};
	vector<int> ppid{3, 0, 5, 3, 10, 5};
    int kill = 5;
    vector<int> t = s.killProcess(pid, ppid, kill);
	for(auto l: t) cout << l << " ";
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
583. Delete Operation for Two Strings
Given two words word1 and word2, find the minimum number of steps required to 
make word1 and word2 the same, where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
Note:
The length of given words won't exceed 500.
Characters in given words can only be lower-case letters.

/*
    Submission Date: 2017-05-13
    Runtime: 29 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int row = word2.size() + 1;
        int col = word1.size() + 1;
        int dp[501][501];
        for(int i = 0; i < row; i++) dp[i][0] = i;
        for(int i = 0; i < col; i++) dp[0][i] = i;

        for(int i = 1; i < row; i++) {
            for(int j = 1; j < col; j++) {
                if(word2[i - 1] == word1[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + 1;
                }
            }
        }
        
        return dp[row - 1][col - 1];
    }
};

int main() {
	Solution s;
    cout << s.minDistance("sea", "eat");
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
593. Valid Square
Given the coordinates of four points in 2D space, return whether the four points could construct a square.

The coordinate (x,y) of a point is represented by an integer array with two integers.

Example:
Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
Output: True
Note:

All the input integers are in the range [-10000, 10000].
A valid square has four equal sides with positive length and four equal angles (90-degree angles).
Input points have no order.
/*
    Submission Date: 2017-05-27
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    double eucl_sq(vector<int>& p1, vector<int>& p2) {
        return pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2);
    }

    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // distance squared
        vector<double> dist{eucl_sq(p1, p2), eucl_sq(p1, p3), eucl_sq(p1, p4), eucl_sq(p2, p3), eucl_sq(p2, p4), eucl_sq(p3, p4)};

        sort(dist.begin(), dist.end());

        // should result in 4 equal length sides and two longer sides that are the diagonals 
        bool equal_sides = dist[0] == dist[1] && dist[1] == dist[2] && dist[2] == dist[3];
        bool non_zero_sides = dist[0] > 0;

        // pythagoras: x^2 + x^2 = y^2 => 2x^2 = y^2
        bool correct_diagonals = dist[4] == dist[5] &&  2*dist[0] == dist[4];
        return equal_sides && non_zero_sides && correct_diagonals;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
594. Longest Harmonious Subsequence
We define a harmonious array is an array where the difference between its maximum value and its minimum 
value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all 
its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.
/*
    Submission Date: 2017-05-27
    Runtime: 109 ms
    Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> freq;
        int max_len = 0;
        for(int d: nums) {
            int current = 0;
            if(freq.find(d) != freq.end()) {
                current += freq[d];
                freq[d] += 1;
            } else {
                freq[d] = 1;
            }

            int adj = 0;
            if(freq.find(d-1) != freq.end()) {
                adj = max(adj, freq[d-1]);
            }

            if(freq.find(d+1) != freq.end()) {
                adj = max(adj, freq[d+1]);
            }

            if(adj == 0) continue;
            current += adj + 1;
            max_len = max(current, max_len);
        }
        return max_len;
    }
};

int main() {
    vector<int> v{1,3,2,2,5,2,3,7};
    Solution s;
    cout << s.findLHS(v) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
598. Range Addition II
Given an m * n matrix M initialized with all 0's and several update operations.

Operations are represented by a 2D array, and each operation is represented by an array with 
two positive integers a and b, which means M[i][j] should be added by one for all 0 <= i < a 
and 0 <= j < b.

You need to count and return the number of maximum integers in the matrix after performing 
all the operations.

Example 1:
Input: 
m = 3, n = 3
operations = [[2,2],[3,3]]
Output: 4
Explanation: 
Initially, M = 
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]

After performing [2,2], M = 
[[1, 1, 0],
 [1, 1, 0],
 [0, 0, 0]]

After performing [3,3], M = 
[[2, 2, 1],
 [2, 2, 1],
 [1, 1, 1]]

So the maximum integer in M is 2, and there are four of it in M. So return 4.
Note:
The range of m and n is [1,40000].
The range of a is [1,m], and the range of b is [1,n].
The range of operations size won't exceed 10,000.
/*
    Submission Date: 2017-05-29
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {
        for(vector<int> op: ops) {
            m = min(m, op[0]);
            n = min(n, op[1]);
        }
        return m*n;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
599. Minimum Index Sum of Two Lists
Suppose Andy and Doris want to choose a restaurant for dinner, and they both have a list of 
favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index sum. If there 
is a choice tie between answers, output all of them with no order requirement. You could assume 
there always exists an answer.

Example 1:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
Output: ["Shogun"]
Explanation: The only restaurant they both like is "Shogun".
Example 2:
Input:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["KFC", "Shogun", "Burger King"]
Output: ["Shogun"]
Explanation: The restaurant they both like and have the least index sum is "Shogun" with 
index sum 1 (0+1).
Note:
The length of both lists will be in the range of [1, 1000].
The length of strings in both lists will be in the range of [1, 30].
The index is starting from 0 to the list length minus 1.
No duplicates in both lists.
/*
    Submission Date: 2017-05-29
    Runtime: 103 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> m;
        for(int i = 0; i < list1.size(); i++) {
            m[list1[i]] = i;
        }
        
        vector<string> res;
        int min_index_sum = -1;
        for(int i = 0; i < list2.size(); i++) {
            string s2 = list2[i];
            if(m.count(s2)) {
                int new_sum = i + m[s2];
                if(min_index_sum == -1) {
                    min_index_sum = new_sum;
                    res.push_back(s2);
                    continue;
                }
                
                if(new_sum == min_index_sum) {
                    res.push_back(s2);
                } else if(new_sum < min_index_sum) {
                    min_index_sum = new_sum;
                    res.clear();
                    res.push_back(s2);
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<string> v1{"Shogun","Tapioca Express","Burger King","KFC"};
    vector<string> v2{"Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"};
    vector<string> t = s.findRestaurant(v1, v2);
    cout << t.size() << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
604. Design Compressed String Iterator
Design and implement a data structure for a compressed string iterator. 
It should support the following operations: next and hasNext.

The given compressed string will be in the form of each letter followed 
by a positive integer representing the number of this letter existing in 
the original uncompressed string.

next() - if the original string still has uncompressed characters, return 
the next letter; Otherwise return a white space.
hasNext() - Judge whether there is any letter needs to be uncompressed.

Example:

StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");

iterator.next(); // return 'L'
iterator.next(); // return 'e'
iterator.next(); // return 'e'
iterator.next(); // return 't'
iterator.next(); // return 'C'
iterator.next(); // return 'o'
iterator.next(); // return 'd'
iterator.hasNext(); // return true
iterator.next(); // return 'e'
iterator.hasNext(); // return false
iterator.next(); // return ' '

/*
    Submission Date: 2017-06-11
    Runtime: 12 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

class StringIterator {
vector<pair<char, long long>> v_;
int index_;
public:
    StringIterator(string compressedString) {
        index_ = 0;
        int len = compressedString.size();
        int i = 0;
        while(i < len) {
            char c = compressedString[i];
            i++;
            string rep = "";
            while(i < len && isdigit(compressedString[i])) {
                rep += compressedString[i];
                i++;
            }
            
            long long times = stoll(rep);
            // cout << c << ' ' << times << endl;
            v_.emplace_back(c, times);
        }
    }
    
    char next() {
        if(!hasNext()) return ' ';
        pair<char, long long>& p = v_[index_];
        p.second--;
        if(p.second == 0) index_++;
        return p.first;
    }
    
    bool hasNext() {
        return index_ < v_.size();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
605. Can Place Flowers
Suppose you have a long flowerbed in which some of the plots are planted 
and some are not. However, flowers cannot be planted in adjacent plots - 
they would compete for water and both would die.

Given a flowerbed (represented as an array containing 0 and 1, where 0 means 
empty and 1 means not empty), and a number n, return if n new flowers can be 
planted in it without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: True
Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: False
Note:
The input array won't violate no-adjacent-flowers rule.
The input array size is in the range of [1, 20000].
n is a non-negative integer which won't exceed the input array size.

/*
    Submission Date: 2017-06-11
    Runtime: 19 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int len = flowerbed.size();
        vector<int> v;

        // v.push_back(-1);
        for(int i = 0; i < len; i++) {
            if(flowerbed[i]) {
                v.push_back(i);
            }
        }
        // v.push_back(len);

        int v_len = v.size();
        for(int i = 1; i < v_len; i++) {
            int num_zeros = v[i] - v[i-1] - 1;
            // cout << v[i] << " " << v[i-1] << " " << num_zeros << " " << (num_zeros - 1)/2 << endl;
            if(num_zeros > 0) {
                int diff = (num_zeros - 1)/2;
                n -= diff;
            }
        }

        if(v_len) {
            n -= v[0]/2;
            // cout << n << endl;
            n -= (len - v[v_len - 1] - 1)/2;
            // cout << n << endl;
        } else {
            n -= (len+1)/2;
        }

        // cout << "n" << n << endl;
        return n <= 0;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
606. Construct String from Binary Tree
You need to construct a string consists of parenthesis and integers from a 
binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you 
need to omit all the empty parenthesis pairs that don't affect the one-to-one 
mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one 
mapping relationship between the input and the output.

/*
    Submission Date: 2017-06-11
    Runtime: 15 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    string tree2str(TreeNode* t) {
        if(t == NULL) return "";
        string root = to_string(t -> val);
        string left = tree2str(t -> left);
        string right = tree2str(t -> right);
        
        if(left.empty() && right.empty())
            return root;
        if(!left.empty() && right.empty())
            return root + "(" + left + ")";
        
        return root + "(" + left + ")" + "(" + right + ")";
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
609. Find Duplicate File in System
Given a list of directory info including directory path, and all the files 
with contents in this directory, you need to find out all the groups of 
duplicate files in the file system in terms of their paths.

A group of duplicate files consists of at least two files that have exactly 
the same content.

A single directory info string in the input list has the following format:

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, 
f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm. Note 
that n >= 1 and m >= 0. If m = 0, it means the directory is just the root 
directory.

The output is a list of group of duplicate file paths. For each group, it 
contains all the file paths of the files that have the same content. A 
file path is a string that has the following format:

"directory_path/file_name.txt"

Example 1:
Input:
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", 
"root 4.txt(efgh)"]
Output:  
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]

Note:
No order is required for the final output.

You may assume the directory name, file name and file content only has letters 
and digits, and the length of file content is in the range of [1,50].

The number of files given is in the range of [1,20000].

You may assume no files or directories share the same name in the same directory.

You may assume each given directory info represents a unique directory. Directory 
path and file info are separated by a single blank space.

Follow-up beyond contest:
Imagine you are given a real file system, how will you search files? DFS or BFS?

If the file content is very large (GB level), how will you modify your solution?

If you can only read the file by 1kb each time, how will you modify your solution?

What is the time complexity of your modified solution? 

What is the most time-consuming part and memory consuming part of it? 

How to optimize?

How to make sure the duplicated files you find are not false positive?

/*
    Submission Date: 2017-06-11
    Runtime: 19 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

class Solution {
    pair<string, string> getContent(string& s) {
        int bracket_ind = s.rfind("(") + 1;
        string content = s.substr(bracket_ind, s.size() - bracket_ind - 1);
        string filename = s.substr(0, bracket_ind - 1);
        return make_pair(filename, content);
    }
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        // key content, value file
        unordered_map<string, vector<string>> m;
        for(string path: paths) {
            stringstream ss(path);
            string token;
            string dir = "";
            while(getline(ss, token, ' ')) {
                if(dir.empty()) {
                    dir = token;
                } else {
                    string file = token;
                    pair<string, string> p = getContent(file);
                    if(m.count(p.second)) {
                        m[p.second].push_back(dir + "/" + p.first);
                    } else {
                        m[p.second] = {dir + "/" + p.first};
                    }
                }
            }
        }
        
        vector<vector<string>> res;
        for(pair<string, vector<string>> p: m) {
            if(p.second.size() > 1) res.push_back(p.second);
        }
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
611. Valid Triangle Number
Given an array consists of non-negative integers, your task is to count 
the number of triplets chosen from the array that can make triangles if we 
take them as side lengths of a triangle.

Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].

/*
    Submission Date: 2017-06-11
    Runtime: 442 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int count = 0;
        int len = nums.size();
        for(int i = 0; i < len; i++) {
            if(nums[i] == 0) continue;
            for(int j = i + 1; j < len; j++) {
                int sum = nums[i] + nums[j];
                vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), sum);
                
                int index = it - nums.begin() - 1;
                count += max(index - j, 0);
                // cout << index << ' '  << j << ' ' <<count<< endl;
            }
        }
        return count;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
617. Merge Two Binary Trees
Given two binary trees and imagine that when you put one of them to cover the 
other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two 
nodes overlap, then sum node values up as the new value of the merged node. 
Otherwise, the NOT null node will be used as the node of new tree.

Example 1:
Input: 
    Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
         3
        / \
       4   5
      / \   \ 
     5   4   7
Note: The merging process must start from the root nodes of both trees.

/*
    Submission Date: 2017-06-11
    Runtime: 45 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode* mergeTreesHelper(TreeNode* t1, TreeNode* t2) {
        if(t1 == NULL && t2 == NULL) return NULL;
        
        TreeNode* curr = new TreeNode(-1);
        int new_val = -1;
        if(t1 != NULL && t2 != NULL) {
            new_val = t1 -> val + t2 -> val;
        } else if(t1 != NULL) {
            new_val = t1 -> val;
        } else {
            new_val = t2 -> val;
        }
        
        curr -> val = new_val;
        
        TreeNode* left = mergeTreesHelper(t1 ? t1 -> left : NULL, t2 ? t2 -> left : NULL);
        TreeNode* right = mergeTreesHelper(t1 ? t1 -> right : NULL, t2 ? t2 -> right : NULL);
        curr -> left = left;
        curr -> right = right;
        return curr;
    }
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        return mergeTreesHelper(t1, t2);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
623. Add One Row to Tree
Given the root of a binary tree, then value v and depth d, you need to add a row of 
nodes with value v at the given depth d. The root node is at depth 1.

The adding rule is: given a positive integer depth d, for each NOT null tree nodes 
N in depth d-1, create two tree nodes with value v as N's left subtree root and right 
subtree root. And N's original left subtree should be the left subtree of the new left 
subtree root, its original right subtree should be the right subtree of the new right 
subtree root. If depth d is 1 that means there is no depth d-1 at all, then create a 
tree node with value v as the new root of the whole original tree, and the original 
tree is the new root's left subtree.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1
Note:
The given d is in range [1, maximum depth of the given tree + 1].
The given binary tree has at least one tree node.

/*
    Submission Date: 2017-06-18
    Runtime: 19 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    void getRow(TreeNode* root, int d, vector<TreeNode*>& vec) {
        if(root == NULL) return;
        if(d == 0) {
            vec.push_back(root);
            return;
        }
        
        getRow(root -> left, d - 1, vec);
        getRow(root -> right, d - 1, vec);
    }
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        // get all nodes at depth d - 1
        vector<TreeNode*> vec;
        if(d == 1) {
            TreeNode* new_root = new TreeNode(v);
            new_root -> left = root;
            root = new_root;
        } else {
            getRow(root, d - 2, vec);
            for(auto t: vec) {
                TreeNode* left = t -> left;
                TreeNode* right = t -> right;
                t -> left = new TreeNode(v);
                t -> right = new TreeNode(v);
                t -> left -> left = left;
                t -> right -> right = right;
            }
        }
        return root;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
624. Maximum Distance in Arrays
Given m arrays, and each array is sorted in ascending order. Now you can pick up two 
integers from two different arrays (each array picks one) and calculate the distance. 
We define the distance between two integers a and b to be their absolute difference 
|a-b|. Your task is to find the maximum distance.

Example 1:
Input: 
[[1,2,3],
 [4,5],
 [1,2,3]]
Output: 4
Explanation: 
One way to reach the maximum distance 4 is to pick 1 in the first or third array 
and pick 5 in the second array.
Note:
Each given array will have at least 1 number. There will be at least two non-empty arrays.
The total number of the integers in all the m arrays will be in the range of [2, 10000].
The integers in the m arrays will be in the range of [-10000, 10000].

/*
    Submission Date: 2017-06-18
    Runtime: 32 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Start {
    int index;
    int first_value;
};

struct End {
    int index;
    int last_value;
};

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int N = arrays.size();
        vector<Start> v;
        vector<End> v2;
        for(int i = 0; i < N; i++) {
            Start e = {i, arrays[i][0]};
            End e2 = {i, arrays[i].back()};
            v.push_back(e);
            v2.push_back(e2);
        }

        sort(v.begin(), v.end(), [](Start e, Start b){ return e.first_value < b.first_value; });
        sort(v2.begin(), v2.end(), [](End e, End b){ return e.last_value > b.last_value; });

        int max_dist = -1;
        int max_search = N;

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < max_search; j++) {
                if(v[i].index != v2[j].index) {
                    max_dist = max(abs(v2[j].last_value - v[i].first_value), max_dist);
                    max_search = j;
                    break;
                }
            }
        }
        return max_dist;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
628. Maximum Product of Three Numbers
Given an integer array, find three numbers whose product is maximum and output the maximum product.

Example 1:
Input: [1,2,3]
Output: 6
Example 2:
Input: [1,2,3,4]
Output: 24
Note:
The length of the given array will be in range [3,104] and all elements are in the range [-1000, 1000].
Multiplication of any three numbers in the input won't exceed the range of 32-bit signed integer.

/*
    Submission Date: 2017-07-09
    Runtime: 79 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int N = nums.size();
        
        if(N < 3) return INT_MIN;
        
        sort(nums.begin(), nums.end());
        
        // three largest or 1 largest and 2 smallest
        return max(nums[N-1]*nums[N-2]*nums[N-3], nums[N-1]*nums[0]*nums[1]);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
636. Exclusive Time of Functions
Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, 
find the exclusive time of these functions.

Each function has a unique id, start from 0 to n-1. A function may be called recursively or by 
another function.

A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" 
means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the 
very end of time 0.

Exclusive time of a function is defined as the time spent within this function, the time spent by 
calling other functions should not be considered as this function's exclusive time. You should 
return the exclusive time of each function sorted by their function id.

Example 1:
Input:
n = 2
logs = 
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.
Note:
Input logs will be sorted by timestamp, NOT log id.
Your output should be sorted by function id, which means the 0th element of your output corresponds 
to the exclusive time of function 0.
Two functions won't start or end at the same time.
Functions could be called recursively, and will always end.
1 <= n <= 100

/*
    Submission Date: 2017-07-15
    Runtime: 63 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <cassert>

using namespace std;

struct Log {
    int id;
    string status;
    int timestamp;
};

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> times(n, 0);
        stack<Log> st;
        for(string log: logs) {
            stringstream ss(log);
            string temp, temp2, temp3;
            getline(ss, temp, ':');
            getline(ss, temp2, ':');
            getline(ss, temp3, ':');

            Log item = {stoi(temp), temp2, stoi(temp3)};
            if(item.status == "start") {
                st.push(item);
            } else {
                assert(st.top().id == item.id);

                int time_added = item.timestamp - st.top().timestamp + 1;
                times[item.id] += item.timestamp - st.top().timestamp + 1;
                st.pop();

                if(!st.empty()) {
                    assert(st.top().status == "start");
                    times[st.top().id] -= time_added;
                }
            }
        }

        return times;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
637. Average of Levels in Binary Tree
Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.

Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return 
[3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.

/*
    Submission Date: 2017-07-09
    Runtime: 22 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        vector<double> res;
        
        while(!q.empty()) {
            int size = q.size();
            int size1 = 0;
            double sum = 0;
            for(int i = 0; i < size; i++) {
                TreeNode* f = q.front();
                if(f) {
                    sum += f -> val;
                    size1++;
                    q.push(f -> left);
                    q.push(f -> right);
                }
                
                q.pop();
            }
            if(size1)
            res.push_back(sum/size1);
        }
        
        return res;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
638. Shopping Offers
In LeetCode Store, there are some kinds of items to sell. Each item has a price.

However, there are some special offers, and a special offer consists of one or more different kinds of 
items with a sale price.

You are given the each item's price, a set of special offers, and the number we need to buy for each item. 
The job is to output the lowest price you have to pay for exactly certain items as given, where you could
 make optimal use of the special offers.

Each special offer is represented in the form of an array, the last number represents the price you need 
to pay for this special offer, other numbers represents how many specific items you could get if you buy 
this offer.

You could use any of special offers as many times as you want.

Example 1:
Input: [2,5], [[3,0,5],[1,2,10]], [3,2]
Output: 14
Explanation: 
There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
In special offer 1, you can pay $5 for 3A and 0B
In special offer 2, you can pay $10 for 1A and 2B. 
You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
Example 2:
Input: [2,3,4], [[1,1,0,4],[2,2,1,9]], [1,2,1]
Output: 11
Explanation: 
The price of A is $2, and $3 for B, $4 for C. 
You may pay $4 for 1A and 1B, and $9 for 2A ,2B and 1C. 
You need to buy 1A ,2B and 1C, so you may pay $4 for 1A and 1B (special offer #1), and $3 for 1B, $4 
for 1C. 
You cannot add more items, though only $9 for 2A ,2B and 1C.
Note:
There are at most 6 kinds of items, 100 special offers.
For each item, you need to buy at most 6 of them.
You are not allowed to buy more items than you want, even if that would lower the overall price.

/*
    Submission Date: 2017-07-09
    Runtime: 26 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    unordered_map<string, int> m;
public:
    int shoppingOffersHelper(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        string key = "";
        
        int N = needs.size();
        
        int res = INT_MAX;
        
        int count = 0;
        int price_cost = 0;
        for(int i = 0; i < N; i++) {
            key += to_string(needs[i]);
            count += needs[i] == 0;
            price_cost += needs[i]*price[i];
        }
        
        if(m.count(key)) return m[key];
        
        if(count == N) return 0;
        
        res = min(res, price_cost);
        
        vector<vector<int>> restore;
        for(auto it = special.begin(); it != special.end();) {
            vector<int> sp = *it;
            
            bool should_erase = false;
            for(int i = 0; i < N; i++) {
                if(sp[i] > needs[i]) {
                    should_erase = true;
                    break;
                }
            }
            
            if(should_erase) {
                restore.push_back(sp);
                it = special.erase(it);
            } else {
                // everything in sp[i] <= needs[i] so we can take it
                for(int i = 0; i < N; i++) {
                    needs[i] -= sp[i];
                }
                
                res = min(sp[N] + shoppingOffersHelper(price, special, needs), res);
                for(int i = 0; i < N; i++) {
                    needs[i] += sp[i];
                }
                it++;
            }
        }
        
        for(auto e: restore) special.push_back(e);
        return m[key] = res;
    }
    
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {       
        return shoppingOffersHelper(price, special, needs);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
640. Solve the Equation
Solve a given equation and return the value of x in the form of string "x=#value". The equation contains 
only '+', '-' operation, the variable x and its coefficient.

If there is no solution for the equation, return "No solution".

If there are infinite solutions for the equation, return "Infinite solutions".

If there is exactly one solution for the equation, we ensure that the value of x is an integer.

Example 1:
Input: "x+5-3+x=6+x-2"
Output: "x=2"
Example 2:
Input: "x=x"
Output: "Infinite solutions"
Example 3:
Input: "2x=x"
Output: "x=0"
Example 4:
Input: "2x+3x-6x=x+2"
Output: "x=-1"
Example 5:
Input: "x=x+2"
Output: "No solution"

/*
    Submission Date: 2017-07-09
    Runtime: 0 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <tuple>

using namespace std;

class Solution {
public:
    pair<long long, long long> getCount(string s) {
        long long x_count = 0;
        long long c_count = 0;
        for(int i = 0; i < s.size();) {
            string prev = "";
            bool seen_number = false;
            bool end_x = false;
            while(i < s.size()) {
                if(isdigit(s[i])) {
                    prev += s[i];
                    seen_number = true;
                    i++;
                } else if(s[i] == '+' || s[i] == '-') {
                    if(!seen_number) {
                        prev += s[i];
                        i++;
                    } else {
                        break;
                    }
                } else if(s[i] == 'x') {
                    end_x = true;
                    i++;
                    break;
                }
            }

            if(end_x) {
                if(prev == "+") x_count++;
                else if(prev == "-") x_count--;
                else if(prev == "") x_count++;
                else x_count += stoll(prev);
            } else {
                if(prev == "+") c_count++;
                else if(prev == "-") c_count--;
                else if(prev == "") c_count++;
                else c_count += stoll(prev);
            }
        }

        return {x_count, c_count};
    }
    string solveEquation(string equation) {
        // put all the x on the left side and all the numbers on the right side
        string s = equation;
        string inf = "Infinite solutions";
        string none = "No solution";

        int eq_ind = s.find("=");
        if(eq_ind == string::npos) return none;

        string left = s.substr(0, eq_ind);
        string right = s.substr(eq_ind + 1);

        
        long long x_count1, c_count1;
        tie(x_count1, c_count1) = getCount(left);

        long long x_count2, c_count2;
        tie(x_count2, c_count2) = getCount(right);

        long long left_x_count = x_count1 - x_count2;
        long long right_c_count = c_count2 - c_count1;

        if(left_x_count == 0) return right_c_count == 0 ? inf : none;

        return "x=" + to_string(right_c_count/left_x_count);
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
643. Maximum Average Subarray I
Given an array consisting of n integers, find the contiguous subarray of given length k that 
has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation: Maximum average is (12-5-6+50)/4 = 51/4 = 12.75
Note:
1 <= k <= n <= 30,000.
Elements of the given array will be in the range [-10,000, 10,000].

/*
    Submission Date: 2017-07-15
    Runtime: 199 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        int max_average = INT_MIN;
        for(int i = 0; i < nums.size(); i++) {
            if(i < k) {
                sum += nums[i];
            } else {
                if(i == k) max_average = max(max_average, sum);
                sum = sum - nums[i - k] + nums[i];
                max_average = max(max_average, sum);
            }
        }
        if(k == nums.size()) return (double)sum/k;
        return (double)max_average/k;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
645. Set Mismatch
The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of 
the numbers in the set got duplicated to another number in the set, which results in repetition of one 
number and loss of another number.

Given an array nums representing the data status of this set after the error. Your task is to firstly 
find the number occurs twice and then find the number that is missing. Return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]
Note:
The given array size will in the range [2, 10000].
The given array's numbers won't have any order.

/*
    Submission Date: 2017-07-23
    Runtime: 62 ms
    Difficulty: EASY
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        unordered_map<int, int> freq;
        for(auto num: nums) freq[num]++;
        
        int N = nums.size();
        int duplicate = -1;
        int missing = -1;
        for(int i = 1; i <= N; i++) {
            if(missing != -1 && duplicate != -1) break;
            if(!freq.count(i)) {
                missing = i;
            } else if(freq[i] >= 2) {
                duplicate = i;
            }
        }
        return {duplicate, missing};
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
646. Maximum Length of Pair Chain
You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be 
formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given 
pairs. You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]
Note:
The number of given pairs will be in the range [1, 1000].

/*
    Submission Date: 2017-07-23
    Runtime: 82 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](vector<int> v1, vector<int> v2){
            return v1[1] < v2[1];
        });
        
        vector<vector<int>> res;
        
        for(auto p: pairs) {
            if(res.empty() || res.back()[1] < p[0]) {
                res.push_back(p);
            }
        }
        
        return res.size();
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
647. Palindromic Substrings
Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even 
they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
Note:
The input string length won't exceed 1000.

/*
    Submission Date: 2017-07-23
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int Manacher(string s) {
        const char kNullChar = '\0';
        string str = string(1, kNullChar);

        for(auto c: s) str += string(1, c) + kNullChar;

        string max_str = "";
        int len = str.size();
        int right = 0;
        int center = 0;
        vector<int> dp(len, 0);

        for(int i = 1; i < len; i++) {
            int mirr = 2*center - i;

            // i is within right so can take the minimum of the mirror or distance from right
            if(i < right) {
                dp[i] = min(right - i, dp[mirr]);
            }

            // keep expanding around i while it is the same and increment P[i]
            int left_index = i - (1 + dp[i]);
            int right_index = i + (1 + dp[i]);
            while(left_index != -1 && right_index != len && str[left_index] == str[right_index]) {
                left_index--;
                right_index++;
                dp[i]++;
            }

            // i goes beyond current right so it is the new center
            if(i + dp[i] > right) {
                center = i;
                right = i + dp[i];
            }
        }
        
        int count = 0;
        for(int i = 0; i < len; i++) {
            count += ceil((double)dp[i]/2.0);
        }
        return count;
    }

    int countSubstrings(string s) {
        return Manacher(s);
    }

    int countSubstrings2(string s) {
        int res = 0;
        int N = s.size();
        int left, right;
        for(int i = 0; i < N; i++) {
            res++;
            
            // treat as odd
            left = i - 1;
            right = i + 1;
            while(left >= 0 && right < N && s[left] == s[right]) {
                left--;
                right++;
                res++;
            }
            
            // treat as even
            left = i;
            right = i + 1;
            while(left >= 0 && right < N && s[left] == s[right]) {
                left--;
                right++;
                res++;
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
648. Replace Words
In English, we have a concept called root, which can be followed by some other words to form another 
longer word - let's call this word successor. For example, the root an, followed by other, which can 
form another word another.

Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor 
in the sentence with the root forming it. If a successor has many roots can form it, replace it with the 
root with the shortest length.

You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
Note:
The input will only have lower-case letters.
1 <= dict words number <= 1000
1 <= sentence words number <= 1000
1 <= root length <= 100
1 <= sentence words length <= 1000

/*
    Submission Date: 2017-07-23
    Runtime: 159 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        unordered_set<string> ds(dict.begin(), dict.end());
        set<int> word_size;
        for(auto ds_e: ds) {
            word_size.insert(ds_e.size());
        }

        stringstream ss(sentence);
        string temp;

        vector<string> res;
        while(getline(ss, temp, ' ')) {
            bool found = false;
            for(auto len: word_size) {
                if(len > temp.size()) {
                    res.push_back(temp);
                    found = true;
                    break;
                } else {
                    if(ds.count(temp.substr(0, len))) {
                        res.push_back(temp.substr(0, len));
                        found = true;
                        break;
                    }
                }
            }

            if(!found) {
                res.push_back(temp);
            }
        }

        return accumulate(res.begin(), res.end(), string(), [](string memo, string a){
            return memo.empty() ? a : memo + " " + a;
        });
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
649. Dota2 Senate
In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. Now the senate wants to make a decision about 
a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator 
can exercise one of the two rights:

Ban one senator's right: 
A senator can make another senator lose all his rights in this and all the following rounds.
Announce the victory: 
If this senator found the senators who still have rights to vote are all from the same party, he can announce 
the victory and make the decision about the change in the game.
Given a string representing each senator's party belonging. The character 'R' and 'D' represent the Radiant 
party and the Dire party respectively. Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. This 
procedure will last until the end of voting. All the senators who have lost their rights will be skipped 
during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party, you need to predict 
which party will finally announce the victory and make the change in the Dota2 game. The output should be 
Radiant or Dire.

Example 1:
Input: "RD"
Output: "Radiant"
Explanation: The first senator comes from Radiant and he can just ban the next senator's right in the round 1. 
And the second senator can't exercise any rights any more since his right has been banned. 
And in the round 2, the first senator can just announce the victory since he is the only guy in the senate 
who can vote.
Example 2:
Input: "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in the round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in the round 1. 
And in the round 2, the third senator can just announce the victory since he is the only guy in the senate 
who can vote.
Note:
The length of the given string will in the range [1, 10,000].

/*
    Submission Date: 2017-07-30
    Runtime: 69 ms
    Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

class Solution {
public:
    string predictPartyVictory(string senate) {
        while(!senate.empty()) {
            for(int i = 0; i < senate.size();) {
                char curr = senate[i];
                int j = i;
                for(; j < senate.size(); j++) {
                    if(senate[j] != curr) {
                        break;
                    }
                }
            
                if(j == senate.size()) {
                    j = 0;
                    for(; j < i; j++) {
                        if(senate[j] != curr) {
                            break;
                        }
                    }

                    if(j == i) {
                        if(curr == 'R') return "Radiant";
                        return "Dire";
                    } else {
                        senate = senate.substr(0, j) + senate.substr(j + 1);
                    }
                } else {
                    senate = senate.substr(0, j) + senate.substr(j + 1);
                    i++;
                }
            }
        }
        return "";
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
650. 2 Keys Keyboard
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad 
for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps 
permitted. Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
Note:
The n will be in the range [1, 1000].

/*
    Submission Date: 2017-07-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = dp[1] = 0;

        for(int i = 1; i <= n; i++) {
            int cost = dp[i] + 1;
            int temp = i*2;
            if(temp > n) break; 
            while(temp <= n) {
                dp[temp] = min(dp[temp], ++cost);
                temp += i;
            }
        }

        return dp[n];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
652. Find Duplicate Subtrees
Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to 
return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1: 
        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:
      2
     /
    4
and
    4
Therefore, you need to return above trees' root in the form of a list.

/*
    Submission Date: 2017-07-30
    Runtime: 45 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    string preorder(TreeNode* root, unordered_map<string, int>& freq, vector<TreeNode*>& res) {
        if(root != NULL) {
            string left = preorder(root -> left, freq, res);
            string right = preorder(root -> right, freq, res);
            
            string str = to_string(root -> val) + " " + left + right;
            
            if(freq[str] == 1) res.push_back(root);
            freq[str]++;
            return str;
        } else {
            return "null ";
        }
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> freq;
        vector<TreeNode*> res;
        preorder(root, freq, res);
        return res;
    }
};

int main() {
    return 0;
}