/*
212. Word Search II
Given a 2D board and a list of words from the dictionary, find all words in the
board.

Each word must be constructed from letters of sequentially adjacent cell, where
"adjacent" cells are those horizontally or vertically neighboring. The same
letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.

You would need to optimize your backtracking to pass the larger test. Could you
stop backtracking earlier?

If the current candidate does not exist in all words' prefix, you could stop
backtracking immediately. What kind of data structure could answer such query
efficiently?

/*
    Submission Date: 2017-07-26
    Runtime: 99 ms
    Difficulty: HARD
*/

#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

struct TrieNode {
  bool is_leaf;
  TrieNode* children[26];
  TrieNode() {
    is_leaf = false;
    for (int i = 0; i < 26; i++) children[i] = NULL;
  }
};

class Trie {
  TrieNode* root_;

 public:
  Trie() { root_ = new TrieNode(); }

  TrieNode* insert(const vector<string>& words) {
    for (auto word : words) insert(word);
    return root_;
  }

  void insert(string word) {
    TrieNode* curr = root_;
    for (int i = 0; i < word.size(); i++) {
      int letter_index = word[i] - 'a';
      if (curr->children[letter_index] == NULL) {
        curr->children[letter_index] = new TrieNode();
      }
      curr = curr->children[letter_index];
    }
    curr->is_leaf = true;
  }
};

class Solution {
  vector<int> dx{-1, 1, 0, 0};
  vector<int> dy{0, 0, -1, 1};

 public:
  void check(const vector<vector<char>>& board, const TrieNode* node,
             string curr, int row, int col, int rows, int cols,
             unordered_set<string>& res, set<pair<int, int>>& visited) {
    if (node->is_leaf) res.insert(curr);

    visited.insert({row, col});

    for (int i = 0; i < 4; i++) {
      int new_row = row + dy[i];
      int new_col = col + dx[i];
      if (0 <= new_row && new_row < rows && 0 <= new_col && new_col < cols) {
        if (visited.count({new_row, new_col})) continue;  // visited already

        char board_char = board[new_row][new_col];
        if (node->children[board_char - 'a'] == NULL)
          continue;  // no words to match

        check(board, node->children[board_char - 'a'],
              curr + string(1, board_char), new_row, new_col, rows, cols, res,
              visited);
      }
    }

    visited.erase({row, col});
  }
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    if (board.empty()) return {};

    Trie trie;
    TrieNode* root = trie.insert(words);
    int rows = board.size();
    int cols = board.front().size();

    unordered_set<string> res;
    set<pair<int, int>> visited;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        char board_char = board[i][j];
        if (root->children[board_char - 'a'] != NULL) {
          check(board, root->children[board_char - 'a'], string(1, board_char),
                i, j, rows, cols, res, visited);
        }
      }
    }

    vector<string> ret(res.begin(), res.end());
    return ret;
  }
};
int main() { return 0; }