// linkedstack1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
	Stack st;
	for (int i = 0; i < 16; i++) {
		int p = i + 1;
		st.push(p);
	}
	st.pop();
	cout << st.top() << "\n";
	Stack st1 = st;
	st1.print();
    return 0;
}

