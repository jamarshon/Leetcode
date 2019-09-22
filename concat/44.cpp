
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1030. Matrix Cells in Distance Order
We are given a matrix with R rows and C columns has cells with integer
coordinates (r, c), where 0 <= r < R and 0 <= c < C.

Additionally, we are given a cell in that matrix with coordinates (r0, c0).

Return the coordinates of all cells in the matrix, sorted by their distance from
(r0, c0) from smallest distance to largest distance.  Here, the distance between
two cells (r1, c1) and (r2, c2) is the Manhattan distance, |r1 - r2| + |c1 -
c2|.  (You may return the answer in any order that satisfies this condition.)

Example 1:

Input: R = 1, C = 2, r0 = 0, c0 = 0
Output: [[0,0],[0,1]]
Explanation: The distances from (r0, c0) to other cells are: [0,1]

Example 2:

Input: R = 2, C = 2, r0 = 0, c0 = 1
Output: [[0,1],[0,0],[1,1],[1,0]]
Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2]
The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.

Example 3:

Input: R = 2, C = 3, r0 = 1, c0 = 2
Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2,2,3]
There are other answers that would also be accepted as correct, such as
[[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].

Note:

  1 <= R <= 100
  1 <= C <= 100
  0 <= r0 < R
  0 <= c0 < C
/*
  Submission Date: 2019-09-07
  Runtime: 220 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  string GetKey(int x, int y) { return to_string(x) + '-' + to_string(y); }

 public:
  // bfs
  vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
    queue<pair<int, int>> q{{{r0, c0}}};
    unordered_set<string> seen{GetKey(r0, c0)};
    vector<vector<int>> res;
    while (!q.empty()) {
      auto p = q.front();
      res.push_back({p.first, p.second});
      q.pop();
      for (int i = 0; i < 4; i++) {
        int x = dx[i] + p.first;
        int y = dy[i] + p.second;
        if (0 <= x && x < R && 0 <= y && y < C) {
          string key = GetKey(x, y);
          if (!seen.count(key)) {
            seen.insert(key);
            q.emplace(x, y);
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
1046. Last Stone Weight
We have a collection of rocks, each rock has a positive integer weight.

Each turn, we choose the two heaviest rocks and smash them together.  Suppose
the stones have weights x and y with x <= y.  The result of this smash is:

  If x == y, both stones are totally destroyed;
  If x != y, the stone of weight x is totally destroyed, and the stone of weight
y has new weight y-x.

At the end, there is at most 1 stone left.  Return the weight of this stone (or
0 if there are no stones left.)

Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation:
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value
of last stone.

Note:

  1 <= stones.length <= 30
  1 <= stones[i] <= 1000
/*
  Submission Date: 2019-09-07
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>

using namespace std;

class Solution {
 public:
  int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    while (pq.size() >= 2) {
      auto x = pq.top();
      pq.pop();
      auto y = pq.top();
      pq.pop();

      if (x != y) pq.push(abs(x - y));
    }
    return pq.empty() ? 0 : pq.top();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1047. Remove All Adjacent Duplicates In String
Given a string S of lowercase letters, a duplicate removal consists of choosing
two adjacent and equal letters, and removing them.

We repeatedly make duplicate removals on S until we no longer can.

Return the final string after all such duplicate removals have been made.  It is
guaranteed the answer is unique.

Example 1:

Input: "abbaca"
Output: "ca"
Explanation:
For example, in "abbaca" we could remove "bb" since the letters are adjacent and
equal, and this is the only possible move.  The result of this move is that the
string is "aaca", of which only "aa" is possible, so the final string is "ca".

Note:

  1 <= S.length <= 20000
  S consists only of English lowercase letters.
/*
  Submission Date: 2019-09-07
  Runtime: 24 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string removeDuplicates(string S) {
    // using a stack if we encounter a character
    // that was previously seen then we can pop from
    // the stack and not add the current character.
    // this exposes a previous character in the string
    // which can match with the next character as needed.
    vector<char> stk;
    for (int i = 0; i < S.size(); i++) {
      if (!stk.empty() && stk.back() == S[i])
        stk.pop_back();
      else
        stk.push_back(S[i]);
    }

    return string(stk.begin(), stk.end());
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1051. Height Checker
Students are asked to stand in non-decreasing order of heights for an annual
photo.

Return the minimum number of students not standing in the right positions. 
(This is the number of students that must move in order for all students to be
standing in non-decreasing order of height.)

Example 1:

Input: [1,1,4,2,1,3]
Output: 3
Explanation:
Students with heights 4, 3 and the last 1 are not standing in the right
positions.

Note:

  1 <= heights.length <= 100
  1 <= heights[i] <= 100
/*
  Submission Date: 2019-08-25
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  // sort the list and see compare elmentwise between
  // the two lists to see how many elements are out of place
  int heightChecker(vector<int>& heights) {
    int res = 0;
    vector<int> v = heights;
    sort(v.begin(), v.end());
    for (int i = 0; i < heights.size(); i++) res += v[i] != heights[i];
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1071. Greatest Common Divisor of Strings
For strings S and T, we say "T divides S" if and only if S = T + ... + T  (T
concatenated with itself 1 or more times)

Return the largest string X such that X divides str1 and X divides str2.

Example 1:

Input: str1 = "ABCABC", str2 = "ABC"
Output: "ABC"

Example 2:

Input: str1 = "ABABAB", str2 = "ABAB"
Output: "AB"

Example 3:

Input: str1 = "LEET", str2 = "CODE"
Output: ""

Note:

  1 <= str1.length <= 1000
  1 <= str2.length <= 1000
  str1[i] and str2[i] are English uppercase letters.
/*
  Submission Date: 2019-09-21
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  string gcdOfStrings(string str1, string str2) {
    /*
    Lyndon and Schützenberger states that A+B=B+A
    (commutative concatenation) iff A and B consist of a
    substring C where  C^i = C+...+C = A and C^j = C+...+C = B
    ie both strings are the powers of the same
    string
    */
    return str1 + str2 == str2 + str1
               ? str1.substr(0, gcd(str1.size(), str2.size()))
               : "";
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1078. Occurrences After Bigram
Given words first and second, consider occurrences in some text of the form
"first second third", where second comes immediately after first, and third
comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.

Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second
= "good"
Output: ["girl","student"]

Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]

Note:

  1 <= text.length <= 1000
  text consists of space separated words, where each word consists of lowercase
English letters.
  1 <= first.length, second.length <= 10
  first and second consist of lowercase English letters.
/*
  Submission Date: 2019-09-04
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
 public:
  // store the last two words and return the current word
  // if the last two words match `first`, `second`
  vector<string> findOcurrences(string text, string first, string second) {
    vector<string> res;
    stringstream ss(text);
    string token;
    string last, lastlast;
    while (ss >> token) {
      if (lastlast.empty()) {
        lastlast = token;
      } else if (last.empty()) {
        last = token;
      } else {
        if (lastlast == first && last == second) {
          res.push_back(token);
        }
        lastlast = last;
        last = token;
      }
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1089. Duplicate Zeros
Given a fixed length array arr of integers, duplicate each occurrence of zero,
shifting the remaining elements to the right.

Note that elements beyond the length of the original array are not written.

Do the above modifications to the input array in place, do not return anything
from your function.

Example 1:

Input: [1,0,2,3,0,4,5,0]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,0,0,2,3,0,0,4]

Example 2:

Input: [1,2,3]
Output: null
Explanation: After calling your function, the input array is modified to:
[1,2,3]

Note:

  1 <= arr.length <= 10000
  0 <= arr[i] <= 9
/*
  Submission Date: 2019-09-17
  Runtime: 20 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void duplicateZeros(vector<int>& arr) {
    /*
    two passes where i is the original arr index
    and j is the new arr index. stop when j >= N
    then go backwards and fill
    */
    int N = arr.size();
    int i = 0, j = 0;
    for (; i < N && j < N; i++) {
      j += (arr[i] == 0) ? 2 : 1;
    }

    while (i >= 0 && j >= 0) {
      i--;
      if (i >= 0) {
        if (arr[i] == 0) {
          if (j - 1 < N) arr[j - 1] = 0;
          if (j - 2 < N) arr[j - 2] = 0;
          j -= 2;
        } else {
          arr[j - 1] = arr[i];
          j--;
        }
      }
    }
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1103. Distribute Candies to People
We distribute some number of candies, to a row of n = num_people people in the
following way:

We then give 1 candy to the first person, 2 candies to the second person, and so
on until we give n candies to the last person.

Then, we go back to the start of the row, giving n + 1 candies to the first
person, n + 2 candies to the second person, and so on until we give 2 *
n candies to the last person.

This process repeats (with us giving one more candy each time, and moving to the
start of the row after we reach the end) until we run out of candies.  The last
person will receive all of our remaining candies (not necessarily one more than
the previous gift).

Return an array (of length num_people and sum candies) that represents the final
distribution of candies.

Example 1:

Input: candies = 7, num_people = 4
Output: [1,2,3,1]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0,0].
On the third turn, ans[2] += 3, and the array is [1,2,3,0].
On the fourth turn, ans[3] += 1 (because there is only one candy left), and the
final array is [1,2,3,1].

Example 2:

Input: candies = 10, num_people = 3
Output: [5,2,3]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0].
On the third turn, ans[2] += 3, and the array is [1,2,3].
On the fourth turn, ans[0] += 4, and the final array is [5,2,3].

Constraints:

  1 <= candies <= 10^9
  1 <= num_people <= 1000
/*
  Submission Date: 2019-09-08
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> distributeCandies(int candies, int num_people) {
    int i = 1, j = 0;
    vector<int> res(num_people, 0);
    while (candies) {
      i = min(candies, i);
      candies -= i;
      res[j] += i;
      i++;
      j = (j + 1) % num_people;
    }
    return res;
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1108. Defanging an IP Address
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

Example 1:
Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
Example 2:
Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"

Constraints:

  The given address is a valid IPv4 address.
/*
  Submission Date: 2019-08-25
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
 public:
  string defangIPaddr(string address) {
    istringstream ss(address);
    string res, token;
    string splitter = "[.]";
    while (getline(ss, token, '.')) {
      res += token + splitter;
    }
    return res.substr(0, res.size() - 3);
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1122. Relative Sort Array
Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all
elements in arr2 are also in arr1.

Sort the elements of arr1 such that the relative ordering of items in arr1 are
the same as in arr2.  Elements that don't appear in arr2 should be placed at the
end of arr1 in ascending order.

Example 1:
Input: arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
Output: [2,2,2,1,4,3,3,9,6,7,19]

Constraints:

  arr1.length, arr2.length <= 1000
  0 <= arr1[i], arr2[i] <= 1000
  Each arr2[i] is distinct.
  Each arr2[i] is in arr1.
/*
  Submission Date: 2019-09-03
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    unordered_map<int, int> arr2_to_ind;
    for (int i = 0; i < arr2.size(); i++) {
      arr2_to_ind[arr2[i]] = i;
    }

    auto end_it = arr2_to_ind.end();

    sort(arr1.begin(), arr1.end(),
         [&arr2_to_ind, &end_it](const int& left, const int& right) {
           auto left_it = arr2_to_ind.find(left);
           auto right_it = arr2_to_ind.find(right);
           if (left_it == end_it && right_it == end_it) {
             // ascending order
             return left < right;
           } else if (left_it == end_it) {
             // put the right in front as the left is not defined
             return false;
           } else if (right_it == end_it) {
             // put the left in front as the right is not defined
             return true;
           } else {
             // return the relative order of left, right
             return left_it->second < right_it->second;
           }
         });

    return arr1;
  }
};

int main() { return 0; }

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
