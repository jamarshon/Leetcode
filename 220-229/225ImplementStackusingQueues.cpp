/*
225. Implement Stack using Queues
Implement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to back, 
peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively. You may simulate 
a queue by using a list or deque (double-ended queue), as long as you use only 
standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top 
operations will be called on an empty stack).

/*
    Submission Date: 2017-08-12
    Runtime: 3 ms
    Difficulty: EASY
*/

#include <iostream>
#include <queue>

using namespace std;

// one queue - pop efficient, reverse queue everytime push
// push item to queue and take the 0 to N-1 elements before it and place it behind it
// so 1,2,3,4,5 becomes 5,4,3,2,1 through rotating the queue
// 1
// 1,2 -> 2 -> 2,1
// 2,1,3 -> 1,3,2 -> 3,2,1
// 3,2,1,4 -> 2,1,4,3 -> 1,4,3,2 - > 4,3,2,1
// 4,3,2,1,5 -> 3,2,1,5,4 -> 2,1,5,4,3 -> 1,5,4,3,2 -> 5,4,3,2,1
// push - O(n), top/pop/empty O(1)
class MyStack {
    queue<int> q_;
public:
    MyStack() {}
    
    void push(int x) {
        q_.push(x);
        for(int i = 0, N = q_.size(); i < N - 1; i++) {
            q_.push(q_.front());
            q_.pop();
        }
    }
    
    int pop() {
        int front_el = q_.front();
        q_.pop();
        return front_el;
    }
    
    int top() {
        return q_.front();
    }
    
    bool empty() {
        return q_.empty();
    }
};

// two queues - pop efficient, same as above 1 queue except instead use additional queue to rotate  
// push - o(n), pop/top/empty - o(1)
// for pop/top just choose the non empty queue and return front and pop if necessary
// empty check if both queues are empty
// push choose the empty queue (any queue if both are empty)
// and push the value to it. Move all items in the other queue into this queue
// this maintains one empty queue and one queue that has all its elements reversed
// e.g insert 1,2,3,4,5 should result in a queue with 5,4,3,2,1 and an empty queue 
// /* push 1 to A */ [1]        [] 
// /* push 2 to B */ [1]        [2]         -> []           [2,1]       /* remove 1 from A and move to B */
// /* push 3 to A */ [3]        [2,1]       -> [3,2,1]      []          /* remove 2,1 from B and move to A */
// /* push 4 to B */ [3,2,1]    [4]         ->  []          [4,3,2,1]   /* remove 3,2,1 from A and move to B */
// /* push 5 to A */ [5]        [4,3,2,1]   ->  [5,4,3,2,1] []          /* remove 4,3,2,1 from B and move to A */

class MyStack2 {
    queue<int> q1_, q2_;
public:
    MyStack2() {}
    
    void push(int x) {
        if(q1_.empty()) {
            q1_.push(x);
            while(!q2_.empty()) {
                q1_.push(q2_.front());
                q2_.pop();
            }
        } else {
            q2_.push(x);
            while(!q1_.empty()) {
                q2_.push(q1_.front());
                q1_.pop();
            }
        }
    }
    
    int pop() {
        int top_el = top();
        if(q2_.empty()) {
            q1_.pop();
        } else {
            q2_.pop();
        }
        return top_el;
    }
    
    int top() {
        return q2_.empty() ? q1_.front() : q2_.front();
    }
    
    bool empty() {
        return q1_.empty() && q2_.empty();
    }
};

// one queue - push efficient
// pop/top - o(n), push/empty - o(1)
class MyStack3 {
    queue<int> q_;
public:
    MyStack3() {}
    
    void push(int x) {
        q_.push(x);
    }
    
    int pop() {
        for(int i = 0, N = q_.size(); i < N - 1; i++) {
            q_.push(q_.front());
            q_.pop();
        }
        int last_el = q_.front();
        q_.pop();
        return last_el;
    }
    
    int top() {
        int last_el = pop();
        push(last_el);
        return last_el;
    }
    
    bool empty() {
        return q_.empty();
    }
};


// two queues - push efficient
// pop/top - o(n), push/empty - o(1)
// push to non empty queue
// pop by taking everything except the last element in the non empty queue and put it in the empty queue 
// take the only element in the empty queue
class MyStack4 {
    queue<int> q1_, q2_;
public:
    MyStack4() {}
    
    void push(int x) {
        if(!q1_.empty()) {
            q1_.push(x);
        } else {
            q2_.push(x);
        }
    }
    
    int popHelper(queue<int>& empty_q, queue<int>& non_empty_q) {
        for(int i = 0, N = non_empty_q.size(); i < N - 1; i++) {
            empty_q.push(non_empty_q.front());
            non_empty_q.pop();
        }

        int last_el = non_empty_q.front();
        non_empty_q.pop();

        return last_el;
    }

    int pop() {
        int last_el = q1_.empty() ? popHelper(q1_, q2_) : popHelper(q2_, q1_);
        return last_el;
    }
    
    int top() {
        int last_el = pop();
        push(last_el);
        return last_el;
    }
    
    bool empty() {
        return q1_.empty() && q2_.empty();
    }
};

int main() {
    return 0;
}