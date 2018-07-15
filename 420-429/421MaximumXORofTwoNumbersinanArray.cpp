/*
421. Maximum XOR of Two Numbers in an Array
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:
Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.

/*
    Submission Date: 2018-07-01
    Runtime: 47 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    TrieNode* children[2];
    TrieNode() {
        children[0] = children[1] = NULL;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        TrieNode* root = new TrieNode();
        // insert all numbers in trie in bit representation with msb near root
        for(const auto& n: nums) {
            TrieNode* curr = root;
            for(int i = 31; i >= 0; i--) {
                bool bit = n & (1 << i);
                if(curr->children[bit] == NULL) curr->children[bit] = new TrieNode();
                curr = curr->children[bit];
            }
        }
        
        // for each number search for the complementary if it exists, else take other path
        int res = 0;
        for(const auto& n: nums) {
            TrieNode* curr = root;
            int max_value = 0;
            for(int i = 31; i >= 0; i--) {
                bool bit = n & (1 << i);
                bool comp_bit = !bit;
                if(curr->children[comp_bit] == NULL) {
                    // take other path and since same number nothing is added
                    curr = curr->children[bit];
                } else {
                    // take complentary path and since a different number is added, add to the max_value
                    max_value += (1 << i);
                    curr = curr->children[comp_bit];
                }
            }
            res = max(res, max_value);
        }
        return res;
    }
};

int main() {
    return 0;
}