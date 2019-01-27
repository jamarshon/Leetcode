
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
462. Minimum Moves to Equal Array Elements II
Given a non-empty integer array, find the minimum number of moves required to
make all array elements equal, where a move is incrementing a selected element
by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:
Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one
element):

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]

/*
    Submission Date: 2018-07-01
    Runtime: 18 ms
    Difficulty: MEDIUM
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  O(nlogn) given that it is sorted compute the sum and say that is the lhs_cost
  rhs_cost = 0. as i decreases, there is a block of width i+1 and height diff
  that is removed from lhs_cost and a block of width N-i-1 and height diff that
  is added to the rhs_cost

  compute the lhs_cost, rhs_cost for all i and take the minimum.
  */
  typedef long long ll;
  int minMoves2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    ll lhs_cost = 0;
    for (const auto& e : nums) lhs_cost += nums.back() - e;
    ll res = lhs_cost;

    ll rhs_cost = 0;
    int N = nums.size();
    for (int i = N - 2; i >= 0; i--) {
      int diff = nums[i + 1] - nums[i];
      lhs_cost -= diff * (i + 1);
      rhs_cost += diff * (N - i - 1);
      res = min(res, lhs_cost + rhs_cost);
    }
    return res;
  }
};

class Solution2 {
 public:
  /*
  proof is suppose x is between two numbers (y, z where y <= z)
  then u can say the sum of deviation is (x-y) + (z-x) = z - y.
  so given an array of size n, u can just keep removing the min and max elements
  which would be equivalent to finding the median as it is the x between all the
  pairs of y,z. (need y,z to be as far apart as possible in order to ensure x is
  between them)
  */
  int minMoves2_sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int res = 0;
    int N = nums.size();
    for (int i = 0; i < N / 2; i++) {
      res += abs(nums[i] - nums[N - i - 1]);
    }
    return res;
  }

  int minMoves2(vector<int>& nums) {
    int res = 0;
    int N = nums.size();
    nth_element(nums.begin(), nums.begin() + N / 2, nums.end());

    int median = nums[N / 2];

    for (const auto& e : nums) {
      res += abs(e - median);
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
463. Island Perimeter
You are given a map in form of a two-dimensional integer grid where 1 represents
land and 0 represents water. Grid cells are connected horizontally/vertically
(not diagonally). The grid is completely surrounded by water, and there is
exactly one island (i.e., one or more connected land cells). The island doesn't
have "lakes" (water inside that isn't connected to the water around the island).
One cell is a square with side length 1. The grid is rectangular, width and
height don't exceed 100. Determine the perimeter of the island.

Example:

[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Answer: 16
Explanation: The perimeter is the 16 yellow stripes in the image below:

/*
    Submission Date: 2018-05-31
    Runtime: 245 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, -1, 1};

 public:
  int islandPerimeter(vector<vector<int>>& grid) {
    int res = 0;
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[0].size(); j++) {
        if (grid[i][j] == 0) continue;
        for (int k = 0; k < 4; k++) {
          int new_x = dx[k] + j;
          int new_y = dy[k] + i;
          // if out of bounds or is a zero element, add one
          if (new_x < 0 || new_x >= grid[0].size() || new_y < 0 ||
              new_y >= grid.size() || grid[new_y][new_x] == 0) {
            res++;
          }
        }
      }
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
468. Validate IP Address
Write a function to check whether an input string is a valid IPv4 address or
IPv6 address or neither.

IPv4 addresses are canonically represented in dot-decimal notation, which
consists of four decimal numbers, each ranging from 0 to 255, separated by dots
("."), e.g.,172.16.254.1;

Besides, leading zeros in the IPv4 is invalid. For example, the address
172.16.254.01 is invalid.

IPv6 addresses are represented as eight groups of four hexadecimal digits, each
group representing 16 bits. The groups are separated by colons (":"). For
example, the address 2001:0db8:85a3:0000:0000:8a2e:0370:7334 is a valid one.
Also, we could omit some leading zeros among four hexadecimal digits and some
low-case characters in the address to upper-case ones, so
2001:db8:85a3:0:0:8A2E:0370:7334 is also a valid IPv6 address(Omit leading zeros
and using upper cases).

However, we don't replace a consecutive group of zero value with a single empty
group using two consecutive colons (::) to pursue simplicity. For example,
2001:0db8:85a3::8A2E:0370:7334 is an invalid IPv6 address.

Besides, extra leading zeros in the IPv6 is also invalid. For example, the
address 02001:0db8:85a3:0000:0000:8a2e:0370:7334 is invalid.

Note:
You may assume there is no extra space or special characters in the input
string.

Example 1:
Input: "172.16.254.1"

Output: "IPv4"

Explanation: This is a valid IPv4 address, return "IPv4".

Example 2:
Input: "2001:0db8:85a3:0:0:8A2E:0370:7334"

Output: "IPv6"

Explanation: This is a valid IPv6 address, return "IPv6".

Example 3:
Input: "256.256.256.256"

Output: "Neither"

Explanation: This is neither a IPv4 address nor a IPv6 address.
/*
  Submission Date: 2019-01-26
  Runtime: 0 ms
  Difficulty: MEDIUM
*/
#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> split(const string& IP, const char& delim) {
    vector<string> tokens;
    string token;
    stringstream ss(IP);
    while (getline(ss, token, delim)) {
      if (token.empty()) return {};
      tokens.push_back(token);
    }
    return tokens;
  }
  string validIPAddress(string IP) {
    if (IP.empty() || IP.back() == ':' || IP.back() == '.') return "Neither";
    vector<string> tokens;
    if (IP.find('.') != string::npos) {
      tokens = split(IP, '.');
      if (tokens.size() != 4) return "Neither";
      for (const auto& token : tokens) {
        if (token.size() > 4) return "Neither";
        if (token == "0") continue;
        if (token[0] == '0') return "Neither";
        for (const auto& c : token) {
          if (isdigit(c)) continue;
          return "Neither";
        }
        if (stoi(token) > 255) return "Neither";
      }
      return "IPv4";
    } else if (IP.find(':' != string::npos)) {
      tokens = split(IP, ':');
      if (tokens.size() != 8) return "Neither";
      for (const auto& token : tokens) {
        if (token.size() > 4) return "Neither";
        for (const auto& c : token) {
          if (isdigit(c) || ('a' <= tolower(c) && tolower(c) <= 'f')) continue;
          return "Neither";
        }
      }
      return "IPv6";
    } else {
      return "Neither";
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
474. Ones and Zeroes
In the computer world, use restricted resource you have to generate maximum
benefit is what we always want to pursue.
For now, suppose you are a dominator of m 0s and n 1s respectively. On the other
hand, there is an array with strings consisting of only 0s and 1s.


Now your task is to find the maximum number of strings that you can form with
given m 0s and n 1s. Each 0 and 1 can be used at most once.



Note:

The given numbers of 0s and 1s will both not exceed 100
The size of given string array won't exceed 600.



Example 1:
Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
Output: 4

Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3
1s, which are “10,”0001”,”1”,”0”



Example 2:
Input: Array = {"10", "0", "1"}, m = 1, n = 1
Output: 2

Explanation: You could form "10", but then you'd have nothing left. Better form
"0" and "1".

/*
    Submission Date: 2018-07-12
    Runtime: 32 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  dp[i][j] is the maximum elements to find i 0's and j 1's
  need to do this for every element in v
  need to go from bottom right to top left as shouldn't visit
  a value that is updated already
  */
  int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    dp[0][0] = 0;

    int res = 0;
    for (const auto& s : strs) {
      int num_zero = 0, num_one = 0;
      for (const auto& c : s) {
        num_zero += c == '0';
        num_one += c == '1';
      }

      // i + num_zero <= m => i <= m - num_zero
      for (int i = m - num_zero; i >= 0; i--) {
        for (int j = n - num_one; j >= 0; j--) {
          // if dp[i][j] can be found
          if (dp[i][j] != -1) {
            dp[i + num_zero][j + num_one] =
                max(dp[i + num_zero][j + num_one], 1 + dp[i][j]);

            res = max(res, dp[i + num_zero][j + num_one]);
          }
        }
      }
    }

    return res;
  }
};

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct Hash {
  template <typename T, typename U>
  size_t operator()(const pair<T, U>& p) const {
    size_t seed = 0;
    hash_combine(seed, p.first);
    hash_combine(seed, p.second);
    return seed;
  }
};

class Solution3 {
 public:
  /*
  curr has key i, j where i is number of 0 and j is number of 1
  the value is the maximum amount of elements to get there
  
  start curr with m,n and 0
  
  for every number, loop over every i,j and see if we can use the number
  meaning i-number_0, j-number_1 is >= 0, 0. we reached this new state with
  1 + kv.second so max this on every time we hit this new state from using
  a different i,j state as well as max this with not using number.
  */
  int findMaxForm(vector<string>& strs, int m, int n) {
    int N = strs.size();
    vector<pair<int, int>> v(N, {0, 0});
    for (int i = 0; i < N; i++) {
      for (const auto& c : strs[i]) {
        v[i].first += c == '0';
        v[i].second += c == '1';
      }
    }

    unordered_map<pair<int, int>, int, Hash> curr;
    curr[make_pair(m, n)] = 0;

    int res = 0;
    for (int i = N - 1; i >= 0; i--) {
      unordered_map<pair<int, int>, int, Hash> new_curr;
      for (const auto& kv : curr) {
        const auto& p = kv.first;
        if (p.first >= v[i].first && p.second >= v[i].second) {
          const auto& new_p =
              make_pair(p.first - v[i].first, p.second - v[i].second);
          new_curr[new_p] = max(new_curr[new_p], 1 + kv.second);
          if (curr.count(new_p))
            new_curr[new_p] = max(curr[new_p], new_curr[new_p]);
          res = max(res, new_curr[new_p]);
        }
      }

      for (const auto& kv : new_curr) {
        curr[kv.first] = kv.second;
      }
    }
    return res;
  }
};

class Solution2 {
 public:
  /*
  take or not take v[index] this solution times out
  */
  int f(int index, const vector<pair<int, int>>& v, int N, int m, int n) {
    if (index == N) return 0;

    int res = f(index + 1, v, N, m, n);
    if (v[index].first <= m && v[index].second <= n) {
      res = max(
          res, 1 + f(index + 1, v, N, m - v[index].first, n - v[index].second));
    }
    return res;
  }
  int findMaxForm(vector<string>& strs, int m, int n) {
    int N = strs.size();
    vector<pair<int, int>> v(N, {0, 0});
    for (int i = 0; i < N; i++) {
      for (const auto& c : strs[i]) {
        v[i].first += c == '0';
        v[i].second += c == '1';
      }
    }

    return f(0, v, N, m, n);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
475. Heaters
Winter is coming! Your first job during the contest is to design a standard
heater with fixed warm radius to warm all the houses.

Now, you are given positions of houses and heaters on a horizontal line, find
out minimum radius of heaters so that all houses could be covered by those
heaters.

So, your input will be the positions of houses and heaters seperately, and your
expected output will be the minimum radius standard of heaters.

Note:
Numbers of houses and heaters you are given are non-negative and will not exceed
25000. Positions of houses and heaters you are given are non-negative and will
not exceed 10^9. As long as a house is in the heaters' warm radius range, it can
be warmed. All the heaters follow your radius standard and the warm radius will
the same. Example 1: Input: [1,2,3],[2] Output: 1 Explanation: The only heater
was placed in the position 2, and if we use the radius 1 standard, then all the
houses can be warmed. Example 2: Input: [1,2,3,4],[1,4] Output: 1 Explanation:
The two heater was placed in the position 1 and 4. We need to use radius 1
standard, then all the houses can be wa
/*
    Submission Date: 2018-06-24
    Runtime: 73 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution2 {
 public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    if (houses.empty()) return 0;

    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());

    int N = houses.size();
    int M = heaters.size();
    vector<int> dp(N, INT_MAX);
    // heaters[j] is the smallest heater greater than houses[i]
    for (int i = 0, j = 0; i < N && j < M;) {
      if (heaters[j] >= houses[i]) {
        dp[i] = heaters[j] - houses[i];
        i++;
      } else {
        j++;
      }
    }

    // heaters[j] is the largest element smaller than houses[i]
    for (int i = N - 1, j = M - 1; i >= 0 && j >= 0;) {
      if (heaters[j] <= houses[i]) {
        dp[i] = min(dp[i], houses[i] - heaters[j]);
        i--;
      } else {
        j--;
      }
    }

    return *max_element(dp.begin(), dp.end());
  }
};

class Solution {
 public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    if (houses.empty()) return 0;

    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());

    int i = 0;
    int N = heaters.size();

    int res = -1;
    for (const auto& house : houses) {
      while (i + 1 < N &&
             abs(heaters[i + 1] - house) <= abs(heaters[i] - house))
        i++;
      res = max(res, abs(heaters[i] - house));
    }
    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
476. Number Complement
Given a positive integer, output its complement number. The complement strategy
is to flip the bits of its binary representation.

Note:
The given integer is guaranteed to fit within the range of a 32-bit signed
integer. You could assume no leading zero bit in the integer’s binary
representation. Example 1: Input: 5 Output: 2 Explanation: The binary
representation of 5 is 101 (no leading zero bits), and its complement is 010. So
you need to output 2. Example 2: Input: 1 Output: 0 Explanation: The binary
representation of 1 is 1 (no leading zero bits), and its complement is 0. So you
need to output 0.
/*
    Submission Date: 2018-05-31
    Runtime: 6 ms
    Difficulty: EASY
*/
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  // flip all bits then find the highest power of 2. Make that and all bits
  // below it to 1 and AND it with the previous number.
  int findComplement(int num) { return ~num & ((1 << (int)log2(num) + 1) - 1); }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
477. Total Hamming Distance
The Hamming distance between two integers is the number of positions at which
the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the
given numbers.


Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010
(just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2
+ 2 = 6.



Note:

Elements of the given array are in the range of 0  to 10^9
Length of the array will not exceed 10^4.

/*
    Submission Date: 2018-07-08
    Runtime: 40 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  o(n) for the ith bit count how many 0 and how many 1 there are
  suppose there are x 0's and y 1's, then there are total x*y pairs
  because for every value in x, it can pair y values in y.
  */
  int totalHammingDistance(vector<int>& nums) {
    int N = nums.size();
    int res = 0;
    for (int i = 0; i < 31; i++) {
      int one_cnt = 0;
      for (const auto& n : nums) {
        bool one = n & (1 << i);
        one_cnt += one;
      }

      res += one_cnt * (N - one_cnt);
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
479. Largest Palindrome Product
Find the largest palindrome made from the product of two n-digit numbers.

Since the result could be very large, you should return the largest palindrome
mod 1337.

Example:

Input: 2

Output: 987

Explanation: 99 x 91 = 9009, 9009 % 1337 = 987

Note:

The range of n is [1,8].
/*
    Submission Date: 2018-06-24
    Runtime: 713 ms
    Difficulty: EASY
*/
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
 public:
  typedef long long ll;
  int largestPalindrome(int n) {
    if (n == 1) return 9;

    ll x = pow(10, n) - 1LL;  // 99
    ll max_x = x * x;

    ll lower = pow(10, n - 1);  // 10
    ll upper = x;               // 99
    while (x) {
      // take a string of n digits and reverse + concat to get string of 2n
      // digits
      string s = to_string(x);
      string rev = s;
      reverse(rev.begin(), rev.end());
      ll num = stoll(s + rev);
      if (num > max_x) {
        x--;
        continue;
      }

      // use upper instead of sqrt(num) as upper is larger
      for (ll fact = upper; fact > lower; fact--) {
        /* fact*fact >= num ensures that fact is greater than the second factor
           and we do not redo calculation on the lower factors e.g num = 20 fact
           = 5 5*5 >= 20 (takes in 5 and 4) fact = 4 4*4 < 20 (does not
           reconsider lower factors as they have already been checked)
            
            fact*fact >= num
            fact >= num/fact (upper > num/fact)
        */
        if (num / fact < lower || fact * fact < num) break;

        if (num % fact == 0) {
          return num % 1337;
        }
      }
      x--;
    }
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
481. Magical String
A magical string S consists of only '1' and '2' and obeys the following rules:


The string S is magical because concatenating the number of contiguous
occurrences of characters '1' and '2' generates the string S itself.



The first few elements of string S is the following:
S = "1221121221221121122……"



If we group the consecutive '1's and '2's in S, it will be:


1   22  11  2  1  22  1  22  11  2  11  22 ......


and the occurrences of '1's or '2's in each group are:


1   2      2    1   1    2     1    2     2    1    2    2 ......



You can see that the occurrence sequence above is the S itself.



Given an integer N as input, return the number of '1's in the first N number in
the magical string S.


Note:
N will not exceed 100,000.



Example 1:
Input: 6
Output: 3
Explanation: The first 6 elements of magical string S is "12211" and it contains
three 1's, so return 3.

/*
    Submission Date: 2018-07-10
    Runtime: 8 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  unordered_map<char, char> t{{'1', '2'}, {'2', '1'}};

 public:
  /*
  if(s[i] == '1') the last character should only occur once so push the opposite
  else the last character should occur twice so push the same then the opposite
  
  keep track of s.size() as well as the one_cnt
  */
  int magicalString(int n) {
    if (n == 0) return 0;
    int one_cnt = 1;
    string s = "1";
    int i = 0;
    while (s.size() < n) {
      if (s[i] == '1') {
        s.push_back(t[s.back()]);
        if (s.back() == '1') one_cnt++;
      } else {  // s[i] == '2'
        s.push_back(s.back());
        if (s.back() == '1') one_cnt++;
        if (s.size() < n) {
          s.push_back(t[s.back()]);
          if (s.back() == '1') one_cnt++;
        }
      }
      i++;
    }

    return one_cnt;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
482. License Key Formatting
You are given a license key represented as a string S which consists only
alphanumeric character and dashes. The string is separated into N+1 groups by N
dashes.

Given a number K, we would want to reformat the strings such that each group
contains exactly K characters, except for the first group which could be shorter
than K, but still must contain at least one character. Furthermore, there must
be a dash inserted between two groups and all lowercase letters should be
converted to uppercase.

Given a non-empty string S and a number K, format the string according to the
rules described above.

Example 1:
Input: S = "5F3Z-2e-9-w", K = 4

Output: "5F3Z-2E9W"

Explanation: The string S has been split into two parts, each part has 4
characters. Note that the two extra dashes are not needed and can be removed.
Example 2:
Input: S = "2-5g-3-J", K = 2

Output: "2-5G-3J"

Explanation: The string S has been split into three parts, each part has 2
characters except the first part as it could be shorter as mentioned above.
Note:
The length of string S will not exceed 12,000, and K is a positive integer.
String S consists only of alphanumerical characters (a-z and/or A-Z and/or 0-9)
and dashes(-). String S is non-empty.
/*
    Submission Date: 2018-06-09
    Runtime: 13 ms
    Difficulty: EASY
*/
#include <cctype>
#include <iostream>

using namespace std;

class Solution {
 public:
  string licenseKeyFormatting(string S, int K) {
    string s = "";
    // remove dashes and lower case letter
    for (const auto& c : S) {
      if (c == '-') continue;
      s.push_back(toupper(c));
    }

    int N = s.size();
    int first_size = N % K;

    string res = "";
    res.reserve(N + (N - 1) / 2);
    for (int i = 0; i < N; i++) {
      if (i > 0 && (i - first_size) % K == 0) res.push_back('-');
      res.push_back(s[i]);
    }

    return res;
  }
};

int main() { return 0; }
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
485. Max Consecutive Ones
Given a binary array, find the maximum number of consecutive 1s in this array.

Example 1:
Input: [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
/*
    Submission Date: 2018-06-03
    Runtime: 37 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    int curr = 0;
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 1) {
        curr++;
        res = max(res, curr);
      } else {
        curr = 0;
      }
    }
    return res;
  }
};

int main() { return 0; }