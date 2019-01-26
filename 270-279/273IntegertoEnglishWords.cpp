/*
273. Integer to English Words
Convert a non-negative integer to its english words representation. Given input
is guaranteed to be less than 2^31 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
Seven"

/*
    Submission Date: 2017-08-12
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string numberToWords(int num) {
    if (num == 0) return "Zero";

    vector<pair<int, string>> val_to_str{
        {1e9, "Billion"}, {1e6, "Million"}, {1e3, "Thousand"}, {1e2, "Hundred"},
        {90, "Ninety"},   {80, "Eighty"},   {70, "Seventy"},   {60, "Sixty"},
        {50, "Fifty"},    {40, "Forty"},    {30, "Thirty"},    {20, "Twenty"},
        {19, "Nineteen"}, {18, "Eighteen"}, {17, "Seventeen"}, {16, "Sixteen"},
        {15, "Fifteen"},  {14, "Fourteen"}, {13, "Thirteen"},  {12, "Twelve"},
        {11, "Eleven"},   {10, "Ten"},      {9, "Nine"},       {8, "Eight"},
        {7, "Seven"},     {6, "Six"},       {5, "Five"},       {4, "Four"},
        {3, "Three"},     {2, "Two"},       {1, "One"}};

    string res = "";
    function<string(string, string)> add = [](const string& a,
                                              const string& b) {
      return a.empty() ? b : a + " " + b;
    };

    while (num) {
      for (auto p : val_to_str) {
        if (num == 0) break;
        if (num >= p.first) {
          int to_change = num / p.first;
          if (to_change == 1 && p.first < 1e2) {
            res = add(res, p.second);
            if (num == p.first) {
              num = 0;
              break;
            }
          } else {
            res = add(add(res, numberToWords(to_change)), p.second);
          }
          num %= p.first;
        }
      }
    }
    return res;
  }
};

int main() { return 0; }