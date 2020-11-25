// stack2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>

using namespace std;

int f(int x)
{
	return (x*x) % 10;
}

int l(int x) {
	if (x == 0 || x == 1) {
		return 1;
	}
	return x * l(x - 1);
}

int m(int x, int y) {
	if (x < y) {
		return x;
	}
	return y;
}

int s(int x)
{
	if (x == 9) {
		return 0;
	}
	else
		return x + 1;
}

int p(int x)
{
	if (x == 0) {
		return 9;
	}
	else
		return x - 1;
}

int valueOfString1(string str)
{
	stack<int> st1;
	stack<char> st2;
	int i = 0;
	char a = '0';
	while (str[i]) {
		if (str[i] >= 48 && str[i] <= 57) {
			int number = str[i] - a;
			st1.push(number);
		}
		if (str[i] == 'p' || str[i] == 's') {
			st2.push(str[i]);
		}
		i++;
	}
	
	while (st2.empty() == false) {
		if (st2.top() == 's') {
			int number = s(st1.top());
			st1.pop();
			st1.push(number);
			st2.pop();
		}
		else if (st2.top() == 'p') {
			int number = p(st1.top());
			st1.pop();
			st1.push(number);
			st2.pop();
		}
	}
	return st1.top();
}

int valueOfString2(string str)
{
	stack<int> st1;
	stack<char> st2;
	int i = 0;
	char a = '0';

	while (str[i]) {
		if (str[i] >= 48 && str[i] <= 57) {
			st1.push(str[i] - a);
		}
		if (str[i] == 'f' || str[i] == 'l' || str[i] == 'm') {
			st2.push(str[i]);
		}
		i++;
	}

	while (st2.empty() == false) {
		if (st2.top() == 'f') {
			int number = f(st1.top());
			st1.pop();
			st1.push(number);
			st2.pop();
		}
		else if(st2.top() == 'l') {
			int number = l(st1.top());
			st1.pop();
			st1.push(number);
			st2.pop();
		}
		else if (st2.top() == 'm') {
			int number1 = st1.top();
			st1.pop();
			int number2 = st1.top();
			st1.pop();
			int number = m(number1, number2);
			st1.push(number);
			st2.pop();
		}
	}
	return st1.top();
}

int main()
{
	cout << valueOfString1("s(s(p(5)))") << "\n";
	cout << valueOfString2("f(m(6, l(4)))") << "\n";

    return 0;
}

