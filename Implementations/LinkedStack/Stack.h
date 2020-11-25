#pragma once
#include <iostream>

using namespace std;

struct node {
	int data;
	node * next;
};

class Stack
{
public:
	Stack();
	Stack(const Stack &);
	Stack & operator =(const Stack &);

	void eraseStack();
	void copyStack(const Stack &);
	bool empty() const;
	void print();

	void push(int &);
	void pop();
	int top() const;

	~Stack();

private:
	node * topNode;
};

