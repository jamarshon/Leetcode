using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

template <typename U>
struct ListNode {
	U val;
	ListNode* next;
	ListNode(U x): val(x), next(NULL){}
};

template <typename U>
class LinkedListUtil {
	public:
		void printList(ListNode<U>* node) {
			ListNode<U>* current = node;
			while(current != NULL) {
				cout << current -> val << " ";
				current = current -> next;
			}
			cout << endl;
		}

		ListNode<U>* vec2Node(vector<U> vec) {
			int len = vec.size();
			if(len == 0){ return NULL; }
			ListNode<U>* head = new ListNode<U>(vec[0]);
			ListNode<U>* current = head;
			for(int i = 1; i < len; i++) {
				current -> next = new ListNode<U>(vec[i]);
				current = current ->next;
			}
			
			return head;
		}

		vector<ListNode<U>*> convertToVecOfListNodes(vector<vector<U>> vec) {
			vector<ListNode<U>*> ret(vec.size());
			transform(vec.begin(), vec.end(), ret.begin(),
				[this](vector<U> currentVec){ 
					return vec2Node(currentVec); 
				});

			return ret;
		}

};