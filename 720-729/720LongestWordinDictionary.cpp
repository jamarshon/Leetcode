/*
720. Longest Word in Dictionary
Given a list of strings words representing an English Dictionary, find the
longest word in words that can be built one character at a time by other words
in words. If there is more than one possible answer, return the longest word
with the smallest lexicographical order.

If there is no answer, return the empty string.
Example 1:
Input:
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation:
The word "world" can be built one character at a time by "w", "wo", "wor", and
"worl". Example 2: Input: words = ["a", "banana", "app", "appl", "ap", "apply",
"apple"] Output: "apple" Explanation: Both "apply" and "apple" can be built from
other words in the dictionary. However, "apple" is lexicographically smaller
than "apply". Note:

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
    for (int i = 0; i < 26; i++) child[i] = NULL;
  }
};

class Trie {
 public:
  TrieNode* root_;

  /** Initialize your data structure here. */
  Trie() { root_ = new TrieNode(); }

  /** Inserts a word into the trie. */
  void insert(string word) {
    TrieNode* curr = root_;
    for (auto c : word) {
      if (curr->child[c - 'a'] == NULL) curr->child[c - 'a'] = new TrieNode();
      curr = curr->child[c - 'a'];
    }
    curr->is_word = true;
  }
};

class Solution {
 public:
  string dfs(TrieNode* node, string letter) {
    if (node == NULL || !node->is_word) return "";
    string max_child = "";
    for (int i = 0; i < 26; i++) {
      string child = dfs(node->child[i], string(1, 'a' + i));
      if (child.size() > max_child.size()) {
        max_child = child;
      }
    }

    return letter + max_child;
  }
  string longestWord(vector<string>& words) {
    Trie trie;
    for (const auto& s : words) trie.insert(s);
    trie.root_->is_word = true;
    return dfs(trie.root_, "");
  }
};

int main() { return 0; }