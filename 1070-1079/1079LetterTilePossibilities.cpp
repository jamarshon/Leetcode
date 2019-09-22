/*
1079. Letter Tile Possibilities
You have a set of tiles, where each tile has one letter tiles[i] printed on it. 
Return the number of possible non-empty sequences of letters you can make.

Example 1:

Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
"ABA", "BAA".

Example 2:

Input: "AAABBC"
Output: 188

Note:

  1 <= tiles.length <= 7
  tiles consists of uppercase English letters.
/*
  Submission Date: 2019-09-21
  Runtime: 52 ms
  Difficulty: MEDIUM
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int f(vector<int>& count) {
    int sum = 0;
    for (int i = 0; i < 26; i++) {
      // no letters here
      if (count[i] == 0) continue;
      // use this letter
      sum++;
      count[i]--;
      sum += f(count);
      count[i]++;
    }
    return sum;
  }
  int numTilePossibilities(string tiles) {
    vector<int> count(26, 0);
    for (const auto& c : tiles) count[c - 'A']++;
    return f(count);
  }
};

class Solution2 {
 public:
  void f(const string& tiles, const int& index, const string& curr,
         unordered_set<string>& comb) {
    if (!curr.empty()) {
      comb.insert(curr);
    }
    if (index >= tiles.size()) return;

    // use this letter by putting it any of the positions of curr
    for (int i = 0; i <= curr.size(); i++) {
      f(tiles, index + 1, curr.substr(0, i) + tiles[index] + curr.substr(i),
        comb);
    }
    // ignore this letter
    f(tiles, index + 1, curr, comb);
  }
  int numTilePossibilities(string tiles) {
    unordered_set<string> comb;
    f(tiles, 0, "", comb);
    // for(auto e: comb) cout << e << endl;
    return comb.size();
  }
};

int main() { return 0; }
