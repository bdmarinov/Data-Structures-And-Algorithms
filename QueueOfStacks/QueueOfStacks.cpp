// ZadachiNoraFB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <string>
#include <queue>

using namespace std;

void printStack(const stack<int> & st)
{
	stack<int> temp = st;
	while (!temp.empty()) {
		cout << temp.top() << " ";
		temp.pop();
	}
	//cout << "\n";
}

void printQueue(const queue<stack<int>> & q)
{
	queue<stack<int>> temp = q;
	while (!temp.empty()) {
		printStack(temp.front());
		temp.pop();
	}
	cout << "\n";
}

bool checkTopAverage(const queue<stack<int>> & q)
{
	queue<stack<int>> temp = q;
	stack<int> lastStack = temp.back();
	int last = 0, avg = lastStack.size();
	while (!lastStack.empty()) {
		last += lastStack.top();
		lastStack.pop();
	}
	last /= avg;
	int first = temp.front().top();

	if (first != last) {
		return false;
	}

	
	for (int i = 0; i < temp.size() - 1; i++) {
		first = 0;
		last = 0;
		avg = temp.front().size();
		while (!temp.front().empty()) {
			first += temp.front().top();
			temp.front().pop();
		}
		first /= avg;
		temp.pop();
		last = temp.front().top();

		if (first != last) {
			return false;
		}
	}

	return true;
}

int main()
{
	/*queue<stack<int>> q;
	stack<int> s1, s2, s3;

	s1.push(1);
	s1.push(2);
	s1.push(3);

	s2.push(2);
	s2.push(2);
	s2.push(2);

	s3.push(1);
	s3.push(6);
	s3.push(2);
	

	
	cout << "queue printing: \n";
	q.push(s1);
	q.push(s2);
	q.push(s3);

	printQueue(q);
	cout << "\n";
	cout << checkTopAverage(q) << "\n";
	*/

	queue<stack<int>> q;
	stack<int> s1, s2, s3, s4;

	s1.push(7);

	s2.push(1);
	s2.push(4);
	s2.push(5);
	s2.push(-2);
	s2.push(7);

	s3.push(-1);
	s3.push(4);
	s3.push(6);
	s3.push(8);
	s3.push(3);

	s4.push(4);
	s4.push(10);

	q.push(s1);
	q.push(s2);
	q.push(s3);
	q.push(s4);

	cout << checkTopAverage(q) << "\n";

    return 0;
}

