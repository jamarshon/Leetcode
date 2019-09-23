
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1137. N-th Tribonacci Number
The Tribonacci sequence Tn is defined as follows: 

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.

Example 1:

Input: n = 4
Output: 4
Explanation:
T_3 = 0 + 1 + 1 = 2
T_4 = 1 + 1 + 2 = 4

Example 2:

Input: n = 25
Output: 1389537

Constraints:

  0 <= n <= 37
  The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 -
1.
/*
  Submission Date: 2019-09-08
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int tribonacci(int n) {
    if (n <= 1) return n;
    int T0 = 0, T1 = 1, T2 = 1;
    for (int i = 2; i < n; i++) {
      int T3 = T0 + T1 + T2;
      T0 = T1;
      T1 = T2;
      T2 = T3;
    }

    return T2;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1154. Day of the Year
Given a string date representing a Gregorian calendar date formatted as
YYYY-MM-DD, return the day number of the year.

Example 1:

Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.

Example 2:

Input: date = "2019-02-10"
Output: 41

Example 3:

Input: date = "2003-03-01"
Output: 60

Example 4:

Input: date = "2004-03-01"
Output: 61

Constraints:

  date.length == 10
  date[4] == date[7] == '-', and all other date[i]'s are digits
  date represents a calendar date between Jan 1st, 1900 and Dec 31, 2019.
/*
  Submission Date: 2019-09-23
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  }
  int dayOfYear(string date) {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8));
    bool is_leap_year = isLeapYear(year);
    int res = 0;
    for (int i = 0; i < month - 1; i++) {
      res += days_in_month[i];
    }
    return res + day + (is_leap_year && month > 2);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1160. Find Words That Can Be Formed by Characters
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each
character can only be used once).

Return the sum of lengths of all good strings in words.

Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation:
The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.

Example 2:

Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation:
The strings that can be formed are "hello" and "world" so the answer is 5 + 5 =
10.

Note:

  1 <= words.length <= 1000
  1 <= words[i].length, chars.length <= 100
  All strings contain lowercase English letters only.
/*
  Submission Date: 2019-08-25
  Runtime: 172 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  // count the frequency of letters in chars and
  // make sure the string has at most that many letters
  // and no unknown letters
  int countCharacters(vector<string>& words, string chars) {
    unordered_map<char, int> freqs;
    for (const auto& e : chars) freqs[e]++;
    int res = 0;
    for (const auto& s : words) {
      unordered_map<char, int> freqs_copy = freqs;
      bool ok = true;
      for (const auto& e : s) {
        if (!freqs_copy.count(e)) {
          ok = false;
          break;
        }
        freqs_copy[e]--;
        if (freqs_copy[e] == 0) freqs_copy.erase(e);
      }
      if (ok) res += s.size();
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1161. Maximum Level Sum of a Binary Tree
Given the root of a binary tree, the level of its root is 1, the level of its
children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at
level X is maximal.

Example 1:

Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.

Note:

  The number of nodes in the given tree is between 1 and 10^4.
  -10^5 <= node.val <= 10^5
/*
  Submission Date: 2019-09-21
  Runtime: 208 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int maxLevelSum(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int max_level = -1;
    int max_sum = INT_MIN;
    int level = 1;
    while (!q.empty()) {
      int sum = 0;
      for (int i = 0, N = q.size(); i < N; i++) {
        TreeNode* curr = q.front();
        sum += curr->val;
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
      }
      if (max_level == -1 || sum > max_sum) {
        max_level = level;
        max_sum = sum;
      }
      level++;
    }
    return max_level;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1170. Compare Strings by Frequency of the Smallest Character
Let's define a function f(s) over a non-empty string s, which calculates the
frequency of the smallest character in s. For example, if s = "dcce" then f(s) =
2 because the smallest character is "c" and its frequency is 2.

Now, given string arrays queries and words, return an integer array answer,
where each answer[i] is the number of words such that f(queries[i]) < f(W),
where W is a word in words.

Example 1:

Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd")
< f("zaaaz").

Example 2:

Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]
Explanation: On the first query only f("bbb") < f("aaaa"). On the second query
both f("aaa") and f("aaaa") are both > f("cc").

Constraints:

  1 <= queries.length <= 2000
  1 <= words.length <= 2000
  1 <= queries[i].length, words[i].length <= 10
  queries[i][j], words[i][j] are English lowercase letters.
/*
  Submission Date: 2019-09-07
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  // linear finds the smallest character and its frequency
  int f(const string& s) {
    char smallest = 'z' + 1;
    for (const auto& c : s) smallest = min(smallest, c);
    int freq = 0;
    for (const auto& c : s) freq += c == smallest;
    return freq;
  }

 public:
  vector<int> numSmallerByFrequency(vector<string>& queries,
                                    vector<string>& words) {
    int w_size = words.size();

    // compute all the f of words and sort them
    vector<int> f_ws(w_size);
    for (int i = 0; i < w_size; i++) f_ws[i] = f(words[i]);
    sort(f_ws.begin(), f_ws.end());

    int q_size = queries.size();
    vector<int> res(q_size);
    for (int i = 0; i < q_size; i++) {
      int f_q = f(queries[i]);
      // find the f of a query and binary search the first
      // f of a word larger than it. return the number
      // of elements further right/greater than the iterator
      // (e.g. > f_q)
      auto it = upper_bound(f_ws.begin(), f_ws.end(), f_q);
      res[i] = f_ws.end() - it;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1175. Prime Arrangements
Return the number of permutations of 1 to n so that prime numbers are at prime
indices (1-indexed.)

(Recall that an integer is prime if and only if it is greater than 1, and cannot
be written as a product of two positive integers both smaller than it.)

Since the answer may be large, return the answer modulo 10^9 + 7.

Example 1:

Input: n = 5
Output: 12
Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is
not because the prime number 5 is at index 1.

Example 2:

Input: n = 100
Output: 682289015

Constraints:

  1 <= n <= 100
/*
  Submission Date: 2019-09-21
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int mod = 1e9 + 7;

  // get the number of primes from [2, n]
  int sieve(int n) {
    int cnt = 0;
    vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= sqrt(n); i++) {
      if (is_prime[i]) {
        cnt++;
        for (int j = i * i; j <= n; j += i) {
          is_prime[j] = false;
        }
      }
    }
    for (int i = sqrt(n) + 1; i <= n; i++) cnt += is_prime[i];
    return cnt;
  }

  long long factorial(int n) {
    long long res = 1;
    for (int i = 1; i <= n; i++) res = (res * i) % mod;
    return res;
  }

  int numPrimeArrangements(int n) {
    /*
    return num_primes! * (n - num_primes)!
    because there are num_primes! ways to organize the primes
    and (n - num_primes)! ways to organize the composites
    */
    int num_primes = sieve(n);
    int num_composites = n - sieve(n);
    return (factorial(num_primes) * factorial(num_composites)) % mod;
  }
};

int main() { return 0; }

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
