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
#include <map>
#include <list>
#include <vector>

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

//Find the lowest common ancestor of two given nodes in a given binary tree.
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	int val;
};

int nodeLevel(TreeNode* node) {
	int level = 0;
	while(node) {
		node = node->parent;
		level += 1;
		
	}
	return level;
}

//TreeNode* lowestCommonAncestor(TreeNode* tree, TreeNode* node1, TreeNode* node2) {
//
////	if(node1!=node2 && ) {
////		
////	}
//}

//1) What is LRU. How to Implement it.
//2) Find kth smallest element in an array.
//3) In a file, there are two columns, first column has some word (String) and 2nd column has some value (Double).
//Example :-
//ABC 23.4
//ERF 34.89
//WERT 122.9

// Find kth smallest element in an array.
struct LRU
{
	std::map<std::string, int> list;
	
};

std::list<int> findSmallest(int k, std::vector<int> source)
{
	std::list<int> ret = std::list<int>();
	if(source.size()==0)
		return ret;
	else
		ret.push_back(source[0]);
	for(int i = 1; i < source.size(); i++)
	{
		if(ret.size()<k || source[i]<ret.back())
		{
			for(auto j = ret.begin(); ; j++)
			{
				if(source[i]<*j || j == ret.end())
				{
					ret.insert(j, source[i]);
					if(ret.size()>k)
						ret.pop_back();
					break;
				}

			}
		}
	}
	return ret;
}


void test7() {
	std::vector<int> target = std::vector<int>();
	
	for(int i = 0; i<10; i++)
	{
		int num = random()%100;
		target.push_back(num);
		std::cout<<num<<" ";
	}
	std::cout<<std::endl;
	std::list<int> result = findSmallest(5, target);
	for(auto i = result.begin(); i!= result.end(); i++)
	{
		std::cout<<*i<<" ";
	}
	std::cout<<std::endl;
}

//2) Given a string str. You have to make this string to square string with maximum length. A square string is of the following format:

//str = x + x; where x is any string. Return length of this square string.
//Example
//str = ababa
//Max length square string = 4;
//str = abcd
//Max length square string = 1;

int squareLength(std::string& input)
{
	int windowSize = input.size()/2;
	while(windowSize>1)
	{
		for(int i=0; i+windowSize*2<=input.size(); i++)
		{
			if(input.substr(i, windowSize)==input.substr(i+windowSize, windowSize))
			{
				return windowSize;
			}
		}
		windowSize--;
	}
	return 1;
}
void test8()
{
	std::string input = "dededededede";
	std::cout<< squareLength(input)<<std::endl;
}


//1) Asked about current project. Asked to draw architecture of my project. Then Asked to design a new feature that is currently not there in my project.
//2) Design undo and redo operation in Microsoft Word like text editor.
//3) Design Hit Counter. (Design Hit Counter)

int main(int argc, const char * argv[]) {
	// insert code here...

	test8();
    return 0;
}
