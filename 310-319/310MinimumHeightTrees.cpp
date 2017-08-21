/*
310. Minimum Height Trees
For a undirected graph with tree characteristics, we can choose any 
node as the root. The result graph is then a rooted tree. Among all 
possible rooted trees, those with minimum height are called minimum 
height trees (MHTs). Given such a graph, write a function to find all 
the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will 
be given the number n and a list of undirected edges (each edge is a 
pair of labels).

You can assume that no duplicate edges will appear in edges. Since 
all edges are undirected, [0, 1] is the same as [1, 0] and thus 
will not appear together in edges.

Example 1:

Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3
return [1]

Example 2:

Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5
return [3, 4]

Note:

(1) According to the definition of tree on Wikipedia: “a tree is 
an undirected graph in which any two vertices are connected by 
exactly one path. In other words, any connected graph without 
simple cycles is a tree.”

(2) The height of a rooted tree is the number of edges on the 
longest downward path between the root and a leaf.
/*
    Submission Date: 2017-08-21
    Runtime: 76 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if(n == 1) return {0}; // one node so the root of mht is itself
        
        vector<unordered_set<int>> graph(n);
        for(auto p: edges) {
            graph[p.first].insert(p.second);
            graph[p.second].insert(p.first);
        }
        
        vector<int> leaves;
        for(int i = 0; i < n; i++) {
            // this node is connected to only one other node (parent) so it is a leaf
            if(graph[i].size() == 1) {
                leaves.push_back(i);
            }
        }
        
        // reverse BFS the idea is to select nodes that are only connected to one other node
        // these nodes are leafs and are removed. Update the new leafs by keeping track of the
        // number of children of each node. If it goes to 1, it means it is only connected to its
        // parent and is now a leaf
        // when there are only 2 or less leafs then it means these are the roots
        
        while(n > 2) { // tree has more than 2 nodes
            n -= leaves.size(); // remove the leafs
            
            vector<int> new_leaves;
            for(auto leaf: leaves) {
                int parent = *graph[leaf].begin();
                graph[parent].erase(leaf); // from the parent remove the leaf
                if(graph[parent].size() == 1) { // if the parent has no children, it is now a new leaf
                    new_leaves.push_back(parent);
                }
            }
            leaves = new_leaves;
        }
        
        return leaves;
    }
};

int main() {
    Solution s;
    return 0;
}