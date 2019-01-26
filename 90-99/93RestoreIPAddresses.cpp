/*
93. Restore IP Addresses
Given a string containing only digits, restore it by returning all possible
valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

/*
    Submission Date: 2017-06-28
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void restoreIpAddressesHelper(string rem, string curr, int periods,
                                vector<string>& res) {
    if (periods == 4) {
      if (rem.empty()) {
        res.push_back(curr);
      }
      return;
    }

    int len = rem.size();

    if (len == 0) return;

    if (!curr.empty()) curr += '.';

    string first_substr = rem.substr(0, 1);
    restoreIpAddressesHelper(rem.substr(1), curr + first_substr, periods + 1,
                             res);

    if (len > 1) {
      string second_substr = rem.substr(0, 2);
      if (stoi(second_substr) >= 10) {
        restoreIpAddressesHelper(rem.substr(2), curr + second_substr,
                                 periods + 1, res);
      }
    }

    if (len > 2) {
      string third_substr = rem.substr(0, 3);
      if (stoi(third_substr) >= 100 && stoi(third_substr) <= 255) {
        restoreIpAddressesHelper(rem.substr(3), curr + third_substr,
                                 periods + 1, res);
      }
    }
  }

  vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    restoreIpAddressesHelper(s, "", 0, res);
    return res;
  }
};

int main() {
  Solution s;
  return 0;
}