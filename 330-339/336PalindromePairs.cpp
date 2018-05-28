/*
336. Palindrome Pairs
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the 
two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
/*
    Submission Date: 2018-05-28
    Runtime: 525 ms
    Difficulty: HARD
*/
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    vector<int> palindrome_suffix;
    int index = -1;
    vector<Node*> child = vector<Node*>(26, NULL);
};

class Solution {
public:
    /*
        is_pal O(n)
        insert O(k^2) 
        traverse O(k^2)

        For each word[i] in words, place the word in a trie. if the node is the end of the word, set node->index = i
        for each j from [0, words[i].size()), check if a suffix of [j, words[i].size()) is a palindrome. if it is
        then store i as palindrome_suffix for that node.

        For each word[i] in words, reverse it and traverse the trie. If the current node is end of a word then check if
        a suffix of rev(words[i]) is a palindrome.

        'bat' 'abatab'
        reverse 'abatab', 'bataba' we find 'bat' then check if suffix 'aba' is a palindrome to see 'bat' + 'abatab'

        if rev(words[i]) has a letter not in trie then return
        once rev(words[i]) has completely been traversed it means either the current node is end of word

        'bat' 'tab'
        reverse 'tab', 'bat' we find 'bat' return 'bat' + 'tab'

        or there are palindrome suffix

        'bataba' 'tab'
        'batdd' 'tab'
        The palindrome suffix of 'aba' and 'dd' means there is 'bataba' + 'tab' and 'batdd' + 'tab'
    */
    unordered_map<string, bool> dp_;
    
    bool is_pal(const string& s) {
        if(dp_.count(s)) return dp_[s];
        int N = s.size();
        for(int i = 0; i < N/2; i++) {
            if(s[i] != s[N-i-1]) return dp_[s] = false;
        }
        
        return dp_[s] = true;
    }
    
    
    void insert(Node* root, const string& s, const int& index) {
        Node* curr = root;
        for(int i = 0; i < s.size(); i++) {
            if(is_pal(s.substr(i))) curr->palindrome_suffix.push_back(index);
            if(curr->child[s[i] - 'a'] == NULL) curr->child[s[i] - 'a'] = new Node();
            curr = curr->child[s[i] - 'a'];
        }
        curr->index = index;
    }
    
    void traverse(Node* root, const string& s, const int& index, vector<vector<int>>& res) {
        Node* curr = root;
        for(int i = 0; i < s.size(); i++) {
            if(curr->index != -1 && is_pal(s.substr(i))) {
                res.push_back({curr->index, index});
            }
            if(curr->child[s[i] - 'a'] == NULL) {
                return;
            }
            curr = curr->child[s[i] - 'a'];
        }
        
        if(curr->index != -1 && index != curr->index) res.push_back({index, curr->index});
        
        for(const auto& e: curr->palindrome_suffix) {
            if(index == e) continue;
            res.push_back({e, index});
        }
    }
    
    vector<vector<int>> palindromePairs(vector<string>& words) {
        Node* root = new Node();
        
        for(int i = 0; i < words.size(); i++) {
            insert(root, words[i], i);
        }
        
        vector<vector<int>> res;
        for(int i = 0; i < words.size(); i++) {
            string s = words[i];
            reverse(s.begin(), s.end());
            traverse(root, s, i, res);
        }
        
        return res;
    }
};

int main() {
    return 0;
}