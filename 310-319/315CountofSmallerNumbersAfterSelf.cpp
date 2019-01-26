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

class Solution2 {
 public:
  /*
      nlogn using tree
      given arr A, traverse A from N-1 to 0 inserting value into tree
      tree is bst (right greater than root, left smaller than root) but it has
     properties of number of left children and number of duplicates this tree
     represents everything to the right of the current element when inserting,
     every right turn indicates that the current element is greater than this
     node so the number of elements this element is greater than is number of
     duplicates from this node and numbers of left children of this node as left
     tree <= node < current element

      e.g. [3, 2, 2, 6, 1]
          1(0, 1)
           \
           6(3, 1)
           /
         2(0, 2)
             \
              3(0, 1)
      adding 5 would put it to the right of 3 so 1(0,1), 2(0,2) and 3(0,1) are
     where it turned right (0 + 1) (0 + 2) + (0 + 1) = 4
  */
  struct Node {
    Node *left, *right;
    int num_left, num_dup;
    int val;
    Node(int _val)
        : val(_val), num_left(0), num_dup(1), left(NULL), right(NULL) {}
  };

  Node* insert(Node* root, int val, int& sum) {
    if (root == NULL) {
      return new Node(val);
    } else if (root->val == val) {
      // duplicate increases and sum increases by number of left children
      root->num_dup += 1;
      sum += root->num_left;
    } else if (root->val > val) {
      // go left so number of left children increases
      root->num_left += 1;
      root->left = insert(root->left, val, sum);
    } else {
      // go right so sum increases by number of duplicates and number of left
      // children
      sum += (root->num_dup) + (root->num_left);
      root->right = insert(root->right, val, sum);
    }

    return root;
  }

  vector<int> countSmaller(vector<int>& nums) {
    int N = nums.size();
    vector<int> res(N);
    Node* root = NULL;
    for (int i = N - 1; i >= 0; i--) {
      int sum = 0;
      root = insert(root, nums[i], sum);
      res[i] = sum;
    }
    return res;
  }
};

class Solution {
  typedef pair<int, int> pii;

 public:
  void mergeSort(vector<pii>& v, vector<pii>& sp, vector<int>& res, int start,
                 int end) {
    /* for a subarray of v for indices [start, end], there
    is a left subarray [start, mid] and a right subarray
    [mid + 1, end]. If an item in the left subarray (left[i])
    is less than an item in the right subarray (right[j]),
    then left[i] is the next element in the sorted sequence and
    there are j elements that are smaller than left[i] that is
    to the right of left[i] so res[indexof(left[i])] += j

    use <= because [0,j) should not include numbers that equal
    to left[i]
    */
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort(v, sp, res, start, mid);
    mergeSort(v, sp, res, mid + 1, end);

    int idx = 0;
    int s1 = start, s2 = mid + 1;
    int e1 = mid + 1, e2 = end + 1;
    while (s1 < e1 || s2 < e2) {
      // left goes before right as right is empty (s2 >= e2)
      // or start of left is less than or equal to start of right
      if (s2 >= e2 || (s1 < e1 && v[s1].first <= v[s2].first)) {
        sp[idx++] = v[s1];
        res[v[s1].second] += s2 - mid - 1;
        s1++;
      } else {
        sp[idx++] = v[s2];
        s2++;
      }
    }

    for (int i = 0; i < idx; i++) v[i + start] = sp[i];
  }

  vector<int> countSmaller(vector<int>& nums) {
    int N = nums.size();

    vector<pii> v, sp(N);

    for (int i = 0; i < N; i++) {
      v.emplace_back(nums[i], i);
    }

    vector<int> res(N, 0);

    mergeSort(v, sp, res, 0, N - 1);
    return res;
  }
};

int main() {
  Solution s;
  vector<int> v{5, 2, 6, 1};
  v = s.countSmaller(v);
  for (auto e : v) cout << e << endl;
  return 0;
}