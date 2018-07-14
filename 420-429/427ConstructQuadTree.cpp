/*
427. Construct Quad Tree
We want to use quad trees to store an N x N boolean grid. Each cell in the grid 
can only be true or false. The root node represents the whole grid. For each 
node, it will be subdivided into four children nodes until the values in the 

Each node has another two boolean attributes : isLeaf and val. isLeaf is true if 
and only if the node is a leaf node. The val attribute for a leaf node contains 

Your task is to use a quad tree to represent a given grid. The following example 

Given the 8 x 8 grid below, we want to construct the corresponding quad tree:



It can be divided according to the definition above:



 

The corresponding quad tree should be as following, where each node is 

For the non-leaf nodes, val can be arbitrary, so it is represented as *.



Note:


    N is less than 1000 and guaranteened to be a power of 2.
    If you want to know more about the quad tree, you can refer to its wiki.
/*
    Submission Date: 2018-07-13
    Runtime: 40 ms
    Difficulty: EASY
*/
#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    /*
    cell of size 1 is a leaf and its value is just the grid cell
    else get the 4 quadrants
    they all have to be leafs and their values have to be the same for this to be merged
    else just put a parent node over the 4 quadrants
    */
    Node* help(const vector<vector<int>>& grid, int x, int y, int N) {
        if(N == 1) return new Node(grid[y][x], true, NULL, NULL, NULL, NULL);
        Node* top_left = help(grid, x, y, N/2);
        Node* top_right = help(grid, x + N/2, y, N/2);
        Node* bottom_left = help(grid, x, y + N/2, N/2);
        Node* bottom_right = help(grid, x + N/2, y + N/2, N/2);
        vector<Node*> v{top_left, top_right, bottom_left, bottom_right};
        bool all_same = v[0]->isLeaf;
        for(int i = 1; i < 4; i++) {
            if(!v[i]->isLeaf || v[i]->val != v[0]->val) {
                all_same = false;
                break;
            }
        }
        
        if(all_same) return new Node(v[0]->val, true, NULL, NULL, NULL, NULL);
        else return new Node(-1, false, top_left, top_right, bottom_left, bottom_right);
    }
    
    Node* construct(vector<vector<int>>& grid) {
        int N = grid.size();
        if(N == 0) return NULL;
        return help(grid, 0, 0, N);
    }
};

int main() {
    return 0;
}
