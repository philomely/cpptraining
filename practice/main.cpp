//
//  main.cpp
//  practice
//
//  Created by Aaron Yang on 7/29/16.
//  Copyright © 2016 Aaron Yang. All rights reserved.
//

//Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
//
//If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
//
//You may not alter the values in the nodes, only nodes itself may be changed.
//
//Only constant memory is allowed.
//
//For example,
//Given this linked list: 1->2->3->4->5
//
//For k = 2, you should return: 2->1->4->3->5
//
//For k = 3, you should return: 3->2->1->4->5

#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL){};
};

int count = 0;
struct List {
	ListNode* head=NULL;
	ListNode* tail=NULL;
	void push(int x){
		ListNode* newNode=new ListNode(x);

		if(tail) {
			tail->next = newNode;
			tail = tail->next;
		} else {
			head = tail = newNode;
		}
	}
	void push(ListNode* node) {
		if(tail) {
			tail->next = node;
			tail = tail->next;
		} else {
			head = tail = node;
		}
	}
};
void printList(ListNode* head) {
	ListNode* cur = head;
	do {
		std::cout << cur->val;
		cur=cur->next;
		if(cur)
			std::cout << "->";
		
	} while(cur);
	std::cout << '\n';
}

void test1(){
	List list;
	for(int i = 0; i < 10; ++i)
		list.push(count++);
	printList(list.head);
	
	int k=4;
	ListNode* cur = list.head;
	int curK=k;
	ListNode* loopHead= cur;
	while(cur) {
		//find the first k
		while(curK) {
			curK--;
		}
		if(!curK){
			ListNode* loopEnd=cur;
			loopHead->next=loopEnd->next;
			ListNode* curr=loopHead;
			for(int i=1; i<curK; i++){
				ListNode* t = curr;
				curr = curr->next;
				curr->next = t;
			}
			curK=k;
		}
		cur = cur->next;
	}
	printList(list.head);
}

ListNode* reverseKGroup(ListNode* head, int k) {
	if(!head) return NULL;
	int size = 1;
	ListNode* curr = head;
	while(curr->next) {
		size += 1;
		curr = curr->next;
	}
	if(size<k)
		return head;
	//head->next = NULL;
	int n = size/k;
	ListNode dummy(-1);
	dummy.next = head;
	ListNode* cur=&dummy;
	ListNode* next = cur->next;
	int kk = k;
	ListNode* newHead = NULL;
	ListNode* tail = head;
	int count = 0;
	for (int i=0; i<n; ++i) {
		if(size-count <k-1) {
			tail->next = cur;
			break;

		}
		while(kk--) {
			ListNode* t = next->next;
			next->next = cur;
			cur=next;
			next = t;
			count++;
		}
		if(i == 0) {
			newHead=cur;
			head->next = cur;
			tail = head;
			tail->next = next;
		}
		else {
			ListNode* t=tail->next;
			tail->next = cur;
			tail = t;
			tail->next = next;
		}

		kk=k;
		
	}

	return newHead;
}

ListNode* reverseList(ListNode* head, int k) {
	if(!head) return NULL;
	int size = 0;
	ListNode* curr = head;
	while(curr->next) {
		size += 1;
		curr = curr->next;
	}
	if(size<k)
		return head;
	ListNode* cur=head;
	ListNode* next = cur->next;
	head->next = NULL;
	while(cur && next && --k) {
		ListNode* t = next->next;
		next->next = cur;
		cur=next;
		next = t;
	}
	head->next = next;
	return cur;
}

void test2(){
	//new line
	List list;
	for(int i = 0; i < 9; ++i)
		list.push(count++);
	printList(list.head);
	list.head = reverseKGroup(list.head, 3);
	printList(list.head);
}

//Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
//You should preserve the original relative order of the nodes in each of the two partitions.

ListNode* dolist3(ListNode* head, int x) {
	if(!head)
		return NULL;
	ListNode* smallHead = NULL;
	ListNode* smallCur = NULL;
	ListNode* bigHead = NULL;
	ListNode* bigCur = NULL;
	
	ListNode* cur = head;
	while(cur) {
		if(cur->val < x) {
			if(!smallHead)
				smallHead = smallCur = cur;
			else {
				smallCur->next = cur;
				smallCur = smallCur->next;
			}
		}
		else {
			if(!bigHead)
				bigHead = bigCur = cur;
			else {
				bigCur->next = cur;
				bigCur = bigCur->next;
			}
		}
		cur = cur->next;
	}
	if(smallHead) {
		head = smallHead;
		smallCur->next = bigHead;
	}
	else {
		head = bigHead;
	}
	if(bigCur)
		bigCur->next = NULL;
	return head;
}
void test3() {
	srand (time(NULL));
	List list;
	for(int i = 0; i < 9; ++i)
		list.push(rand()%10);
	printList(list.head);
	list.head = dolist3(list.head, 4);
	printList(list.head);
}

//Reverse a linked list from position m to n. Do it in-place and in one-pass

ListNode* reversePart(ListNode* head, int n) {
	
	ListNode* cur = NULL;
	ListNode* next = head;
	while(n && next) {
		ListNode* t = next->next;
		next->next = cur;
		cur = next;
		next = t;
		n--;
	}
	if(next)
		head->next = next;
	return cur;
}

void test4_1() {
	List list;
	for(int i = 0; i < 9; ++i)
		list.push(count++);
	printList(list.head);
	list.head = reversePart(list.head, 3);
	printList(list.head);
}

ListNode* reversemn(ListNode* head, int m, int n) {
	ListNode* cur = head;
	int count = 1;
	while(cur) {
		if(count >= m - 1 ) {
			cur->next = reversePart(cur->next, n-m+1);
			break;
		}
		count += 1;
		cur = cur->next;
	}
	return head;
}


void test4() {
	List list;
	for(int i = 0; i < 9; ++i)
		list.push(count++);
	printList(list.head);
	list.head = reversemn(list.head, 2, 5);
	printList(list.head);
}

bool hasLoop(ListNode* head) {
	ListNode* cur1 = head;
	ListNode* cur2 = head->next;
	while(cur1 && cur2 && cur2->next) {
		if(cur1==cur2)
			return true;
		cur2 = cur2->next->next;
		cur1 = cur1->next;
	}
	return false;
}

void test6() {
	List list;
	ListNode a(0);
	list.push(&a);
	for(int i = 0; i < 9; ++i)
		list.push(count++);
	ListNode b(0);
	b.next = &a;
	list.push(&b);
	std::cout<<hasLoop(list.head);
}

int main(int argc, const char * argv[]) {
	// insert code here...

	test6();
    return 0;
}
