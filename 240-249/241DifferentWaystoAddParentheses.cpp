/*
241. Different Ways to Add Parentheses
Given a string of numbers and operators, return all possible results from
computing all the different possible ways to group numbers and operators. The
valid operators are +, - and *.

Example 1
Input: "2-1-1".

((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]


Example 2
Input: "2*3-4*5"

(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]

/*
    Submission Date: 2017-08-06
    Runtime: 3 ms
    Difficulty: MEDIUM
*/

#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Element {
  bool is_operator;
  int value;
  Element(bool _is_operator, int _value)
      : is_operator(_is_operator), value(_value) {}
};

struct ETreeNode {
  Element e;
  ETreeNode *left, *right;
  ETreeNode(Element _e) : e(_e), left(NULL), right(NULL) {}
};

class SolutionTree {
 public:
  ETreeNode* cloneWithOffset(ETreeNode* curr, int offset) {
    if (curr == NULL) return NULL;
    Element offset_e = curr->e;
    offset_e.value += offset;

    ETreeNode* new_curr = new ETreeNode(offset_e);
    new_curr->left = cloneWithOffset(curr->left, offset);
    new_curr->right = cloneWithOffset(curr->right, offset);
    return new_curr;
  }

  void destroyTree(ETreeNode* root) {
    if (root == NULL) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
  }

  vector<ETreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    vector<vector<ETreeNode*>> dp(n + 1);
    dp[0] = {NULL};

    for (int len = 1; len <= n; len++) {
      for (int j = 0; j < len; j++) {
        vector<ETreeNode*> left_trees = dp[j], right_trees = dp[len - j - 1];
        for (auto left_tree : left_trees) {
          for (auto right_tree : right_trees) {
            ETreeNode* curr = new ETreeNode(Element{true, j});
            curr->left = cloneWithOffset(left_tree, 0);
            curr->right = cloneWithOffset(right_tree, j + 1);
            dp[len].push_back(curr);
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (auto tree : dp[i]) destroyTree(tree);
    }
    return dp[n];
  }

  void inorderPlaceValuesAndOperators(ETreeNode* root, vector<Element>& numbers,
                                      vector<Element> operators, int& i,
                                      int& j) {
    if (root == NULL) return;
    inorderPlaceValuesAndOperators(root->left, numbers, operators, i, j);
    root->e = operators[i++];
    if (root->left == NULL) {
      root->left = new ETreeNode(numbers[j++]);
    }

    if (root->right) {
      inorderPlaceValuesAndOperators(root->right, numbers, operators, i, j);
    } else {
      root->right = new ETreeNode(numbers[j++]);
    }
  }

  int evaluateTree(ETreeNode* root) {
    assert(root != NULL);  // should never happen as the numbers are the leafs
    if (root->e.is_operator) {
      if (root->e.value == '*') {
        return evaluateTree(root->left) * evaluateTree(root->right);
      } else if (root->e.value == '+') {
        return evaluateTree(root->left) + evaluateTree(root->right);
      } else if (root->e.value == '-') {
        return evaluateTree(root->left) - evaluateTree(root->right);
      } else {
        assert(false);
        return -1;
      }
    } else {
      return root->e.value;
    }
  }

  void preorder(ETreeNode* curr) {
    if (curr == NULL) {
      cout << "NULL ";
    } else {
      if (curr->e.is_operator)
        cout << char(curr->e.value) << ' ';
      else
        cout << (curr->e.value) << ' ';
      preorder(curr->left);
      preorder(curr->right);
    }
  }

  vector<int> diffWaysToCompute(string input) {
    int start = 0;
    int end = 0;
    int N = input.size();

    vector<Element> operators;
    vector<Element> numbers;
    while (end < N) {
      if (input[end] == '*' || input[end] == '-' || input[end] == '+') {
        string s = input.substr(start, end - start);
        if (!s.empty()) {
          numbers.emplace_back(false, stoi(s));
        }
        operators.emplace_back(true, input[end]);
        start = end + 1;
      }
      end++;
    }

    string s = input.substr(start, end - start);
    if (!s.empty()) {
      numbers.emplace_back(false, stoi(s));
    }

    vector<ETreeNode*> uniqueTrees = generateTrees(operators.size());
    vector<int> res;
    int i, j;
    for (auto tree : uniqueTrees) {
      i = j = 0;
      inorderPlaceValuesAndOperators(tree, numbers, operators, i, j);
      res.push_back(evaluateTree(tree));
    }
    return res;
  }
};

class SolutionDP {
  unordered_map<char, function<int(int, int)>> ops_m{
      {'*', [](const int& a, const int& b) { return a * b; }},
      {'+', [](const int& a, const int& b) { return a + b; }},
      {'-', [](const int& a, const int& b) { return a - b; }},
  };

 public:
  vector<int> diffWaysToCompute(string input) {
    vector<int> nums;  // nums will be size N and ops should be size N - 1 but
                       // extra added just for convenience
    vector<char> ops;

    int num;
    char op;
    stringstream ss(input + "+");

    while (ss >> num && ss >> op) {
      nums.push_back(num);
      ops.push_back(op);
    }

    int N = nums.size();
    if (N == 1) return nums;

    /**
        dp[i][j] is a vector of all possible values from operations from index i
       to j inclusive where indexes correspond with integers from the nums array
        e.g. "2*3-4*5" -> nums = [2,3,4,5] and ops = ['*', '-', '*'] dp[2][3] =
       {20} as 4*5 or ops[2](dp[2][2], dp[3][3])

        dp[i][i] would just be {nums[i]}
        dp[i][j] would be {op[k](dp[i][k], dp[k+1][j]), ... for all k from [i,
       j)} final result is just indexes 0 to N-1 or dp[0][N-1]
    */
    vector<vector<vector<int>>> dp(N, vector<vector<int>>(N));

    for (int i = N - 1; i >= 0; i--) {
      for (int j = i; j < N; j++) {
        if (i == j) {
          dp[i][j] = {nums[i]};
        } else {
          for (int k = i; k < j; k++) {
            vector<int>& left = dp[i][k];
            vector<int>& right = dp[k + 1][j];
            function<int(int, int)> op = ops_m[ops[k]];
            for (auto left_el : left) {
              for (auto right_el : right) {
                dp[i][j].push_back(op(left_el, right_el));
              }
            }
          }
        }
      }
    }
    return dp[0][N - 1];
  }
};

class Solution {
  unordered_map<string, vector<int>> dp;
  unordered_map<char, function<int(int, int)>> ops_m{
      {'*', [](const int& a, const int& b) { return a * b; }},
      {'+', [](const int& a, const int& b) { return a + b; }},
      {'-', [](const int& a, const int& b) { return a - b; }},
  };

 public:
  vector<int> diffWaysToCompute(string input) {
    if (dp.count(input)) return dp[input];
    int N = input.size();
    vector<int> res;
    for (int i = 0; i < N; i++) {
      if (!isdigit(input[i])) {
        vector<int> left = diffWaysToCompute(input.substr(0, i));
        vector<int> right = diffWaysToCompute(input.substr(i + 1));
        function<int(int, int)> op = ops_m[input[i]];
        for (auto left_el : left) {
          for (auto right_el : right) {
            res.push_back(op(left_el, right_el));
          }
        }
      }
    }

    if (res.empty()) res.push_back(stoi(input));  // no operations left
    return dp[input] = res;
  }
};

int main() {
  Solution s;
  vector<int> v = s.diffWaysToCompute("2*3-4*5");
  for (auto e : v) cout << e << endl;
  return 0;
}