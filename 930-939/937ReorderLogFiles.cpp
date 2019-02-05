/*
937. Reorder Log Files
You have an array of logs.  Each log is a space delimited string of words.

For each log, the first word in each log is an alphanumeric identifier.  Then,
either:

  Each word after the identifier will consist only of lowercase letters, or;
  Each word after the identifier will consist only of digits.

We will call these two varieties of logs letter-logs and digit-logs.  It is
guaranteed that each log has at least one word after its identifier.

Reorder the logs so that all of the letter-logs come before any digit-log.  The
letter-logs are ordered lexicographically ignoring identifier, with the
identifier used in case of ties.  The digit-logs should be put in their original
order.

Return the final order of the logs.

Example 1:

Input: ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
Output: ["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"]

Note:

  0 <= logs.length <= 100
  3 <= logs[i].length <= 100
  logs[i] is guaranteed to have an identifier, and a word after the identifier.
/*
  Submission Date: 2019-02-05
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> reorderLogFiles(vector<string>& logs) {
    // move digit logs to the back
    int i = logs.size() - 1;
    for (int j = logs.size() - 1; j >= 0; j--) {
      size_t first_space_ind = logs[j].find(' ');
      if (isdigit(logs[j][first_space_ind + 1])) {
        swap(logs[i--], logs[j]);
      }
    }

    // sort the letter logs
    sort(logs.begin(), logs.begin() + i + 1,
         [](const string& lhs, const string& rhs) {
           size_t lhs_ind = lhs.find(' ');
           size_t rhs_ind = rhs.find(' ');
           string lhs_sub = lhs.substr(lhs_ind + 1);
           string rhs_sub = rhs.substr(rhs_ind + 1);
           if (lhs_sub == rhs_sub)
             return lhs.substr(0, lhs_ind) < rhs.substr(0, rhs_ind);
           return lhs_sub < rhs_sub;
         });
    return logs;
  }
};

int main() { return 0; }
