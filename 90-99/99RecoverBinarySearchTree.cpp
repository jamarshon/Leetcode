/*
99. Recover Binary Search Tree
Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

/*
    Submission Date: 2017-08-02
    Runtime: 32 ms
    Difficulty: HARD
*/

#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
public:
    void findIllegals(TreeNode* root, TreeNode* minimum, TreeNode* maximum, 
            vector<tuple<TreeNode*, TreeNode*, bool>>& illegals) {

        if(root == NULL) return;

        int curr_val = root -> val;
        bool is_less_than_minimum = minimum == NULL ? false : (curr_val < minimum -> val);
        bool is_greater_than_maximum = maximum == NULL ? false : (curr_val > maximum -> val);

        if(is_less_than_minimum || is_greater_than_maximum) {
            if(is_less_than_minimum) {
                illegals.emplace_back(minimum, root, true);
            } else {
                illegals.emplace_back(maximum, root, false);
            }
            return;
        }

        findIllegals(root -> left, minimum, root, illegals);
        findIllegals(root -> right, root, maximum, illegals);
    }

    void searchTree(TreeNode* root, TreeNode*& res, function<bool(TreeNode*, TreeNode*)> criteria) {
        if(root == NULL) return;
        if(criteria(root, res)) {
            res = root;
        }

        searchTree(root -> left, res, criteria);
        searchTree(root -> right, res, criteria);
    }

    void recoverTree(TreeNode* root) {
        vector<tuple<TreeNode*, TreeNode*, bool>> illegals;
        findIllegals(root, NULL, NULL, illegals);

        int N = illegals.size();
        assert(N == 1 || N == 2);

        TreeNode* limit1, *violate1, *limit2, *violate2, *to_switch;
        bool violate1_is_smaller_than_limit, violate2_is_smaller_than_limit;

        limit1 = violate1 = limit2 = violate2 = to_switch = NULL;
        violate1_is_smaller_than_limit = violate2_is_smaller_than_limit = false;

        tie(limit1, violate1, violate1_is_smaller_than_limit) = illegals[0];
        if(N == 1) {
            // we have limit1 and a child node (violate1) which does not fit it's boundaries
            // if violate1_is_smaller_than_limit, limit1 is too large so we find the smallest 
            // node from violate1 and replace limit1 with this node
            if(violate1_is_smaller_than_limit) {
                searchTree(violate1, to_switch, [](const TreeNode* curr, const TreeNode* res){
                    return res == NULL ? true : (res -> val > curr -> val);
                });
            } else {
                searchTree(violate1, to_switch, [](const TreeNode* a, const TreeNode* res){
                    return res == NULL ? true : (res -> val < a -> val);
                });
            }

            swap(limit1 -> val, to_switch -> val);
        } else if(N == 2) {
            // we have two nodes that violate the limits meaning they are not on the same path to the
            // root (ie lca(a,b) != a or b) so we just swap violate1 and violate2
            // denote anc as lca(violate1, violate2)
            // if violate1 is smaller than its limit, it means it went from the left tree of anc into 
            // right tree of anc and violate2 went from right tree to left. So violate2 should be greater
            // than its limit 
            tie(limit2, violate2, violate2_is_smaller_than_limit) = illegals[1];
            swap(violate2 -> val, violate1 -> val);
            assert(violate1_is_smaller_than_limit != violate2_is_smaller_than_limit);
        }
    }
};

class Solution {
private:
    TreeNode* first_, *second_, *prev_;
public:
    void inorder(TreeNode* root) {
        if(root == NULL) return;

        inorder(root -> left);

        bool prev_element_greater_than_current = prev_ == NULL ? false : (prev_ -> val > root -> val);

        if(prev_element_greater_than_current) {
            if(first_ == NULL) first_ = prev_;
            second_ = root;
        }

        prev_ = root;
        inorder(root -> right);
    }
    void recoverTree(TreeNode* root) {
        first_ = second_ = prev_ = NULL;
        inorder(root);
        swap(first_ -> val, second_ -> val);
    }
};

int main() {
    return 0;
}