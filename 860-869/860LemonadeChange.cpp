/*
860. Lemonade Change
At a lemonade stand, each lemonade costs $5. 

Customers are standing in a queue to buy from you, and order one at a time 
(in the order specified by bills).

Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.  
You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

Note that you don't have any change in hand at first.

Return true if and only if you can provide every customer with correct change.

 

Example 1:

Input: [5,5,5,10,20]
Output: true
Explanation: 
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.
Example 2:

Input: [5,5,10]
Output: true
Example 3:

Input: [10,10]
Output: false
Example 4:

Input: [5,5,10,10,20]
Output: false
Explanation: 
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can't give change of $15 back because we only have two $10 bills.
Since not every customer received correct change, the answer is false.
 

Note:

0 <= bills.length <= 10000
bills[i] will be either 5, 10, or 20.
/*
    Submission Date: 2018-07-01
    Runtime: 30 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        // change[0] is number of 5's and change[1] is number of 10's.
        // 20's will never be given back so no need to count them.
        vector<int> change(2, 0);
        for(const auto& e: bills) {
            if(e == 5) {
                change[0]++;
            } else if(e == 10) { // can only give a 5 back
                if(change[0] == 0) return false;
                change[0]--;
                change[1]++;
            } else { // e == 20 can give back either 5 and 10 or 3 fives
                if(change[1] > 0 && change[0] > 0) { // try to give back the 10 first as it is less useful
                    change[1]--;
                    change[0]--;
                } else if(change[0] >= 3) {
                    change[0] -= 3;
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};

int main() {
    return 0;
}