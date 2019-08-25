/*
1108. Defanging an IP Address
Given a valid (IPv4) IP address, return a defanged version of that IP address.

A defanged IP address replaces every period "." with "[.]".

Example 1:
Input: address = "1.1.1.1"
Output: "1[.]1[.]1[.]1"
Example 2:
Input: address = "255.100.50.0"
Output: "255[.]100[.]50[.]0"

Constraints:

  The given address is a valid IPv4 address.
/*
  Submission Date: 2019-08-25
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
 public:
  string defangIPaddr(string address) {
    istringstream ss(address);
    string res, token;
    string splitter = "[.]";
    while (getline(ss, token, '.')) {
      res += token + splitter;
    }
    return res.substr(0, res.size() - 3);
  }
};

int main() { return 0; }
