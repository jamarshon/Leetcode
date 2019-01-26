/*
282. Expression Add Operators
Given a string that contains only digits 0-9 and a target value, return all
possibilities to add binary operators (not unary) +, -, or * between the digits
so they evaluate to the target value.

Examples:
"123", 6 -> ["1+2+3", "1*2*3"]
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

/*
    Submission Date: 2017-08-12
    Runtime: 59 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void getOperators(string num, int index, int target, string curr, int val,
                    string curr_product, int product, vector<string>& res) {
    int N = num.size();
    if (index == N) {  // no more numbers to process
      if (curr.empty()) {
        // result just contains multiplication curr="" curr_product="ab*c*de" ->
        // "ab*c*de"
        if (product == target) res.push_back(curr_product);
      } else {
        // try add/subtract product to current and see if it reaches target
        // e.g curr = "ab*c*de + f - g*hi"
        // curr_product = "jk*lmn*qr" -> "ab*c*de + f - g*hi - jk*lmn*qr"
        // or "ab*c*de + f - g*hi + jk*lmn*qr". curr_product could just be one
        // number like "qrs"
        if (val - product == target) res.push_back(curr + "-" + curr_product);
        if (val + product == target) res.push_back(curr + "+" + curr_product);
      }
      return;
    }

    int sub_val = num[index] - '0';
    for (int i = index + 1; i <= N; i++) {
      string sub = num.substr(index, i - index);

      // either continue product
      if (!curr_product.empty()) {
        getOperators(num, i, target, curr, val, curr_product + "*" + sub,
                     product * sub_val, res);
      }

      // end product and add or subtract it
      if (!curr.empty()) {
        getOperators(num, i, target, curr + "-" + curr_product, val - product,
                     sub, sub_val, res);
      }

      string new_curr = curr.empty() ? curr_product : curr + "+" + curr_product;
      getOperators(num, i, target, new_curr, val + product, sub, sub_val, res);

      // cannot process multiple zeros e.g 000 + xyz, 0xy or 000*xy is not valid
      // must be single zeros and no leading zeros
      if (num[index] == '0') break;

      // check for overflow of sub_val
      int char_val = num[i] - '0';
      if (sub_val > (INT_MAX - char_val) / 10) break;

      sub_val = sub_val * 10 + char_val;
    }
  }

  vector<string> addOperators(string num, int target) {
    vector<string> res;
    getOperators(num, 0, target, "", 0, "", 0, res);
    return res;
  }
};

int main() { return 0; }