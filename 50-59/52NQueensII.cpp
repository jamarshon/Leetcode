/*
52. N-Queens II
Follow up for N-Queens problem.

Now, instead outputting board configurations, return the total number of distinct solutions.

/*
    Submission Date: 2017-07-08
    Runtime: 3 ms
    Difficulty: HARD
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
    int nQueens(int arr[], int n, int index) {
        if(index == n) return 1;

        bool allowed[n];
        fill(allowed, allowed + n, true);

        for(int i = 0; i < index; i++) {
            allowed[arr[i]] = false; // column
            int diff = abs(index - i); // diagonal abs(x1 - x2) == abs(y1 - y2)
            if(0 <= arr[i] + diff && arr[i] + diff < n) allowed[arr[i] + diff] = false;
            if(0 <= arr[i] - diff && arr[i] - diff < n) allowed[arr[i] - diff] = false;
        }

        int count = 0;
        for(int i = 0; i < n; i++) {
            if(allowed[i]) {
                arr[index] = i;
                count += nQueens(arr, n, index + 1);
            }
        }

        return count;
    }
public:
    int totalNQueens(int n) {
        if(n == 0) return 0;
        int arr[n];

        return nQueens(arr, n, 0);
    }
};

int main() {
    Solution s;
    return 0;
}