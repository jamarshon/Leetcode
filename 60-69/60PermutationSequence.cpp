/*
60. Permutation Sequence

The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

/*
    Submission Date: 2017-06-24
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<int, int> combinations{
      {0, 1},   {1, 1},   {2, 2},    {3, 6},     {4, 24},
      {5, 120}, {6, 720}, {7, 5040}, {8, 40320}, {9, 362880}};

 public:
  string getPermutation(vector<char>& available, int n, int k, int comb_index) {
    if (available.empty()) return "";

    int index = (k - 1) / combinations[comb_index];
    char leading_char = available[index];
    available.erase(available.begin() + index);

    k -= index * combinations[comb_index];

    return string(1, leading_char) +
           getPermutation(available, n, k, comb_index - 1);
  }
  string getPermutation(int n, int k) {
    vector<char> available;

    char target = '0' + n;
    for (char i = '1'; i <= target; i++) {
      available.push_back(i);
    }

    return getPermutation(available, n, k, n - 1);
  }
};

int main() {
  Solution s;
  for (int i = 1; i <= 6; i++) cout << s.getPermutation(3, i) << endl;
  return 0;
}