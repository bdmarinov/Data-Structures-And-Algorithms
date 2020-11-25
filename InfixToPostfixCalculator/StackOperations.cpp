// Stackexercisesupr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
#include <string>
#include <cstring>

using namespace std;

int pow(int base, int exp)
{
	if (exp == 0) {
		return 1;
	}
	if (exp == 1) {
		return base;
	}
	return base * pow(base, exp - 1);
}

int getLongestNumber(const string & expression)
{
	stack<char> buffer;

	int i = 0;
	while (expression[i]) {
		if (expression[i] >= 48 && expression[i] <= 57) {
			buffer.push(expression[i]);
		}
		i++;
	}

	int number = 0;
	while (!buffer.empty()) {
		int helper = '0';
		int adder = buffer.top() - helper;
		number += adder*pow(10, buffer.size() - 1);
		buffer.pop();
	}
	
	return number;
}

void sortStacks(stack<int> & one, stack<int> & two)
{
	stack<int> sorted;

	while (!one.empty() && !two.empty()) {
		if (one.top() <= two.top()) {
			sorted.push(one.top());
			one.pop();
		}
		else {
			sorted.push(two.top());
			two.pop();
		}
	}
	while (!one.empty()) {
		sorted.push(one.top());
		one.pop();
	}
	while (!two.empty()) {
		sorted.push(two.top());
		two.pop();
	}

	while (!sorted.empty()) {
		cout << sorted.top() << " ";
		sorted.pop();
	}
	cout << "\n";
	//return sorted;
}

bool checkCorrect(const string & expression)
{
	stack<char> buffer;
	
	int i = 0;
	while (expression[i]) {
		if (expression[i] == '(') {
			buffer.push(expression[i]);
		}
		else if (expression[i] == ')') {
			if (buffer.empty()) {
				return false;
			}
			buffer.pop();
		}
		i++;
	}
	return buffer.empty();
}

int s(int value)
{
	if (value == 9) {
		return 0;
	}
	return value + 1;
}

int p(int value)
{
	if (value == 0) {
		return 9;
	}
	return value - 1;
}
int getValue(const string & expression)
{
	stack<int> numbers;
	stack<char> letters;

	int a = '0', i = 0;
	while (expression[i]) {
		if (expression[i] == 's' || expression[i] == 'p') {
			letters.push(expression[i]);
		}
		else if (expression[i] >= 48 && expression[i] <= 57) {
			numbers.push(expression[i]-a);
		}
		i++;
	}
	
	while (!letters.empty()) {
		if (letters.top() == 's') {
			int value = s(numbers.top());
			numbers.pop();
			letters.pop();
			numbers.push(value);
		}
		else if(letters.top() == 'p') {
			int value = p(numbers.top());
			numbers.pop();
			letters.pop();
			numbers.push(value);
		}
	}
	return numbers.top();
}

int calculate(char symbol, int a, int b)
{
	switch (symbol) {
	case '+': return a + b;
		break;
	case '-': return b - a;
		break;
	case '*': return a * b;
		break;
	case '/': return b / a;
		break;
	}
}

int calculatePolski(const string & expression)
{
	stack<int> value;
	int a = '0', i = 0;

	while (expression[i]) {
		if (expression[i] >= 48 && expression[i] <= 57) {
			value.push(expression[i] - a);
		}
		else {
			if (value.size() >= 2) {
				int number1 = value.top();
				value.pop();
				int number2 = value.top();
				value.pop();
				value.push(calculate(expression[i], number1, number2));
			}
		}
		i++;
	}
	return value.top();
}

int calculatePolskiWithNegatives(const string & expression)
{
	stack<int> values, helper;
	stack<char> negatives;

	int a = '0', i = 0;

	while (expression[i]) {
		if (expression[i] == '-' && (expression[i + 1] >= 48 && expression[i + 1] <= 57)) {
			negatives.push(expression[i]);
		}

		if (expression[i] >= 48 && expression[i] <= 57) {
			helper.push(expression[i] - a);
		}

		if (expression[i] == ' ' && !helper.empty()) {
			int value = 0;
			while (!helper.empty()) {
				value += helper.top()*pow(10, helper.size() - 1);
				helper.pop();
			}
			values.push(value);
		}
		if (expression[i] == '+' || expression[i] == '/' || expression[i] == '*' || expression[i] == '%' || (expression[i] == '-' && (expression[i] == ' ' || expression[i + 1] == '\0'))) {
			int number1 = values.top();
			values.pop();
			if (!negatives.empty()) {
				number1 = -number1;
				negatives.pop();
			}
			int number2 = values.top();
			values.pop();
			if (!negatives.empty()) {
				number2 = -number2;
				negatives.pop();
			}
			values.push(calculate(expression[i], number1, number2));
		}
		i++;
	}
	return values.top();
}

int precedence(char symbol)
{
	switch (symbol) {
	case '+': return 0;
		break;
	case '-': return 0;
		break;
	case '*': return 1;
		break;
	case '/': return 1;
		break;
	case '^': return 2;
		break;
	}
	return -1;
}

bool isOperand(char symbol)
{
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')||(symbol >= 48 && symbol <= 57)) {
		return true;
	}
	return false;
}

bool isOperator(char symbol)
{
	if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
		return true;
	}
	return false;
}

void infixToPostfix(const string & expression)
{
	stack<char> operators;
	int i = 0;

	while (expression[i]) {
		if (isOperand(expression[i])) {
			cout << expression[i];
		}
		else if (expression[i] == '(') {
			operators.push(expression[i]);
		}
		else if (expression[i] == ')') {
			while (!operators.empty() && operators.top() != '(') {
				cout << operators.top();
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			}
		}
		else{
				while (!operators.empty() && precedence(expression[i]) <= precedence(operators.top())) {
					cout << operators.top();
					operators.pop();	
			}
				operators.push(expression[i]);
		}
		i++;
	}

	while (!operators.empty()) {
		cout << operators.top();
		operators.pop();
	}
}

char * infixToPostfixConversion(const string & expression)
{
	int i = 0, brackets = 0, j = 0;
	string temp = expression;
	while (temp[i]){
		if (temp[i] == '(' || temp[i] == ')') {
			brackets++;
		}
		i++;
	}
	int length = temp.length() - brackets + 1;
	cout << length << "\n";
	char * newExpression = new char[length];
	stack<char> operators;
	i = 0;

	while (expression[i]) {
		if (isOperand(expression[i])) {
			newExpression[j] = expression[i];
			j++;
		}
		else if (expression[i] == '(') {
			operators.push(expression[i]);
		}
		else if (expression[i] == ')') {
			while (!operators.empty() && operators.top() != '(') {
				newExpression[j] = operators.top();
				j++;
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			}
		}
		else {
			while (!operators.empty() && precedence(expression[i]) <= precedence(operators.top())) {
				newExpression[j] = operators.top();
				j++;
				operators.pop();
			}
			operators.push(expression[i]);
		}
		i++;
	}

	while (!operators.empty()) {
		newExpression[j] = operators.top();
		j++;
		operators.pop();
	}
	newExpression[j] = '\0';
	return newExpression;
}


int main()
{
	cout << 6*pow(10, 3) << "\n";
	cout << int('0') << "\n";
	cout << getLongestNumber("yhr5mk98kf046ej") << "\n";

	stack<int> one,two;
	one.push(15);
	one.push(13);
	one.push(9);
	one.push(4);
	one.push(2);

	two.push(16);
	two.push(12);
	two.push(11);
	two.push(5);
	two.push(3);

	sortStacks(one, two);
	//cout << sorted.top() << "\n";
	cout << checkCorrect("((()(()))))") << "\n"; //((()(())))
	cout << getValue("s(s(p(s(9)))") << "\n";
	cout << calculatePolski("23+5*5/") << "\n";
	cout << calculatePolskiWithNegatives("5 -5 +") << "\n";

	infixToPostfix("a+b*(c^d-e)^(f+g*h)-i");
	cout << "\n";

	char * expression = infixToPostfixConversion("(2+3)*5/5");
	cout << "\n";
	cout << expression << "\n";
	//cout << calculatePolskiWithNegatives(expression) << "\n";


    return 0;
}

