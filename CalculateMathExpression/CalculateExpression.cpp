// calculateExpression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>

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

int precedence(char symbol)
{
	switch (symbol) {
	case '+':return 0;
	
	case '-': return 0;

	case '*': return 1;

	case '/': return 1;

	case '^': return 2;
	}
}

bool isNumber(char symbol)
{
	if (symbol >= 48 && symbol <= 57) {
		return true;
	}
	return false;
}

int calculate(char symbol, int a, int b)
{
	switch (symbol) {
	case '+': return a + b;
	case '-': return b - a;
	case '*': return a * b;
	case '/': return b / a;
	case '^': return pow(b, a);
	}
}

bool isOperator(char symbol)
{
	if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
		return true;
	}
	return false;
}

int evaluateExpression(const string & expression)
{
	stack<int> values;
	stack<int> numbers;
	stack<char> operators;
	int a = '0', i = 0;
	
	while (expression[i]) {
		if (isNumber(expression[i])) {
			values.push(expression[i] - a);
		}
		if ((expression[i] == ' ' || expression[i + 1] == '\0') && !values.empty()) {
			int value = 0, power = 0;
			while (!values.empty()) {
				value += values.top() * pow(10, power);
				power++;
				values.pop();
			}
			numbers.push(value);
			cout << "numbers top: " << numbers.top() << "\n";
		}
		if (expression[i] == '(') {
			operators.push(expression[i]);
		}
		if (expression[i] == ')') {
			while (!operators.empty() && operators.top() != '(') {
				int number1 = numbers.top();
				numbers.pop();

				int number2 = numbers.top();
				numbers.pop();

				numbers.push(calculate(operators.top(), number1, number2));
				operators.pop();
			}
			operators.pop();
		}
		if(isOperator(expression[i])) {
			while (!operators.empty() && (precedence(expression[i]) <= precedence(operators.top()))) {
				int number1 = numbers.top();
				numbers.pop();
				cout << "number1: " << number1 << "\n";

				int number2 = numbers.top();
				numbers.pop();
				cout << "number2: " << number1 << "\n";

				numbers.push(calculate(operators.top(), number1, number2));
				operators.pop();
			}
			operators.push(expression[i]);
		}
		i++;
	}

	while (!operators.empty()) {
		int number1 = numbers.top();
		numbers.pop();

		int number2 = numbers.top();
		numbers.pop();

		numbers.push(calculate(operators.top(), number1, number2));
		operators.pop();
	}

	return numbers.top();
}

int main()
{
	cout << evaluateExpression("10 + 2 * 6") << "\n";
	cout << evaluateExpression("100 * 2 + 12") << "\n";
	cout << evaluateExpression("100 * (2 + 12)") << "\n";
	//cout << evaluateExpression("100 * ( 2 + 12 ) / 14") << "\n";

    return 0;
}

