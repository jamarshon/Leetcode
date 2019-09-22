
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1185. Day of the Week
Given a date, return the corresponding day of the week for that date.

The input is given as three integers representing the day, month and year
respectively.

Return the answer as one of the following values {"Sunday", "Monday", "Tuesday",
"Wednesday", "Thursday", "Friday", "Saturday"}.

Example 1:

Input: day = 31, month = 8, year = 2019
Output: "Saturday"

Example 2:

Input: day = 18, month = 7, year = 1999
Output: "Sunday"

Example 3:

Input: day = 15, month = 8, year = 1993
Output: "Sunday"

Constraints:

  The given dates are valid dates between the years 1971 and 2100.
/*
  Submission Date: 2019-09-08
  Runtime: 0 ms
  Difficulty: EASY
*/
#include <iostream>

using namespace std;

class Solution {
  string days[7] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                    "Friday", "Saturday", "Sunday"};

  int reference_year = 1900;
  bool IsLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
  }

  int month_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

 public:
  string dayOfTheWeek(int day, int month, int year) {
    int diff_year = year - reference_year;
    // the number of days from full years
    int diff_common_days = diff_year * 365;

    // the number of leap days from full years
    // leap years are divisible 4 unless it is divisible by 100 where
    // it has to be divisible by 400 (i.e. 2000)
    int diff_leap_days =
        (diff_year - 1) / 4 - (diff_year - 1) / 100 + (year > 2000);
    int diff_days = diff_common_days + diff_leap_days;

    // days from the number of months
    bool is_leap_year = IsLeapYear(year);
    for (int i = 0; i < month - 1; i++) {
      diff_days += month_days[i] + (is_leap_year && i == 1);
    }

    // days from the number of days in this month
    diff_days += day - 1;

    // jan 1, 1900 is a monday so do modulo
    return days[diff_days % 7];
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
1189. Maximum Number of Balloons
Given a string text, you want to use the characters of text to form as many
instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of
instances that can be formed.

Example 1:

Input: text = "nlaebolko"
Output: 1

Example 2:

Input: text = "loonbalxballpoon"
Output: 2

Example 3:

Input: text = "leetcode"
Output: 0

Constraints:

  1 <= text.length <= 10^4
  text consists of lower case English letters only.
/*
  Submission Date: 2019-09-17
  Runtime: 8 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
  string target = "balloon";
  unordered_map<char, int> target_freq;

 public:
  Solution() {
    for (const auto& c : target) target_freq[c]++;
  }

  // count the frequency of chars in text and then
  // count the frequency of chars in target
  // for all the characters in target,
  // if it does not exist in text, then return 0
  // as a target letter is not present
  // else take the minimum of the frequency in the
  // text divide by the frequency in the target
  int maxNumberOfBalloons(string text) {
    unordered_map<char, int> freq;
    for (const auto& c : text) freq[c]++;
    int res = INT_MAX;
    for (const auto& c : target) {
      if (!freq.count(c)) return 0;
      res = min(res, freq[c] / target_freq[c]);
    }
    return res;
  }
};

int main() { return 0; }
