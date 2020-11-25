#pragma once
#include <iostream>

using namespace std;

struct node {

	int data;
	node * next;
};

class Queue
{
public:
	Queue();
	Queue(const Queue &);
	Queue & operator =(const Queue &);

	bool empty() const;

	void copyQueue(const Queue &);
	void eraseQueue();
	void print();

	void push(int);
	void pop();
	int head() const;

	~Queue();

private:
	node * front;
	node * back;

};

