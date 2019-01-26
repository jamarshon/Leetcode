/*
38. Count and Say
The count-and-say sequence is the sequence of integers with the first five terms
as following:

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
    if (n == 1) return "1";
    string prev = countAndSay(n - 1);
    int len = prev.size();
    string res = "";
    for (int i = 0; i < len; i++) {
      int j = i + 1;
      for (; j < len; j++) {
        if (prev[i] != prev[j]) {
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

int main() { return 0; }