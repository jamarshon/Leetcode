/*
232. Implement Queue using Stacks
Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Notes:
You must use only standard operations of a stack -- which means 
only push to top, peek/pop from top, size, and is empty operations 
are valid.
Depending on your language, stack may not be supported natively. You 
may simulate a stack by using a list or deque (double-ended queue), as 
long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or 
peek operations will be called on an empty queue).
/*
    Submission Date: 2017-08-21
    Runtime: 3 ms
    Difficulty: EASY
*/
#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
    stack<int> input_, output_;
public:
    MyQueue() {}

    void push(int x) {
        input_.push(x);
    }

    int pop() {
        int output_top = peek();
        output_.pop();
        return output_top;
    }

    int peek() {
        if(output_.empty()) {
            // reverse input_ stack by taking the top and making it at the bottom of output_
            while(!input_.empty()) {
                int input_top = input_.top();
                output_.push(input_top);
                input_.pop();
            }
        }

        return output_.top();
    }

    bool empty() {
        return input_.empty() && output_.empty();
    }
};

int main() {
    return 0;
}