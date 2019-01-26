/*
443. String Compression
Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the
original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of
the array.


Follow up:
Could you solve it using only O(1) extra space?


Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be:
["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".
Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be:
["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is
replaced by "b12". Notice each digit has it's own entry in the array. Note: All
characters have an ASCII value in [35, 126]. 1 <= len(chars) <= 1000.
/*
    Submission Date: 2018-06-24
    Runtime: 9 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  /*
  since length of 1 are not included the compressed string will always be less
  than the full string e.g a12 is smaller than aaa... hence it is safe to just
  overwrite existing string
  */
  int compress(vector<char>& s) {
    int write = 0;
    int N = s.size();
    for (int i = 0; i < N;) {
      int start = i;
      while (i < N && s[start] == s[i]) i++;
      string freq = to_string(i - start);
      s[write++] = s[start];
      if (i - start > 1)
        for (const auto& d : freq) s[write++] = d;
    }
    return write;
  }
};

int main() { return 0; }