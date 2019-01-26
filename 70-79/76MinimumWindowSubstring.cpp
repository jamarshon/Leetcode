/*
76. Minimum Window Substring
Given a string S and a string T, find the minimum window in S which will contain
all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the
empty string "".

If there are multiple such windows, you are guaranteed that there will always be
only one unique minimum window in S.

/*
    Submission Date: 2017-06-23
    Runtime: 86 ms
    Difficulty: HARD
*/

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    list<int> l;
    unordered_map<char, list<list<int>::iterator>> m;
    unordered_map<char, int> dict;

    for (auto c : t) dict[c]++;

    int len = s.size();
    int target = t.size();
    string res = "";

    for (int i = 0; i < len; i++) {
      // check if current character is in t
      if (dict.count(s[i])) {
        auto it = m.find(s[i]);

        // check if there is a list for this letter
        if (it != m.end()) {
          list<list<int>::iterator>& list_of_list_it = it->second;
          // if there is a list and its size is same as the frequency we must
          // remove the first element from the list and the iterator from the
          // map
          if (list_of_list_it.size() == dict[s[i]]) {
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
        if (l.size() == target) {
          string sub = s.substr(l.front(), i - l.front() + 1);
          if (res.empty() || sub.size() < res.size()) res = sub;
        }
      }
    }

    return res;
  }
};

int main() { return 0; }