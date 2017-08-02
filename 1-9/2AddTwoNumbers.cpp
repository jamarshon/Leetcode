/*
2. Add Two Numbers
You are given two linked lists representing two non-negative numbers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/*
	Submission Date: 2016-07-10
	Runtime: 40 ms
	Difficulty: MEDIUM
*/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
	public:
	    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	    	int l1Val, l2Val, total;
	    	ListNode* head = l1;
	        ListNode* prev = NULL;
	    	int carryover = 0;
	        while(l1 != NULL && l2 != NULL) {
	        	l1Val = l1 -> val;
	        	l2Val = l2 -> val;
	        	total = l1Val + l2Val + carryover;
	        	l1 -> val = total % 10;
	        	carryover = total > 9 ? 1 : 0;
	        	prev = l1;
	        	l1 = l1 -> next;
	        	l2 = l2 -> next;
	        }
	        // The minimum length list has been all added up meaning
	        // if l1 is shorter, then just append the remaining l2
	        // if l2 is shorter, then keep l1
	        if(l1 == NULL && l2 != NULL) {
	            l1 = prev;
	            l1 -> next = l2;
	            l1 = l1 -> next;
	        }

	        // Using the carryover, just distribute it over the remaining elements
	        while(l1 != NULL) {
	        	l1Val = l1 -> val;
	        	total = l1Val + carryover;
	        	l1 -> val = total % 10;
	        	carryover = total > 9 ? 1 : 0;
	        	prev = l1;
	        	l1 = l1 -> next;
	        }

	        // End of both lists, if there is still a carryover than create a new node
	        if(carryover == 1) {
	            ListNode* lastNode = new ListNode(1);
	            prev -> next = lastNode;
	        }
	        return head;
	    }
};

int main() {
	return 0;
}


