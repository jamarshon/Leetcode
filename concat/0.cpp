
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
	Runtime: 6 ms
	Difficulty: MEDIUM
*/

using namespace std;

#include <vector>
#include <algorithm>

class Solution {
public:
    string longestPalindrome(string s) {
        const char kNullChar = '\0';
        string str = string(1, kNullChar);
        for(auto c: s) str += string(1, c) + kNullChar;
        
        int N = str.size();
        vector<int> dp(N, 0);
        int right = 0;
        int center = 0;
        
        string longest_palindrome = "";
        for(int i = 1; i < N; i++) {
            int mirror = 2*center - i;
            if(i < right) {
                dp[i] = min(right - i, dp[mirror]);
            }
            
            int left_ind = i - (1 + dp[i]);
            int right_ind = i + (1 + dp[i]);
            while(left_ind >= 0 && right_ind < N && str[left_ind] == str[right_ind]) {
                left_ind--;
                right_ind++;
                dp[i]++;
            }
            
            int pal_len = right_ind - left_ind - 1;
            if(pal_len > longest_palindrome.size()) {
                longest_palindrome = str.substr(left_ind + 1, pal_len);
            }
            
            if(i + dp[i] > right) {
                right = i + dp[i];
                center = i;
            }
        }
        
        auto it = remove_if(longest_palindrome.begin(), longest_palindrome.end(), [&kNullChar](const char& c){ return c== kNullChar; });
        longest_palindrome.erase(it, longest_palindrome.end());
        return longest_palindrome;
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