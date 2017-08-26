/*
315. Count of Smaller Numbers After Self
You are given an integer array nums and you have to return a 
new counts array. The counts array has the property where 
counts[i] is the number of smaller elements to the right of 
nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
/*
    Submission Date: 2017-08-26
    Runtime: 36 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
        nlogn using tree
        given arr A, traverse A from N-1 to 0 inserting value into tree
        tree is bst (right greater than root, left smaller than root) but it has properties
        of number of left children and number of duplicates
        this tree represents everything to the right of the current element
        when inserting, every right turn indicates that the current element is greater than
        this node so the number of elements this element is greater than is
        number of duplicates from this node and numbers of left children of this node as 
        left tree <= node < current element

        e.g. [3, 2, 2, 6, 1]
            1(0, 1)
             \
             6(3, 1)
             /
           2(0, 2)
               \
                3(0, 1)
        adding 5 would put it to the right of 3 so 1(0,1), 2(0,2) and 3(0,1) are where it turned right
        (0 + 1) (0 + 2) + (0 + 1) = 4
    */
    struct Node {
        Node* left, *right;
        int num_left, num_dup;
        int val;
        Node(int _val): val(_val), num_left(0), num_dup(1), left(NULL), right(NULL) {}
    };

    Node* insert(Node* root, int val, int& sum) {
        if(root == NULL) {
            return new Node(val);
        } else if(root -> val == val) {
            // duplicate increases and sum increases by number of left children
            root -> num_dup += 1;
            sum += root -> num_left;
        } else if(root -> val > val) {
            // go left so number of left children increases
            root -> num_left += 1;
            root -> left = insert(root -> left, val, sum);
        } else {
            // go right so sum increases by number of duplicates and number of left children
            sum += (root -> num_dup) + (root -> num_left);
            root -> right = insert(root -> right, val, sum);
        }

        return root;
    }

    vector<int> countSmaller(vector<int>& nums) {
        int N = nums.size();
        vector<int> res(N);
        Node* root = NULL;
        for(int i = N-1; i >= 0; i--) {
            int sum = 0;
            root = insert(root, nums[i], sum); 
            res[i] = sum;
        }
        return res;
    }
};


int main() {
    Solution s;
    return 0;
}