
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
260. Single Number III
Given an array of numbers nums, in which exactly two elements 
appear only once and all the other elements appear exactly twice. 
Find the two elements that appear only once.

For example:

Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].

Note:
The order of the result is not important. So in the above example, 
[5, 3] is also correct.
Your algorithm should run in linear runtime complexity. Could you 
implement it using only constant space complexity?
/*
    Submission Date: 2017-08-23
    Runtime: 23 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // 1, 2, 1, 3, 2, 5 -> 3 ^ 5 = 011 ^ 101 = 110
        int xor_all = 0; // x ^ y
        for(auto num: nums) xor_all ^= num;
        
        // lsb of 110 is 010 so xor all number that has this bit set
        // 2 ^ 2 ^ 3 = 010 ^ 010 ^ 011 = 011
        int lsb = xor_all & ~(xor_all-1);
        int xor_same_lsb = 0;
        for(auto num: nums) {
            if(num & lsb) xor_same_lsb ^= num;
        }
        
        // xor_same_lsb is x and xor_all ^ x = (x ^ y) ^ x = y
        int x = xor_same_lsb;
        int y = xor_all ^ x;
        return {x,y};
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
263. Ugly Number
Write a program to check whether a given number is an ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
For example, 6, 8 are ugly while 14 is not ugly since it includes another prime factor 7.

Note that 1 is typically treated as an ugly number.

/*
    Submission Date: 2017-08-06
    Runtime: 6 ms
    Difficulty: EASY
*/

#include <iostream>

using namespace std;

class Solution {
public:
    bool isUgly2(int num) {
        if(num <= 0) return false;
        if(num == 1) return true;

        if(num % 2 == 0) return isUgly(num / 2);
        if(num % 3 == 0) return isUgly(num / 3);
        if(num % 5 == 0) return isUgly(num / 5);
        
        return false;
    }

    bool isUgly(int num) {
        if(num <= 0) return false;

        int primes[3] = {2,3,5};
        for(int i = 0; i < 3; i++) {
            while(num % primes[i] == 0) {
                num /= primes[i];
            }
        }

        return num == 1;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
264. Ugly Number II
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only 
include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 
is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n 
does not exceed 1690.
/*
    Submission Date: 2017-08-23
    Runtime: 36 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        typedef long long ll;
        typedef pair<ll,ll> pll;

        // pair where first is value and second is the minimum permissable
        // index for arr

        // we keep track of the smallest value using min heap and
        // remove the value to add smallest*arr[i] for i from index to 3
        // the index keeps track of allowable factors as 2*2*3 and
        // 3*2*2 is the same so by only keeping factors in increasing
        // order we can avoid duplicates
        // when n - 1 elements are removed then the top of the min heap
        // is the answer
        auto cmp = [](const pll& lhs, const pll& rhs) {
            return lhs.first == rhs.first ? lhs.second > rhs.second : lhs.first > rhs.first;
        };

        priority_queue<pll, vector<pll>, decltype(cmp)> pq(cmp);
        pq.emplace(1,0);

        int removed = 0;
        ll arr[3] = {2, 3, 5};
        while(removed < n - 1) {
            pll top = pq.top();
            pq.pop();

            for(int i = top.second; i < 3; i++) {
                pq.emplace(top.first*arr[i], i);
            }
            removed++;
        }

        return pq.top().first;
    }
};

int main() {
    Solution s;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
268. Missing Number
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, 
find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you implement 
it using only constant extra space complexity?

/*
    Submission Date: 2017-08-12
    Runtime: 29 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        int N = nums.size();
        for(int i = 1; i <= N; i++) {
            res ^= i;
            res ^= nums[i-1];
        }
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
273. Integer to English Words
Convert a non-negative integer to its english words representation. Given input is 
guaranteed to be less than 2^31 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

/*
    Submission Date: 2017-08-12
    Runtime: 16 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    string numberToWords(int num) {
        if(num == 0) return "Zero";
        
        vector<pair<int, string>> val_to_str{
            {1e9, "Billion"}, {1e6, "Million"}, {1e3, "Thousand"}, {1e2, "Hundred"},
            {90, "Ninety"}, {80, "Eighty"}, {70, "Seventy"}, {60, "Sixty"}, {50, "Fifty"},
            {40, "Forty"}, {30, "Thirty"}, {20, "Twenty"}, {19, "Nineteen"}, {18, "Eighteen"},
            {17, "Seventeen"}, {16, "Sixteen"}, {15, "Fifteen"}, {14, "Fourteen"}, {13, "Thirteen"},
            {12, "Twelve"}, {11, "Eleven"}, {10, "Ten"}, {9, "Nine"}, {8, "Eight"}, {7, "Seven"},
            {6, "Six"}, {5, "Five"}, {4, "Four"}, {3, "Three"}, {2, "Two"}, {1, "One"}
        };

        string res = "";
        function<string(string, string)> add = [](const string& a, const string& b){
            return a.empty() ? b : a + " " + b;
        };

        while(num) {
            for(auto p: val_to_str) {
                if(num == 0) break;
                if(num >= p.first) {
                    int to_change = num / p.first;
                    if(to_change == 1 && p.first < 1e2) {
                        res = add(res, p.second);
                        if(num == p.first) {
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

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
274. H-Index
Given an array of citations (each citation is a non-negative integer) 
of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has 
index h if h of his/her N papers have at least h citations each, and 
the other N − h papers have no more than h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the 
researcher has 5 papers in total and each of them had received 
3, 0, 6, 1, 5 citations respectively. Since the researcher has 
3 papers with at least 3 citations each and the remaining two 
with no more than 3 citations each, his h-index is 3.

Note: If there are several possible values for h, the maximum one 
is taken as the h-index.
/*
    Submission Date: 2017-08-26
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
    3, 0, 6, 1, 5 -> 0, 1, 3, 5, 6
                i    0, 1, 2, 3, 4
              N - i  5, 4, 3, 2, 1  
    h index is choose index from [0,n] such that
    h elements have citations >= h and N - h have citations < h

    Bucket sort
    bucket[i] for i = [0,n) indicates frequency of value i
    in citations. bucket[n] indications frequency of value >= n
    in citations.

    sum[i] shows how many element are greater than or equal to
    i so if sum[i] >= i then h = i as there are sum[i] elements
    greater than or equal to i and N - i elements smaller than
    i.

    3, 0, 6, 1, 5

    buckets
    0 1 2 3 4 5
    1 1 0 1 0 2

    sum   5 4 3 3 2 2  
    index 0 1 2 3 4 5 
    */
    int hIndex(vector<int>& citations) {
        int N = citations.size();

        vector<int> bucket(N + 1, 0);
        for(auto c: citations) {
            // if citation greater than N just use N
            // else increase bucket[c]
            bucket[min(c, N)]++; 
        }

        int sum = 0;
        for(int i = N; i >= 0; i--) {
            sum += bucket[i];
            if(sum >= i) return i;
        }

        return 0;
    }
};

int main() {
    Solution s;
    vector<int> v{3, 0, 6, 1, 5};
    cout << s.hIndex(v) << endl;
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
275. H-Index II
Follow up for H-Index: What if the citations array is sorted in 
ascending order? Could you optimize your algorithm?
/*
    Submission Date: 2017-08-30
    Runtime: 192 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    3, 0, 6, 1, 5 -> 0, 1, 3, 5, 6
                i    0, 1, 2, 3, 4
              N - i  5, 4, 3, 2, 1  
    h index is choose index from [0,n] such that
    h elements have citations >= h and N - h have citations < h

    sort and see if citations[i] >= N - i as N - i is the number
    of elements that are greater than or equal to this element
    from [i,N). Since it is sorted, i elements are less than citations[i].
    If citations[i] is greater than N - i, it means
    h = N - i as h elements [i, N) have citations[i] >= h 
    and h elements [0, i) have citations[i] < h
    */
    int hIndex(vector<int>& citations) {
        int N = citations.size();
        for(int i = 0; i < N; i++) {
            if(citations[i] >= N - i) {
                return N - i;
            }
        }
        return 0;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
278. First Bad Version
You are a product manager and currently leading a team to develop a new product. 
Unfortunately, the latest version of your product fails the quality check. 
Since each version is developed based on the previous version, all the 
versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, 
which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is 
bad. Implement a function to find the first bad version. You should minimize the 
number of calls to the API.

/*
    Submission Date: 2017-08-12
    Runtime: 46 ms
    Difficulty: EASY
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1;
        int high = n;
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(isBadVersion(mid)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
279. Perfect Squares
Given a positive integer n, find the least number of perfect square numbers 
(for example, 1, 4, 9, 16, ...) which sum to n.

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, 
return 2 because 13 = 4 + 9.

/*
    Submission Date: 2017-08-12
    Runtime: 59 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        if(n == 0) return 0;
        int sq = sqrt(n);
        vector<int> dp(n + 1);

        iota(dp.begin(), dp.end(), 0);

        // dp[i][j] means minimum number using [0,i] squares for the number j
        // dp[i][j] = min(
        //              dp[i-1][j], // we don't use this square
        //              dp[i][j-i*i] // we use this square )
        // since we only use the previous row, just save space with 1d vector
        for(int i = 2; i <= sq; i++) {
            for(int j = 1; j <= n; j++) {
                int r = j - i*i;
                if(r >= 0) {
                    dp[j] = min(dp[j], dp[r] + 1);
                }
            }
        }

        return dp[n];
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
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
    void getOperators(string num, int index, int target, 
                        string curr, int val, 
                        string curr_product, int product, vector<string>& res) {

        int N = num.size();
        if(index == N) { // no more numbers to process
            if(curr.empty()) { 
                // result just contains multiplication curr="" curr_product="ab*c*de" -> "ab*c*de" 
                if(product == target) res.push_back(curr_product);
            } else {
                // try add/subtract product to current and see if it reaches target
                // e.g curr = "ab*c*de + f - g*hi" 
                // curr_product = "jk*lmn*qr" -> "ab*c*de + f - g*hi - jk*lmn*qr" 
                // or "ab*c*de + f - g*hi + jk*lmn*qr". curr_product could just be one number like "qrs"
                if(val - product == target) res.push_back(curr + "-" + curr_product);  
                if(val + product == target) res.push_back(curr + "+" + curr_product);
            }
            return;
        }

        int sub_val = num[index] - '0';
        for(int i = index + 1; i <= N; i++) {
            string sub = num.substr(index, i - index);

            // either continue product
            if(!curr_product.empty()) {
                getOperators(num, i, target, curr, val, 
                                        curr_product + "*" + sub, product * sub_val, res);
            }

            // end product and add or subtract it
            if(!curr.empty()) {
                getOperators(num, i, target, curr + "-" + curr_product, val - product, 
                                        sub, sub_val, res);
            }

            string new_curr = curr.empty() ? curr_product : curr + "+" + curr_product;
            getOperators(num, i, target, new_curr, val + product, 
                                        sub, sub_val, res);

            // cannot process multiple zeros e.g 000 + xyz, 0xy or 000*xy is not valid must be 
            // single zeros and no leading zeros
            if(num[index] == '0') break;

            // check for overflow of sub_val
            int char_val = num[i] - '0';
            if(sub_val > (INT_MAX - char_val)/10) break; 

            sub_val = sub_val*10 + char_val;
        }
    }

    vector<string> addOperators(string num, int target) {
        vector<string> res;
        getOperators(num, 0, target, "", 0, "", 0, res);
        return res;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
283. Move Zeroes
Given an array nums, write a function to move all 0's to the end 
of it while maintaining the relative order of the non-zero elements.

For example, given nums = [0, 1, 0, 3, 12], after calling your 
function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.

/*
    Submission Date: 2017-08-30
    Runtime: 16 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int N = nums.size();
        int read_idx = 0, write_idx = 0;
        while(read_idx < N) {
            if(nums[read_idx] != 0) {
                nums[write_idx] = nums[read_idx];
                write_idx++;
            }
            read_idx++;
            
        }
        
        while(write_idx < N) nums[write_idx++] = 0;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
284. Peeking Iterator
Given an Iterator class interface with methods: next() and hasNext(), 
design and implement a PeekingIterator that support the peek() 
operation -- it essentially peek() at the element that will be 
returned by the next call to next().

Here is an example. Assume that the iterator is initialized to the 
beginning of the list: [1, 2, 3].

Call next() gets you 1, the first element in the list.

Now you call peek() and it returns 2, the next element. Calling 
next() after that still return 2.

You call next() the final time and it returns 3, the last element. 
Calling hasNext() after that should return false.

Follow up: How would you extend your design to be generic and work 
with all types, not just integer?
/*
    Submission Date: 2017-08-30
    Runtime: 3 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
    Iterator* it_;
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        it_ = new Iterator(nums);
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        assert(hasNext());
        Iterator* temp = new Iterator(*it_);
        int res = it_ -> next();
        delete it_;
        it_ = temp;
        return res;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        assert(hasNext());
        return it_ -> next();
    }

    bool hasNext() const {
        return it_ -> hasNext();
    }
};

class PeekingIterator2 : public Iterator {
    int prev_;
    bool remaining_;
    Iterator* it_;
public:
    PeekingIterator2(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        it_ = new Iterator(nums);
        remaining_ = it_ -> hasNext();
        if(remaining_) {
            prev_ = it_ -> next();
        }
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        return prev_;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        int res = prev_;
        remaining_ = it_ -> hasNext();
        if(remaining_) prev_ = it_ -> next();
        return res;
    }

    bool hasNext() const {
        return remaining_;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
287. Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is 
between 1 and n (inclusive), prove that at least one duplicate number 
must exist. Assume that there is only one duplicate number, find the 
duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n^2).
There is only one duplicate number in the array, but it could be 
repeated more than once.
/*
    Submission Date: 2017-08-30
    Runtime: 12 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        Find beginning of cycle of linked list. nums[i] represents
        node i has a link to node nums[i]. since nums[i] is [1,n]
        it means it will always have a link to an element in the 
        array. there are n+1 numbers and they span from [1,n] so
        a duplicate must exist eg n = 2 -> 1,2,_ . 
        pigeonhole principle states that if n items are put into m 
        containers, with n > m, then at least one container must 
        contain more than one item. 
        a cycle will occur as two numbers point to the same index
        one number going into the cycle and the second completing
        the cycle e.g [1,3,4,2,2] ->
        indices 0 -> 1 -> 3 -> 2 -> 4 -> 2
        values  1 -> 3 -> 2 -> 4 -> 2 -> 4
        0 can't be the start of the cycle as there is no number
        going into the cycle (index 0) meaning this method won't work 
        (the guarantee of nums[i] between [1,n] must exist).
    */
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while(slow != fast);
        
        slow = 0;
        while(slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
289. Game of Life
According to the Wikipedia's article: "The Game of Life, also known 
simply as Life, is a cellular automaton devised by the British 
mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live 
(1) or dead (0). Each cell interacts with its eight neighbors 
(horizontal, vertical, diagonal) using the following four rules 
(taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused 
by under-population.
Any live cell with two or three live neighbors lives on to the next 
generation.
Any live cell with more than three live neighbors dies, as if by 
over-population..
Any dead cell with exactly three live neighbors becomes a live cell, 
as if by reproduction.
Write a function to compute the next state (after one update) of the 
board given its current state.

Follow up: 
Could you solve it in-place? Remember that the board needs to be 
updated at the same time: You cannot update some cells first and 
then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In 
principle, the board is infinite, which would cause problems 
when the active area encroaches the border of the array. How 
would you address these problems?
/*
    Submission Date: 2017-08-30
    Runtime: 0 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    typedef pair<int,int> pii;
public:
    int getAdajacent(const vector<vector<int>>& board, int row, int col, int M, int N) {
        int res = 0;
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                if(i == 0 && j == 0) continue;
                int x = row + i;
                int y = col + j;
                if(0 <= x && x < M && 0 <= y && y < N) {
                    res += board[x][y] & 1;
                }
            }
        }
        
        return res;
    }
    void gameOfLife(vector<vector<int>>& board) {
        if(board.empty()) return;
        
        vector<pii> make_live, make_dead;
        int M = board.size();
        int N = board[0].size();
        
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                int live = getAdajacent(board, i, j, M, N);
                if(board[i][j] == 0) {
                    if(live == 3) make_live.emplace_back(i, j);
                } else {
                    if(live < 2 || live > 3) make_dead.emplace_back(i, j);
                }
            }
        }
        
        for(auto p: make_dead) board[p.first][p.second] = 0;
        for(auto p: make_live) board[p.first][p.second] = 1;
    }
    
    void gameOfLife2(vector<vector<int>>& board) {
        if(board.empty()) return;
        
        int M = board.size();
        int N = board[0].size();
        
        /*
            O(1) space by storing whether to toggle for the next 
            state in the second bit. 1x means needs to toggle whereas 
            0x means doesn't need to toggle. Get state of z by (z & 1) 
            and get whether to toggle by (z >> 1) so next state of
            z is just (z >> 1) ^ (z & 1)
        */
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                int live = getAdajacent(board, i, j, M, N);
                if(board[i][j] == 0) {
                    board[i][j] |= (live == 3) << 1;
                } else {
                    board[i][j] |= (live < 2 || live > 3) << 1;
                }
            }
        }
        
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                board[i][j] = (board[i][j] >> 1) ^ (board[i][j] & 1);
            }
        }
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
290. Word Pattern
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a 
letter in pattern and a non-empty word in str.

Examples:
pattern = "abba", str = "dog cat cat dog" should return true.
pattern = "abba", str = "dog cat cat fish" should return false.
pattern = "aaaa", str = "dog cat cat dog" should return false.
pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains 
lowercase letters separated by a single space.
/*
    Submission Date: 2017-09-10
    Runtime: 0 ms
    Difficulty: EASY
*/
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char,string> letter_to_word;
        unordered_map<string,char> word_to_letter;
        
        stringstream ss(str);
        string word;
        
        int i = 0, N = pattern.size();
        while(i < N) {
            ss >> word;
            if(word.empty()) return false;
            if(letter_to_word.count(pattern[i]) || word_to_letter.count(word)) {
                if(word_to_letter[word] != pattern[i] || letter_to_word[pattern[i]] != word) return false;
            } else {
                letter_to_word[pattern[i]] = word;
                word_to_letter[word] = pattern[i];
            }
            i++;
        }
        
        bool rem = (bool)(ss >> word);
        return !rem;
    }
};

int main() {
    return 0;
}