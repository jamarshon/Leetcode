/*
4. Median of Two Sorted Arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

/*
	Submission Date: 2016-07-22
	Runtime: 88 ms
	Difficulty: HARD
*/

using namespace std;
#include "../UtilityHelper.hpp"
class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        vector<int> tempArr;
        int temp, i, j, maxOfLeft, minOfRight;
        int m = A.size(),
            n = B.size();

        if(m > n) {
            // swap A and B such that the length of A (m) is less than B (n)
            tempArr = A;
            A = B;
            B = tempArr;
            temp = m;
            m = n;
            n = temp;
        }
        if(n == 0){ return -1; }

        int imin = 0,
            imax = m,
            halfLen = (m + n + 1) / 2;

        while(imin <= imax) {
            i = (imin + imax) / 2;
            j = halfLen - i;
            if(j > 0 && i < m && B[j - 1] > A[i]) {
                imin = i + 1; // i is too small, must increase it
            } else if(i > 0 && j < n && A[i - 1] > B[j]) {
                imax = i - 1; // i is too big, must decrease it
            } else {
                // i is perfect
                if(i == 0) { maxOfLeft = B[j - 1]; }
                else if(j == 0) { maxOfLeft = A[i - 1]; }
                else { maxOfLeft = max(A[i - 1], B[j - 1]); }

                if((m + n) % 2 == 1) {
                    return maxOfLeft;
                }

                if(i == m) { minOfRight = B[j]; }
                else if(j == n) { minOfRight = A[i]; }
                else { minOfRight = min(A[i], B[j]); }

                return (maxOfLeft + minOfRight) / 2.0;
            }
        }
    }
};

///////////////////TestCases////////////////////////////////////////
int main() {
	Solution s;
	UtilityHelper<int, double> util;
	double output, result;

	vector<vector<vector<int>>> inputs = {
		{ {1, 3}, {2} }, // testcase 1
		{ {1, 2}, {3, 4} }, // testcase 2
		{ {}, {1}}, // testcase 3 
		{ {1, 2}, {1, 2, 3} }, // testcase 4
		{ {1}, {2, 3, 4} }, // testcase 5
        { {5, 6}, {1, 2, 3, 4, 7} }, // testcase 6
        { {2}, {} }, // testcase 7
        { {2, 5}, {1, 3, 4} }, // testcase 8
        { {1, 2, 3}, {1, 2} }, // testcase 9
        { {1, 2}, {3, 4, 5} }, // testcase 10
        { {3, 4, 5}, {1, 2, 6, 7, 8}}, // testcase 11
        { {5, 6}, {1, 2, 3, 4} }, // testcase 12
        { {4, 5, 6, 8}, {1, 2, 3, 7, 9, 10} }, // testcase 13
        { {1, 2, 3, 4}, {5, 6, 7, 8} }, // testcase 14
        
	};
	vector<double> outputs = {
		2.0, // testcase 1
		2.5, // testcase 2
		1.0, // testcase 3
		2.0, // testcase 4
		2.5, // testcase 5
        4.0, // testcase 6
        2.0, // testcase 7
        3.0, // testcase 8
        2.0, // testcase 9
        3.0, // testcase 10
        4.5, // testcase 11
        3.5, // testcase 12
        5.5, // testcase 13
        4.5, // testcase 14
	};

    int numTestCases = inputs.size();

	vector<vector<int>> input;
	for(int i = 0; i < numTestCases; i++) {
		input = inputs[i];
		output = outputs[i];

		printf("Test Case %d: \n", i);

		cout << "Input: ";
		util.printT(input[0]);
		util.printT(input[1]);

		cout << "Output: ";
		cout << output << endl;

		cout << "Function Output: ";
		result = s.findMedianSortedArrays(input[0], input[1]);
		cout << result << endl;

		cout << endl;
	}
}