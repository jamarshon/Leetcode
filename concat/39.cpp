
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
929. Unique Email Addresses
Every email consists of a local name and a domain name, separated by the @ sign.

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is
the domain name.

Besides lowercase letters, these emails may contain '.'s or '+'s.

If you add periods ('.') between some characters in the local name part of an
email address, mail sent there will be forwarded to the same address without
dots in the local name.  For example, "alice.z@leetcode.com" and
"alicez@leetcode.com" forward to the same email address.  (Note that this rule
does not apply for domain names.)

If you add a plus ('+') in the local name, everything after the first plus sign
will be ignored. This allows certain emails to be filtered, for
example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule
does not apply for domain names.)

It is possible to use both of these rules at the same time.

Given a list of emails, we send one email to each address in the list.  How many
different addresses actually receive mails? 

Example 1:

Input:
["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually
receive mails

Note:

  1 <= emails[i].length <= 100
  1 <= emails.length <= 100
  Each emails[i] contains exactly one '@' character.
/*
  Submission Date: 2019-01-26
  Runtime: 40 ms
  Difficulty: EASY
*/
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int numUniqueEmails(vector<string>& emails) {
    unordered_set<string> uniq_emails;

    for (const auto& email : emails) {
      size_t at_ind = email.find('@');
      if (at_ind == string::npos) return -1;
      string res = "";
      for (int i = 0; i < at_ind; i++) {
        if (email[i] == '.') continue;
        if (email[i] == '+') break;
        res.push_back(email[i]);
      }

      for (int i = at_ind + 1; i < email.size(); i++) {
        res.push_back(email[i]);
      }

      uniq_emails.insert(res);
    }

    return uniq_emails.size();
  }
};

int main() { return 0; }

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
933. Number of Recent Calls
Write a class RecentCounter to count recent requests.

It has only one method: ping(int t), where t represents some time in
milliseconds.

Return the number of pings that have been made from 3000 milliseconds ago until
now.

Any ping with time in [t - 3000, t] will count, including the current ping.

It is guaranteed that every call to ping uses a strictly larger value of t than
before.

Example 1:

Input: inputs = ["RecentCounter","ping","ping","ping","ping"], inputs =
[[],[1],[100],[3001],[3002]]
Output: [null,1,2,3,3]

Note:

  Each test case will have at most 10000 calls to ping.
  Each test case will call ping with strictly increasing values of t.
  Each call to ping will have 1 <= t <= 10^9.
/*
  Submission Date: 2019-01-26
  Runtime: 252 ms
  Difficulty: EASY
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef priority_queue<int, vector<int>, greater<int>> MinHeap;
class RecentCounter {
  MinHeap heap;

 public:
  RecentCounter() {}

  int ping(int t) {
    while (!heap.empty() && heap.top() < t - 3000) {
      heap.pop();
    }
    heap.push(t);
    return heap.size();
  }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

int main() { return 0; }
