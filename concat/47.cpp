
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1180. Count Substrings with Only One Distinct Letter
Given a string S, return the number of substrings that have only one distinct
letter.

Example 1:

Input: S = "aaaba"
Output: 8
Explanation: The substrings with one distinct letter are "aaa", "aa", "a", "b".
"aaa" occurs 1 time.
"aa" occurs 2 times.
"a" occurs 4 times.
"b" occurs 1 time.
So the answer is 1 + 2 + 4 + 1 = 8.

Example 2:

Input: S = "aaaaaaaaaa"
Output: 55

Constraints:

  1 <= S.length <= 1000
  S[i] consists of only lowercase English letters.
/*
  Submission Date: 2019-09-07
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int countLetters(string S) {
    // count the number of repeating consecutive characters
    // there are n*(n+1) substrings of them
    int N = S.size();
    int res = 0;
    for (int i = 0; i < N;) {
      int j = i;
      while (j < N && S[i] == S[j]) j++;
      res += (j - i) * (j - i + 1) / 2;
      i = j;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1184. Distance Between Bus Stops
A bus has n stops numbered from 0 to n - 1 that form a circle. We know the
distance between all pairs of neighboring stops where distance[i] is the
distance between the stops number i and (i + 1) % n.

The bus goes along both directions i.e. clockwise and counterclockwise.

Return the shortest distance between the given start and destination stops.

Example 1:

Input: distance = [1,2,3,4], start = 0, destination = 1
Output: 1
Explanation: Distance between 0 and 1 is 1 or 9, minimum is 1.

Example 2:

Input: distance = [1,2,3,4], start = 0, destination = 2
Output: 3
Explanation: Distance between 0 and 2 is 3 or 7, minimum is 3.

Example 3:

Input: distance = [1,2,3,4], start = 0, destination = 3
Output: 4
Explanation: Distance between 0 and 3 is 6 or 4, minimum is 4.

Constraints:

  1 <= n <= 10^4
  distance.length == n
  0 <= start, destination < n
  0 <= distance[i] <= 10^4
/*
  Submission Date: 2019-09-17
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int distanceBetweenBusStops(vector<int>& distance, int start,
                              int destination) {
    // sum represents the sum of array from i to j where i < j
    // total_sum is the whole array sum
    // the result is the minimum of sum and total_sum - sum
    // as that is doing the reverse direction
    int total_sum = 0, sum = 0;
    if (start > destination) swap(start, destination);
    for (int i = 0; i < distance.size(); i++) {
      if (start <= i && i < destination) {
        sum += distance[i];
      }
      total_sum += distance[i];
    }
    return min(sum, total_sum - sum);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1185. Day of the Week
Given a date, return the corresponding day of the week for that date.

The input is given as three integers representing the day, month and year
respectively.

Return the answer as one of the following values {"Sunday", "Monday", "Tuesday",
"Wednesday", "Thursday", "Friday", "Saturday"}.

Example 1:

Input: day = 31, month = 8, year = 2019
Output: "Saturday"

Example 2:

Input: day = 18, month = 7, year = 1999
Output: "Sunday"

Example 3:

Input: day = 15, month = 8, year = 1993
Output: "Sunday"

Constraints:

  The given dates are valid dates between the years 1971 and 2100.
/*
  Submission Date: 2019-09-08
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
  string days[7] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                    "Friday", "Saturday", "Sunday"};

  int reference_year = 1900;
  bool IsLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  }

  int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

 public:
  string dayOfTheWeek(int day, int month, int year) {
    int diff_year = year - reference_year;
    // the number of days from full years
    int diff_common_days = diff_year * 365;

    // the number of leap days from full years
    // leap years are divisible 4 unless it is divisible by 100 where
    // it has to be divisible by 400 (i.e. 2000)
    int diff_leap_days =
        (diff_year - 1) / 4 - (diff_year - 1) / 100 + (year > 2000);
    int diff_days = diff_common_days + diff_leap_days;

    // days from the number of months
    bool is_leap_year = IsLeapYear(year);
    for (int i = 0; i < month - 1; i++) {
      diff_days += month_days[i] + (is_leap_year && i == 1);
    }

    // days from the number of days in this month
    diff_days += day - 1;

    // jan 1, 1900 is a monday so do modulo
    return days[diff_days % 7];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1189. Maximum Number of Balloons
Given a string text, you want to use the characters of text to form as many
instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of
instances that can be formed.

Example 1:

Input: text = "nlaebolko"
Output: 1

Example 2:

Input: text = "loonbalxballpoon"
Output: 2

Example 3:

Input: text = "leetcode"
Output: 0

Constraints:

  1 <= text.length <= 10^4
  text consists of lower case English letters only.
/*
  Submission Date: 2019-09-17
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  string target = "balloon";
  unordered_map<char, int> target_freq;

 public:
  Solution() {
    for (const auto& c : target) target_freq[c]++;
  }

  // count the frequency of chars in text and then
  // count the frequency of chars in target
  // for all the characters in target,
  // if it does not exist in text, then return 0
  // as a target letter is not present
  // else take the minimum of the frequency in the
  // text divide by the frequency in the target
  int maxNumberOfBalloons(string text) {
    unordered_map<char, int> freq;
    for (const auto& c : text) freq[c]++;
    int res = INT_MAX;
    for (const auto& c : target) {
      if (!freq.count(c)) return 0;
      res = min(res, freq[c] / target_freq[c]);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1200. Minimum Absolute Difference
Given an array of distinct integers arr, find all pairs of elements with the
minimum absolute difference of any two elements. 

Return a list of pairs in ascending order(with respect to pairs), each pair [a,
b] follows

  a, b are from arr
  a < b
  b - a equals to the minimum absolute difference of any two elements in arr

Example 1:

Input: arr = [4,2,1,3]
Output: [[1,2],[2,3],[3,4]]
Explanation: The minimum absolute difference is 1. List all pairs with
difference equal to 1 in ascending order.

Example 2:

Input: arr = [1,3,6,10,15]
Output: [[1,3]]

Example 3:

Input: arr = [3,8,-10,23,19,-4,-14,27]
Output: [[-14,-10],[19,23],[23,27]]

Constraints:

  2 <= arr.length <= 10^5
  -10^6 <= arr[i] <= 10^6
/*
  Submission Date: 2019-09-22
  Runtime: 120 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int min_abs_difference = INT_MAX;
    for (int i = 1; i < arr.size(); i++) {
      min_abs_difference = min(min_abs_difference, abs(arr[i] - arr[i - 1]));
    }
    vector<vector<int>> res;
    for (int i = 1; i < arr.size(); i++) {
      if (abs(arr[i] - arr[i - 1]) == min_abs_difference) {
        res.push_back({arr[i - 1], arr[i]});
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1221. Split a String in Balanced Strings
Balanced strings are those who have equal quantity of 'L' and 'R' characters.

Given a balanced string s split it in the maximum amount of balanced strings.

Return the maximum amount of splitted balanced strings.

Example 1:

Input: s = "RLRRLLRLRL"
Output: 4
Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring
contains same number of 'L' and 'R'.

Example 2:

Input: s = "RLLLLRRRLR"
Output: 3
Explanation: s can be split into "RL", "LLLRRR", "LR", each substring contains
same number of 'L' and 'R'.

Example 3:

Input: s = "LLLLRRRR"
Output: 1
Explanation: s can be split into "LLLLRRRR".

Constraints:

  1 <= s.length <= 1000
  s[i] = 'L' or 'R'
/*
  Submission Date: 2019-10-14
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int balancedStringSplit(string s) {
    // greedily get substrings where as soon as we hit
    // 0 again then use it and start the next substring
    // as we need to use all characters of s
    int res = 0;
    int cnt = 0;
    for (const auto& e : s) {
      cnt += e == 'L';
      cnt -= e == 'R';
      res += cnt == 0;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1281. Subtract the Product and Sum of Digits of an Integer
Given an integer number n, return the difference between the product of its
digits and the sum of its digits.
 
Example 1:

Input: n = 234
Output: 15
Explanation:
Product of digits = 2 * 3 * 4 = 24
Sum of digits = 2 + 3 + 4 = 9
Result = 24 - 9 = 15

Example 2:

Input: n = 4421
Output: 21
Explanation:
Product of digits = 4 * 4 * 2 * 1 = 32
Sum of digits = 4 + 4 + 2 + 1 = 11
Result = 32 - 11 = 21

Constraints:

  1 <= n <= 10^5
/*
  Submission Date: 2020-04-10
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int subtractProductAndSum(int n) {
    int product = 1;
    int sum = 0;
    while (n) {
      int x = n % 10;
      n /= 10;
      product *= x;
      sum += x;
    }
    return product - sum;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1295. Find Numbers with Even Number of Digits
Given an array nums of integers, return how many of them contain an even number
of digits.
 
Example 1:

Input: nums = [12,345,2,6,7896]
Output: 2
Explanation:
12 contains 2 digits (even number of digits). 
345 contains 3 digits (odd number of digits). 
2 contains 1 digit (odd number of digits). 
6 contains 1 digit (odd number of digits). 
7896 contains 4 digits (even number of digits). 
Therefore only 12 and 7896 contain an even number of digits.

Example 2:

Input: nums = [555,901,482,1771]
Output: 1
Explanation:
Only 1771 contains an even number of digits.

Constraints:

  1 <= nums.length <= 500
  1 <= nums[i] <= 10^5
/*
  Submission Date: 2020-04-12
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findNumbers(vector<int>& nums) {
    int res = 0;
    for (const auto& x : nums) {
      const int& num_digits = floor(log10(x)) + 1;
      res += num_digits % 2 == 0;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1313. Decompress Run-Length Encoded List
We are given a list nums of integers representing a list compressed with
run-length encoding.

Consider each adjacent pair of elements [freq, val] = [nums[2*i],
nums[2*i+1]] (with i >= 0).  For each such pair, there are freq elements with
value val concatenated in a sublist. Concatenate all the sublists from left to
right to generate the decompressed list.

Return the decompressed list.

Example 1:

Input: nums = [1,2,3,4]
Output: [2,4,4,4]
Explanation: The first pair [1,2] means we have freq = 1 and val = 2 so we
generate the array [2].
The second pair [3,4] means we have freq = 3 and val = 4 so we generate [4,4,4].
At the end the concatenation [2] + [4,4,4] is [2,4,4,4].

Example 2:

Input: nums = [1,1,2,3]
Output: [1,3,3]

Constraints:

  2 <= nums.length <= 100
  nums.length % 2 == 0
  1 <= nums[i] <= 100
/*
  Submission Date: 2020-04-12
  Runtime: 44 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> decompressRLElist(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); i += 2) {
      int freq = nums[i];
      int val = nums[i + 1];
      for (int j = 0; j < freq; j++) {
        res.push_back(val);
      }
    }

    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1342. Number of Steps to Reduce a Number to Zero
Given a non-negative integer num, return the number of steps to reduce it to
zero. If the current number is even, you have to divide it by 2, otherwise, you
have to subtract 1 from it.

Example 1:

Input: num = 14
Output: 6
Explanation: 
Step 1) 14 is even; divide by 2 and obtain 7. 
Step 2) 7 is odd; subtract 1 and obtain 6.
Step 3) 6 is even; divide by 2 and obtain 3. 
Step 4) 3 is odd; subtract 1 and obtain 2. 
Step 5) 2 is even; divide by 2 and obtain 1. 
Step 6) 1 is odd; subtract 1 and obtain 0.

Example 2:

Input: num = 8
Output: 4
Explanation: 
Step 1) 8 is even; divide by 2 and obtain 4. 
Step 2) 4 is even; divide by 2 and obtain 2. 
Step 3) 2 is even; divide by 2 and obtain 1. 
Step 4) 1 is odd; subtract 1 and obtain 0.

Example 3:

Input: num = 123
Output: 12

Constraints:

  0 <= num <= 10^6
/*
  Submission Date: 2020-04-05
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int numberOfSteps(int num) {
    if (num == 0) return 0;
    return 1 + (num % 2 == 0 ? numberOfSteps(num / 2) : numberOfSteps(num - 1));
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1365. How Many Numbers Are Smaller Than the Current Number
Given the array nums, for each nums[i] find out how many numbers in the array
are smaller than it. That is, for each nums[i] you have to count the number of
valid j's such that j != i and nums[j] < nums[i].

Return the answer in an array.

Example 1:

Input: nums = [8,1,2,2,3]
Output: [4,0,1,1,3]
Explanation:
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3).
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1).
For nums[3]=2 there exist one smaller number than it (1).
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

Example 2:

Input: nums = [6,5,4,8]
Output: [2,1,0,3]

Example 3:

Input: nums = [7,7,7,7]
Output: [0,0,0,0]

Constraints:

  2 <= nums.length <= 500
  0 <= nums[i] <= 100
/*
  Submission Date: 2020-04-13
  Runtime: 16 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    typedef pair<int, int> pii;
    vector<pii> v;
    int N = nums.size();
    v.reserve(N);
    for (int i = 0; i < N; i++) {
      v.emplace_back(nums[i], i);
    }

    sort(v.begin(), v.end());
    vector<int> res(N, 0);
    int duplicate = 0;
    for (int i = 0; i < N; i++) {
      if (i == 0) {
        res[v[i].second] = 0;
      } else {
        if (v[i].first == v[i - 1].first)
          duplicate++;
        else
          duplicate = 0;
        res[v[i].second] = i - duplicate;
      }
    }
    return res;
  }
};

int main() { return 0; }
