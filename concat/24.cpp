
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
720. Longest Word in Dictionary
Given a list of strings words representing an English Dictionary, find the longest word in words that can be 
built one character at a time by other words in words. If there is more than one possible answer, return the longest word with 
the smallest lexicographical order.

If there is no answer, return the empty string.
Example 1:
Input: 
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation: 
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input: 
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: 
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".
Note:

All the strings in the input will only contain lowercase letters.
The length of words will be in the range [1, 1000].
The length of words[i] will be in the range [1, 30].
/*
    Submission Date: 2018-05-24
    Runtime: 56 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    bool is_word;
    TrieNode* child[26];
    TrieNode() {
        is_word = false;
        for(int i = 0; i < 26; i++) child[i] = NULL;
    }
};

class Trie {
public:
    TrieNode* root_;
    
    /** Initialize your data structure here. */
    Trie() {
        root_ = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* curr = root_;
        for(auto c: word) {
            if(curr -> child[c - 'a'] == NULL) curr -> child[c - 'a'] = new TrieNode();
            curr = curr -> child[c - 'a'];
        }
        curr -> is_word = true;
    }
};

class Solution {
public:
    string dfs(TrieNode* node, string letter) {
        if(node == NULL || !node->is_word) return "";
        string max_child = "";
        for(int i = 0; i < 26; i++) {
            string child = dfs(node -> child[i], string(1, 'a' + i));
            if(child.size() > max_child.size()) {
                max_child = child;
            }
        }
        
        return letter + max_child;
    }
    string longestWord(vector<string>& words) {
        Trie trie;
        for(const auto& s: words) trie.insert(s);
        trie.root_ -> is_word = true;
        return dfs(trie.root_, "");
    }
};

int main() {
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
836. Rectangle Overlap
A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are the coordinates of its bottom-left corner, and (x2, y2) are 
the coordinates of its top-right corner.

Two rectangles overlap if the area of their intersection is positive.  To be clear, two rectangles that only touch at the corner or edges do not overlap.

Given two rectangles, return whether they overlap.

Example 1:

Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
Output: true
Example 2:

Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
Output: false
Notes:

Both rectangles rec1 and rec2 are lists of 4 integers.
All coordinates in rectangles will be between -10^9 and 10^9.
/*
    Submission Date: 2018-05-24
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool intersects(int a1, int a2, int b1, int b2) {
        return !(b1 >= a2 || a1 >= b2);
    }
    
    // Check if x intervals intersect and y intervals intersect
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return intersects(rec1[0], rec1[2], rec2[0], rec2[2]) && intersects(rec1[1], rec1[3], rec2[1], rec2[3]);
    }
};

int main() {
    return 0;
}