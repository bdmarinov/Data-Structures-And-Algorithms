// StackLongestValidSubstring.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;

int getLongestValid(const string & expression)
{
	stack<char> parentheses;
	int counter = 0, i = 0, index = -1;

	while (expression[i]) {
		if (expression[i] == '(') {
			parentheses.push(expression[i]);
		}
		if (expression[i] == ')') {
			if (!parentheses.empty()) {
				parentheses.pop();
				counter += 2;
			}
		}
		i++;
	}
	return counter;
}

int main()
{

	cout << getLongestValid("((()") << "\n";
	cout << getLongestValid(")()())") << "\n";
	cout << getLongestValid("()(()))))") << "\n";
	cout << getLongestValid("((((()()))))()))())))))))") << "\n";
	//i = 13
    return 0;
}

