/*
707. Design Linked List
Design your implementation of the linked list. You can choose to use the singly 
linked list or the doubly linked list. A node in a singly linked list should 
have two attributes: val and next. val is the value of the current node, and 
next is a pointer/reference to the next node. If you want to use the doubly 
linked list, you will need one more attribute prev to indicate the previous node 
in the linked list. Assume all nodes in the linked list are 0-indexed. 

Implement these functions in your linked list class:


    get(index) : Get the value of the index-th node in the linked list. If the 
index is invalid, return -1. 
    addAtHead(val) : Add a node of value val before the first element of the linked 
list. After the insertion, the new node will be the first node of the linked 
list. 
    addAtTail(val) : Append a node of value val to the last element of the linked 
list. 
    addAtIndex(index, val) : Add a node of value val before the index-th node in 
the linked list. If index equals to the length of linked list, the node will be 
appended to the end of linked list. If index is greater than the length, the 
node will not be inserted. 
    deleteAtIndex(index) : Delete the index-th node in the linked list, if the 
index is valid. 


Example:

MyLinkedList linkedList = new MyLinkedList();
linkedList.addAtHead(1);
linkedList.addAtTail(3);
linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
linkedList.get(1);            // returns 2
linkedList.deleteAtIndex(1);  // now the linked list is 1->3
linkedList.get(1);            // returns 3


Note:


    All values will be in the range of [1, 1000].
    The number of operations will be in the range of [1, 1000].
    Please do not use the built-in LinkedList library.
/*
    Submission Date: 2018-07-15
    Runtime: 24 ms
    Difficulty: EASY
*/
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int _val): val(_val), next(NULL) {}
};

class MyLinkedList {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    int size = 0;
public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        
    }
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    /* o(n) */
    
    ListNode* getNode(int index) {
        if(index >= size) return NULL;
        
        ListNode* curr = head;
        for(int i = 0; i < index && curr; i++) {
            curr = curr->next;
        }
        return curr;
    }
    
    int get(int index) {
        ListNode* curr = getNode(index);
        return curr ? curr->val : -1;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    /* o(1) */
    void addAtHead(int val) {
        ListNode* add = new ListNode(val);
        add->next = head;
        head = add;
        if(tail == NULL) tail = head;
        size++;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    /* o(1) */
    void addAtTail(int val) {
        ListNode* add = new ListNode(val);
        if(tail == NULL) {
            head = add;
        } else {
            tail->next = add;
        }
        tail = add;
        size++;
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    /* o(n) */
    void addAtIndex(int index, int val) {
        if(index > size) return;
        if(index == 0) {
            addAtHead(val);
        } else if(index == size) {
            addAtTail(val);
        } else { // index [1, size-1]
            ListNode* curr = getNode(index-1);
            ListNode* next = curr->next;
            curr->next = new ListNode(val);
            curr->next->next = next;
            size++;
        }
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    /* o(n) */
    void deleteAtIndex(int index) {
        if(index >= size) return;
        if(index == 0) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        } else { // index [1, size-1]
            ListNode* curr = getNode(index-1);
            ListNode* temp = curr->next;
            if(temp == tail) {
                tail = curr;
            }
            curr->next = temp->next;
            delete temp;
        }
        
        size--;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList obj = new MyLinkedList();
 * int param_1 = obj.get(index);
 * obj.addAtHead(val);
 * obj.addAtTail(val);
 * obj.addAtIndex(index,val);
 * obj.deleteAtIndex(index);
 */

int main() {
    return 0;
}
