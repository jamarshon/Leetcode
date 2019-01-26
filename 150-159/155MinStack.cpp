/*
155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element
in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

/*
    Submission Date: 2017-07-21
    Runtime: 29 ms
    Difficulty: EASY
*/

#include <cassert>
#include <iostream>
#include <stack>

using namespace std;

struct MinStackNode {
  int val;
  MinStackNode* next;
  int min_so_far;
};

class MinStack {
  MinStackNode* top_node;

 public:
  MinStack() { top_node = NULL; }

  void push(int x) {
    MinStackNode* new_top = new MinStackNode();
    new_top->val = x;
    new_top->next = top_node;

    if (top_node == NULL) {
      new_top->min_so_far = x;
    } else if (top_node->min_so_far <= x) {
      new_top->min_so_far = top_node->min_so_far;
    } else {
      new_top->min_so_far = x;
    }

    top_node = new_top;
  }

  void pop() {
    assert(top_node != NULL);
    MinStackNode* temp = top_node;
    top_node = top_node->next;
    delete temp;
  }

  int top() {
    assert(top_node != NULL);
    return top_node->val;
  }

  int getMin() { return top_node->min_so_far; }
};

int main() { return 0; }