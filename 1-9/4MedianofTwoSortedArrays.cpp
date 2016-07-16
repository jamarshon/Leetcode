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
	Submission Date: 2016-07-X
	Runtime: X ms
	Difficulty: HARD
*/

using namespace std;
#include "../UtilityHelper.hpp"
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return findMedianSortedArraysHelper(nums1, nums2, 0, nums1.size() - 1, 0, nums2.size() - 1);
    }

    double findMedianSortedArraysHelper(vector<int> v1, vector<int> v2, 
    									int i1, int j1, int i2, int j2) {
    	int len1 = j1 - i1 + 1,
    		len2 = j2 - i2 + 1;

        int m1 = floor((i1 + j1) / 2),
            m2 = floor((i2 + j2) / 2);

        UtilityHelper<int, double> util;
        cout << "a" << endl;
        util.printT(v1, i1, j1 + 1);
        util.printT(v2, i2, j2 + 1);
    	// if either vectors are empty then return the median of the non-empty one
    	if(len1 == 0 && len2 == 0) {
    		return -1.0;
    	} else if(len1 == 0) {
    		return median(v2, len2, m2);
    	} else if(len2 == 0) {
    		return median(v1, len1, m1);
    	}

    	// if the vectors both only include one element then return the average of them
		if(len1 == 1 && len2 == 1) {
			return (v1[i1] + v2[i2]) / 2.0;
    	} else if(len1 == 1) {
    		return medianCombineOneElement(v2, v1[i1], len2, m2);
    	} else if(len2 == 1) {
    		return medianCombineOneElement(v1, v2[i2], len1, m1);
    	}

        double median1 = median(v1, len1, m1),
            median2 = median(v2, len2, m2);

    	// if the size of both vectors are 2 then take the average of the
    	// max first element and min second element
    	if(len1 == 2 && len2 == 2) {
    		int maxFirstElement = max(v1[i1], v2[i2]),
    			minSecondElement = min(v1[j1], v2[j2]);
    		return (maxFirstElement + minSecondElement) / 2.0;
    	}  else if(len1 == 2) {
            // one vector is of size 2 and it has a smaller median than the other vector
            return medianCombineTwoElements(v2, v1[i1], v1[j1], len2, m2);
        }  else if(len2 == 2) {
            return medianCombineTwoElements(v1, v2[i2], v2[j2], len1, m1);
        }

    	if(median1 > median2) {
    		// the median is within the first half of v1 and last half of v2.
            // Using the min of remaining numbers in the two halves of both v1 and v2 
            // (denote as maxNumRemovableElems), 
            // the new target area of v1 is the vector with maxNumRemovableElems removed 
            // from the end (but can only remove up to half the elements aka up to m1)
            // and the target area of v2 is the vector with maxNumRemovableElems removed 
            // from the beginning (but can only remove up to half the elements aka up to m2)
            int numElementFirstHalfV2 = m2 - i2,
                numElementLastHalfV1 = j1 - m1,
                maxNumRemovableElems = min(numElementFirstHalfV2, numElementLastHalfV1);
            int m1AfterRemoval = j1 - maxNumRemovableElems,
                m2AfterRemoval = i2 + maxNumRemovableElems;
    		return findMedianSortedArraysHelper(v1, v2, i1, m1AfterRemoval, m2AfterRemoval, j2);
    	} else if(median1 < median2) {
            // same as above, except the median is within first half of v2 and last half of v1
            int numElementFirstHalfV1 = m1 - i1,
                numElementLastHalfV2 = j2 - m2,
                maxNumRemovableElems = min(numElementFirstHalfV1, numElementLastHalfV2);
            int m1AfterRemoval = i1 + maxNumRemovableElems,
                m2AfterRemoval = j2 - maxNumRemovableElems;
    		return findMedianSortedArraysHelper(v1, v2, m1AfterRemoval, j1, i2, m2AfterRemoval);
    	} else {
    		// the median of both vectors are the same so just return the median
    		return median1;
    	}
    }

    double medianCombineOneElement(vector<int> v, int elem, int len, int m) {
    	// elemWithinThreshold means given elem and values of lower bound L and upper bound B,
    	// if elem is less than lower bound L, elemWithinThreshold is L
        // else if elem is greater than upper bound B, elemWithinThreshold is B
        // else elem is between the upper and lower bound, elemWithinThreshold is elem
    	
    	if(len % 2 == 0) {
    		// even length vector so it is just the elemWithinThreshold
            int lower = max(v[m], elem),
                elemWithinThreshold = min(lower, v[m + 1]);
    		return elemWithinThreshold;
    	} else {
            // odd length vector so it is the average of elemWithinThreshold and previous median
            int lower = max(v[m - 1], elem),
                elemWithinThreshold = min(lower, v[m + 1]);
    		return (elemWithinThreshold + v[m]) / 2.0;
    	}
    }

    double medianCombineTwoElements(vector<int> v, int elem1, int elem2, int len, int m) {
        // elemWithinThreshold means given elem and values of lower bound L and upper bound B,
        // if elem is less than lower bound L, elemWithinThreshold is L
        // else if elem is greater than upper bound B, elemWithinThreshold is B
        // else elem is between the upper and lower bound, elemWithinThreshold is elem
        
        if(len % 2 == 0) {
            cout << "eh " << elem1 << " " << v[m] << " " << elem2 << endl;

            // even length
            if(elem1 < v[m]) {
                if(elem2 < v[m]) {
                    return (v[m] + max(v[m - 1], elem2)) / 2.0;
                } else {
                    return (v[m] + min(v[m + 1], elem2)) / 2.0;
                }
            } else {
                if(elem1 < v[m + 2]) {
                    return (elem1 + min(v[m + 1], elem2)) / 2.0;
                } else {
                    return (v[m + 1] + v[m + 2]) / 2.0;
                }
            }
        } else {
            // odd length vector
            if(elem1 < v[m] && elem2 < v[m]) {
                // both elem1 and elem2 are on the left side of v[m]
                return max(elem2, v[m - 1]);
            } else if(elem1 > v[m] && elem2 > v[m]) {
                // both elem1 and elem2 are on the right side of v[m]
                cout << elem1 << " " << elem2 << endl;
                return min(elem1, v[m + 1]);
            } else {
                // elem1 and elem2 are on either side of previous median so they cancel out
                return v[m];
            }
        }
    }

    double median(vector<int> v, int len, int m) {
    	if(len % 2 == 0) {
    		return (v[m] + v[m + 1]) / 2.0;
    	} else {
    		return v[m];
    	}
    } 
};

///////////////////TestCases////////////////////////////////////////
int main() {
	Solution s;
	UtilityHelper<int, double> util;
	double output, result;

	vector<vector<vector<int>>> inputs = {
		/*{ {1, 3}, {2} }, // testcase 1
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
        { {5, 6}, {1, 2, 3, 4} }, // testcase 12*/
        { {4, 5, 6, 8}, {1, 2, 3, 7, 9, 10} }, // testcase 13
        { {1, 2, 3, 4}, {5, 6, 7, 8} }, // testcase 14
        
	};
	vector<double> outputs = {
		/*2.0, // testcase 1
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
        3.5, // testcase 12*/
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