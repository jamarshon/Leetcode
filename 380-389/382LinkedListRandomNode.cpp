/*
382. Linked List Random Node
Given a singly linked list, return a random node's value from the linked list. 

Follow up:
What if the linked list is extremely large and its length is unknown to you? 


Example:
// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should 
solution.getRandom();
/*
    Submission Date: 2018-07-10
    Runtime: 32 ms
    Difficulty: MEDIUM
*/
#include <iostream>
#include <vector>
#include <random>

using namespace std;

 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
    ListNode* head_;
    default_random_engine gen;
    uniform_int_distribution<int> uniform_dist;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        head_ = head;
    }
    
    /*
    resevoir sampling for ensuring each element has an equal probability of being chosen 
    k/n where n is the number of nodes which is unknown and k is the size of the output
    (k randomly chosen nodes). n is not known in advanced and if a node is added the 
    probabilities should update according
    
    fill buffer with the first k element
    for k + 1 to n, give the node a k/i probability of chosen to replace an element in the buffer
    
    proof that this is k/n. the probability the node is chosen is k/i and the probability it is 
    not replaced by any of the further nodes is (1 - 1/i+1)(1 - 1/i+2) ... (1 - 1/n)
    as at the time j, the node has a k/j chance of replacing any of the spots but a 1/j chance
    of replacing that exact cell. so not replaced is 1 - 1/j and this is done for ever
    time j > i
    
    (k/i)(1 - 1/i+1)(1 - 1/i+2) ... (1 - 1/n)
    (k/i)(i / i+1)(i+1 / i+2) ... (n-1 / n)
    k/n
    
    now the case is k=1
    */
    int getRandom() {
        vector<ListNode*> buffer = { head_ };
        
        int i = 1;
        ListNode* curr = head_->next;
        while(curr) {
            i++;
            
            // create a number x between [0, i) and if 0 <= x < k then replace buffer[x] with element
            // for a k/i chance
            uniform_int_distribution<int>::param_type new_range(0, i-1);
            uniform_dist.param(new_range);
            
            int x = uniform_dist(gen);
            if(x < buffer.size()) { // x == 0
                buffer[x] = curr;
            }
            curr = curr->next;
        }
        
        return buffer[0]->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */

int main() {
    return 0;
}
