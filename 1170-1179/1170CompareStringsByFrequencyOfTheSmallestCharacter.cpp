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
