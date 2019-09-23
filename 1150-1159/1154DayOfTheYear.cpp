/*
1154. Day of the Year
Given a string date representing a Gregorian calendar date formatted as
YYYY-MM-DD, return the day number of the year.

Example 1:

Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.

Example 2:

Input: date = "2019-02-10"
Output: 41

Example 3:

Input: date = "2003-03-01"
Output: 60

Example 4:

Input: date = "2004-03-01"
Output: 61

Constraints:

  date.length == 10
  date[4] == date[7] == '-', and all other date[i]'s are digits
  date represents a calendar date between Jan 1st, 1900 and Dec 31, 2019.
/*
  Submission Date: 2019-09-23
  Runtime: 4 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
 public:
  int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  }
  int dayOfYear(string date) {
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8));
    bool is_leap_year = isLeapYear(year);
    int res = 0;
    for (int i = 0; i < month - 1; i++) {
      res += days_in_month[i];
    }
    return res + day + (is_leap_year && month > 2);
  }
};

int main() { return 0; }
