/*
825. Friends Of Appropriate Ages
Some people will make friend requests. The list of their ages is given and ages[i] 
is the age of the ith person. 

Person A will NOT friend request person B (B != A) if any of the following conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will not 
friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.
/*
    Submission Date: 2018-06-29
    Runtime: 39 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    1 <= ages[i] <= 120
    so have a[i] be the frequency of age i
    for an age i, there should be an age j <= i which can be friends with
    j > 0.5*i + 7     ie. j = 0.5*i + 8
    j must be !(j > 100 && i < 100) note this will never occur as j <= i
    
    so for every person of age i (a[i]) and every person of age j (a[j])
    there can be a[j] * a[i] friend requests made as for a person in j
    can make friend with every person in i (a[i] times) and there are a[j] of these people
    
    if j == i, then it is a[i] * (a[i] - 1) as every person in i 
    can make friends with a[i] - 1 people as they cannot make friends with themself
    */
    int numFriendRequests(vector<int>& ages) {
        vector<int> a(121, 0);
        
        for(const auto& e: ages) a[e]++;
        
        int res = 0;
        for(int i = 1; i < 121; i++) {
            for(int j = 0.5*i + 8; j <= i; j++) res += a[j] * (a[i] - (i == j));
        }
        
        return res;
    }
};

int main() {
    return 0;
}