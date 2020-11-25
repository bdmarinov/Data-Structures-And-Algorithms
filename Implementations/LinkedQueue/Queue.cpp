#include "stdafx.h"
#include "Queue.h"


Queue::Queue()
{
	front = nullptr;
	back = nullptr;
}

Queue::Queue(const Queue & other)
{
	front = nullptr;
	back = nullptr;
	copyQueue(other);
}

Queue & Queue::operator =(const Queue & other)
{
	if (this != &other) {
		eraseQueue();
		copyQueue(other);
	}
	return *this;
}

void Queue::copyQueue(const Queue & other)
{
	node * p = other.front;
	while (p) {
		push(p->data);
		p = p->next;
	}
}

bool Queue::empty() const
{
	return front == nullptr;
}

void Queue::eraseQueue()
{
	while (!empty()) {
		pop();
	}
}

void Queue::print()
{
	node * p = front;
	while (p) {
		cout << p->data;
		p = p->next;
	}
}

void Queue::push(int value)
{
	node * p = new node;
	p->data = value;
	p->next = nullptr;
	back = p;

	if (empty()) {
		front = p;
	}
	else {
		back->next = p;
	}
}

void Queue::pop()
{
	if (empty()){
		return;
	}
	if (front == back) {
		front = back = nullptr;
	}
	else {
		front = front->next;
	}
	delete front;

}

int Queue::head() const
{
	return front->data;
}

Queue::~Queue()
{
	eraseQueue();
}
