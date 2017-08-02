/*
84. Largest Rectangle in Histogram
Given n non-negative integers representing the histogram's bar height where the width of each bar is 
1, find the area of largest rectangle in the histogram.

Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.

/*
    Submission Date: 2017-08-01
    Runtime: 19 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea2(vector<int>& heights) {
        stack<int> st;
        heights.push_back(0);
        int max_area = 0;
        // maintain increasing height stack
        // if current height (heights[i]) is less than last element in stack,
        // last element st[j] is bounded by heights[i] so the width is 
        // i - 1 (right_boundary) - st[j-1] (left boundary) and area is width*heights[st[j]]
        // keep removing elements of stack until reach smaller height which allows height[i] to be added to stack
        // if stack is empty it means st[j] is not bounded on the left (minimum of heights from 0 to st[j]) 
        // so it is just i - 1 - (-1) which is i
        for(int i = 0, len = heights.size(); i < len; i++) {
            if(st.empty() || heights[i] >= heights[st.top()]) {
                st.push(i);
            } else {
                while(true) {
                    int top_ind = st.top();
                    st.pop();
                    int curr_area = st.empty() ? i*heights[top_ind] : (i - st.top() - 1)*heights[top_ind];
                    max_area = max(max_area, curr_area);
                    if(st.empty() || heights[i] >= heights[st.top()]) {
                        st.push(i);
                        break;
                    }
                }
            }
        }

        heights.pop_back();
        return max_area;
    }

    int largestRectangleArea(vector<int>& heights) {
        // at index i the area would be heights[i]*(the first index smaller than heights[i] on the right - the first index
        // smaller than heights[i] on the left - 1) for example in {2,1,5,6,2,3} the area at index 2 would be 5*(index of 2 - index of 1)
        // 5*(4-1-1) = 10

        // to construct left and right in linear time we can take advantage of the fact of jumps. for example
        // 4, 200, 100, 10, 5 the left of 10 is 4 as it is the first number smaller to it when moving left that is left[3] = 0
        // since 10 is greater than 5, we just need to compare 5 with elements smaller than 10 so skip 100, 200 by using left array
        // to find the first number smaller than 10 which is 4 
        int N = heights.size();
        vector<int> left(N), right(N);
        for(int i = 0; i < N; i++) {
            int index = i - 1;
            while(index >= 0 && heights[index] >= heights[i]) {
                index = left[index];
            }
            left[i] = index;
        }

        for(int i = N-1; i >= 0; i--) {
            int index = i + 1;
            while(index < N && heights[index] >= heights[i]) {
                index = right[index];
            }
            right[i] = index;
        }

        int max_area = 0;
        for(int i = 0; i < N; i++) {
            max_area = max(max_area, heights[i]*(right[i] - left[i] - 1));
        }

        return max_area;
    }
};

int main() {
    return 0;
}