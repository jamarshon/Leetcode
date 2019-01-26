/*
133. Clone Graph
Clone an undirected graph. Each node in the graph contains a label and a list of
its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and
each neighbor of the node. As an example, consider the serialized graph
{0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as
separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a
self-cycle. Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/

/*
    Submission Date: 2017-07-18
    Runtime: 33 ms
    Difficulty: MEDIUM
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct UndirectedGraphNode {
  int label;
  vector<UndirectedGraphNode *> neighbors;
  UndirectedGraphNode(int x) : label(x){};
};

class Solution {
  unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> m;
  unordered_set<UndirectedGraphNode *> visited;

 public:
  void cloneGraph(UndirectedGraphNode *head, UndirectedGraphNode *node) {
    visited.insert(node);
    for (auto neighbor : node->neighbors) {
      if (!m.count(neighbor)) {
        m[neighbor] = new UndirectedGraphNode(neighbor->label);
      }

      head->neighbors.push_back(m[neighbor]);
      if (!visited.count(neighbor)) {
        cloneGraph(m[neighbor], neighbor);
      }
    }
  }

  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (node == NULL) return NULL;

    UndirectedGraphNode *head = new UndirectedGraphNode(node->label);
    m[node] = head;
    cloneGraph(head, node);
    return head;
  }
};

int main() { return 0; }