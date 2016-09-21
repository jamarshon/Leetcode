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
	Runtime: 35 ms
	Difficulty: HARD
*/

using namespace std;
#include "../UtilityHelper.hpp"
class Solution {
public:
    double findMedianSortedArrays(vector<int>& C, vector<int>& D) {
        int cLen = C.size(),
            dLen = D.size();
        vector<int> A;
        vector<int> B;
        int i, j, M, N;
        if(cLen < dLen) {
            A = C;
            B = D;
            M = cLen;
            N = dLen;
        } else {
            B = C;
            A = D;
            N = cLen;
            M = dLen;
        }

        int imin = 0,
            imax = M,
            halfLen = (M + N + 1)/2; // this is middle index of the combined length of A and B
        int maxLeft, minRight;
        while(imin <= imax) {
            i = (imin + imax) / 2;
            j = halfLen - i;
            if(i > 0 && j < N && A[i-1] > B[j]) {
                imax = i - 1; // i is too large so decrease it
            } else if(j > 0 && i < M && B[j-1] > A[i]) {
                imin = i + 1; // i is too small so increase it
            } else {
                if(i == 0){ maxLeft = B[j-1]; }
                else if(j == 0){ maxLeft = A[i-1]; }
                else{ maxLeft = max(B[j-1], A[i-1]); }
                if((M + N) % 2 == 1) {
                    return maxLeft;
                }

                if(i == M){ minRight = B[j]; }
                else if(j == N){ minRight = A[i]; }
                else{ minRight = min(B[j], A[i]); }
                return (maxLeft + minRight) / 2.0;
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