#include "stdafx.h"
#include "Stack.h"


Stack::Stack()
{
	topNode = nullptr;
}

Stack::Stack(const Stack & other)
{
	topNode = nullptr;
	copyStack(other);
}

Stack & Stack::operator =(const Stack & other)
{
	if (this != &other) {
		eraseStack();
		copyStack(other);
	}
	return *this;
}

void Stack::copyStack(const Stack & other)
{
	node * p = other.topNode;
	Stack helper;

	while (p != nullptr) {
		helper.push(p->data);
		p = p->next;
	}
	while (!helper.empty()) {
		int temp = helper.top();
		push(temp);
		helper.pop();
	}
}

void Stack::eraseStack()
{
	while (!empty()) {
		pop();
	}
}

bool Stack::empty() const
{
	return topNode == nullptr;
}

void Stack::push(int & value)
{
	node * p = new node;
	p->data = value;
	p->next = topNode;

	topNode = p;
}

void Stack::pop()
{
	if (empty()) {
		return;
	}
	node * p = topNode;
	topNode = topNode->next;
	delete p;
}

int Stack::top() const
{
	return topNode->data;
}

void Stack::print()
{
	while (!empty()) {
		cout << top() << " ";
		pop();
	}
	cout << "\n";
}

Stack::~Stack()
{
	eraseStack();
}
